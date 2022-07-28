//
// Created by parsab on 6/14/22.
//

#ifndef QUACK_FNTYPECHECKER_H
#define QUACK_FNTYPECHECKER_H

#include "EnvironmentBuilder.hpp"

namespace quack {
namespace sema {

class StmtTypeChecker : public EnvironmentBuilder<StmtTypeChecker> {
public:
  StmtTypeChecker(const CompoundStmt &cmpStmt, type::QTypeDB &typedb,
                  type::QType *parentType = nullptr,
                  type::QType *returnType = nullptr, bool isConstructor = false)
      : EnvironmentBuilder<StmtTypeChecker>(cmpStmt, typedb, parentType, returnType,
                           isConstructor) {}

#define STMT_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &);
#include "ASTNodes.def"

  bool isLegal() { return visitCompoundStmt(fnBody); }
};

} // namespace sema
} // namespace quack
#endif // QUACK_FNTYPECHECKER_H
