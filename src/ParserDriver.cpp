//
// Created by Parsa Bagheri on 9/11/20.
//

#include "ParserDriver.hpp"

namespace quack::parser {

int ParserDriver::parse(const std::string &filename) {
  _curFile = filename;
  _location.initialize(&_curFile);
  _scanBegin();
  yy::parser parser(*this);
#ifdef YYDEBUG
  parser.set_debug_level(_traceParsing);
#endif// YYDEBUG
  int res = parser.parse();
  _scanEnd();
  return res;
}

/// Defined in Lexer.lpp
//    void ParserDriver::_scanEnd() {}
//    void ParserDriver::_scanBegin() {}

}// namespace quack::parser
