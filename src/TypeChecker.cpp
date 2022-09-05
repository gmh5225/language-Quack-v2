//
// Created by parsab on 6/12/22.
//

#include "TypeChecker.hpp"
#include "ClassVerifier.hpp"
#include "StmtVerifier.hpp"

namespace quick {
namespace sema {

bool TypeChecker::verify() {
  Env environment;
  int numErrors = 0;
  auto &tdb = type::QTypeDB::get();

  // Registering all classes
  for (auto &clss : tu.getClasses()) {
    auto &className = clss->getClassIdent().getName();
    if (tdb.getType(className)) {
      logError(file, clss->getClassIdent().getLocation(),
               "redefinition of class <" + className + ">");
      return false;
    }

    auto super = clss->getSuper();
    type::QType *superType = nullptr;
    if (super) {
      auto &superName = super->getName();
      superType = tdb.getType(superName);
      if (!superType) {
        logError(file, clss->getSuper()->getLocation(),
                 "type not found <" + superName + ">");
        return false;
      }
    } else {
      superType = tdb.getType("Object");
    }

    assert(superType);
    tdb.registerNewType(className, superType);
  }

  // Checking classes
  for (auto &clss : tu.getClasses()) {
    ClassVerifier cv(file, *clss);
    if (!cv.verify())
      numErrors++;
  }

  // Checking main
  StmtVerifier stmtTypeChecker(tu.getCompoundStmt(), environment, nullptr,
                               tdb.getIntegerType());
  if (!stmtTypeChecker.isLegal())
    numErrors++;

  if (!numErrors)
    return true;

  std::cerr << "total errors: " << numErrors << "\n";
  return false;
}

} // namespace sema
} // namespace quick