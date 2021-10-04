//
// Created by Parsa Bagheri on 3/26/21.
//

#include "TypeChecker.hpp"
#include "Utils.hpp"

namespace quack::semant {

bool TypeChecker::traverseIntegerLiteral(const IntegerLiteral &) const {
  setCurType(tdb->getType("Integer"));
  return true;
}

bool TypeChecker::traverseFloatLiteral(const FloatLiteral &) const {
  setCurType(tdb->getType("Float"));
  return true;
}

bool TypeChecker::traverseBoolLiteral(const BoolLiteral &) const {
  setCurType(tdb->getType("Boolean"));
  return true;
}

bool TypeChecker::traverseStringLiteral(const StringLiteral &) const {
  setCurType(tdb->getType("String"));
  return true;
}

bool TypeChecker::traverseBinaryOperator(
    const BinaryOperator &binaryOperator) const {
  Type *left, *right;

  if (traverseExpression(binaryOperator.getLHS())) {
    left = getCurType();

    if (traverseExpression(binaryOperator.getRHS())) {
      right = getCurType();
      if (!left->hasMethod(tdb->lookUpOperator(binaryOperator.getOpCode()))) {
        std::string binop =
            BinaryOperator::getOperators().at(binaryOperator.getOpCode());
        logError(binaryOperator.getLHS(), "binary operator < " + binop +
                                              " > is not defined for "
                                              "object of type < " +
                                              left->getName() + " >");
        return false;
      }

      if (!right->hasMethod(tdb->lookUpOperator(binaryOperator.getOpCode()))) {
        std::string binop =
            BinaryOperator::getOperators().at(binaryOperator.getOpCode());
        logError(binaryOperator.getRHS(), "binary operator < " + binop +
                                              " > is not defined for "
                                              "object of type < " +
                                              left->getName() + " >");
        return false;
      }

      /// Order matters here,
      /// first check if its a comparison
      switch (binaryOperator.getOpCode()) {
      case BinaryOperator::Operator::Equals:
      case BinaryOperator::Operator::Less:
      case BinaryOperator::Operator::LessEqual:
      case BinaryOperator::Operator::Greater:
      case BinaryOperator::Operator::GreaterEqual:
        setCurType(tdb->getType("Bool"));
        return true;
      default:
        break;
      }

      /// If its not a comparison then it's an arithmetic operation
      if (left == right) {
        setCurType(right);
        return true;

      } else {
        logError(binaryOperator,
                 "left-hand-side's type < " + left->getName() +
                     " > doesn't match right-hand-side's type < " +
                     right->getName() + " >");
        return false;
      }
    }
  }

  logError(binaryOperator, "type error");
  return false;
}

bool TypeChecker::traverseLValueIdent(const LValueIdent &lValue) const {
  Type *type;
  if (getVariableType(_envStack, lValue.getSymbol(), &type)) {
    setCurType(type);
    return true;
  }

  logError(lValue, "variable < " + lValue.getSymbol() + " > is not defined");
  return false;
}

bool TypeChecker::traverseIdentifier(const Identifier &ident) const {
  if (isInEnvironmentStack(_envStack, ident.getName()))
    return getVariableType(_envStack, ident.getName(), &_curType);

  return false;
}

bool TypeChecker::traverseMemberAccess(const MemberAccess &memAccess) const {
  if (!traverseExpression(memAccess.getExpression())) {
    return false;
  }

  Type *type = _curType;
  if (auto *memberType = type->getMemberType(memAccess.getMember().getName())) {
    setCurType(memberType);
    return true;
  }

  logError(memAccess,
           "variable < " + memAccess.getSymbol() + " > is not defined");
  return false;
}

bool TypeChecker::traverseCall(const Call &call) const {
  if (call.isConstructorCall()) {
    if (tdb->hasType(call.getCallee()->getName())) {
      setCurType(tdb->getType(call.getCallee()->getName()));
      return _curType != nullptr;
    } else {
      logError(call, "type < " + call.getCallee()->getName() + " > not found");
    }
  } else {
    if (traverseExpression(*call.getCaller())) {
      auto *callerType = _curType;
      if (callerType->hasMethodWithoutPostfix(call.getCallee()->getName())) {
        auto *method =
            callerType->getMethodWithoutPostFix(call.getCallee()->getName());
        if (!method) {
          logError(call, "type < " + callerType->getName() +
                             " > has no method with name < "
                   + call.getCallee()->getName() + " >");
          return false;
        }
        setCurType(method->returnType);
        return _curType != nullptr;
      }
    }
  }

  return false;
}

} // namespace quack::semant