//
// Created by Parsa Bagheri on 3/26/21.
//

#include "Utils.hpp"

#include <algorithm>

namespace quack {

static void logError(const std::string &message, const std::string &location) {
  std::cerr << "error: " << location << message << "\n\n";
}

void logError(const ast::ASTNode &node, const std::string &message) {
  logError(message, "@" + node.getLocation().toString() + ": ");
}

void logError(const std::string &message) { logError(message, ""); }

} // namespace quack