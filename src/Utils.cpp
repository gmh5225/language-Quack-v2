//
// Created by Parsa Bagheri on 3/26/21.
//

#include "Utils.hpp"

#include <fstream>
#include <algorithm>

namespace quick {

void logError(std::fstream &file, const frontend::Location &loc, const std::string &message, const std::string &fname) {
  auto curPos = file.tellg();
  file.clear();
  file.seekg(0);
  int curLine = 1;
  for(; curLine < loc.l_from && !file.eof(); curLine++)
    file.ignore(std::numeric_limits<int>::max(), '\n');

  std::string line;

  std::cerr << fname << ": " << loc.toString() << ": " << message << std::endl;
  for(;curLine < loc.l_to + 1 && !file.eof(); curLine++) {
    std::getline(file, line);
    std::cerr << "    " << curLine << ")    " << line;
  }

  std::cerr << "\n\n";
  file.clear();
  file.seekg(curPos);
}

static void logError(const std::string &message, const std::string &location) {
  std::cerr << "error: " << location << message << "\n\n";
}

void logError(const ast::ASTNode &node, const std::string &message) {
  logError(message, "@" + node.getLocation().toString() + ": ");
}

void logError(const std::string &message) { logError(message, ""); }

} // namespace quick