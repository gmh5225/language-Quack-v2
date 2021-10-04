//
// Created by Parsa Bagheri on 9/9/20.
//

#ifndef QUACK_PRINTVISITOR_HPP
#define QUACK_PRINTVISITOR_HPP

#include "AST.hpp"
#include "ASTNodes.def"
#include "ASTVisitor.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

namespace quack::ast {
class PrintVisitor : public ASTVisitor<PrintVisitor> {
  mutable unsigned _level;

  enum class IndentationType {
    DiagBar,/// " `"
    VertBar,/// " |"
    Space,  /// "  "
    HorzBar /// " -"
  };

  std::unordered_map<IndentationType,
                     const char *>
      _indentationTypeLookUp{{IndentationType::DiagBar, " \u2514"},/// unicode box drawing characters
                             {IndentationType::VertBar, " \u2502"},
                             {IndentationType::HorzBar, "\u2500"},
                             {IndentationType::Space, "  "}};

  mutable std::vector<IndentationType> _indentation;

  inline void indent(IndentationType indentationType) const {
    if (!_indentation.empty() && _indentation.back() == IndentationType::DiagBar) {
      if (_indentation.back() == IndentationType::DiagBar) {
        _indentation.pop_back();
        _indentation.push_back(IndentationType::Space);
      }
    }
    _indentation.push_back(indentationType);
  }

  inline void dedent() const {
    if (!_indentation.empty()) {
      _indentation.pop_back();
    }
  }

  /// prints string to out stream
  void emit(const std::string &str) const {
    for (const auto i : _indentation) {
      std::cout << _indentationTypeLookUp.at(i);
    }
    std::cout << _indentationTypeLookUp.at(IndentationType::HorzBar) << str;
  }

  void emitln(const std::string &str) const {
    emit(str);
    std::cout << std::endl;
  }

public:
  explicit PrintVisitor(const TranslationUnit &translationUnit)
      : ASTVisitor<PrintVisitor>(translationUnit), _level(0), _indentation() {}

  bool traverseTranslationUnit(const TranslationUnit &translationUnit) const override;

  bool traverseIntegerLiteral(const IntegerLiteral &integerLiteral) const override;

  bool traverseFloatLiteral(const FloatLiteral &floatLiteral) const override;

  bool traverseBoolLiteral(const BoolLiteral &boolLiteral) const override;

  bool traverseStringLiteral(const StringLiteral &stringLiteral) const override;

  bool traverseIdentifier(const Identifier &identifier) const override;

  bool traverseVarDecl(const VarDecl &varDecl) const override;

  bool traverseLValueIdent(const LValueIdent &lValue) const override;

  bool traverseCompoundStmt(const CompoundStmt &compoundStmt) const override;

  bool traverseAssignment(const Assignment &assignment) const override;

  bool traverseValueStmt(const ValueStmt &valueStmt) const override;

  bool traverseBinaryOperator(const BinaryOperator &binaryOperator) const override;

  bool traverseReturn(const Return &) const override;

  bool traverseIf(const If &) const override;

  bool traverseWhile(const While &) const override;

  bool traverseCall(const Call &) const override;
};

}// namespace quack::ast
#endif//QUACK_PRINTVISITOR_HPP
