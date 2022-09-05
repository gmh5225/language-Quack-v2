//
// Created by parsab on 6/12/22.
//

#ifndef QUACK_TYPECHECKER_HPP
#define QUACK_TYPECHECKER_HPP

#include "ASTVisitor.hpp"
#include "EnvironmentBuilder.hpp"
#include "QTypeDB.hpp"

namespace quick {
namespace sema {

class TypeChecker {
  std::fstream &file;
  const ast::TranslationUnit &tu;

public:
  TypeChecker(std::fstream &f, const ast::TranslationUnit &tu) : file(f), tu(tu) {}
  bool verify();
};

} // namespace sema
} // namespace quick

#endif // QUACK_TYPECHECKER_HPP
