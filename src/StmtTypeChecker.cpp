//
// Created by parsab on 6/14/22.
//

#include "StmtVerifier.hpp"

namespace quick {
namespace sema {

bool StmtVerifier::visitIf(const ast::If &ifStmt) {
  if (auto type = exprTC.visitExpression(ifStmt.getCond())) {
    if (type != tdb.getBoolType()) {
      logError(ifStmt.getCond(),
               "Conditional expression doesn't reduce to < Bool > type");
      return false;
    }
  } else
    return false;

  (void)env.addNewScope();
  if (!this->visitCompoundStmt(ifStmt.getIfBlock()))
    return false;

  sema::Scope ifEnv = env.popCurrentScope();
  auto &elseEnv = env.addNewScope();
  if (ifStmt.hasElse()) {
    if (!this->visitCompoundStmt(*ifStmt.getElseBlock()))
      return false;
  }

  sema::Scope newScope = And(ifEnv, elseEnv);
  (void)env.popCurrentScope();

  if (!env.mergeScope(newScope)) {
    logError(ifStmt,
             "Type conflict between variable declared in if and/or else stmts "
             "body and parent scope");
    return false;
  }

  return true;
}

bool StmtVerifier::visitAssignment(const ast::Assignment &assignment) {
  sema::Scope &scope = env.back();

  auto rhsType = exprTC.visitExpression(assignment.getRHS());
  if (!rhsType)
    return false;

  if (auto *ident = dynamic_cast<const IdentifierExpression *>(&assignment.getLHS())) {
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
          type::QVarDecl{rhsType, memAccess->getMember().getName()});

    } else if (memberType != rhsType || !rhsType->isDescendentOf(memberType)) {
      logError(assignment, "Conflict between rhs type <" + rhsType->getName() +
                               "> and lhs type <" + memberType->getName() +
                               ">");
      return false;
    }
  }

  return true;
}

bool StmtVerifier::visitStaticAssignment(
    const ast::StaticAssignment &assignment) {
  auto &decl = assignment.getDecl();
  if (decl.isMemberDecl() && !isConstructor) {
    logError(decl, "Member declaration outside of a class constructor");
    return false;
  }

  auto rhsType = exprTC.visitExpression(assignment.getRHS());
  if (!rhsType)
    return false;

  auto lhsType = tdb.getType(decl.getType().getName());
  if (!lhsType) {
    logError(decl, "No such type <" + decl.getType().getName() + ">");
    return false;
  }

  if (lhsType != rhsType && !rhsType->isDescendentOf(lhsType)) {
    logError(assignment,
             "Conflict between declared type <" + lhsType->getName() +
                 "> and right hand side type <" + rhsType->getName() + ">");
    return false;
  }

  if (decl.isMemberDecl()) {
    auto &memDecl = static_cast<const StaticMemberDecl &>(decl);
    auto &var = memDecl.getObject().getMember().getName();
    auto *t = exprTC.visitExpression(memDecl.getObject());
    if (t->getMembers().count(var)) {
      logError(decl, "Member already declared");
      return false;
    }
    t->insertMember(type::QVarDecl{lhsType, var});

  } else {
    auto &varDecl = static_cast<const VarDecl &>(decl);
    auto &var = varDecl.getVar().getName();
    if (env.back().lookup(var)) {
      logError(decl, "Redeclaration of variable <" + var + ">");
      return false;
    }
    env.back().insert({var, lhsType});
  }

  return true;
}

bool StmtVerifier::visitWhile(const ast::While &whileStmt) {
  if (auto type = exprTC.visitExpression(whileStmt.getCond())) {
    if (type != tdb.getBoolType()) {
      logError(whileStmt.getCond(),
               "Conditional expression doesn't reduce to < Bool > type");
      return false;
    }
  } else {
    return false;
  }
  (void)env.addNewScope();
  auto res = this->visitCompoundStmt(whileStmt.getBlock());
  (void)env.popCurrentScope();
  return res;
}

bool StmtVerifier::visitCompoundStmt(const ast::CompoundStmt &cmpStmt) {
  for (auto &stmt : cmpStmt)
    if (!visitStatement(*stmt))
      return false;
  return true;
}

bool StmtVerifier::visitValueStmt(const ast::ValueStmt &valueStmt) {
  return exprTC.visitExpression(valueStmt.getExpr()) != nullptr;
}

bool StmtVerifier::visitReturn(const ast::Return &returnStmt) {
  if (isConstructor) {
    logError(returnStmt,
             "return statement can't be used in the body of a constructor");
    return false;
  }

  if (returnType != nullptr) {
    if (auto retval = returnStmt.getRetVal()) {
      auto retType = exprTC.visitExpression(*retval);
      if (!retType)
        return false;

      if (retType != returnType && !retType->isDescendentOf(returnType)) {
        logError(returnStmt, "Expected <" + returnType->getName() +
                                 "> type to be returned but got <" +
                                 retType->getName() + ">");
        return false;
      }
    }
  }

  return true;
}

bool StmtVerifier::visitPrintStatement(const ast::PrintStatement &printStmt) {
  for (auto &expr: *printStmt.getArgs()) {
    if(!exprTC.visitExpression(*expr))
      return false;
  }
  return true;
}

bool StmtVerifier::isLegal() {
  (void)env.addNewScope();
  auto res = visitCompoundStmt(cmpStmt);
  (void)env.popCurrentScope();
  return res;
}

} // namespace sema
} // namespace quick