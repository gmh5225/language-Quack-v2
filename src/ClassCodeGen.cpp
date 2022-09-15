//
// Created by parsab on 9/8/22.
//

#include "ClassCodeGen.h"

namespace quick::codegen {
bool ClassCodeGen::visitClass(const quick::Class &) { return true; }

bool ClassCodeGen::visitMethods(const quick::Methods &) { return false; }

bool ClassCodeGen::visitMethod(const quick::Method &) { return false; }

bool ClassCodeGen::generateCreateFunction(llvm::Function *createFn,
                                          llvm::Function *initFn,
                                          StructType *type, StructType *vtable,
                                          MethodTable &methodTable) {
  auto &cntx = module.getContext();

  auto *bb = llvm::BasicBlock::Create(cntx, typeName + "_create", createFn);
  builder.SetInsertPoint(bb);

  // Calculate size of type
  auto &dl = module.getDataLayout();
  auto size = dl.getTypeAllocSize(type);

  // Create malloc call
  auto mallocFn =
      getOrCreateFnSym("malloc", module, llvm::Type::getInt8PtrTy(cntx),
                       {llvm::Type::getInt64Ty(cntx)});
  auto memPtr = builder.CreateCall(
      mallocFn, {builder.getInt(APInt(64, size.getFixedSize()))});
  auto thisPtr = builder.CreateBitCast(memPtr, llvm::PointerType::get(type, 0));

  auto vtableArrType = llvm::ArrayType::get(llvm::Type::getInt8PtrTy(cntx),
                                            vtable->getNumElements());
  // Generate global vtable instance and set it as objects vtable
  auto vtableInstName = std::string(typeName) + "Vtable";
  auto globalVtable =
      module.getOrInsertGlobal(vtableInstName, vtableArrType, [&]() {
        std::vector<Constant *> funcs(methodTable.size() + 1);
        llvm::Constant *superVtableInst = module.getOrInsertGlobal(
            std::string(super->getName()) + "Vtable", super->getVtable());
        assert(superVtableInst);
        funcs[0] = superVtableInst;
        for (auto &entry : methodTable) {
          std::string fnName = entry.first();
          fnName.insert(0, entry.second.second.second->getName());
          auto fn =
              module.getOrInsertFunction(fnName, entry.second.second.first);
          if (auto fnGv = dyn_cast<GlobalValue>(fn.getCallee())) {
            funcs[entry.second.first] = fnGv;
          }
        }
        auto constantStruct = ConstantStruct::get(vtable, funcs);
        auto gv =
            new GlobalVariable(module, vtable, true,
                               llvm::GlobalValue::LinkageTypes::InternalLinkage,
                               constantStruct, vtableInstName);
        return gv;
      });

  auto vtablePtr = builder.CreateStructGEP(thisPtr, 0);
  builder.CreateStore(globalVtable, vtablePtr);

  // Create init call
  std::vector<Value *> args;
  args.push_back(thisPtr);
  for (auto &arg : createFn->args()) {
    args.push_back(&arg);
  }
  builder.CreateCall(initFn, args);
  builder.CreateRet(thisPtr);
  return true;
}

bool ClassCodeGen::generateInitFunction(llvm::Function *initFn,
                                        llvm::Function *superInitFn) {
  auto &cntx = module.getContext();
  auto &constructor = theClass.getConstructor();

  auto *bb = llvm::BasicBlock::Create(cntx, typeName + "_init", initFn);
  builder.SetInsertPoint(bb);

  FnCodeGen::Args args;
  for (const auto &param : constructor.getParams()) {
    args.push_back({param->getVar().getName(), nullptr});
  }
  for (size_t i = 0, end = args.size(); i < end; i++) {
    args[i].second = initFn->getArg(i);
  }

  auto irType = tr.get(qType);
  LLVMEnv env;
  auto &scope = env.addNewScope();
  scope.insert({"this", initFn->getArg(0)});
  FnCodeGen constructorCodeGen(builder, module, constructor.getBody(), tr, env,
                               qType, typeName + "_init", irType, args);

  for (auto &stmt : constructor.getBody()) {
    // checking if it's a super type initializer
    if (auto *valStmt = stmt->as_a<ValueStmt>()) {
      if (auto *call = valStmt->getExpr().as_a<Call>()) {
        if (auto *fn = call->getCallee().as_a<LValue>()) {
          auto s = theClass.getSuper();
          if (!s || s->getName() == "Object")
            continue;

          // initializing super members
          std::vector<llvm::Value *> arguments;
          for (auto &arg : call->getArgs()) {
            auto val =
                constructorCodeGen.getExprCodeGen().visitExpression(*arg);
            assert(val);
            arguments.push_back(val);
          }
          builder.CreateCall(superInitFn, arguments);
          continue;
        }
      }
    }

    // otherwise use FnCodeGenerator to generate code
    if (!constructorCodeGen.visitStatement(*stmt))
      return false;
  }
  env.popCurrentScope();
  builder.CreateRetVoid();
  return true;
}

MethodTable ClassCodeGen::generateVTable(IRType *irType, StructType *vtable) {
  std::vector<std::pair<StringRef, FunctionType *>> newMethods(
      qType->getMethods().size());
  MethodTable methodTable = super->getMethodTable();
  for (auto &p : qType->getMethods()) {
    std::string methodName = p.first();
    std::vector<llvm::Type *> formalTypes;
    formalTypes.push_back(irType->getType());
    for (auto &[type, var] : p.second.second->getFormals()) {
      auto fIRType = tr.get(type);
      assert(fIRType);
      formalTypes.push_back(fIRType->getType());
    }
    auto *mRetType = tr.get(p.second.second->getReturnType());
    assert(mRetType);
    auto fnType =
        llvm::FunctionType::get(mRetType->getType(), formalTypes, false);
    if (methodTable.count(methodName)) {
      // override

      auto &m = methodTable[methodName];
      m.second = {fnType, irType};
    } else {
      newMethods[p.second.first] = {methodName, fnType};
    }
  }
  updateMethodTable(irType, methodTable, newMethods, vtable, superVtable);
  return std::move(methodTable);
}

type::Table<Type *> ClassCodeGen::generateMemberTable() {
  type::Table<Type *> memberTable;
  for (auto &member : qType->getMembers()) {
    auto memberType = tr.get(member.second.second);
    assert(memberType);
    memberTable[member.first()] = {member.second.first, memberType->getType()};
  }

  return memberTable;
}

ClassCodeGen::ClassCodeGen(const Class &theClass, llvm::Module &module,
                           llvm::IRBuilder<> &builder, LLVMTypeRegistry &tr)
    : theClass(theClass), module(module), builder(builder), tr(tr),
      tdb(type::QTypeDB::get()), typeName(theClass.getClassIdent().getName())
//        , env(),exprCG(module, builder, tr, env, llvmEnv) {}
{
  qType = tdb.getType(typeName);
  assert(qType);
  if (theClass.getSuper()) {
    auto type = tr.get(theClass.getSuper()->getName());
    assert(type);
    super = dynamic_cast<ComplexType *>(type);
    assert(super);
    superVtable = super->getVtable();
  } else {
    super = dynamic_cast<ComplexType *>(tr.get("Object"));
    assert(super);
    superVtable = tr.getObjectVtable();
  }
}

bool ClassCodeGen::generate() {
  auto &constructor = theClass.getConstructor();
  std::string constructorName = typeName + "_create";
  auto vtable =
      llvm::StructType::create(module.getContext(), typeName + "_vtable");

  // Creating the type
  auto memberTable = generateMemberTable();

  auto ctype = ComplexType::create(tr, module, typeName, super,
                                   std::move(memberTable), {}, vtable);

  auto irType = ctype.get();
  tr.registerType(std::move(ctype));

  // Creating the vtable
  auto methodTable = generateVTable(irType, vtable);
  irType->setMethodTable(std::move(methodTable));
  irType->setVTable(vtable);

  // Creating the create/init functions
  std::vector<llvm::Type *> params;
  for (auto &p : constructor.getParams()) {
    auto irT = tr.get(p->getType().getName());
    assert(irT);
    params.push_back(irT->getType());
  }
  auto createFnType = llvm::FunctionType::get(irType->getType(), params, false);
  auto createFn =
      llvm::Function::Create(createFnType, llvm::GlobalValue::ExternalLinkage,
                             typeName + "_create", module);
  params.insert(params.begin(), irType->getType());

  std::string superName;
  if (theClass.getSuper())
    superName = theClass.getSuper()->getName();
  else
    superName = "Object";

  auto superInitFn =
      getOrCreateFnSym(superName + "_init", module, irType->getType(), params);

  auto &cntx = builder.getContext();
  auto initFnType =
      llvm::FunctionType::get(llvm::Type::getVoidTy(cntx), params, false);
  auto initFn =
      llvm::Function::Create(initFnType, llvm::GlobalValue::ExternalLinkage,
                             typeName + "_init", module);

  initFn->setDSOLocal(true);
  createFn->setDSOLocal(true);

  // Creating the init function
  if (!generateInitFunction(initFn, superInitFn)) {
    return false;
  }

  // Creating the create function
  if (!generateCreateFunction(createFn, initFn, irType->getStructType(), vtable,
                         irType->getMethodTable())) {
    return false;
  }

  return visitClass(theClass);
}

} // namespace quick::codegen