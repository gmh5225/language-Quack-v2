//
// Ensures the body of a function is legal
//

#ifndef QUACK_ENVIRONMENTBUILDER_HPP
#define QUACK_ENVIRONMENTBUILDER_HPP

#include "ASTVisitor.hpp"
#include "ExprTypeChecker.hpp"
#include "QType.hpp"

namespace quack {

using namespace ast;

template <typename Derived>
class EnvironmentBuilder : public ASTVisitor<Derived, bool> {
protected:
  const CompoundStmt &fnBody;
  type::QTypeDB &tdb;
  type::QType *parentType; // the type that the compound statement is in the
                           // environment of
  type::QType *returnType;
  bool isConstructor; // If compound statement belongs to constructor of a type
  sema::Env env;
  sema::ExprTypeChecker exprTC;

  EnvironmentBuilder(const CompoundStmt &cmpStmt, type::QTypeDB &typedb,
                     type::QType *parentType = nullptr,
                     type::QType *returnType = nullptr,
                     bool isConstructor = false)
      : fnBody(cmpStmt), tdb(typedb), parentType(parentType),
        returnType(returnType), isConstructor(isConstructor), exprTC(tdb, env) {
  }

  bool visitCompoundStmt(const CompoundStmt &);
  bool visitAssignment(const Assignment &);
  bool visitStaticAssignment(const StaticAssignment &);
  bool visitIf(const If &);
  sema::Scope &addNewScope() {
    env.push_back(sema::Scope());
    return env.back();
  }
  sema::Scope &getCurrentScope() { return env.back(); }
  sema::Scope popCurrentScope() {
    sema::Scope s = std::move(env.back());
    env.pop_back();
    return s;
  }
};

/// Compound Stmt Environment Builder:
/// This function visits every assignment to collect declared variables in this
/// block. Furthermore, it visits every if stmt, because variables defined in
/// all paths of execution in an if stmt, must be defined in the if stmts parent
/// environment.
template <typename Derived>
bool EnvironmentBuilder<Derived>::visitCompoundStmt(
    const CompoundStmt &compoundStmt) {
  for (auto &stmt : compoundStmt) {
    switch (stmt->getKind()) {
    case Statement::Kind::StaticAssignment:
      if (!visitStaticAssignment(static_cast<const StaticAssignment &>(*stmt)))
        return false;
      break;
    case Statement::Kind::Assignment:
      if (!visitAssignment(static_cast<const Assignment &>(*stmt)))
        return false;
      break;
    case Statement::Kind::If:
      if (!visitIf(static_cast<const If &>(*stmt)))
        return false;
      break;
    default:
      break;
    }
  }
  return true;
}

template <typename Derived>
bool EnvironmentBuilder<Derived>::visitIf(const If &ifStmt) {
  if (auto type = exprTC.visitExpression(ifStmt.getCond())) {
    if (type != tdb.getBoolType()) {
      logError(ifStmt.getCond(),
               "Conditional expression doesn't reduce to < Bool > type");
      return false;
    }
  } else
    return false;

  (void)addNewScope();
  if (!this->visitCompoundStmt(ifStmt.getIfBlock()))
    return false;

  auto ifEnv = popCurrentScope();
  auto &elseEnv = addNewScope();
  if (ifStmt.hasElse()) {
    if (!this->visitCompoundStmt(*ifStmt.getElseBlock()))
      return false;
  }

  sema::Scope newScope = ifEnv.And(elseEnv);
  popCurrentScope();

  if (!env.mergeScope(newScope)) {
    logError(ifStmt,
             "Type conflict between variable declared in if and/or else stmts "
             "body and parent scope");
    return false;
  }

  return true;
}

template <typename Derived>
bool EnvironmentBuilder<Derived>::visitStaticAssignment(
    const StaticAssignment &assignment) {
  auto &varDecl = assignment.getDecl();
  if (varDecl.isMemberDecl() && !isConstructor) {
    logError(varDecl, "Member declaration outside of a class constructor");
    return false;
  }

  auto &var = varDecl.getVar().getName();

  auto rhsType = exprTC.visitExpression(assignment.getRHS());
  if (!rhsType)
    return false;

  auto lhsType = tdb.getType(varDecl.getType().getName());
  if (!lhsType) {
    logError(varDecl, "No such type <" + varDecl.getType().getName() + ">");
    return false;
  }

  if (lhsType != rhsType && !rhsType->isDescendentOf(lhsType)) {
    logError(assignment,
             "Conflict between declared type <" + lhsType->getName() +
                 "> and right hand side type <" + rhsType->getName() + ">");
    return false;
  }

  if (varDecl.isMemberDecl()) {
    auto &memDecl = static_cast<const StaticMemberDecl &>(varDecl);
    auto *t = exprTC.visitExpression(memDecl.getObject());
    if (t->getMembers().count(var)) {
      logError(varDecl, "Member already declared");
      return false;
    }
    t->insertMember(type::NamedVar{lhsType, var});

  } else {
    if (env.back().count(var)) {
      logError(varDecl,
               "Variable <" + var + "> already declared in current scope");
      return false;
    }
    env.back().insert({var, lhsType});
  }

  return true;
}

template <typename Derived>
bool EnvironmentBuilder<Derived>::visitAssignment(
    const Assignment &assignment) {
  sema::Scope &scope = env.back();

  auto rhsType = exprTC.visitExpression(assignment.getRHS());
  if (!rhsType)
    return false;

  if (auto *ident = dynamic_cast<const LValueIdent *>(&assignment.getLHS())) {
    auto &var = ident->getVar().getName();
    if (auto *varType = env.lookup(var)) {
      if (varType != rhsType) {
        logError(assignment, "Conflict between rhs type <" +
                                 rhsType->getName() + "> and variable type <" +
                                 varType->getName() + ">");
        return false;
      }
    } else {
      scope.insert({var, rhsType});
    }
  } else if (auto *memAccess =
                 dynamic_cast<const MemberAccess *>(&assignment.getLHS())) {
    auto *objType = exprTC.visitExpression(memAccess->getObject());
    if (!objType)
      return false;

    // Check if we have memory access right
    if (objType != parentType) {
      logError(assignment, "Cannot access member of type <" +
                               objType->getName() + "> in this scope");
      return false;
    }

    auto *memberType = objType->lookUpMember(memAccess->getMember().getName());
    if (!memberType) {
      if (!isConstructor) {
        logError(*memAccess, "No such member <" +
                                 memAccess->getMember().getName() +
                                 ">. Cannot add member outside of constructor");
        return false;
      }
      objType->insertMember(
          type::NamedVar{rhsType, memAccess->getMember().getName()});

    } else if (memberType != rhsType || !rhsType->isDescendentOf(memberType)) {
      logError(assignment, "Conflict between rhs type <" + rhsType->getName() +
                               "> and lhs type <" + memberType->getName() +
                               ">");
      return false;
    }
  }

  return true;
}

} // namespace quack
#endif // QUACK_ENVIRONMENTBUILDER_HPP
