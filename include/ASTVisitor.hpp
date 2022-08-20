//
// Created by Parsa Bagheri on 9/9/20.
//

#ifndef QUACK_ASTVISITOR_HPP
#define QUACK_ASTVISITOR_HPP

#include "AST.hpp"

namespace quack::ast {

/// ASTVisitor interface declares static dispatch methods for visiting each node
/// of the AST
template <typename Derived, typename RetType, typename... Args>
class ASTVisitor {
  inline Derived *getDerived() { return static_cast<Derived *>(this); }

public:
/// Default node handler, defines visitors for every node and returns default
/// RetType
#define NODE_HANDLER(NODE)                                                     \
  RetType visit##NODE(const NODE &node, Args &&...args) { return RetType(); }
#include "ASTNodes.def"

/// Dispatches to derived classes method
#define DISPATCH(NODE, OBJ)                                                    \
  return getDerived()->visit##NODE(static_cast<const NODE &>((OBJ)),           \
                                   std::forward<Args>(args)...)

  /// Abstract node handlers that dispatch to concrete subtype in the AST
  RetType visitLValue(const LValue &lValue, Args &&...args) {
    switch (lValue.getKind()) {
    case LValue::Kind::LValueIdent:
      DISPATCH(LValueIdent, lValue);
    case LValue::Kind::MemberAccess:
      DISPATCH(MemberAccess, lValue);
    default:
      return RetType();
    }
  }

  RetType visitExpression(const Expression &expression, Args &&...args) {
    switch (expression.getKind()) {
    case Expression::Kind::BinaryOperator:
      DISPATCH(BinaryOperator, expression);
    case Expression::Kind::UnaryOperator:
      DISPATCH(UnaryOperator, expression);
    case Expression::Kind::LValue:
      return visitLValue(static_cast<const LValue &>(expression),
                         std::forward<Args>(args)...);
    case Expression::Kind::IntegerLiteral:
      DISPATCH(IntegerLiteral, expression);
    case Expression::Kind::FloatLiteral:
      DISPATCH(FloatLiteral, expression);
    case Expression::Kind::BoolLiteral:
      DISPATCH(BoolLiteral, expression);
    case Expression::Kind::StringLiteral:
      DISPATCH(StringLiteral, expression);
    case Expression::Kind::Call:
      DISPATCH(Call, expression);
    default:
      return RetType();
    }
  }

  RetType visitStatement(const Statement &statement, Args &&...args) {
    switch (statement.getKind()) {
    case Statement::Kind::Assignment:
      DISPATCH(Assignment, statement);
    case Statement::Kind::StaticAssignment:
      DISPATCH(StaticAssignment, statement);
    case Statement::Kind::ValueStmt:
      DISPATCH(ValueStmt, statement);
    case Statement::Kind::Return:
      DISPATCH(Return, statement);
    case Statement::Kind::If:
      DISPATCH(If, statement);
    case Statement::Kind::While:
      DISPATCH(While, statement);
    case Statement::Kind::Print:
      DISPATCH(PrintStatement, statement);
    default:
      return RetType();
    }
  }
}; // ASTVisitor

} // namespace quack::ast

#endif // QUACK_ASTVISITOR_HPP
