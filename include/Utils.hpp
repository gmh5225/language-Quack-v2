//
// Created by Parsa Bagheri on 3/26/21.
//

#ifndef QUACK_UTILS_HPP
#define QUACK_UTILS_HPP

#include <map>
#include <string>
#include <vector>

#include "llvm/IR/IRBuilder.h"

#include "AST.hpp"

namespace quack {

void logError(const ast::ASTNode &, const std::string &message);
void logError(const std::string &message);

} // namespace quack

#endif // QUACK_UTILS_HPP
