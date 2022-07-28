//
// Created by parsab on 6/14/22.
//

#include "Environment.hpp"

using namespace llvm;

namespace quack {

namespace sema {

bool Env::isInCurrentScope(StringRef name) const { return back().count(name); }

bool Env::contains(StringRef name) const {
  for (auto it = this->rbegin(); it != this->rend(); it++)
    if (it->count(name))
      return true;
  return false;
}

type::QType *Env::lookup(StringRef name) const {
  for (auto it = this->rbegin(); it != this->rend(); it++)
    if (auto t = it->lookup(name))
      return t;
  return nullptr;
}

Scope Scope::And(const Scope &other) {
  Scope s;
  for (auto [k, t1] : *this) {
    if (auto *t2 = other.lookup(k)) {
      // If the types are the same or if there is a common ancestor,
      // insert it to the 'and' scope
      if (t1 == t2)
        s.insert({k, t1});
      else if (auto lca = t1->lowestCommonAncestor(t2))
        s.insert({k, lca});
    }
  }
  return s;
}

/// Merges scope s with the current scope
bool Env::mergeScope(const Scope &s) {
  auto &curScope = back();
  for (auto [k, t1] : s) {
    if (auto t2 = curScope.lookup(k)) {
      if (t2 != t1 && !t1->isDescendentOf(t2))
        return false;
    } else {
      curScope.insert({k, t1});
    }
  }
  return true;
}

} // namespace sema

} // namespace quack