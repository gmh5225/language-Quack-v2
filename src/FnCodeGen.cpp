//
// Created by parsab on 6/12/22.
//

#include "FnCodeGen.hpp"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace quick::codegen {

//static llvm::Value *getNoOp(llvm::Module *module, llvm::LLVMContext &cntx) {
//  auto *ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(cntx), false);
//  static llvm::Value *noop = llvm::Function::Create(
//      ftype, llvm::Function::ExternalLinkage, "llvm.donothing", module);
//  return noop;
//}

Function *getOrCreateFnSym(const std::string &functionName,
                                  llvm::Module &module, llvm::Type *resultType,
                                  llvm::ArrayRef<Type *> params,
                                  bool isVarArgs) {
  Function *func = module.getFunction(functionName);
  if (!func) {
    FunctionType *FuncTy = FunctionType::get(resultType, params, isVarArgs);
    func = Function::Create(FuncTy, GlobalValue::ExternalLinkage, functionName,
                            module);
    func->setCallingConv(CallingConv::C);
  }
  return func;
}

Function *getOrCreateFnSym(const std::string &functionName,
                           llvm::Module &module, FunctionType *FuncTy,
                           bool isVarArgs) {
  Function *func = module.getFunction(functionName);
  if (!func) {
    func = Function::Create(FuncTy, GlobalValue::ExternalLinkage, functionName,
                            module);
    func->setCallingConv(CallingConv::C);
  }
  return func;
}

static inline llvm::Value *visitIntOrFloat(IRBuilder<> &builder,
                                           llvm::Type *type, Value *literal) {
  auto alloca = builder.CreateAlloca(type);
  alloca->setAlignment(MaybeAlign(8));
  auto store = builder.CreateStore(literal, alloca);
  store->setAlignment(MaybeAlign(8));
  auto load = builder.CreateLoad(alloca);
  load->setAlignment(MaybeAlign(8));
  return load;
}

llvm::Value *
ExprCodeGen::visitIntegerLiteral(const ast::IntegerLiteral &integer) {
  return visitIntOrFloat(builder, builder.getInt64Ty(),
                         builder.getInt64(integer.get()));
}

llvm::Value *ExprCodeGen::visitFloatLiteral(const ast::FloatLiteral &floating) {
  return visitIntOrFloat(
      builder, builder.getDoubleTy(),
      ConstantFP::get(llvm::Type::getDoubleTy(llvmCntx), floating.get()));
}

llvm::Value *ExprCodeGen::visitBoolLiteral(const ast::BoolLiteral &boolean) {
  return visitIntOrFloat(builder, builder.getInt64Ty(),
                         builder.getInt64(boolean.get()));
}

std::string interpEscapeSeq(const char *str) {
  std::stringstream ss;
  for (; *str != '\0'; str++) {
    if (*str == '\\') {
      str++;
      if (*str == '\0')
        break;
      char c = *str;
      switch (c) {
      case 'n':
        ss << '\n';
        break;
      case 't':
        ss << '\t';
        break;
      default:
        ss << '\\';
        ss << c;
      }
    } else if (*str != '\"') {
      ss << *str;
    }
  }
  return ss.str();
}

llvm::Value *ExprCodeGen::visitStringLiteral(const ast::StringLiteral &strLit) {
  llvm::Value *str =
      builder.CreateGlobalStringPtr(interpEscapeSeq(strLit.get().c_str()));
  Function *func = module.getFunction("String_create");
  if (!func) {
    logError("Link Error: function <String_create> not found");
    return nullptr;
  }
  return builder.CreateCall(func, {str});
}

llvm::Value *ExprCodeGen::visitNothingLiteral(const ast::NothingLiteral &) {
  Function *func = module.getFunction("Nothing_create");
  if (!func) {
    logError("Link Error: function <Nothing_create> not found");
    return nullptr;
  }
  return builder.CreateCall(func, {});
}

