//
// Created by Parsa Bagheri on 3/26/21.
//

#ifndef QUACK_TYPECHECKER_HPP
#define QUACK_TYPECHECKER_HPP

#include "Type.hpp"

#include "ASTVisitor.hpp"
#include "CompoundStmtChecker.hpp"
#include "Utils.hpp"

namespace quack::semant {

using namespace ast;

class TypeChecker : public ASTVisitor<TypeChecker> {
  mutable Type *_curType; /* current type in the AST will be stored here */
  EnvironmentStack &_envStack;
  TypeDataBase *tdb;

public:
  TypeChecker(const TranslationUnit &root, EnvironmentStack &envStack)
      : ASTVisitor<TypeChecker>(root), _envStack(envStack), _curType(),
        tdb(TypeDataBase::getTypeDB()) {}

  ~TypeChecker() = default;

  bool traverseIntegerLiteral(const IntegerLiteral &) const override;

  bool traverseFloatLiteral(const FloatLiteral &) const override;

  bool traverseBoolLiteral(const BoolLiteral &) const override;

  bool traverseStringLiteral(const StringLiteral &) const override;

  bool traverseBinaryOperator(const BinaryOperator &) const override;

  bool traverseLValueIdent(const LValueIdent &) const override;

  bool traverseMemberAccess(const MemberAccess &) const override;

  bool traverseIdentifier(const Identifier &) const override;

  bool traverseCall( const Call &) const override;

  Type *getCurType() const { return _curType; }

private:
  void setCurType(Type *cur) const { _curType = cur; }
};

} // namespace quack::semant
#endif // QUACK_TYPECHECKER_HPP
