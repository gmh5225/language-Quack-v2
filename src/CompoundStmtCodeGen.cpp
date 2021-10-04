//
// Created by Parsa Bagheri on 3/24/21.
//

#include "CompoundStmtCodeGen.hpp"
#include "CompoundStmtChecker.hpp"
#include "Type.hpp"
#include "TypeChecker.hpp"
#include "Utils.hpp"

#include "llvm/Transforms/Utils/BasicBlockUtils.h"

namespace quack::codegen {

CompoundStmtCodeGen::CompoundStmtCodeGen(const TranslationUnit &root,
                                         CodeGenerator *codeGen,
                                         ScopeStack &allocaStack,
                                         EnvironmentStack &envStack,
                                         llvm::IRBuilder<> &builder,
                                         llvm::BasicBlock *basicBlock)
    : ASTVisitor<CompoundStmtCodeGen>(root), _context(basicBlock->getContext()),
      _builder(builder), _parentFunction(basicBlock->getParent()),
      _codeGen(codeGen), _envStack(envStack), _bbName(basicBlock->getName()),
      _basicBlock(basicBlock), _scopeStack(allocaStack),
      _module(*basicBlock->getModule()), tdb(TypeDataBase::getTypeDB()) {
  _typeChecker = std::make_unique<semant::TypeChecker>(root, _envStack);
}

bool CompoundStmtCodeGen::traverseCompoundStmt(
    const CompoundStmt &compoundStmt) const {
  for (const auto &stmt : compoundStmt) {
    if (!traverseStatement(stmt))
      return false;

    if (stmt.getKind() == Statement::Kind::Return)
      break;
  }

  return true;
}

bool CompoundStmtCodeGen::declareVar(const std::string &symbol,
                                     Type *symbolType) const {
  if (isInScopeStack(_scopeStack, symbol)) {
    /// is already declared
    return true;
  }

  auto &locals = _scopeStack.back();
  llvm::Type *type = symbolType->getLLVMType();
  llvm::AllocaInst *allocaInst = _builder.CreateAlloca(
      llvm::PointerType::getUnqual(type), nullptr, symbol);
  setCurValue(allocaInst);
  locals.insert({symbol, allocaInst});
  return _curValue != nullptr;
}

bool CompoundStmtCodeGen::traverseMemberAccess(
    const MemberAccess &memberAccess) const {
  //  auto *type = tdb->getType()
  return false;
}

bool CompoundStmtCodeGen::traverseAssignment(
    const Assignment &assignment) const {
  llvm::Value *rvalue;
  llvm::Value *lvalue;
  Type *lhsType, *rhsType;
  auto &locals = _scopeStack.back();
  auto &lhs = assignment.getLeftHandSide();
  auto &rhs = assignment.getRightHandSide();

  if (_typeChecker->traverseExpression(rhs))
    rhsType = _typeChecker->getCurType();
  else
    return false;

  if (_typeChecker->traverseExpression(lhs))
    lhsType = _typeChecker->getCurType();

    /// FIXME
  if (auto *memberAccess = dynamic_cast<const MemberAccess *>(&lhs)) {
    if (getVariableAllocation(_scopeStack, "this", &lvalue)) {
      Type *thisType;
      if (!getVariableType(_envStack, "this", &thisType))
        return false;
      auto *addr = thisType->getMemberAddr(
          _builder, memberAccess->getMember().getName(), lvalue);
      lvalue = addr;
    }
  } else {
    const std::string &lhsSymbol = lhs.getSymbol();

    Scope &localAlloca = _scopeStack.back();

    if (!isInScopeStack(_scopeStack, lhsSymbol)) {
      if (lhsType != nullptr) {
        if (!this->declareVar(lhsSymbol, lhsType))
          return false;
      } else {
        if (!this->declareVar(lhsSymbol, rhsType))
          return false;
      }
    } else {
      if (!this->traverseLValue(lhs)) {
        return false;
      }
    }
    if (!getVariableAllocation(_scopeStack, lhsSymbol, &lvalue))
      return false;
  }

  if (this->traverseExpression(rhs)) {
    rvalue = getCurVal();

    // rvalue is a pointer, needs to be stored
    auto *loadedRval = _builder.CreateLoad(rvalue);

    /* Primitives are no longer supported
    /// Creating implicit casts from Int type aka i64 to Float type aka double
    if (lhsType == _codeGen->getTypes().at("Float") &&
        *rhsType == _codeGen->getTypes().at("Int")) {
      rvalue =
          _builder.CreateSIToFP(rvalue, llvm::Type::getDoubleTy(_context));

    } else if (*lhsType == _codeGen->getTypes().at("Int") &&
               *rhsType == _codeGen->getTypes().at("Float")) {
      rvalue =
          _builder.CreateFPToSI(rvalue, llvm::Type::getInt64Ty(_context));
    }*/
    _builder.CreateStore(loadedRval, lvalue, /*isVolatile*/ false);
    setCurValue(lvalue);
    return true;
  }

  return false;
}

bool CompoundStmtCodeGen::traverseVarDecl(const VarDecl &varDecl) const {
  auto *varType = tdb->getType(varDecl.getType().getName());
  auto &name = varDecl.getVar().getName();
  return this->declareVar(name, varType);
}

bool CompoundStmtCodeGen::traverseIntegerLiteral(
    const IntegerLiteral &integer) const {

  long number = integer.getInteger();

  auto *fn = _module.getFunction("newInteger");
  if (!fn) {
    logError("runtime error, function < newString > not found");
    return false;
  }

  auto *intType = tdb->getType("Integer");
  if (!intType)
    return false;

  llvm::FunctionCallee fnCallee(fn);
  auto *pointer = _builder.CreateAlloca(
      llvm::PointerType::getUnqual(intType->getLLVMType()));
  auto *theInt =
      llvm::ConstantInt::get(_context, llvm::APInt(64, number, true));
  auto *value = _builder.CreateCall(fnCallee, {theInt});
  if (_builder.CreateStore(value, pointer)) {
    setCurValue(pointer);
    return true;
  }

  return false;
}

bool CompoundStmtCodeGen::traverseFloatLiteral(
    const FloatLiteral &floating) const {
  double number = floating.getFloat();

  auto *fn = _module.getFunction("newFloat");
  if (!fn) {
    logError("runtime error, function < newString > not found");
    return false;
  }

  llvm::FunctionCallee fnCallee(fn);
  auto theFloat = llvm::ConstantFP::get(_context, llvm::APFloat(number));
  setCurValue(_builder.CreateCall(fnCallee, {theFloat}));
  return _curValue != nullptr;
}

bool CompoundStmtCodeGen::traverseBoolLiteral(
    const BoolLiteral &boolLiteral) const {
  if (boolLiteral.getBool()) {
    setCurValue(llvm::ConstantFP::get(_context, llvm::APFloat(1.0)));
  } else {
    setCurValue(llvm::ConstantFP::get(_context, llvm::APFloat(0.0)));
  }
  return _curValue != nullptr;
}

bool CompoundStmtCodeGen::traverseStringLiteral(
    const StringLiteral &stringLiteral) const {
  const auto &str = stringLiteral.getText();

  auto *fn = _module.getFunction("newString");
  if (!fn) {
    logError("runtime error, function < newString > not found");
    return false;
  }

  llvm::FunctionCallee fnCallee(fn);
  auto *strType = tdb->getType("String");
  if (!strType)
    return false;

  auto *pointer = _builder.CreateAlloca(
      llvm::PointerType::getUnqual(strType->getLLVMType()));
  auto *globalString =
      _builder.CreateGlobalString(stringLiteral.getText(), ".str");
  auto *castGlobalString = _builder.CreateBitCast(
      globalString,
      llvm::PointerType::getUnqual(llvm::Type::getInt8Ty(_context)));
  auto *value = _builder.CreateCall(fnCallee, {castGlobalString});
  if (_builder.CreateStore(value, pointer)) {
    setCurValue(pointer);
    return true;
  }

  return false;
}

static auto createDispatch(llvm::IRBuilder<> &builder,
                           BinaryOperator::Operator op, Type *objType,
                           llvm::Value *object) {
  switch (op) {
  case BinaryOperator::Operator::Plus:
    return objType->loadFunction(builder, "add", object);
  case BinaryOperator::Operator::Minus:
    return objType->loadFunction(builder, "sub", object);
  case BinaryOperator::Operator::Times:
    return objType->loadFunction(builder, "mul", object);
  case BinaryOperator::Operator::Divide:
    return objType->loadFunction(builder, "div", object);
  case BinaryOperator::Operator::Less:
    return objType->loadFunction(builder, "lt", object);
  case BinaryOperator::Operator::LessEqual:
    return objType->loadFunction(builder, "lte", object);
  case BinaryOperator::Operator::Greater:
    return objType->loadFunction(builder, "gt", object);
  case BinaryOperator::Operator::GreaterEqual:
    return objType->loadFunction(builder, "gte", object);
  case BinaryOperator::Operator::Modulo:
    return objType->loadFunction(builder, "mod", object);
  case BinaryOperator::Operator::Equals:
    return objType->loadFunction(builder, "equals", object);
  }
}

bool CompoundStmtCodeGen::traverseBinaryOperator(
    const BinaryOperator &binaryOperator) const {

  //  quack::semant::TypeChecker _
  if (!_typeChecker->traverseExpression(binaryOperator.getLHS()))
    return false;

  auto *lhsType = _typeChecker->getCurType();

  if (!_typeChecker->traverseExpression(binaryOperator.getRHS()))
    return false;

  auto *rhsType = _typeChecker->getCurType();

  if (!traverseExpression(binaryOperator.getLHS()))
    return false;

  auto *lhs = _builder.CreateLoad(getCurVal());

  if (!traverseExpression(binaryOperator.getRHS()))
    return false;

  auto *rhs = _builder.CreateLoad(getCurVal());

  /* Primitives are no longer supported
  if (binaryOperator.isCompare()) {
    /// cast the rhs and lhs to float to use FCmp instruction
    if (lhs->getType() == llvm::Type::getInt64Ty(_context)) {
      lhs = _builder.CreateCast(llvm::CastInst::SIToFP, lhs,
                                llvm::Type::getDoubleTy(_context));
    }

    if (rhs->getType() == llvm::Type::getInt64Ty(_context)) {
      rhs = _builder.CreateCast(llvm::CastInst::SIToFP, rhs,
                                llvm::Type::getDoubleTy(_context));
    }
  }*/
  auto [callType, obj] =
      createDispatch(_builder, binaryOperator.getOpCode(), lhsType, lhs);
  if (callType == nullptr || obj == nullptr)
    return false;

  auto *ptr = _builder.CreateAlloca(
      llvm::PointerType::getUnqual(lhsType->getLLVMType()));
  if (auto *val = _builder.CreateCall(callType, obj, {lhs, rhs})) {
    _builder.CreateStore(val, ptr);
    _curValue = ptr;
    return true;
  }

  return false;
}

bool CompoundStmtCodeGen::traverseReturn(const Return &returnStmt) const {
  if (returnStmt.getRetVal()) {
    if (traverseExpression(*(returnStmt.getRetVal())))
      setCurValue(_builder.CreateRet(_curValue));
    else
      return false;
  } else
    setCurValue(_builder.CreateRetVoid());

  return true;
}

bool CompoundStmtCodeGen::traverseLValueIdent(
    const LValueIdent &lValueIdent) const {
  auto &name = lValueIdent.getVar().getName();
  llvm::Value *alloca = nullptr;
  if (getVariableAllocation(_scopeStack, name, &alloca)) {
    setCurValue(_builder.CreateLoad(alloca, name.c_str()));
    return true;
  }

  return false;
}

static void insertBranchInst(llvm::BasicBlock *condBB,
                             llvm::BasicBlock *mergeBB,
                             llvm::IRBuilder<> &builder) {
  if (condBB->getTerminator() != nullptr) {
    switch (condBB->getTerminator()->getOpcode()) {
    case llvm::Instruction::Ret:
    case llvm::Instruction::Br:
      return;
    default:
      break;
    }
  }
  builder.CreateBr(mergeBB);
}

bool CompoundStmtCodeGen::traverseIf(const If &ifStmt) const {

  /// Finding variables that are declared in both if and else environments
  semant::CompoundStmtChecker semantChecker(_root, _envStack, *_typeChecker);
  _envStack.push_back(Environment());
  if (!semantChecker.traverseIf(ifStmt))
    return false;

  const Environment &env = _envStack.front();

  /// Allocating memory for declared variables in this scope
  for (auto &it : env) {
    if (!declareVar(it.first, it.second))
      return false;
  }

  /// Generating code for condition and branching
  if (!traverseExpression(ifStmt.getCond()))
    return false;

  auto *value = getCurVal();

  /// if the conditional is not a compare binop, then check if it's not 0.0
  if (ifStmt.getCond().getKind() != Expression::Kind::BinaryOperator)
    value = _builder.CreateFCmpONE(
        value, llvm::ConstantFP::get(_context, llvm::APFloat(0.0)), "ifcond");

  /// Generating code for if and else blocks
  auto *function = _builder.GetInsertBlock()->getParent();

  llvm::BasicBlock *thenBB =
      llvm::BasicBlock::Create(_context, "then", function);
  llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(_context, "else");
  llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(_context, "ifcont");

  _builder.CreateCondBr(value, thenBB, elseBB);

  _builder.SetInsertPoint(thenBB);

  /// Emit if block
  _scopeStack.push_back(Scope());
  CompoundStmtCodeGen thenCodeGen(_root, _codeGen, _scopeStack, _envStack,
                                  _builder, thenBB);
  if (!thenCodeGen.traverseCompoundStmt(ifStmt.getIfBlock()))
    return false;

  _scopeStack.pop_back();

  setCurValue(thenCodeGen.getCurVal());

  /// Branching to merge block
  thenBB = &(function->getBasicBlockList().back());
  _builder.SetInsertPoint(thenBB); /* get the most recent block */
  insertBranchInst(thenBB, mergeBB, _builder);

  /// Emit else block.
  function->getBasicBlockList().push_back(elseBB);
  _builder.SetInsertPoint(elseBB);

  if (ifStmt.getElseBlock() != nullptr) {
    _scopeStack.push_back(Scope());
    CompoundStmtCodeGen elseCodeGen(_root, _codeGen, _scopeStack, _envStack,
                                    _builder, elseBB);
    if (!elseCodeGen.traverseCompoundStmt(*ifStmt.getElseBlock()))
      return false;

    setCurValue(elseCodeGen.getCurVal());
    _scopeStack.pop_back();
  }

  /// Branching to merge block
  elseBB = &(function->getBasicBlockList().back());
  _builder.SetInsertPoint(elseBB);
  insertBranchInst(elseBB, mergeBB, _builder);

  /// Emit merge block.
  function->getBasicBlockList().push_back(mergeBB);
  _builder.SetInsertPoint(mergeBB);

  return true;
}

bool CompoundStmtCodeGen::traverseWhile(const While &whileStmt) const {

  if (!traverseExpression(whileStmt.getCond()))
    return false;
  auto *value = getCurVal();

  auto *function = _builder.GetInsertBlock()->getParent();

  value = _builder.CreateFCmpONE(
      value, llvm::ConstantFP::get(_context, llvm::APFloat(0.0)), "whilecond");

  llvm::BasicBlock *whileBB =
      llvm::BasicBlock::Create(_context, "do", function);
  llvm::BasicBlock *contBB = llvm::BasicBlock::Create(_context, "cont");

  _builder.CreateCondBr(value, whileBB, contBB);
  _builder.SetInsertPoint(whileBB);

  _scopeStack.push_back(Scope());
  CompoundStmtCodeGen whileCodeGen(_root, _codeGen, _scopeStack, _envStack,
                                   _builder, whileBB);
  if (!whileCodeGen.traverseCompoundStmt(whileStmt.getBlock()))
    return false;
  _scopeStack.pop_back();

  setCurValue(whileCodeGen.getCurVal());

  whileBB = &(function->getBasicBlockList().back());
  _builder.SetInsertPoint(whileBB); /* get the most recent block */
  _builder.CreateCondBr(value, whileBB, contBB);

  function->getBasicBlockList().push_back(contBB);
  _builder.SetInsertPoint(contBB);

  return true;
};

bool CompoundStmtCodeGen::traverseCall(const Call &call) const {
  if (call.isConstructorCall()) {
    auto *type = tdb->getType(call.getCallee()->getName());
    assert(type);

    auto fn = tdb->getConstructor(call.getCallee()->getName());
    assert(fn);

    auto *tmp = _builder.CreateAlloca(llvm::PointerType::getUnqual
                                     (type->getLLVMType()));
    llvm::SmallVector<llvm::Value *>args;
    for (auto &arg: *call.getArgs()) {
      auto res = traverseExpression(arg);
      assert(res);
      args.push_back(_curValue);
    }

    auto *retVal = _builder.CreateCall(fn, args);
    setCurValue(tmp);
    return _builder.CreateStore(retVal, tmp) != nullptr;

  } else {
    auto &caller = *(call.getCaller());

    // loading expression
    traverseExpression(caller);
    auto *object = getCurVal();

    // create dispatch
    _typeChecker->traverseExpression(caller);
    auto *type = _typeChecker->getCurType();
    assert(type);

    auto adjustedName = type->adjustMethodName(call.getCallee()->getName());
    if (adjustedName.empty())
      return false;

    auto [fnType, fn] =
        type->loadFunction(_builder, adjustedName, object);

    assert(fnType && fn);

    llvm::SmallVector<llvm::Value *> args;
    args.push_back(object);
    for (const auto &it : call.getArgs()->getSequence()) {
      if (!this->traverseExpression(*it))
        return false;

      assert(_curValue);
      args.push_back(_curValue);
    }

    setCurValue(_builder.CreateCall(fnType, fn, std::move(args)));

    return _curValue != nullptr;
  }

  return true;
}

} // namespace quack::codegen