llvm::Value *ExprCodeGen::visitCall(const ast::Call &call) {
  std::vector<Value *> argVals;
  for (auto &arg: call.getArgs()) {
    auto *argVal = visitExpression(*arg);
    assert(argVal);
    argVals.push_back(argVal);
  }
  if (call.getCallee().getKind() == LValue::Kind::Ident) {
    // maybe constructor
    auto *ident = static_cast<const IdentifierExpression *>(&call.getCallee());
    auto *irType = typeRegistery.get(ident->getVarName());
    assert(irType);
    // constructor
    auto *constructor = getOrCreateFnSym(ident->getVarName() + "_create", module, nullptr, false);
    return builder.CreateCall(constructor, argVals);
  } else {
    auto *memAccess = static_cast<const MemberAccess *>(&call.getCallee());
    auto &methodName = call.getCallee().getVarName();
    auto *obj = visitExpression(memAccess->getObject());
    assert(obj);
    auto irType = typeRegistery.get(obj->getType());
    assert(irType);
    std::vector<Value *> args;
    return irType->dispatch(builder, methodName.c_str(), obj, argVals, &module);
  }
}

llvm::Value *ExprCodeGen::visitIdentifierExpression(
    const ast::IdentifierExpression &lvalue) {
  auto val = llvmEnv.lookup(lvalue.getVar().getName());
  assert(val && "value must exist in the environment");
  auto load = builder.CreateLoad(val);
  load->setAlignment(MaybeAlign(8));
  return load;
}

llvm::Value *ExprCodeGen::visitMemberAccess(const ast::MemberAccess &memberAccess) {
  auto obj = visitExpression(memberAccess.getObject());
  assert(obj);

  auto &member = memberAccess.getVarName();
  auto *irType = typeRegistery.get(obj->getType());
  auto complexType = dynamic_cast<ComplexType *>(irType);
  assert(complexType);
  auto memberIdx = complexType->getMembers().lookup(member).first;
  auto ptr = builder.CreateStructGEP(obj, memberIdx);
  return builder.CreateLoad(ptr);
}

llvm::Value *ExprCodeGen::visitUnaryOperator(const ast::UnaryOperator &unOp) {
  Value *val = visitExpression(unOp.getOperand());
  if (!val)
    return nullptr;

  // Getting the corresponding LLVM type for the type
  auto *llvmType = typeRegistery.get(val->getType());
  assert(llvmType);

  auto dispatch = [&](const char *m) {
    return llvmType->dispatch(builder, m, val, {});
  };

  // Creating dispatches (method calls) based on the operator string
  switch (unOp.getOpCode()) {
  case UnaryOperator::Operator::Neg:
    return dispatch(type::op::UnaryOperator[type::op::NEG]);
  case UnaryOperator::Operator::Not:
    return dispatch(type::op::UnaryOperator[type::op::NOT]);
  }

  return nullptr;
}

