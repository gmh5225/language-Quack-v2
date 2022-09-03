//
// Created by Parsa Bagheri on 9/2/20.
//

#include "AST.hpp"

namespace quick::ast {

bool CompoundStmt::hasReturn() const {
  for (auto &stmt : *this) {
    // Checking if Compound statement has a return
    if (stmt->getKind() == Statement::Kind::Return)
      return true;

    // Checking if all paths of an If statement return
    if (stmt->getKind() == Statement::Kind::If) {
      auto *ifStmt = static_cast<If *>(stmt.get());
      if (!ifStmt->getElseBlock())
        continue;
      if (ifStmt->getIfBlock().hasReturn() &&
          ifStmt->getElseBlock()->hasReturn())
        return true;
    }
  }
  return false;
}

} // namespace quick::ast