//
// Created by parsab on 8/28/22.
//

/// TODO: make a recursive descent parser

#ifndef QUICK_QUICKPARSER_HPP
#define QUICK_QUICKPARSER_HPP

#include "AST.hpp"
#include "QuickTokenizer.hpp"

namespace quick::frontend {

//using namespace quick::ast;
//
//class QuickParser {
//  QuickTokenizer tokenizer;
//  std::fstream &file;
//  const std::string &fileName;
//
//  /// Sequence<T> := T
//  ///             | T , Sequence<T>
//  template<typename T>
//  std::unique_ptr<Sequence<T>> parseExpressionSequence() {
//    auto seq = std::make_unique<Sequence<T>>();
//    do {
//
//      auto tok = tokenizer.getNextToken();
//      if (tok == TOKEN::COLON)
//        return seq;
//
//      if (tok == TOKEN::COMMA) {
//
//      }
//
//      auto expr = parseExpression();
//      if (!expr)
//        return nullptr;
//      seq->push_back(std::move(expr));
//    } while (true);
//  }
//
//  std::unique_ptr<Expression> parseExpression() {
//    auto tok = tokenizer.getNextToken();
//    switch (tok) {
//    case TOKEN::PAREN_OPEN: {
//      if (auto expr = parseExpression()) {
//        auto nextTok = tokenizer.getNextToken();
//        if (nextTok == TOKEN::PAREN_CLOSE)
//          return expr;
//
//        logError(file, tokenizer.getLoc(),
//                 std::string("Parser: expected ')' but got '") + getTokName(nextTok));
//        return nullptr;
//      }
//    }
//    case TOKEN::TRUE:
//      return std::make_unique<BoolLiteral>(tokenizer.getLoc(), true);
//    case TOKEN::FALSE:
//      return std::make_unique<BoolLiteral>(tokenizer.getLoc(), false);
//    case TOKEN::INT: {
//      long theInt = std::atoi(tokenizer.getBuffer().c_str());
//      return std::make_unique<IntegerLiteral>(tokenizer.getLoc(), theInt);
//    }
//    case TOKEN::FLOAT: {
//      double theFloat = std::atof(tokenizer.getBuffer().c_str());
//      return std::make_unique<FloatLiteral>(tokenizer.getLoc(), theFloat);
//    }
//    default:
//      logError(file, tokenizer.getLoc(),
//               std::string("Parser: unexpected token ") + getTokName(tok),
//               fileName);
//      return nullptr;
//    }
//  }
//
//
//  /// statement := expression ;
//  ///
//  std::unique_ptr<Statement> parseStatement() {
//    auto tok = tokenizer.getNextToken();
//    switch (tok) {
//    case TOKEN::PRINT: {
//      auto exprSeq = parseExpressionSequence();
//      if (!exprSeq)
//        return nullptr;
//
//      return std::make_unique<PrintStatement>()
//    }
//    }
//  }
//
//  std::unique_ptr<CompoundStmt> parseCompoundStmt() { return nullptr; }
//  std::unique_ptr<TranslationUnit> parseTranslationUnit() { return nullptr; }
//
//public:
//  QuickParser(std::fstream &f, const std::string &fileName)
//      : file(f), tokenizer(f), fileName(fileName) {}
//  std::unique_ptr<ASTNode> parse() { return parseTranslationUnit(); }
//};

} // namespace quick::frontend

#endif // QUICK_QUICKPARSER_HPP