/// Emits IR for left and right hand side of the expression, then creates
/// appropriate dispatches for the binary operation: primitives will
/// use primitive binary operations like (add, div, sub, ...), and complex
/// types will use dynamic method dispatch
llvm::Value *
ExprCodeGen::visitBinaryOperator(const ast::BinaryOperator &binOp) {
  // Emit IR for left hand side
  Value *lhs = visitExpression(binOp.getLHS());
  if (!lhs)
    return nullptr;

  // Getting the corresponding LLVM type for the type of left hand side
  auto *llvmType = typeRegistery.get(lhs->getType());
  assert(llvmType);

  // Emitting IR for the right hand side
  Value *rhs = visitExpression(binOp.getRHS());
  if (!rhs)
    return nullptr;

  auto dispatch = [&](const char *m) {
    return llvmType->dispatch(builder, m, lhs, {rhs});
  };

  // Creating dispatches (method calls) based on the operator string
  switch (binOp.getOpCode()) {
  case BinaryOperator::Operator::Plus:
    return dispatch(type::op::ArithmeticOperator[type::op::ADD]);
  case BinaryOperator::Operator::Minus:
    return dispatch(type::op::ArithmeticOperator[type::op::SUB]);
  case BinaryOperator::Operator::Times:
    return dispatch(type::op::ArithmeticOperator[type::op::MUL]);
  case BinaryOperator::Operator::Divide:
    return dispatch(type::op::ArithmeticOperator[type::op::DIV]);
  case BinaryOperator::Operator::Modulo:
    return dispatch(type::op::ArithmeticOperator[type::op::MOD]);
  case BinaryOperator::Operator::Less:
    return dispatch(type::op::ComparisonOperator[type::op::LT]);
  case BinaryOperator::Operator::LessEqual:
    return dispatch(type::op::ComparisonOperator[type::op::LE]);
  case BinaryOperator::Operator::Greater:
    return dispatch(type::op::ComparisonOperator[type::op::GT]);
  case BinaryOperator::Operator::GreaterEqual:
    return dispatch(type::op::ComparisonOperator[type::op::GE]);
  case BinaryOperator::Operator::Equals:
    return dispatch(type::op::ComparisonOperator[type::op::EQ]);
  case BinaryOperator::Operator::NotEquals:
    return dispatch(type::op::ComparisonOperator[type::op::NE]);
  }

  assert(false && "shouldn't get to this point");
  return nullptr;
}

/// First builds the environment and creates allocations for variables declared
/// in this environment, then visits every statement
bool FnCodeGen::visitCompoundStmt(const CompoundStmt &compoundStmt) {
  for (auto &stmt : compoundStmt)
    if (!visitStatement(*stmt))
      return false;
  return true;
}

// bool FnCodeGen::visitVarDecl(const VarDecl &varDecl) { return false; }
//
// bool FnCodeGen::visitLValueIdent(const IdentifierExpression &lValue) { return
// false; }

/// Sometimes if statements produce blocks "if.cont" that might be empty, and
/// have no predecessors(if body of if has return stmt).
/// These blocks have to be removed, this helper function does that.
static void removeEmptyBB(IRBuilder<> &builder) {
  auto insertionBB = builder.GetInsertBlock();
  if (insertionBB->empty()) {
    assert(insertionBB->hasNPredecessors(0) && "Can't have predecessors");
    insertionBB->eraseFromParent();
  }
}

