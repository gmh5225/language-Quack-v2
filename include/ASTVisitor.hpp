//
// Created by Parsa Bagheri on 9/9/20.
//

#ifndef QUACK_ASTVISITOR_HPP
#define QUACK_ASTVISITOR_HPP

#include "AST.hpp"
#include "ASTNodes.def"

namespace quack::ast {
/// Forward refs of ASTNode classes
#define X(ASTNodeType) class ASTNodeType;

AST_NODES

#undef X

/// Static casts an lvalue reference
#define STATIC_REF_CAST(CAST_TO, OBJ) (*static_cast<const CAST_TO *>(&OBJ))

/// ASTVisitor interface declares methods for visiting each node of the AST
template <typename Derived> class ASTVisitor {
protected:
  using DerivedType = Derived;
  const TranslationUnit &_root;
  explicit ASTVisitor(const TranslationUnit &translationUnit)
      : _root(translationUnit){};

public:
  virtual ~ASTVisitor() = default;

  const Derived *getDerived() const {
    return reinterpret_cast<const Derived *>(this);
  }

  /// Declares a virtual traverse*ASTNode method for each node in the AST
#define X(ASTNodeType)                                                         \
  virtual bool traverse##ASTNodeType(const ASTNodeType &) const;

  AST_NODES

#undef X

  bool traverseAST() const {
    return getDerived()->traverseTranslationUnit(_root);
  }

}; // ASTVisitor

template <typename Derived>
bool ASTVisitor<Derived>::traverseTranslationUnit(
    const TranslationUnit &translationUnit) const {
  if (getDerived()->traverseClasses(translationUnit.getClasses()))
    return getDerived()->traverseCompoundStmt(
        translationUnit.getCompoundStmt());
  return false;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseParameters(const Parameters &params) const {
  for (const auto &param : params) {
    if (!getDerived()->traverseVarDecl(param))
      return false;
  }
  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseClasses(const Classes &classes) const {
  for (const auto &clss : classes) {
    if (!getDerived()->traverseClass(clss))
      return false;
  }
  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseClass(const Class &clss) const {

  if (!getDerived()->traverseIdentifier(clss.getClassIdent()))
    return false;

  if (!getDerived()->traverseIdentifier(*(clss.getSuper())))
    return false;

  if (!getDerived()->traverseMethod(clss.getConstructor()))
    return false;

  if (!getDerived()->traverseMethods(clss.getMethods()))
    return false;

  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseMethods(const Methods &methods) const {
  for (const auto &method : methods) {
    if (!getDerived()->traverseMethod(method))
      return false;
  }
  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseMethod(const Method &method) const {

  if (!getDerived()->traverseIdentifier(method.getMethodIdent()))
    return false;

  if (!getDerived()->traverseParameters(method.getParams()))
    return false;

  if (!getDerived()->traverseIdentifier(method.getReturnType()))
    return false;

  if (!getDerived()->traverseCompoundStmt(method.getBody()))
    return false;

  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseIntegerLiteral(
    const IntegerLiteral &integerLiteral) const {
  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseFloatLiteral(
    const FloatLiteral &floatLiteral) const {
  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseBoolLiteral(
    const BoolLiteral &boolLiteral) const {
  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseStringLiteral(const StringLiteral &) const {
  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseIdentifier(
    const Identifier &identifier) const {
  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseArguments(const Arguments &) const {
  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseCall(const Call &) const {
  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseVarDecl(const VarDecl &varDecl) const {
  if (getDerived()->traverseIdentifier(varDecl.getVar()))
    return getDerived()->traverseIdentifier(varDecl.getType());
  return false;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseLValueIdent(const LValueIdent &lValue) const {
  return getDerived()->traverseIdentifier(lValue.getVar());
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseLValue(const LValue &lValue) const {
  switch (lValue.getKind()) {
  case LValue::Kind::LValueIdent:
    return getDerived()->traverseLValueIdent(
        STATIC_REF_CAST(LValueIdent, lValue));
  case LValue::Kind::VarDecl:
    return getDerived()->traverseVarDecl(STATIC_REF_CAST(VarDecl, lValue));
  case LValue::Kind::MemberAccess:
    return getDerived()->traverseMemberAccess(
        STATIC_REF_CAST(MemberAccess, lValue));
  default:
    return true;
  }
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseCompoundStmt(
    const CompoundStmt &compoundStmt) const {
  /// stmt a unique_ptr to a statement
  for (const auto &stmt : compoundStmt)
    if (!getDerived()->traverseStatement(stmt))
      return false;

  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseAssignment(
    const Assignment &assignment) const {
  if (getDerived()->traverseLValue(assignment.getLeftHandSide()))
    return getDerived()->traverseExpression(assignment.getRightHandSide());
  return false;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseValueStmt(const ValueStmt &valueStmt) const {
  return getDerived()->traverseExpression(valueStmt.getExpr());
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseReturn(const Return &returnStmt) const {
  if (returnStmt.getRetVal() != nullptr)
    return getDerived()->traverseExpression(*returnStmt.getRetVal());
  return true;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseIf(const If &ifStmt) const {
  if (getDerived()->traverseExpression(ifStmt.getCond())) {
    if (getDerived()->traverseCompoundStmt(ifStmt.getIfBlock())) {
      if (ifStmt.getElseBlock() != nullptr) {
        if (getDerived()->traverseCompoundStmt(*ifStmt.getElseBlock()))
          return true;
        else
          return false;
      }
      return true;
    }
  }
  return false;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseWhile(const While &whileStmt) const {
  if (getDerived()->traverseExpression(whileStmt.getCond())) {
    if (getDerived()->traverseCompoundStmt(whileStmt.getBlock())) {
      return true;
    }
  }
  return false;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseBinaryOperator(
    const BinaryOperator &binaryOperator) const {
  if (traverseExpression(binaryOperator.getLHS()))
    return getDerived()->traverseExpression(binaryOperator.getRHS());
  return false;
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseMemberAccess(
    const MemberAccess &memAccess) const {
  return traverseExpression(memAccess.getMember());
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseExpression(
    const Expression &expression) const {
  switch (expression.getKind()) {
  case Expression::Kind::BinaryOperator:
    return getDerived()->traverseBinaryOperator(
        STATIC_REF_CAST(BinaryOperator, expression));
  case Expression::Kind::LValue:
    return traverseLValue(STATIC_REF_CAST(LValue, expression));
  case Expression::Kind::Identifier:
    return getDerived()->traverseIdentifier(
        STATIC_REF_CAST(Identifier, expression));
  case Expression::Kind::IntegerLiteral:
    return getDerived()->traverseIntegerLiteral(
        STATIC_REF_CAST(IntegerLiteral, expression));
  case Expression::Kind::FloatLiteral:
    return getDerived()->traverseFloatLiteral(
        STATIC_REF_CAST(FloatLiteral, expression));
  case Expression::Kind::BoolLiteral:
    return getDerived()->traverseBoolLiteral(
        STATIC_REF_CAST(BoolLiteral, expression));
  case Expression::Kind::StringLiteral:
    return getDerived()->traverseStringLiteral(
        STATIC_REF_CAST(StringLiteral, expression));
  case Expression::Kind::Call:
    return getDerived()->traverseCall(STATIC_REF_CAST(Call, expression));
  default:
    return false;
  }
}

template <typename Derived>
bool ASTVisitor<Derived>::traverseStatement(const Statement &statement) const {
  switch (statement.getKind()) {
  case Statement::Kind::Assignment:
    return getDerived()->traverseAssignment(
        STATIC_REF_CAST(Assignment, statement));
  case Statement::Kind::ValueStmt:
    return getDerived()->traverseValueStmt(
        STATIC_REF_CAST(ValueStmt, statement));
  case Statement::Kind::Return:
    return getDerived()->traverseReturn(STATIC_REF_CAST(Return, statement));
  case Statement::Kind::If:
    return getDerived()->traverseIf(STATIC_REF_CAST(If, statement));
  case Statement::Kind::While:
    return getDerived()->traverseWhile(STATIC_REF_CAST(While, statement));
  default:
    return false;
  }
}

} // namespace quack::ast

#endif // QUACK_ASTVISITOR_HPP
