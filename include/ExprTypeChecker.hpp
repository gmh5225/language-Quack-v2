//
// Created by parsab on 6/12/22.
//

#ifndef QUACK_EXPRTYPECHECKER_HPP
#define QUACK_EXPRTYPECHECKER_HPP

#include "ASTVisitor.hpp"
#include "QTypeDB.hpp"
#include "Environment.hpp"

namespace quack {

using namespace ast;

namespace sema {

class ExprTypeChecker : public ASTVisitor<ExprTypeChecker, type::QType *> {
  type::QTypeDB &tdb;
  const Env &env;

public:
  ExprTypeChecker(type::QTypeDB &tdb, Env &env)
      : tdb(tdb), env(env) {
  }

#define EXPR_NODE_HANDLER(NODE) type::QType *visit##NODE(const NODE &);
#include "ASTNodes.def"
};

} // namespace sema
} // namespace quack

#endif // QUACK_EXPRTYPECHECKER_HPP
