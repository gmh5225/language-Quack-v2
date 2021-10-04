//
// Created by Parsa Bagheri on 7/28/21.
//

#include "ClassesCodeGen.hpp"
#include "ClassesChecker.hpp"

namespace quack::codegen {

bool ClassesCodeGen::traverseClass(const Class &clss) const {
  auto *type = tdb->getType(clss.getClassIdent().getName());
  assert(type);

  std::vector<llvm::Constant *> methods;
  for (auto &method : type->getMethods()) {
    if (method.kind == MethodKind::New || method.kind == MethodKind::Override) {
      if (!tdb->createFunction(type, method)) {
        logError("error generating functions");
        return false;
      }
    }

    if (auto *fnPtr = tdb->getFunctionPointer(method.name))
      methods.push_back(fnPtr);
    else {
      logError("no function with name < " + method.name +
               " > in the type "
               "database");
      return false;
    }
  }

  auto vtableName = type->getName() + "VTTemplate";
  //  auto *initializer =
  //      llvm::ConstantStruct::get(type->getLLVMVTableType(), methods);
  //
  //
  //  // FIXME possible issue here, I am dynamically allocating this on heap and
  //  // not freeing it anywhere
  //  llvm::GlobalVariable *vtTemplate = new llvm::GlobalVariable(
  //      _module, type->getLLVMVTableType(), true,
  //      llvm::GlobalValue::InternalLinkage, initializer, vtableName);

  auto globalVtable = _module.getOrInsertGlobal(
      vtableName, type->getLLVMVTableType(),
      [this, type, &methods, &vtableName]() {
        auto *initializer =
            llvm::ConstantStruct::get(type->getLLVMVTableType(), methods);
        return new llvm::GlobalVariable(
            _module, type->getLLVMVTableType(), true,
            llvm::GlobalValue::LinkageTypes::InternalLinkage, initializer,
            vtableName);
      });

  auto *fn = _codeGen->createFunction(type->getConstructorType(),
                                      "new" + type->getName());
  auto *bb = _codeGen->createBBandSetInsertionPoint(_builder, fn);

  EnvironmentStack envStack;
  _codeGen->_scopeStack.push_back(Scope());
  envStack.push_back(Environment());
  auto &env = envStack.back();
  auto &scope = _codeGen->_scopeStack.back();

  llvm::Type *ITy = llvm::Type::getInt32Ty(_context);
  llvm::Constant *allocaSize =
      llvm::ConstantExpr::getSizeOf(type->getLLVMType());
  allocaSize = llvm::ConstantExpr::getTruncOrBitCast(allocaSize, ITy);
  llvm::Instruction *mallocCall = llvm::CallInst::CreateMalloc(
      bb, ITy, type->getLLVMType(), allocaSize, nullptr, nullptr, "");
  _builder.Insert(mallocCall);
  auto initHeaderFn = tdb->getFunctionPointer("initHeader");
  initHeaderFn->print(llvm::errs());
  assert(initHeaderFn);

  _builder.CreateCall(
      initHeaderFn,
      {_builder.CreateBitCast(mallocCall,
                              llvm::PointerType::getUnqual(
                                  tdb->getType("Object")->getLLVMType())),
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(_context), type->getID())
      });

  //  _builder.CreateStore()
  //  auto *templatePtr = _builder.CreateAddrSpaceCast(globalVtable,
  //                                                   llvm::PointerType::get
  //                                                   (globalVtable->getType(),
  //                                                    0));
  auto *addrOfVtable = _builder.CreateStructGEP(mallocCall, 1);
  _builder.CreateStore(globalVtable, addrOfVtable);

  //  _builder.CreateStore()
  env.insert({"this", type});
  scope.insert({"this", mallocCall});
  CompoundStmtCodeGen codeGen(_root, _codeGen, _codeGen->_scopeStack, envStack,
                              _builder, bb);

  if (!codeGen.traverseCompoundStmt(clss.getConstructor().getBody()))
    return false;

  _builder.CreateRet(mallocCall);
  envStack.pop_back();
  _codeGen->_scopeStack.pop_back();

  auto status = true;
  for (auto &method : clss.getMethods())
    if (!traverseMethod(method, type, mallocCall))
      status = false;

  return status;
}

class CompoundStmtAdjuster : public ASTVisitor<CompoundStmtAdjuster> {

  bool doesCompStmtHaveReturn(const CompoundStmt &compStmt) const {
    for (auto &stmt : compStmt) {
      if (stmt.getKind() == Statement::Kind::Return)
        return true;
    }
    return false;
  }

public:
  CompoundStmtAdjuster(const TranslationUnit &tu)
      : ASTVisitor<CompoundStmtAdjuster>(tu) {}
  bool traverseCompoundStmt(const CompoundStmt &compStmt) const override {
    if (doesCompStmtHaveReturn(compStmt))
      return true;
    for (auto &stmt : compStmt) {
      if (auto *ifStmt = dynamic_cast<If *>(&stmt)) {
        if (ifStmt->getElseBlock()) {
          if (traverseCompoundStmt(ifStmt->getIfBlock()) &&
              traverseCompoundStmt(*ifStmt->getElseBlock()))
            return true;
        }
      }
    }
    return false;
  }
};

bool ClassesCodeGen::traverseMethod(const ast::Method &method,
                                    quack::Type *type,
                                    llvm::Value *allocationInst) const {
  EnvironmentStack envStack;
  envStack.push_back(Environment());
  auto &env = envStack.back();
  env.insert({"this", type});

  _codeGen->_scopeStack.push_back(Scope());
  auto &scope = _codeGen->_scopeStack.back();
  scope.insert({"this", allocationInst});

  quack::semant::TypeChecker typeChecker(_root, envStack);
  semant::CompoundStmtChecker semantChecker(_root, envStack, typeChecker);
  if (!semantChecker.traverseCompoundStmt(method.getBody()))
    return false;

  // add the rest of the arguments to this
  auto adjustedName = type->adjustMethodName(method.getMethodIdent().getName());
  auto *fn = tdb->createFunction(type, adjustedName);
  auto *bb = _codeGen->createBBandSetInsertionPoint(_builder, fn);

  CompoundStmtCodeGen codeGen(_root, _codeGen, _codeGen->_scopeStack, envStack,
                              _builder, bb);
  if (!codeGen.traverseCompoundStmt(method.getBody()))
    return false;

  CompoundStmtAdjuster compStmtAdj(_root);
  if (!compStmtAdj.traverseCompoundStmt(method.getBody())) {
    auto *fn = tdb->getConstructor("Nothing");
    assert(fn);

    _builder.CreateRet(_builder.CreateCall(fn));
  }

  envStack.pop_back();
  _codeGen->_scopeStack.pop_back();

  return true;
}

bool ClassesCodeGen::traverseMethod(const ast::Method &method) const {
  //  auto *type = tdb->getType(clss.getClassIdent().getName());
  //  assert(type);
  //  EnvironmentStack envStack;
  //  envStack.push_back(Environment({"this", type}))
  return true;
}

bool ClassesCodeGen::traverseParameters(const Parameters &) const {
  return true;
}

} // namespace quack::codegen