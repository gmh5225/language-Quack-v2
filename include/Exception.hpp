//
// Created by Parsa Bagheri on 3/23/21.
//

#ifndef QUACK_EXCEPTION_HPP
#define QUACK_EXCEPTION_HPP

#include <exception>

#include "AST.hpp"
#include "Location.hpp"

namespace quack {

using namespace ast;

class QuackException : public std::exception {
  const ASTNode &_node;

public:
  explicit QuackException(const ASTNode &node) : _node(node) {}

  const char *what() const throw() {
    return "exception";
  }
};

}// namespace quack

#endif//QUACK_EXCEPTION_HPP
