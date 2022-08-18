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

namespace sema {

/// This class is used to build an environment for a compound statement (block)
class EnvironmentBuilder : public ASTVisitor<EnvironmentBuilder, bool> {
  sema::Env &env;
  type::QTypeDB &tdb;
  sema::ExprTypeChecker exprTC;

  EnvironmentBuilder(sema::Env &env)
      : env(env), tdb(type::QTypeDB::get()), exprTC(tdb, env) {}

  bool visitCompoundStmt(const CompoundStmt &);
  bool visitAssignment(const Assignment &);
  bool visitStaticAssignment(const StaticAssignment &);
  bool visitIf(const If &);

public:
  /// Factory method to update an environment, the only available interface for
  /// this class
  static sema::Scope &update(const CompoundStmt &, Env &);
};

} // namespace sema

} // namespace quack
#endif // QUACK_ENVIRONMENTBUILDER_HPP
