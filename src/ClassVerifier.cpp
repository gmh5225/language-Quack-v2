//
// Created by parsab on 9/3/22.
//

#include "ClassVerifier.hpp"

namespace quick::sema {

bool ClassVerifier::hasRecursiveConstructor() {
  auto isRecursiveCall = [&](const Call &call) {
    if (auto *identExpr = call.getCallee().as_a<IdentifierExpression>()) {
      if (identExpr->getVar().getName() == this->theClass.getClassIdent().getName())
        return true;
    }
    return false;
  };

  auto &constructor = theClass.getConstructor();
  for (auto &stmt : constructor.getBody()) {
    if (auto valueStmt = stmt->as_a<ValueStmt>()) {
      if (auto call = valueStmt->getExpr().as_a<Call>()) {
        if (isRecursiveCall(*call))
          return true;
      }
    }
  }
  return false;
}

bool ClassVerifier::isSuperInitialized(const std::string &superName) {
  auto isSuperConstructor = [&](const Call &call) {
    if (auto *identExpr = call.getCallee().as_a<IdentifierExpression>()) {
      if (identExpr->getVar().getName() == superName)
        return true;
    }
    return false;
  };

  auto &constructor = theClass.getConstructor();
  for (auto &stmt : constructor.getBody()) {
    if (auto valueStmt = stmt->as_a<ValueStmt>()) {
      if (auto call = valueStmt->getExpr().as_a<Call>()) {
        if (isSuperConstructor(*call))
          return true;
      }
    }
  }
  return false;
}

bool ClassVerifier::verifyConstructor() {
  if (hasRecursiveConstructor()) {
    logError(file, theClass.getConstructor().getLocation(), "recursive type constructor detected");
    return false;
  }

  auto &constructor = theClass.getConstructor();
  if (auto superIdent = theClass.getSuper()) {
    auto &superName = superIdent->getName();
    if (type::isPrimitive(superName)) {
      logError(file, superIdent->getLocation(),
               "cannot inherit from a primitive type");
      return false;
    }

    auto *superType = tdb.getType(superName);
    if (!superType) {
      logError(file, superIdent->getLocation(),
               "type <" + superName + "> not found");
      return false;
    }

    if (superName != "Object") {
      if (!isSuperInitialized(superName)) {
        logError(file, theClass.getConstructor().getLocation(),
                 "super class not initialized");
        return false;
      }
    }
  }

  return true;
}

bool ClassVerifier::visitClass(const ast::Class &clss) {
  if (!verifyConstructor())
    return false;

  return true;
}

bool ClassVerifier::verify() {

  return visitClass(theClass);
}

} // namespace quick::sema