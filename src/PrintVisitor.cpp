//
// Created by Parsa Bagheri on 9/9/20.
//

#include "PrintVisitor.hpp"
#include "AST.hpp"

namespace quack::ast {

bool PrintVisitor::traverseTranslationUnit(const TranslationUnit &translationUnit) const {
  emitln("TranslationUnit ");
  indent(IndentationType::DiagBar);
  auto retVal = traverseCompoundStmt(translationUnit.getCompoundStmt());
  dedent();
  return retVal;
}

bool PrintVisitor::traverseIntegerLiteral(const IntegerLiteral &integerLiteral) const {
  emitln("IntegerLiteral "
         "("
         + std::to_string(integerLiteral.getInteger()) + ")");
  return true;
}

bool PrintVisitor::traverseFloatLiteral(const FloatLiteral &floatLiteral) const {
  emitln("FloatLiteral "
         "("
         + std::to_string(floatLiteral.getFloat()) + ")");
  return true;
}

bool PrintVisitor::traverseBoolLiteral(const BoolLiteral &boolLiteral) const {
  emitln("BoolLiteral "
         "("
         + std::to_string(boolLiteral.getBool()) + ")");
  return true;
}

bool PrintVisitor::traverseStringLiteral(const StringLiteral &stringLiteral) const {
  emitln("StringLiteral "
         "("
             + stringLiteral.getText() + ")");
  return true;
}

bool PrintVisitor::traverseIdentifier(const Identifier &identifier) const {
  emitln("Identifier "
         "("
         + identifier.getName() + ")");
  return true;
}

bool PrintVisitor::traverseVarDecl(const VarDecl &varDecl) const {
  emitln("VarDecl ");
  indent(IndentationType::VertBar);
  auto retVal = traverseIdentifier(varDecl.getVar());
  dedent();

  if (retVal) {
    indent(IndentationType::DiagBar);
    retVal = traverseIdentifier(varDecl.getType());
    dedent();
  }
  return retVal;
}

bool PrintVisitor::traverseLValueIdent(const LValueIdent &lValue) const {
  emitln("LValueIdent ");
  indent(IndentationType::DiagBar);
  auto retVal = traverseIdentifier(lValue.getVar());
  dedent();
  return retVal;
}

bool PrintVisitor::traverseCompoundStmt(const CompoundStmt &compoundStmt) const {
  emitln("CompoundStmt ");
  auto retVal = true;
  /// stmt a unique_ptr to a statement
  for (auto stmt = compoundStmt.begin(); stmt != compoundStmt.end(); stmt++) {
    if (retVal) {
      if (stmt == --compoundStmt.end())
        indent(IndentationType::DiagBar);
      else
        indent(IndentationType::VertBar);
      retVal = traverseStatement(*stmt);
      dedent();
    } else
      return false;
  }
  return retVal;
}

bool PrintVisitor::traverseAssignment(const Assignment &assignment) const {
  emitln("Assignment ");
  indent(IndentationType::VertBar);
  auto retval = traverseLValue(assignment.getLeftHandSide());
  dedent();
  indent(IndentationType::DiagBar);
  if (retval) {
    retval = traverseExpression(assignment.getRightHandSide());
  }
  dedent();
  return retval;
}

bool PrintVisitor::traverseValueStmt(const ValueStmt &valueStmt) const {
  emitln("ValueStmt ");
  indent(IndentationType::DiagBar);
  auto retVal = traverseExpression(valueStmt.getExpr());
  dedent();
  return retVal;
}

bool PrintVisitor::traverseBinaryOperator(const BinaryOperator &binaryOperator) const {
  emitln("BinaryOperator "
         "("
         + std::string(binaryOperator
                           .getOpCodeString())
         + ")");
  indent(IndentationType::VertBar);
  auto retVal = traverseExpression(binaryOperator.getRHS());
  dedent();

  if (retVal) {
    indent(IndentationType::DiagBar);
    retVal = traverseExpression(binaryOperator.getLHS());
    dedent();
  }
  return retVal;
}

bool PrintVisitor::traverseReturn(const Return &returnStmt) const {
  emitln("Return ");
  if (returnStmt.getRetVal()) {
    indent(IndentationType::DiagBar);
    auto status = false;
    if (traverseExpression(*(returnStmt.getRetVal())))
      status = true;
    dedent();
    return status;
  }
  return true;
}

bool PrintVisitor::traverseIf(const If &ifStmt) const {
  emitln("If ");
  indent(IndentationType::VertBar);
  emitln("Cond ");
  indent(IndentationType::DiagBar);
  if (traverseExpression(ifStmt.getCond())) {
    dedent();
    if (ifStmt.getElseBlock() != nullptr) {
      dedent();
      indent(IndentationType::VertBar);
    } else {
      dedent();
      indent(IndentationType::DiagBar);
    }
    emitln("Then ");
    indent(IndentationType::DiagBar);

    if (traverseCompoundStmt(ifStmt.getIfBlock())) {
      dedent();
      if (ifStmt.getElseBlock() != nullptr) {
        dedent();
        indent(IndentationType::DiagBar);
        emitln("Else ");
        indent(IndentationType::DiagBar);
        auto status = false;
        if (traverseCompoundStmt(*ifStmt.getElseBlock()))
          status = true;
        dedent();
        dedent();
        return status;
      }
      dedent();
      return true;
    }
  }
  dedent();
  return false;
}

bool PrintVisitor::traverseWhile(const While &whileStmt) const {
  emitln("While ");
  indent(IndentationType::VertBar);
  emitln("Cond ");
  indent(IndentationType::DiagBar);
  if (traverseExpression(whileStmt.getCond())) {
    dedent();
    dedent();
    indent(IndentationType::DiagBar);
    emitln("Block ");
    indent(IndentationType::DiagBar);
    if (traverseCompoundStmt(whileStmt.getBlock())) {
      dedent();
      dedent();
      return true;
    }
  }
  dedent();
  return false;
}

bool PrintVisitor::traverseCall(const Call &call) const {
  /// TODO
  emitln("Call ");
  return true;
}

}// namespace quack::ast