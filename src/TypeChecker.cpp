//
// Created by parsab on 6/12/22.
//

#include "TypeChecker.hpp"
#include "StmtTypeChecker.h"

namespace quack {
namespace sema {

bool TypeChecker::visitTranslationUnit(const ast::TranslationUnit &tu) {
  Env environment;
  // Checking classes

  // Checking main
  auto &tdb = type::QTypeDB::get();
  StmtTypeChecker stmtTypeChecker(tu.getCompoundStmt(), environment, nullptr,
                                  tdb.getIntegerType());
  if (!stmtTypeChecker.isLegal())
    return false;

  return true;
}

} // namespace sema
} // namespace quack