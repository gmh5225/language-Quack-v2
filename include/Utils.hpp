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

namespace quick {

void logError(std::fstream &file, const frontend::Location &loc,
              const std::string &message,
              const std::string &fname = "<unknown-file>");
void logError(const ast::ASTNode &, const std::string &message);
void logError(const std::string &message);

} // namespace quick

#endif // QUACK_UTILS_HPP
