//
// Created by Parsa Bagheri on 3/23/21.
//

#include "CompoundStmtChecker.hpp"

#include "Type.hpp"
#include "Utils.hpp"

#include <iostream>

namespace quack::semant {

bool CompoundStmtChecker::traverseCompoundStmt(
    const CompoundStmt &compoundStmt) const {
  auto status = true;
  for (const auto &stmt : compoundStmt) {
    if (!traverseStatement(stmt))
      status = false;
  }

  return status;
}

bool CompoundStmtChecker::traverseVarDecl(const VarDecl &varDecl) const {
  Environment &env = _stack.back();
  std::string name = varDecl.getVar().getName();
  if (varDecl.isMemberDecl())
    name.insert(0, "this.");

  if (!isInEnvironmentStack(_stack, name)) {
    if (tdb->hasType(varDecl.getType().getName())) {
      env.insert({name, tdb->getType(varDecl.getType().getName())});
      return true;
    } else {
      logError(varDecl, "type < " + varDecl.getType().getName() +
                            " > hasn't been defined");
      return false;
    }
  } else {
    logError(varDecl, "symbol < " + name + " > is already declared as < " +
                          env[name]->getName() + " >");
    return false;
  }
}

bool CompoundStmtChecker::traverseLValueIdent(const LValueIdent &lValue) const {
  const auto &name = lValue.getVar().getName();
  if (isInEnvironmentStack(_stack, name)) {
    return true;
  } else {
    logError(lValue, "symbol < " + name + " > not found");
    return false;
  }
}

bool CompoundStmtChecker::traverseIf(const If &ifStmt) const {
  bool status = true;
  if (_typeChecker.traverseExpression(ifStmt.getCond())) {
    if (_typeChecker.getCurType()->getName() != "Bool") {
      logError(ifStmt.getCond(),
               "conditional expression doesn't reduce to < Bool > type");
      status = false;
    }
  } else {
    status = false;
  }

  _stack.push_back(Environment());

  if (!traverseCompoundStmt(ifStmt.getIfBlock()))
    status = false;

  auto ifEnv = _stack.back(); // copy back environment

  _stack.pop_back();

  _stack.push_back(Environment());
  if (ifStmt.getElseBlock() != nullptr) {
    if (!traverseCompoundStmt(*ifStmt.getElseBlock()))
      status = false;
  }

  auto elseEnv = _stack.back(); // copy back environment
  _stack.pop_back();

  Environment newEnv;

  // taking the intersection of if and else environments
  getIntersectionOf(ifEnv, elseEnv, newEnv);

  // add the new environment to the top environment on the stack
  getUnionOf(_stack.back(), newEnv);

  return status;
}

bool CompoundStmtChecker::traverseWhile(const While &whileStmt) const {
  auto status = true;
  if (!_typeChecker.traverseExpression(whileStmt.getCond()))
    return false;

  if (_typeChecker.getCurType()->getName() != "Bool") {
    logError(whileStmt.getCond(),
             "conditional statement doesn't reduce to Bool type");
    status = false;
  }

  _stack.push_back(Environment());

  if (!traverseCompoundStmt(whileStmt.getBlock()))
    status = false;

  _stack.pop_back();

  return status;
}

bool CompoundStmtChecker::traverseMemberAccess(
    const MemberAccess &memberAccess) const {

  quack::Type *type;

  if (auto *ident =
          dynamic_cast<const Identifier *>(&memberAccess.getExpression())) {

    if (ident->getName() == "this") {
      if (parentType == nullptr) {
        logError(memberAccess, "using \"this\" keyword outside of class "
                               "definition");
        return false;
      } else {
        type = parentType;
      }
    } else {
      if (!_typeChecker.traverseIdentifier(*ident))
        return false;

      type = _typeChecker.getCurType();
    }
  } else {
    if (!_typeChecker.traverseExpression(memberAccess.getExpression()))
      return false;

    type = _typeChecker.getCurType();
  }

  const auto &name = memberAccess.getMember().getName();
  if (type->hasMember(name))
    return true;
  else {
    logError(memberAccess, "type < " + type->getName() +
                               " > doesn't have a method with name < " + name +
                               " >");
    return false;
  }
}

bool CompoundStmtChecker::traverseAssignment(
    const Assignment &assignment) const {

  Type *lhsType, *rhsType;
  std::string lhsSymbol;
  Environment &env = _stack.back();

  if (!_typeChecker.traverseExpression(assignment.getRightHandSide()))
    return false;

  rhsType = _typeChecker.getCurType();
  lhsSymbol = assignment.getLeftHandSide().getSymbol();

  if ((assignment.getLeftHandSide().getKind() == LValue::Kind::LValueIdent ||
       assignment.getLeftHandSide().getKind() == LValue::Kind::MemberAccess) &&
      !isInEnvironmentStack(_stack, lhsSymbol)) {
    // left hand side symbol not found, infer type and declare in environment
    env.insert({lhsSymbol, rhsType});
  }

  if (traverseLValue(assignment.getLeftHandSide())) {
    if (traverseExpression(assignment.getRightHandSide())) {

      if (_typeChecker.traverseLValue(assignment.getLeftHandSide())) {
        lhsType = _typeChecker.getCurType();

        if (rhsType == lhsType)
          return true;
        else
          logError(assignment, "bad assignment: left-hand-side's type < " +
                                   lhsType->getName() +
                                   " > doesn't match "
                                   "right-hand-side's type < " +
                                   rhsType->getName() + " >");
      }
    }
  }

  return false;
}

bool CompoundStmtChecker::traverseCall(const Call &call) const {

  if (auto *caller = call.getCaller())
    if (!caller->isLValue()) {
      logError(call, "caller must be an l-value");
      return false;
    }

  auto checkArgsAgainstParams =
      [this](const std::vector<Parameter> &params,
             const std::vector<std::unique_ptr<Expression>> &args) -> bool {
    auto len = args.size();
    if (len == params.size()) {
      for (int i = 0; i < len; i++) {
        Type *paramType = params.at(i).type;
        Type *argType = nullptr;
        if (this->_typeChecker.traverseExpression(*args.at(i))) {
          argType = this->_typeChecker.getCurType();
        }

        if (argType->getName() != paramType->getName()) {
          logError("expression of type < " + argType->getName() +
                   " > cannot be passed to as a parameter of type"
                   " < " +
                   paramType->getName() + " >");
          return false;
        }
      }
    }
    return true;
  };

  auto *method = call.getCallee();
  auto &methodName = method->getName();
  auto &args = call.getArgs()->getSequence();

  if (auto *caller = call.getCaller()) {
    // method call
    if (!traverseExpression(*caller))
      return false;

    _typeChecker.traverseExpression(*caller);
    Type *type = _typeChecker.getCurType();

    if (!type->hasMethodWithoutPostfix(methodName)) {
      logError("type < " + type->getName() + " > has no method with name < " +
               methodName + " >");
      return false;
    }

    auto *params = type->getMethodWithoutPostFixParams(methodName);
    if (!params) {
      logError("type < " + type->getName() + " > has no method with name < " +
               methodName + " >");
      return false;
    }

    if (!checkArgsAgainstParams(*params, args)) {
      return false;
    }

  } else {
    // constructor
    if (!tdb->hasType(methodName)) {
      logError("type < " + methodName + " > doesn't exists");
      return false;
    }

    Type *type = tdb->getType(methodName);
    if (auto *constructor = type->getConstructor()) {
      if (!checkArgsAgainstParams(constructor->parameters, args)) {
        return false;
      }
    } else {
      logError("type < " + methodName + " > has an implicit constructor");
      return false;
    }
  }

  return true;
}

} // namespace quack::semant