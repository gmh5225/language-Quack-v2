//
// Created by parsab on 6/14/22.
//

#include "Environment.hpp"

namespace quick::sema {

Scope And(const Scope &first, const Scope &other) {
  Scope s;
  for (const auto &[k, t1] : first) {
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

} // namespace quick::sema