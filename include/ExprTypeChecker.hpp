//
// Created by parsab on 6/12/22.
//

#ifndef QUACK_EXPRTYPECHECKER_HPP
#define QUACK_EXPRTYPECHECKER_HPP

#include "ASTVisitor.hpp"
#include "Environment.hpp"
#include "QTypeDB.hpp"

namespace quick {

using namespace ast;

namespace sema {

/// ===-------------------------------------------------------------------=== //
/// An expression visitor that evaluates the type of an expression.
/// ===-------------------------------------------------------------------=== //
class ExprTypeChecker : public ASTVisitor<ExprTypeChecker, type::QType *> {
  type::QTypeDB &tdb;
  const Env &env;

public:
  ExprTypeChecker(type::QTypeDB &tdb, Env &env)
      : tdb(tdb), env(env) {
  }
  type::QType *visitStatement(const Statement &) = delete;
  type::QType *visitTranslationUnit(const TranslationUnit &) = delete;
#define STMT_NODE_HANDLER(NODE) type::QType *visit##NODE(const NODE &) = delete;
#define EXPR_NODE_HANDLER(NODE) type::QType *visit##NODE(const NODE &);
#include "ASTNodes.def"
};

} // namespace sema
} // namespace quick

#endif // QUACK_EXPRTYPECHECKER_HPP
