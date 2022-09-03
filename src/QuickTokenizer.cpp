//
// Created by parsab on 8/28/22.
//

#include "QuickTokenizer.hpp"

#define HANDLE_WITH_AND_WITHOUT_EQUAL_SYM(TOK, ELSE_TOK)                       \
  do {                                                                         \
    if (file.peek() == '=') {                                                  \
      getNextCharUpdateLocTo();                                                \
      return TOK;                                                              \
    }                                                                          \
    return ELSE_TOK;                                                           \
  } while (false)

#define HANDLE_WITH_EQUAL_SYM(TOK)                                             \
  HANDLE_WITH_AND_WITHOUT_EQUAL_SYM(TOK##_EQUAL, TOK)

namespace quick::frontend {

std::string getTokName(TOKEN tok) {
  switch (tok) {
  case TOKEN::CURLY_OPEN:
    return "{";
  case TOKEN::CURLY_CLOSE:
    return "}";
  case TOKEN::PAREN_OPEN:
    return "(";
  case TOKEN::PAREN_CLOSE:
    return ")";
  case TOKEN::COMMA:
    return ",";
  case TOKEN::COLON:
    return ";";
  case TOKEN::DOT:
    return ".";
  case TOKEN::PLUS:
    return "+";
  case TOKEN::PLUS_EQUAL:
    return "+=";
  case TOKEN::MINUS:
    return "-";
  case TOKEN::MINUS_EQUAL:
    return "-=";
  case TOKEN::STAR:
    return "*";
  case TOKEN::STAR_EQUAL:
    return "*=";
  case TOKEN::SLASH:
    return "/";
  case TOKEN::SLASH_EQUAL:
    return "/=";
  case TOKEN::PERCENT:
    return "%";
  case TOKEN::PERCENT_EQUAL:
    return "%=";
  case TOKEN::LESS:
    return "<";
  case TOKEN::LESS_EQUAL:
    return "<=";
  case TOKEN::MORE:
    return ">";
  case TOKEN::MORE_EQUAL:
    return ">=";
  case TOKEN::ASSIGN:
    return "=";
  case TOKEN::EQUAL:
    return "==";
  case TOKEN::NOT:
    return "!";
  case TOKEN::NOT_EQUAL:
    return "!=";
  case TOKEN::ERR:
    return "ERROR";
  case TOKEN::END_OF_FILE:
    return "EOF";
  case TOKEN::STRING:
    return "STRING";
  case TOKEN::INT:
    return "INT";
  case TOKEN::FLOAT:
    return "FLOAT";
  case TOKEN::AND:
    return "and";
  case TOKEN::OR:
    return "or";
  case TOKEN::IF:
    return "if";
  case TOKEN::ELSE:
    return "else";
  case TOKEN::ELIF:
    return "elif";
  case TOKEN::WHILE:
    return "while";
  case TOKEN::RETURN:
    return "return";
  case TOKEN::PRINT:
    return "print";
  case TOKEN::TRUE:
    return "True";
  case TOKEN::FALSE:
    return "False";
  case TOKEN::IDENT:
    return "IDENT";
  }
}

void QuickTokenizer::getNextCharUpdateLocFrom() {
  file.get(lastChar);
  if (lastChar == '\n') {
    curTokLoc.l_from++;
    curTokLoc.c_from = 1;
  } else
    curTokLoc.c_from++;
  curTokLoc.l_to = curTokLoc.l_from;
  curTokLoc.c_to = curTokLoc.c_from;
  curTokLoc.pos++;
}

void QuickTokenizer::getNextCharUpdateLocTo() {
  file.get(lastChar);
  if (lastChar == '\n') {
    curTokLoc.l_to++;
    curTokLoc.c_to = 1;
  } else
    curTokLoc.c_to++;
  curTokLoc.len++;
}

void QuickTokenizer::eatWhiteSpace() {
  // eat white spaces
  while (!file.eof()) {
    if (!std::isspace(file.peek()))
      break;
    getNextCharUpdateLocFrom();
  }
}

void QuickTokenizer::eatLine() {
  getNextCharUpdateLocFrom();
  while (!file.eof()) {
    getNextCharUpdateLocFrom();
    if (lastChar == '\n')
      break;
  }
}

TOKEN QuickTokenizer::parseNumericToken() {
  // parsing integer/float
  auto parseDigit = [this]() {
    do {
      buffer += lastChar;
      if (std::isdigit(file.peek()))
        getNextCharUpdateLocTo();
      else
        break;
    } while (!file.eof());
  };

  parseDigit();
  if (file.peek() == '.') {
    getNextCharUpdateLocTo();
    if (std::isdigit(file.peek())) {
      // float
      parseDigit();
      return TOKEN::FLOAT;
    } else {
      if (file.eof())
        logError(file, curTokLoc, "Tokenizer: expected digit but got 'EOF'");
      else
        logError(file, curTokLoc,
                 std::string("Tokenizer: expected digit but got '") +
                     char(file.peek()) + "'");
      return TOKEN::ERR;
    }
  }
  return TOKEN::INT;
}

TOKEN QuickTokenizer::parseIdentToken() {
  // parsing integer/float
  while (true) {
    buffer += lastChar;
    char c = file.peek();
    if (std::isalnum(c) || c == '_' || c == '-')
      getNextCharUpdateLocTo();
    else
      break;
  }

  // Keywords
  if (buffer == "True") {
    return TOKEN::TRUE;
  } else if (buffer == "False") {
    return TOKEN::FALSE;
  } else if (buffer == "return") {
    return TOKEN::RETURN;
  } else if (buffer == "if") {
    return TOKEN::IF;
  } else if (buffer == "elif") {
    return TOKEN::ELIF;
  } else if (buffer == "else") {
    return TOKEN::ELSE;
  } else if (buffer == "not") {
    return TOKEN::NOT;
  } else if (buffer == "and") {
    return TOKEN::AND;
  } else if (buffer == "or") {
    return TOKEN::OR;
  } else if (buffer == "print") {
    return TOKEN::PRINT;
  }
  return TOKEN::IDENT;
}

TOKEN QuickTokenizer::getNextToken() {
  // keeping track of the location of previous token
  if (prevTokLocs.size() == numLookaheads)
    prevTokLocs.pop();

  buffer.clear();
  curTokLoc.len = 0;

  while (true) {
    // updating current tokens location
    curTokLoc.l_from = curTokLoc.l_to;
    curTokLoc.c_from = curTokLoc.c_to;

    eatWhiteSpace();

    if (file.eof())
      return TOKEN::END_OF_FILE;

    prevTokLocs.push(curTokLoc);

    getNextCharUpdateLocTo();
    if (std::isdigit(lastChar)) {
      return parseNumericToken();
    } else if (std::isalpha(lastChar) || lastChar == '_' || lastChar == '-') {
      // parsing keyword/identifier
      return parseIdentToken();
    } else {
      switch (lastChar) {
      case ';':
      case '{':
      case '}':
      case '(':
      case ')':
      case ':':
      case ',':
      case '.':
        return TOKEN(lastChar);
      case '=':
        HANDLE_WITH_AND_WITHOUT_EQUAL_SYM(TOKEN::EQUAL, TOKEN::ASSIGN);
      case '!':
        HANDLE_WITH_EQUAL_SYM(TOKEN::NOT);
      case '<':
        HANDLE_WITH_EQUAL_SYM(TOKEN::LESS);
      case '>':
        HANDLE_WITH_EQUAL_SYM(TOKEN::MORE);
      case '+':
        HANDLE_WITH_EQUAL_SYM(TOKEN::PLUS);
      case '*':
        HANDLE_WITH_EQUAL_SYM(TOKEN::STAR);
      case '/': {
        if (file.peek() == '/') { // Comment
          eatLine();
          prevTokLocs.pop(); // oops!
          continue;
        }
        HANDLE_WITH_EQUAL_SYM(TOKEN::SLASH);
      }
      case '-':
        HANDLE_WITH_EQUAL_SYM(TOKEN::MINUS);
      case '%':
        HANDLE_WITH_EQUAL_SYM(TOKEN::PERCENT);
      default:
        logError(file, curTokLoc,
                 std::string("Tokenizer: unexpected character '") + lastChar +
                     '"');
        return TOKEN::ERR;
      }
    }
  }
}

bool QuickTokenizer::rollBackToken() {
  buffer.clear();
  if (prevTokLocs.empty())
    return false;

  curTokLoc = prevTokLocs.back();
  prevTokLocs.pop();
  return true;
}

bool QuickTokenizer::rollBackToken(unsigned n) {
  while(n > 0) {
    if (!rollBackToken())
      return false;
    n--;
  }
  return true;
}

} // namespace quick::frontend