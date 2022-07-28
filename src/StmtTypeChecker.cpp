//
// Created by parsab on 6/14/22.
//

#include "StmtTypeChecker.h"

namespace quack {
namespace sema {

/// These are typechecked by parent class
bool StmtTypeChecker::visitIf(const ast::If &ifStmt) { return true; }

bool StmtTypeChecker::visitAssignment(const ast::Assignment &assign) {
  return true;
}

bool StmtTypeChecker::visitStaticAssignment(
    const ast::StaticAssignment &assign) {
  return true;
}

bool StmtTypeChecker::visitWhile(const ast::While &whileStmt) {
  if (auto type = exprTC.visitExpression(whileStmt.getCond())) {
    if (type != tdb.getBoolType()) {
      logError(whileStmt.getCond(),
               "Conditional expression doesn't reduce to < Bool > type");
      return false;
    }
  } else {
    return false;
  }
  return this->visitCompoundStmt(whileStmt.getBlock());
}

bool StmtTypeChecker::visitCompoundStmt(const ast::CompoundStmt &cmpStmt) {
  // build the environment first
  addNewScope();
  if (!EnvironmentBuilder::visitCompoundStmt(cmpStmt))
    return false;
  for (auto &stmt : cmpStmt)
    if (!visitStatement(*stmt))
      return false;
  popCurrentScope();
  return true;
}

bool StmtTypeChecker::visitValueStmt(const ast::ValueStmt &valueStmt) {
  return exprTC.visitExpression(valueStmt.getExpr()) != nullptr;
}

bool StmtTypeChecker::visitReturn(const ast::Return &returnStmt) {
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

} // namespace sema
} // namespace quack