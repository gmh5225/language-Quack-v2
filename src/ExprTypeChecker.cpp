//
// Created by parsab on 6/12/22.
//

#include "ExprTypeChecker.hpp"

using namespace llvm;

namespace quick {
namespace sema {

type::QType *ExprTypeChecker::visitIntegerLiteral(const IntegerLiteral &) {
  return tdb.getIntegerType();
}

type::QType *ExprTypeChecker::visitFloatLiteral(const FloatLiteral &) {
  return tdb.getFloatType();
}

type::QType *ExprTypeChecker::visitBoolLiteral(const BoolLiteral &) {
  return tdb.getBoolType();
}

type::QType *ExprTypeChecker::visitStringLiteral(const StringLiteral &) {
  return tdb.getStringType();
}

type::QType *ExprTypeChecker::visitBinaryOperator(const BinaryOperator &binOp) {
  auto *lhsType = visitExpression(binOp.getLHS());
  if (!lhsType)
    return nullptr;

  auto *rhsType = visitExpression(binOp.getRHS());
  if (!rhsType)
    return nullptr;

  auto checkCall = [&](const char *m) -> type::QType * {
    if (const auto *method = lhsType->lookUpMethod(m)) {
      auto &args = method->getActuals();
      if (args.size() != 1) {
        logError(binOp, "expected 1 argument to the binary operator");
        return nullptr;
      }

      auto *argType = args.back().type;
      if (argType != rhsType && !rhsType->isDescendentOf(argType)) {
        logError(binOp, "can't use argument of type <" + argType->getName() +
                            "> where type <" + rhsType->getName() +
                            "> is expected.");
        return nullptr;
      }

      return method->getReturnType();
    } else {
      logError(binOp, std::string("method <") + m +
                          "> is not defined for type <" + lhsType->getName() +
                          ">");
      return nullptr;
    }
  };

  switch (binOp.getOpCode()) {
  case BinaryOperator::Operator::Plus:
    return checkCall(type::op::ArithmeticOperator[type::op::ADD]);
  case BinaryOperator::Operator::Minus:
    return checkCall(type::op::ArithmeticOperator[type::op::SUB]);
  case BinaryOperator::Operator::Times:
    return checkCall(type::op::ArithmeticOperator[type::op::MUL]);
  case BinaryOperator::Operator::Divide:
    return checkCall(type::op::ArithmeticOperator[type::op::DIV]);
  case BinaryOperator::Operator::Modulo:
    return checkCall(type::op::ArithmeticOperator[type::op::MOD]);
  case BinaryOperator::Operator::Less:
    return checkCall(type::op::ComparisonOperator[type::op::LT]);
  case BinaryOperator::Operator::LessEqual:
    return checkCall(type::op::ComparisonOperator[type::op::LE]);
  case BinaryOperator::Operator::Greater:
    return checkCall(type::op::ComparisonOperator[type::op::GT]);
  case BinaryOperator::Operator::GreaterEqual:
    return checkCall(type::op::ComparisonOperator[type::op::GE]);
  case BinaryOperator::Operator::Equals:
    return checkCall(type::op::ComparisonOperator[type::op::EQ]);
  case BinaryOperator::Operator::NotEquals:
    return checkCall(type::op::ComparisonOperator[type::op::NE]);
  }
  assert(false && "shouldn't get to this point");
  return nullptr;
}

type::QType *ExprTypeChecker::visitUnaryOperator(const UnaryOperator &unOp) {
  type::QType *type = visitExpression(unOp.getOperand());
  if (!type)
    return nullptr;

  auto checkUnOp = [&](const char *op) -> type::QType * {
    if (const auto *method = type->lookUpMethod(op)) {
      if (!method->getActuals().empty()) {
        logError(unOp, "Unary operator doesn't take any arguments");
        return nullptr;
      }

      return method->getReturnType();
    }
    logError(unOp,
             "Type '" + type->getName() + "' has no operator '" + op + "'");
    return nullptr;
  };

  switch (unOp.getOpCode()) {
  case UnaryOperator::Operator::Neg:
    return checkUnOp(type::op::UnaryOperator[type::op::NEG]);
  case UnaryOperator::Operator::Not:
    return checkUnOp(type::op::UnaryOperator[type::op::NOT]);
  default:
    return nullptr;
  }
}

type::QType *ExprTypeChecker::visitCall(const Call &) { return nullptr; }

type::QType *ExprTypeChecker::visitMemberAccess(const MemberAccess &) {
  return nullptr;
}

type::QType *ExprTypeChecker::visitIdentifierExpression(const IdentifierExpression &lvalue) {
  if (auto t = env.lookup(lvalue.getVar().getName()))
    return t;
  else {
    logError(lvalue, "IdentifierExpression <" + lvalue.getVar().getName() +
                         "> not declared in current scope");
    return nullptr;
  }
}

} // namespace sema
} // namespace quick