/// The IR generated for an If statement has this structure:
/// <incoming block>:
///     %0 = <generates ir for condition>
///     %1 = icmp eq i64 %0, 1
///     br i1 %1, label %if.then, label %if.else
///
/// if.then:
///     ...
///     br label if.cont  ; if terminator is not present in then block
///
/// if.else:
///     ...
///     br label if.cont  ; if terminator is not present in else block
///
/// if.cont: ; will be removed if it is the last block of the function and has
/// no terminator
///     ...
bool FnCodeGen::visitIf(const If &ifStmt) {
  // Creating branching basic blocks
  auto &cntx = builder.getContext();
  auto fn = builder.GetInsertBlock()->getParent();
  llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(cntx, "if.then", fn);
  llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(cntx, "if.cont");
  llvm::BasicBlock *elseBB = mergeBB;
  if (ifStmt.hasElse())
    elseBB = llvm::BasicBlock::Create(cntx, "if.else");

  // Emitting IR for if condition
  auto condExpr = exprCG.visitExpression(ifStmt.getCond());
  auto cmp = condExpr;
  // if condition didn't produce a cmp instruction, make one
  if (!llvm::isa<llvm::CmpInst>(condExpr))
    cmp = builder.CreateICmpEQ(condExpr, builder.getInt64(1));
  builder.CreateCondBr(cmp, thenBB, elseBB);

  /// Emits code for compound stmt, and returns the environment of the generated
  /// block
  auto emitBody = [&](const CompoundStmt &body) -> llvm::Optional<LLVMScope> {
    (void)llvmEnv.addNewScope();
    if (!visitCompoundStmt(body))
      return llvm::None;
    if (!body.hasReturn())
      builder.CreateBr(mergeBB);
    else // Erase potentially empty block
      removeEmptyBB(builder);
    return llvmEnv.popCurrentScope();
  };

  // Emitting IR for if.then body
  builder.SetInsertPoint(thenBB);
  auto optThenEnv = emitBody(ifStmt.getIfBlock());
  if (!optThenEnv)
    return false;
  auto &lastThenBB = fn->getBasicBlockList().back();
  auto &ThenEnv = optThenEnv.getValue();

  // Emitting IR for if.else body
  builder.SetInsertPoint(elseBB);
  if (auto elseBlock = ifStmt.getElseBlock()) {
    fn->getBasicBlockList().push_back(elseBB);

    auto optElseEnv = emitBody(*elseBlock);
    if (!optElseEnv)
      return false;

    auto &ElseEnv = optElseEnv.getValue();
    auto &lastElseBB = fn->getBasicBlockList().back();

    fn->getBasicBlockList().push_back(mergeBB);
    builder.SetInsertPoint(mergeBB);

    /// Merges the variables defined in both paths with a phi node
    auto mergePaths = [&]() {
      for (auto &pair : ThenEnv) {
        auto &var = pair.getFirst();
        if (!ElseEnv.lookup(var))
          continue;

        auto &f = pair.getSecond();
        auto &s = ElseEnv[var];

        type::QType *fType = nullptr, *sType = nullptr;
        if (auto irType = tr.get(f->getType()->getPointerElementType())) {
          fType = tdb.getType(irType->getName());
        }

        if (auto irType = tr.get(s->getType()->getPointerElementType())) {
          sType = tdb.getType(irType->getName());
        }

        assert(sType && fType &&
               "must be resolved and exist in tdb by this point -- bug");

        auto lca = fType->lowestCommonAncestor(sType);
        if (!lca)
          continue;

        auto lcaLLVMType = tr.get(lca)->getType();
        auto lcaPtr = llvm::PointerType::get(lcaLLVMType, 0);

        auto phi = builder.CreatePHI(llvm::PointerType::get(lcaLLVMType, 0), 2);
        auto thenVar = ThenEnv.lookup(var);
        auto elseVar = ElseEnv.lookup(var);
        if (lcaPtr != thenVar->getType()) {
          llvm::IRBuilder<>::InsertPointGuard g(builder);
          builder.SetInsertPoint(&lastThenBB.back());
          thenVar = builder.CreateBitCast(thenVar, lcaPtr);
        }

        if (lcaPtr != elseVar->getType()) {
          llvm::IRBuilder<>::InsertPointGuard g(builder);
          builder.SetInsertPoint(&lastElseBB.back());
          elseVar = builder.CreateBitCast(elseVar, lcaPtr);
        }

        phi->addIncoming(elseVar, &lastElseBB);
        phi->addIncoming(thenVar, &lastThenBB);
        llvmEnv.back().insert({var, phi});
      }
    };

    mergePaths();
    return true;
  }

  fn->getBasicBlockList().push_back(mergeBB);
  builder.SetInsertPoint(mergeBB);
  return true;
}

