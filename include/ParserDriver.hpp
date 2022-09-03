//
// Created by Parsa Bagheri on 9/11/20.
//

#ifndef QUACK_PARSERDRIVER_HPP
#define QUACK_PARSERDRIVER_HPP

#include "AST.hpp"
#include "Parser.hpp"

#include <memory>

namespace quick::parser {
class ParserDriver;
}

#define YY_DECL yy::parser::symbol_type yylex(quick::parser::ParserDriver &drv)
YY_DECL;

using namespace quick::ast;

namespace quick::parser {
class ParserDriver {

  friend yy::parser;

  std::unique_ptr<TranslationUnit> _root;

  /// The token's location used by the scanner.
  yy::location _location;

  /// The name of the file being parsed.
  std::string _curFile;

  /// Whether to generate parser debug traces.
  bool _traceParsing;
  /// Whether to generate scanner debug traces.
  bool _traceScanning;

  /// Handling the scanner.
  void _scanBegin();
  void _scanEnd();

public:
  explicit ParserDriver(bool traceParsing = false, bool traceScanning = false) : _traceParsing(traceParsing), _traceScanning(traceScanning) {}

  int parse(const std::string &filename);

  void setRoot(std::unique_ptr<TranslationUnit> root) { _root = std::move(root); }
  TranslationUnit &getRoot() { return *_root; }

  void setTraceParsing(bool traceParsing) { _traceParsing = traceParsing; }
  bool getTraceParsing() const { return _traceParsing; }

  void setTraceScanning(bool traceScanning) { _traceScanning = traceScanning; }
  bool getTraceScanning() const { return _traceScanning; }

  yy::location &getLocation() { return _location; }
};
}// namespace quick::parser

#endif//QUACK_PARSERDRIVER_HPP
