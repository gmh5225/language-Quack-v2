//
// Created by parsab on 6/11/22.
//

#include "EnvironmentBuilder.hpp"

namespace quick::sema {

/// Compound Stmt Environment Builder:
/// This function visits every assignment to collect declared variables in this
/// block. Furthermore, it visits every if stmt, because variables defined in
/// all paths of execution in an if stmt, must be defined in the if stmts parent
/// environment.
bool EnvironmentBuilder::visitCompoundStmt(const CompoundStmt &compoundStmt) {
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

bool EnvironmentBuilder::visitIf(const If &ifStmt) {
  (void)env.addNewScope();
  if (!this->visitCompoundStmt(ifStmt.getIfBlock()))
    return false;

  auto ifEnv = env.popCurrentScope();
  auto &elseEnv = env.addNewScope();
  if (ifStmt.hasElse()) {
    if (!this->visitCompoundStmt(*ifStmt.getElseBlock()))
      return false;
  }

  sema::Scope newScope = And(ifEnv, elseEnv);
  (void)env.popCurrentScope();
  auto result = env.mergeScope(newScope);
  assert(result && "must have been type checked by now!");
  return true;
}

bool isMemAccessThis(const ast::MemberAccess &memAccess) {
  if (auto identExpr = memAccess.getObject().as_a<IdentifierExpression>()) {
    return identExpr->getVarName() == "this";
  }
  return false;
};

bool EnvironmentBuilder::visitStaticAssignment(
    const StaticAssignment &assignment) {
  auto &varDecl = assignment.getDecl();

  auto rhsType = exprTC.visitExpression(assignment.getRHS());
  assert(rhsType);

  auto lhsType = tdb.getType(varDecl.getType().getName());
  assert(lhsType);

  if (varDecl.isMemberDecl()) {
    auto &decl = static_cast<const StaticMemberDecl &>(varDecl);
    auto &var = decl.getObject().getMember().getName();
    auto &memDecl = static_cast<const StaticMemberDecl &>(varDecl);
    auto *t = exprTC.visitExpression(memDecl.getObject());
    assert(t);
    //    auto *memberType =
    //    objType->lookUpMember(memAccess->getMember().getName()); if
    //    (!memberType && isMemAccessThis(*memAccess)) {
    //      objType->insertMember(
    //          type::QVarDecl{rhsType, memAccess->getMember().getName()});
    //    }
    if (t->lookUpMember(var)) {
      logError(file, memDecl.getLocation(),
               "variable <" + var +
                   "> already defined in current or super class");
      return false;
    }
    t->insertMember(type::QVarDecl{lhsType, var});
  } else {
    auto &decl = static_cast<const VarDecl &>(varDecl);
    auto &var = decl.getVar().getName();
    if (!env.back().lookup(var))
      env.back().insert({var, lhsType});
  }

  return true;
}

bool EnvironmentBuilder::visitAssignment(const Assignment &assignment) {
  sema::Scope &scope = env.back();

  auto rhsType = exprTC.visitExpression(assignment.getRHS());
  assert(rhsType);

  if (auto *ident =
          dynamic_cast<const IdentifierExpression *>(&assignment.getLHS())) {
    auto &var = ident->getVar().getName();
    if (!env.contains(var)) {
      scope.insert({var, rhsType});
    }
  } else if (auto *memAccess =
                 dynamic_cast<const MemberAccess *>(&assignment.getLHS())) {
    auto *objType = exprTC.visitExpression(memAccess->getObject());
    assert(objType);

    auto *memberType = objType->lookUpMember(memAccess->getMember().getName());
    if (!memberType && isMemAccessThis(*memAccess)) {
      if (objType->lookUpMember(memAccess->getMember().getName())) {
        objType->insertMember(
            type::QVarDecl{rhsType, memAccess->getMember().getName()});
      }
    }
  }

  return true;
}

sema::Scope &EnvironmentBuilder::update(const CompoundStmt &body, Env &env,
                                        std::fstream &file) {
  EnvironmentBuilder envBuilder(file, env);
  envBuilder.visitCompoundStmt(body);
  return env.back();
}

} // namespace quick::sema