//
// Created by parsab on 6/14/22.
//

#ifndef QUACK_FNTYPECHECKER_H
#define QUACK_FNTYPECHECKER_H

#include "EnvironmentBuilder.hpp"

namespace quack {
namespace sema {

class StmtTypeChecker : public ASTVisitor<StmtTypeChecker, bool> {
  const CompoundStmt &cmpStmt;
  sema::Env &env;
  type::QTypeDB &tdb;
  type::QType *parentType; // the type that the compound statement is in the
                           // environment of
  type::QType *returnType;
  bool isConstructor; // If compound statement belongs to constructor of a type
  sema::ExprTypeChecker exprTC;

public:
  StmtTypeChecker(const CompoundStmt &cmpStmt, sema::Env &env,
                  type::QType *parentType = nullptr,
                  type::QType *returnType = nullptr, bool isConstructor = false)
      : cmpStmt(cmpStmt), env(env), tdb(type::QTypeDB::get()), parentType(parentType),
        returnType(returnType), isConstructor(isConstructor), exprTC(tdb, env) {}

#define STMT_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &);
#include "ASTNodes.def"

  bool isLegal();
};

} // namespace sema
} // namespace quack
#endif // QUACK_FNTYPECHECKER_H
