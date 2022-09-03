//
// Created by parsab on 6/14/22.
//

#ifndef QUACK_FNTYPECHECKER_H
#define QUACK_FNTYPECHECKER_H

#include "EnvironmentBuilder.hpp"

namespace quick {
namespace sema {

/// ===-------------------------------------------------------------------=== //
/// StmtVerifier - A visitor that visits every statement and verifies
/// their legality
/// ===-------------------------------------------------------------------=== //
class StmtVerifier : public ASTVisitor<StmtVerifier, bool> {
  const CompoundStmt &cmpStmt;
  sema::Env &env;
  type::QTypeDB &tdb;
  type::QType *parentType; // the type that the compound statement is in the
                           // environment of
  type::QType *returnType;
  bool isConstructor; // If compound statement belongs to constructor of a type
  sema::ExprTypeChecker exprTC;

public:
  StmtVerifier(const CompoundStmt &cmpStmt, sema::Env &env,
                  type::QType *parentType = nullptr,
                  type::QType *returnType = nullptr, bool isConstructor = false)
      : cmpStmt(cmpStmt), env(env), tdb(type::QTypeDB::get()), parentType(parentType),
        returnType(returnType), isConstructor(isConstructor), exprTC(tdb, env) {}

  // only visits statements
  bool visitExpression(const ast::Expression&) = delete;
#define EXPR_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &) = delete;
#define STMT_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &);
#include "ASTNodes.def"

  bool isLegal();
};

} // namespace sema
} // namespace quick
#endif // QUACK_FNTYPECHECKER_H
