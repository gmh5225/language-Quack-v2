//
// Created by parsab on 9/3/22.
//

#ifndef QUICK_CLASSVERIFIER_HPP
#define QUICK_CLASSVERIFIER_HPP

#include "EnvironmentBuilder.hpp"

namespace quick {
namespace sema {

/// ===-------------------------------------------------------------------=== //
/// ClassVerifier - A visitor that visits every class and verifies
/// their legality
/// ===-------------------------------------------------------------------=== //
class ClassVerifier : public ASTVisitor<ClassVerifier, bool> {
  std::fstream &file;
  const Class &theClass;
  type::QTypeDB &tdb;

  bool isSuperInitialized(const std::string &);
  bool verifyConstructor();
  bool hasRecursiveConstructor();

public:
  ClassVerifier(std::fstream &file, const Class &theClass)
      : file(file), theClass(theClass), tdb(type::QTypeDB::get()) {}

  // only visits classes/methods
  bool visitMethod(const ast::Method &);
  bool visitMethods(const ast::Methods &);
  bool visitClass(const ast::Class &);
  bool visitExpression(const ast::Expression &) = delete;
#define EXPR_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &) = delete;
#define STMT_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &) = delete;
#include "ASTNodes.def"

  bool verify();
};

} // namespace sema
} // namespace quick

#endif // QUICK_CLASSVERIFIER_HPP