/// The IR generated for a while loop follows this structure:
/// <incoming-block>:
///     br label %while.pred
///
/// while.pred:
///     %0 = <generates code for condition expression>
///     %1 = icmp eq i64 %0, 1
///     br i1 %1, label while.loop, label %while.cont
///
/// while.loop:
///     ...
///     br label %while.pred  ; this will be generated if there is no terminator
///
/// while.cont:
///     ...
bool FnCodeGen::visitWhile(const While &whileStmt) {
  auto &cntx = builder.getContext();
  auto fn = builder.GetInsertBlock()->getParent();
  llvm::BasicBlock *predBB = llvm::BasicBlock::Create(cntx, "while.pred", fn);
  llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(cntx, "while.loop", fn);
  llvm::BasicBlock *contBB = llvm::BasicBlock::Create(cntx, "while.cont", fn);
  builder.CreateBr(predBB);

  // Emitting code for the predicate block of the while loop
  builder.SetInsertPoint(predBB);
  auto condExpr = exprCG.visitExpression(whileStmt.getCond());
  auto cmp = condExpr;
  // if condition didn't produce a cmp instruction, make one
  if (!llvm::isa<llvm::CmpInst>(condExpr))
    cmp = builder.CreateICmpEQ(condExpr, builder.getInt64(1));
  builder.CreateCondBr(cmp, loopBB, contBB);

  // Emitting code for the body of the while loop
  builder.SetInsertPoint(loopBB);
  // Declaring the variables in a new scope
  (void)llvmEnv.addNewScope();
  if (!visitCompoundStmt(whileStmt.getBlock()))
    return false;
  llvmEnv.popCurrentScope();

  // Creating a branch instruction for loop bodies without terminator
  if (!whileStmt.getBlock().hasReturn())
    builder.CreateBr(predBB);

  // Continue block
  builder.SetInsertPoint(contBB);
  return true;
}

// bool FnCodeGen::visitMemberAccess(const MemberAccess &memberAccess) {
//   return false;
// }

bool FnCodeGen::visitAssignment(const Assignment &assignment) {
  auto *rhsLLVMVal = exprCG.visitExpression(assignment.getRHS());
  if (!rhsLLVMVal)
    return false;

  if (assignment.getLHS().getKind() == LValue::Kind::Ident) {
    auto *llvmType = tr.get(rhsLLVMVal->getType());
    assert(llvmType && "type must have been registered by this point -- bug");
    auto &lvalue =
        static_cast<const IdentifierExpression &>(assignment.getLHS());
    auto &var = lvalue.getVar().getName();
    if (auto *storage = llvmEnv.lookup(var)) {
      llvmType->instantiate(builder, storage, {rhsLLVMVal});
    } else {
      storage = llvmType->alloc(builder);
      assert(storage);
      llvmEnv.back().insert({var, storage});
      llvmType->instantiate(builder, storage, {rhsLLVMVal});
    }
    return true;
  } else {
    auto *memAccess = static_cast<const MemberAccess *>(&assignment.getLHS());
    auto val = exprCG.visitExpression(memAccess->getObject());
    auto *irType = (ComplexType *)tr.get(val->getType());
    assert(irType);
    auto idx = irType->getMembers()[memAccess->getVarName()].first;
    auto ptr = builder.CreateStructGEP(val, idx);
    builder.CreateStore(rhsLLVMVal, ptr);
    return true;
  }
}

bool FnCodeGen::visitStaticAssignment(const StaticAssignment &assignment) {
  auto *rhsLLVMVal = exprCG.visitExpression(assignment.getRHS());
  if (!rhsLLVMVal)
    return false;

  auto &type = assignment.getDecl().getType().getName();
  auto *qtype = tdb.getType(type);
  assert(qtype && "qtype must exist at this point");

  if (!assignment.getDecl().isMemberDecl()) {
    auto &decl = static_cast<const StaticMemberDecl &>(assignment.getDecl());
    auto &var = decl.getObject().getMember().getName();
    auto *llvmType = tr.get(qtype);
    assert(llvmType && "qtype must exist in tr");
    assert(llvmEnv.back().count(var) == 0 && "must have been type checked");
    auto storage = llvmType->alloc(builder);
    assert(storage);
    llvmEnv.back().insert({var, storage});
    assert(storage && "must have been declared in the environment");
    llvmType->instantiate(builder, storage, {rhsLLVMVal});
    return true;
  } else {
    auto &decl = static_cast<const StaticMemberDecl&>(assignment.getDecl());
    auto *thisObj = llvmEnv.lookup("this");
    assert(thisObj);
    thisObj = builder.CreateLoad(thisObj);
    auto *irType = (ComplexType *)tr.get(thisObj->getType());
    assert(irType);
    auto &varName = decl.getObject().getVarName();
    assert(irType->getMembers().count(varName));
    auto varIdx = irType->getMembers()[varName].first;
    auto *addr = builder.CreateStructGEP(thisObj, varIdx);
    builder.CreateStore(rhsLLVMVal, addr);
    return true;
  }
  return false;
}

