//
// Created by parsab on 6/14/22.
//

#include <memory>

#include "StmtVerifier.hpp"

namespace quick {
namespace sema {

bool StmtVerifier::visitIf(const ast::If &ifStmt) {
  if (auto type = exprTC.visitExpression(ifStmt.getCond())) {
    if (type != tdb.getBoolType()) {
      logError(file, ifStmt.getCond().getLocation(),
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
    logError(file, ifStmt.getLocation(),
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

  if (auto *ident =
          dynamic_cast<const IdentifierExpression *>(&assignment.getLHS())) {
    auto &var = ident->getVar().getName();
    if (auto *varType = env.lookup(var)) {
      if (varType != rhsType && !rhsType->isDescendentOf(varType)) {
        logError(file, assignment.getLocation(),
                 "Conflict between rhs type <" + rhsType->getName() +
                     "> and variable type <" + varType->getName() + ">");
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
      logError(file, assignment.getLocation(),
               "Cannot access member of type <" + objType->getName() +
                   "> in this scope");
      return false;
    }

    auto *memberType = objType->lookUpMember(memAccess->getMember().getName());
    if (!memberType) {
      if (!isConstructor) {
        logError(file, memAccess->getLocation(),
                 "No such member <" + memAccess->getMember().getName() +
                     ">. Cannot add member outside of constructor");
        return false;
      }
      objType->insertMember(
          type::QVarDecl{rhsType, memAccess->getMember().getName()});

    } else if (memberType != rhsType || !rhsType->isDescendentOf(memberType)) {
      logError(file, assignment.getLocation(),
               "Conflict between rhs type <" + rhsType->getName() +
                   "> and lhs type <" + memberType->getName() + ">");
      return false;
    }
  }

  return true;
}

bool StmtVerifier::visitStaticAssignment(
    const ast::StaticAssignment &assignment) {
  auto &decl = assignment.getDecl();
  if (decl.isMemberDecl() && !isConstructor) {
    logError(file, decl.getLocation(),
             "Member declaration outside of a class constructor");
    return false;
  }

  auto rhsType = exprTC.visitExpression(assignment.getRHS());
  if (!rhsType)
    return false;

  auto lhsType = tdb.getType(decl.getType().getName());
  if (!lhsType) {
    logError(file, decl.getLocation(),
             "No such type <" + decl.getType().getName() + ">");
    return false;
  }

  if (lhsType != rhsType && !rhsType->isDescendentOf(lhsType)) {
    logError(file, assignment.getLocation(),
             "Conflict between declared type <" + lhsType->getName() +
                 "> and right hand side type <" + rhsType->getName() + ">");
    return false;
  }

  if (decl.isMemberDecl()) {
    auto &memDecl = static_cast<const StaticMemberDecl &>(decl);
    auto &var = memDecl.getObject().getMember().getName();
    if (auto *identExpr =
            memDecl.getObject().getObject().as_a<IdentifierExpression>()) {
      if (identExpr->getVarName() == "this" && isConstructor) {
        auto *type = env.lookup("this");
        assert(type);
        auto *varType = tdb.getType(memDecl.getType().getName());
        if (!varType) {
          logError(file, memDecl.getLocation(), "type not found");
          return false;
        }
        if (type->getMembers().count(var)) {
          logError(file, decl.getLocation(), "Member already declared");
          return false;
        }
        type->insertMember({varType, var});
      } else {
        logError(file, decl.getLocation(),
                 "Cannot declare member outside of type definition");
        return false;
      }
    }
  } else {
    auto &varDecl = static_cast<const VarDecl &>(decl);
    auto &var = varDecl.getVar().getName();
    if (env.back().lookup(var)) {
      logError(file, decl.getLocation(),
               "Redeclaration of variable <" + var + ">");
      return false;
    }
    env.back().insert({var, lhsType});
  }

  return true;
}

bool StmtVerifier::visitWhile(const ast::While &whileStmt) {
  if (auto type = exprTC.visitExpression(whileStmt.getCond())) {
    if (type != tdb.getBoolType()) {
      logError(file, whileStmt.getCond().getLocation(),
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
    logError(file, returnStmt.getLocation(),
             "return statement can't be used in the body of a constructor");
    return false;
  }

  if (returnType != nullptr) {
    if (auto retval = returnStmt.getRetVal()) {
      auto retType = exprTC.visitExpression(*retval);
      if (!retType)
        return false;

      if (retType != returnType && !retType->isDescendentOf(returnType)) {
        logError(file, returnStmt.getLocation(),
                 "Expected <" + returnType->getName() +
                     "> type to be returned but got <" + retType->getName() +
                     ">");
        return false;
      }
    }
  }

  return true;
}

bool StmtVerifier::visitPrintStatement(const ast::PrintStatement &printStmt) {
  for (auto &expr : *printStmt.getArgs()) {
    if (!exprTC.visitExpression(*expr))
      return false;
  }
  return true;
}

bool StmtVerifier::visitTypeSwitch(const ast::TypeSwitch &typeSwitch) {
  auto curType = exprTC.visitExpression(typeSwitch.getValue());
  int numErrors = 0;
  std::unique_ptr<Scope> mergeScope = nullptr;
  for (auto &c : typeSwitch.getCases()) {
    auto &typeName = c->getVarDecl().getType().getName();
    auto cType = tdb.getType(typeName);
    if (!cType) {
      logError(file, c->getLocation(), "type <" + typeName + "> not found");
      return false;
    }

    if (!cType->isDescendentOf(curType)) {
      logError(file, c->getLocation(),
               "type <" + typeName + "> is not a descendent of type <" +
                   curType->getName() + ">");
      return false;
    }

    auto &caseScope = env.addNewScope();
    auto &varName = c->getVarDecl().getVar().getName();
    caseScope.insert({varName, cType}); // temporarily adding variable
                                        // to current scope
    if (!visitTypeSwitchCase(*c))
      numErrors++;
    caseScope.erase(varName); // removing temporary variable
    if (!mergeScope) {
      mergeScope = std::make_unique<Scope>(caseScope);
    } else {
      mergeScope =
          std::make_unique<Scope>(std::move(And(*mergeScope, caseScope)));
    }
    (void)env.popCurrentScope();
  }
  if (mergeScope)
    env.mergeScope(*mergeScope);
  return numErrors == 0;
}

bool StmtVerifier::visitTypeSwitchCase(
    const ast::TypeSwitchCase &typeSwitchCase) {
  return visitCompoundStmt(typeSwitchCase.getBlock());
}

bool StmtVerifier::isLegal() {
  auto &scope = env.addNewScope();
  if (parentType) {
    scope.insert({"this", parentType});
  }
  auto res = visitCompoundStmt(cmpStmt);
  (void)env.popCurrentScope();
  return res;
}

} // namespace sema
} // namespace quick