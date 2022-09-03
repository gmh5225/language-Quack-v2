//
// Created by parsab on 8/25/22.
//

#ifndef QUICK_QUICKTOKENIZER_HPP
#define QUICK_QUICKTOKENIZER_HPP

#include <fstream>
#include <queue>
#include <string>

#include "Location.hpp"
#include "Utils.hpp"

namespace quick::frontend {

enum class TOKEN : int {
  ERR = -2,
  END_OF_FILE = -1,

  // single char tokens
  CURLY_OPEN = '{',
  CURLY_CLOSE = '}',
  PAREN_OPEN = '(',
  PAREN_CLOSE = ')',
  COMMA = ',',
  COLON = ';',
  DOT = '.',
  PLUS = '+',
  MINUS = '-',
  STAR = '*',
  SLASH = '/',
  PERCENT = '%',
  LESS = '<',
  MORE = '>',
  ASSIGN = '=',
  NOT = '!',

  // multi char tokens
  STRING = 256,
  INT,
  FLOAT,
  PLUS_EQUAL,
  MINUS_EQUAL,
  STAR_EQUAL,
  SLASH_EQUAL,
  PERCENT_EQUAL,
  LESS_EQUAL,
  MORE_EQUAL,
  EQUAL,
  NOT_EQUAL,
  AND,
  OR,
  IF,
  ELSE,
  ELIF,
  WHILE,
  RETURN,
  PRINT,
  TRUE,
  FALSE,
  IDENT
};

// TODO improver perf
std::string getTokName(TOKEN tok);

class QuickTokenizer {
  char lastChar = ' ';
  std::string buffer;
  std::fstream &file;
  Location curTokLoc;
  std::queue<Location> prevTokLocs;
  const unsigned numLookaheads;

  void getNextCharUpdateLocFrom();
  void getNextCharUpdateLocTo();
  void eatWhiteSpace();
  void eatLine();
  TOKEN parseNumericToken();
  TOKEN parseIdentToken();

public:
  explicit QuickTokenizer(std::fstream &file, unsigned numLookaheads = 1)
      : file(file), curTokLoc(1, 1, 1, 1), numLookaheads(numLookaheads) {}

  const std::string &getBuffer() { return buffer; }
  const Location &getLoc() { return curTokLoc; }
  TOKEN getNextToken();
  bool rollBackToken();
  bool rollBackToken(unsigned n);
};

} // namespace quick::frontend

#endif // QUICK_QUICKTOKENIZER_HPP