// bool FnCodeGen::visitCall(const Call &call) { return false; }

bool FnCodeGen::visitValueStmt(const ast::ValueStmt &valueStmt) {
  return exprCG.visitExpression(valueStmt.getExpr());
}

bool FnCodeGen::visitReturn(const ast::Return &returnStmt) {
  llvm::Value *lval;
  if (auto *expr = returnStmt.getRetVal()) {
    lval = exprCG.visitExpression(*expr);
  } else {
    if (isMain()) {
      lval =
          visitIntOrFloat(builder, builder.getInt64Ty(), builder.getInt64(0));
    } else {
      // Nothing type TODO
      lval = nullptr;
    }
  }
  assert(lval);
  builder.CreateRet(lval);
  return true;
}

bool FnCodeGen::visitPrintStatement(const ast::PrintStatement &print) {
  // Creating/Getting a reference to systems printf
  Function *func_printf = getOrCreateFnSym(
      "printf", module, IntegerType::get(module.getContext(), 32), {}, true);

  // Creating the format string, and generating code for expressions
  std::string format;
  llvm::raw_string_ostream ss(format);
  SmallVector<Value *, 4> params;
  for (auto &expr : *print.getArgs()) {
    auto exprVal = exprCG.visitExpression(*expr);
    assert(exprVal);
    auto valType = exprVal->getType();
    if (valType->isIntegerTy()) {
      params.push_back(exprVal);
      ss << "%ld ";
    } else if (valType->isDoubleTy()) {
      params.push_back(exprVal);
      ss << "%g ";
    } else {
      auto t = tr.get(exprVal->getType());
      assert(t && "bug");
      Value *string = exprVal;
      if (t->getName() != "String")
        string = t->dispatch(builder, "__str__", exprVal, {});

      Function *getStringData =
          getOrCreateFnSym("String_getData", module,
                           llvm::Type::getInt8PtrTy(module.getContext()),
                           {string->getType()}, false);
      // getting the data of a string object
      auto str = builder.CreateCall(getStringData, {string});
      params.push_back(str);
      ss << "%s ";
    }
  }
  ss << "\n";
  Value *globalFormatStr = builder.CreateGlobalStringPtr(ss.str());
  params.insert(params.begin(), globalFormatStr);

  // Creating a call to printf
  builder.CreateCall(func_printf, params);
  return true;
}

/// First generates IR for the types defined, then emits IR for the main
/// function
bool FnCodeGen::generate() {
  if (parentType && fnName == MainFn) {
    logError("Cannot generate main function in <" + parentType->getName() +
             "> environment");
    return false;
  }

  // Creating the function
  auto &cntx = builder.getContext();
  auto fnType = llvm::FunctionType::get(builder.getInt64Ty(), {});
  auto fn = llvm::Function::Create(fnType, llvm::GlobalValue::ExternalLinkage,
                                   fnName, module);
  fn->setDSOLocal(true);
  auto *bb = llvm::BasicBlock::Create(cntx, fnName, fn);

  // Emitting IR for body of function
  builder.SetInsertPoint(bb);
  auto &scope = llvmEnv.addNewScope();

  // adding arguments to the environment
  for (auto &arg: args) {
    scope.insert(arg);
  }

  if (!visitCompoundStmt(fnBody))
    return false;
  auto llvmScope = llvmEnv.popCurrentScope();

  // Must create a return stmt if there is none
  if (!fnBody.hasReturn())
    builder.CreateRet(builder.getInt64(0));

  // Removing empty blocks
  removeEmptyBB(builder);
  return true;
}

