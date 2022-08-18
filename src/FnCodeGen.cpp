//
// Created by parsab on 6/12/22.
//

#include "FnCodeGen.hpp"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace quack::codegen {

static llvm::Value *getNoOp(llvm::Module *module, llvm::LLVMContext &cntx) {
  auto *ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(cntx), false);
  static llvm::Value *noop = llvm::Function::Create(
      ftype, llvm::Function::ExternalLinkage, "llvm.donothing", module);
  return noop;
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
                         builder.getInt64(integer.getInteger()));
}

llvm::Value *ExprCodeGen::visitFloatLiteral(const ast::FloatLiteral &floating) {
  return visitIntOrFloat(
      builder, builder.getDoubleTy(),
      ConstantFP::get(llvm::Type::getDoubleTy(llvmCntx), floating.getFloat()));
}

llvm::Value *ExprCodeGen::visitBoolLiteral(const ast::BoolLiteral &boolean) {
  return visitIntOrFloat(builder, builder.getInt64Ty(),
                         builder.getInt64(boolean.getBool()));
}

llvm::Value *ExprCodeGen::visitStringLiteral(const ast::StringLiteral &) {
  return nullptr;
}

llvm::Value *ExprCodeGen::visitCall(const ast::Call &) { return nullptr; }

llvm::Value *ExprCodeGen::visitLValueIdent(const ast::LValueIdent &lvalue) {
  auto val = llvmEnv.lookup(lvalue.getVar().getName());
  assert(val && "value must exist in the environment");
  auto load = builder.CreateLoad(val);
  load->setAlignment(MaybeAlign(8));
  return load;
}

llvm::Value *ExprCodeGen::visitMemberAccess(const ast::MemberAccess &) {
  return nullptr;
}

llvm::Value *ExprCodeGen::visitUnaryOperator(const ast::UnaryOperator &unOp) {
  Value *val = visitExpression(unOp.getOperand());
  if (!val)
    return nullptr;

  // Getting the corresponding LLVM type for the type
  auto *type = exprTC.visitExpression(unOp.getOperand());
  assert(type);
  auto *llvmType = typeRegistery.get(type);
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
  auto *type = exprTC.visitExpression(binOp.getLHS());
  assert(type);
  auto *llvmType = typeRegistery.get(type);
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
// bool FnCodeGen::visitLValueIdent(const LValueIdent &lValue) { return false; }

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
  // Creating necessary basic blocks
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
    auto mergePaths = [&](){
      for (auto &pair : ThenEnv) {
        auto &var = pair.getFirst();
        if (!ElseEnv.lookup(var))
          continue;

        auto &f = pair.getSecond();
        auto &s = ElseEnv[var];
        if (f->getType() != s->getType())
          continue;

        auto phi = builder.CreatePHI(f->getType(), 2);
        phi->addIncoming(ElseEnv.lookup(var), &lastElseBB);
        phi->addIncoming(ThenEnv.lookup(var), &lastThenBB);
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

  auto *qtype = exprTC.visitExpression(assignment.getRHS());
  assert(qtype && "qtype must exist at this point");

  if (assignment.getLHS().getKind() == LValue::Kind::LValueIdent) {
    auto *llvmType = tr.get(qtype);
    auto &lvalue = static_cast<const LValueIdent &>(assignment.getLHS());
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
    // TODO member access
    return false;
  }
}

bool FnCodeGen::visitStaticAssignment(const StaticAssignment &assignment) {
  auto *rhsLLVMVal = exprCG.visitExpression(assignment.getRHS());
  if (!rhsLLVMVal)
    return false;

  auto &var = assignment.getDecl().getVar().getName();
  auto &type = assignment.getDecl().getType().getName();
  auto *qtype = tdb.getType(type);
  assert(qtype && "qtype must exist at this point");

  if (!assignment.getDecl().isMemberDecl()) {
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
    // TODO
    return false;
  }
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
  (void)llvmEnv.addNewScope();
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

} // namespace quack::codegen