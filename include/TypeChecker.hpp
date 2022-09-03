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
public:
  bool visitTranslationUnit(const ast::TranslationUnit &tu);
};

} // namespace sema
} // namespace quick

#endif // QUACK_TYPECHECKER_HPP
