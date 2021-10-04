//
// Created by Parsa Bagheri on 3/23/21.
//

#ifndef QUACK_COMPOUNDSTMTCHECKER_HPP
#define QUACK_COMPOUNDSTMTCHECKER_HPP

#include "AST.hpp"
#include "ASTVisitor.hpp"
#include "TypeChecker.hpp"
#include "TypeInfo.hpp"
#include "Utils.hpp"

#include "Type.hpp"

#include <exception>
#include <map>
#include <set>
#include <stack>

namespace quack::semant {

class TypeChecker;

using namespace ast;

class CompoundStmtChecker : public ASTVisitor<CompoundStmtChecker> {
  friend class CompoundStmtCodeGen;
  EnvironmentStack &_stack;
  TypeChecker &_typeChecker;
  TypeDataBase *tdb;
  Type *parentType; // if the compound stmt is in a class, this will point to
                    // it's corresponding type, otherwise nullptr
  bool isConstructor;

public:
  CompoundStmtChecker(const TranslationUnit &translationUnit,
                      EnvironmentStack &stack, TypeChecker &typeChecker,
                      Type *parentType = nullptr, bool isConstructor = false)
      : ASTVisitor<CompoundStmtChecker>(translationUnit), _stack(stack),
        _typeChecker(typeChecker), tdb(TypeDataBase::getTypeDB()),
        parentType(parentType), isConstructor(isConstructor)
      {}

  bool traverseCompoundStmt(const CompoundStmt &compoundStmt) const override;

  bool traverseAssignment(const Assignment &assignment) const override;

  bool traverseVarDecl(const VarDecl &varDecl) const override;

  bool traverseLValueIdent(const LValueIdent &lValue) const override;

  bool traverseIf(const If &) const override;

  bool traverseWhile(const While &) const override;

  bool traverseCall(const Call &) const override;

  bool traverseMemberAccess(const MemberAccess &) const override;

  ~CompoundStmtChecker() = default;
};

} // namespace quack::semant
#endif // QUACK_COMPOUNDSTMTCHECKER_HPP
