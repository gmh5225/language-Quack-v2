//
// Created by parsab on 6/14/22.
//

#ifndef QUACK_ENVIRONMENT_HPP
#define QUACK_ENVIRONMENT_HPP

#include "QType.hpp"

namespace quack {
namespace sema {

class Scope : public llvm::DenseMap<llvm::StringRef, quack::type::QType *> {
  Scope(const Scope &) = default;
  Scope &operator=(const Scope &) = default;

public:
  using llvm::DenseMap<llvm::StringRef, quack::type::QType *>::DenseMap;
  Scope(Scope &&) = default;
  Scope &operator=(Scope &&) = default;
  Scope copy() { return *this; }
  /// Intersection with another scope
  Scope And(const Scope &);
};

class Env : public llvm::SmallVector<Scope, 3> {
public:
  Env() {
   // this->push_back(Scope());
  }

  bool isInCurrentScope(llvm::StringRef) const;
  bool contains(llvm::StringRef) const;
  type::QType *lookup(llvm::StringRef) const;

  /// Merges scope s with the current scope
  bool mergeScope(const Scope &);
};

}
}
#endif // QUACK_ENVIRONMENT_HPP