static llvm::Value *loadVTable(IRBuilder<> &builder, llvm::Value *obj) {
  auto vtable = builder.CreateStructGEP(obj, 0);
  return builder.CreateLoad(vtable);
}

bool FnCodeGen::visitTypeSwitch(const ast::TypeSwitch &typeSwitch) {
  auto val = exprCG.visitExpression(typeSwitch.getValue());
  auto valType = tr.get(val->getType());
  auto vtableType = tr.getObjectVtable();
  auto vtablePtr = PointerType::get(vtableType, 0);
  auto is_subtype = getOrCreateFnSym("is_subtype", module, builder.getInt8Ty(),
                                     {vtablePtr, vtablePtr}, false);
  auto loadedVtable = loadVTable(builder, val);
  Function *fn = builder.GetInsertBlock()->getParent();
  llvm::BasicBlock *mergeBB;

  for (auto &c : typeSwitch.getCases()) {
    auto &caseType = c->getVarDecl().getType().getName();
    auto *caseQType = tdb.getType(caseType);
    auto *caseLLVMType = tr.get(caseQType);
    auto caseVTableType = caseLLVMType->getVtable();
    assert(caseVTableType && "must have a vtable by this point, primitives should "
                         "have been typechecked -- bug");
    auto caseVtableGetter =
        getOrCreateFnSym(caseType + "_get_vtable", module,
                         llvm::PointerType::get(caseVTableType, 0));
    auto caseVTable = builder.CreateCall(caseVtableGetter);
    auto res = builder.CreateCall(is_subtype, {caseVTable, loadedVtable});
    llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(module.getContext(), "typecase.if." + caseType, fn);
    mergeBB = llvm::BasicBlock::Create(module.getContext(), "typecase.not." + caseType);
    builder.CreateCondBr(res, thenBB, mergeBB);
    builder.SetInsertPoint(thenBB);
    auto &localEnv = llvmEnv.addNewScope();
    auto bitCastVal = builder.CreateBitCast(val, caseLLVMType->getType());
    auto alloca = builder.CreateAlloca(caseLLVMType->getType());
    builder.CreateStore(bitCastVal, alloca);
    localEnv.insert({c->getVarDecl().getVar().getName(), alloca});
    if (!visitCompoundStmt(c->getBlock()))
      return false;
    if (!c->getBlock().hasReturn())
      builder.CreateBr(mergeBB);
    else // Erase potentially empty block
      removeEmptyBB(builder);
    llvmEnv.popCurrentScope();

    builder.SetInsertPoint(mergeBB);
    fn->getBasicBlockList().push_back(mergeBB);
  }
  return true;
}

bool FnCodeGen::visitTypeSwitchCase(const ast::TypeSwitchCase &) {
  return false;
}

// bool FnCodeGen::visitUnaryOperator(const ast::UnaryOperator &unOp) {
//   return false;
// }
//
// bool FnCodeGen::visitIntegerLiteral(const ast::IntegerLiteral &) {
//   return false;
// }
//
// bool FnCodeGen::visitFloatLiteral(const ast::FloatLiteral &) { return false;
// }
//
// bool FnCodeGen::visitBoolLiteral(const ast::BoolLiteral &) { return false; }
//
// bool FnCodeGen::visitStringLiteral(const ast::StringLiteral &) { return
// false; }
//
// bool FnCodeGen::visitBinaryOperator(const ast::BinaryOperator &binop_integer)
// {
//   return false;
// }
//
// bool FnCodeGen::visitIdentifier(const ast::Identifier &) { return false; }

} // namespace quick::codegen