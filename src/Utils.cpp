//
// Created by Parsa Bagheri on 3/26/21.
//

#include "Utils.hpp"

#include <algorithm>

namespace quack {

template <typename K, typename V, typename F>
static bool reverseSearchVector(std::vector<std::map<K, V>> &vec, const K &key,
                                const F &lambda) {
  if (!vec.empty()) {
    for (auto it = vec.rbegin(); it != vec.rend(); it++) {
      auto &map = *it;
      if (map.find(key) == map.end())
        continue;

      lambda(map);

      return true;
    }
  }
  return false;
}

bool isACovariantOfB(const std::string &A, const std::string &B) {
  auto *tdb = TypeDataBase::getTypeDB();
  auto *typeA = tdb->getType(A);

  for (auto curType = typeA; curType != nullptr;
       curType = curType->getSuper()) {
    if (curType->getName() == B)
      return true;
  }

  return false;
}

bool isInEnvironmentStack(EnvironmentStack &envStack, const std::string &var) {
  return reverseSearchVector(envStack, var, [](auto &) {});
}

bool isInScopeStack(ScopeStack &allocaStack, const std::string &var) {
  return reverseSearchVector(allocaStack, var, [](auto &) {});
}

bool getVariableAllocation(ScopeStack &allocaStack, const std::string &var,
                           llvm::Value **alloca) {
  return reverseSearchVector(
      allocaStack, var, [&alloca, &var](auto &map) { *alloca = map[var]; });
}

bool getVariableType(EnvironmentStack &envStack, const std::string &var,
                     Type **type) {
  return reverseSearchVector(envStack, var,
                             [&type, &var](auto &env) { *type = env[var]; });
}

static void logError(const std::string &message, const std::string &location) {
  std::cerr << "error: " << location << message << "\n\n";
}

void logError(const ast::ASTNode &node, const std::string &message) {
  logError(message, "@" + node.getLocation().toString() + ": ");
}

void logError(const std::string &message) { logError(message, ""); }

bool hasBuiltInTypes(Types &types) {
  if (types.find("Int") == types.end() || types.find("Float") == types.end() ||
      types.find("Bool") == types.end()) {
    return false;
  }

  return true;
}

bool isSpecialTypeAssignment(TypeInfo *a, TypeInfo *b, Types &types) {
  if (!hasBuiltInTypes(types))
    return false;

  // special cases
  if ((*a == types.at("Float") && *b == types.at("Int")) ||
      (*b == types.at("Float") && *a == types.at("Int"))) {
    return true;
  }

  return false;
}

Type *getCommonParentType(Type *a, Type *b) {
  if (a->getName() == b->getName())
    return a;

  auto *tdb = TypeDataBase::getTypeDB();
  // special cases
  if ((a == tdb->getType("Float") && b == tdb->getType("Int")) ||
      (b == tdb->getType("Float") && a == tdb->getType("Int")))
    return tdb->getType("Float");

  return b;
}

void getIntersectionOf(Environment &a, Environment &b,
                       Environment &intersection) {
  auto &shorter = a.size() < b.size() ? a : b;
  auto &longer = a.size() >= b.size() ? a : b;

  for (auto &it : shorter) {
    if (longer.find(it.first) != longer.end()) {
      intersection.insert(
          {it.first, getCommonParentType(it.second, longer[it.first])});
    }
  }
}

void getUnionOf(Environment &a, Environment &b) {
  for (auto &it : b) {
    if (a.find(it.first) == a.end()) {
      a.insert({it.first, it.second});
    }
  }
}

} // namespace quack