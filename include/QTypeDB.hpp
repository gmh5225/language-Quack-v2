//
// Created by parsab on 6/12/22.
//

#ifndef QUACK_QTYPEDB_HPP
#define QUACK_QTYPEDB_HPP

#include "QType.hpp"
#include "LLVMType.hpp"

namespace quick::type {

/// ===-------------------------------------------------------------------=== //
/// All Quick types are registered in this singleton
/// ===-------------------------------------------------------------------=== //
class QTypeDB : public std::unordered_map<std::string, std::unique_ptr<QType>> {
  QTypeDB();

public:
  QTypeDB &operator=(const QType &) = delete;
  QTypeDB(const QTypeDB &) = delete;

  static QTypeDB &get() {
    static QTypeDB db;
    return db;
  }

  /// Adds a new type to the data base
  QType *registerNewType(const std::string &name, QType *parent);

  /// Builtin types
  QType *getObjectType() const;
  QType *getIntegerType() const;
  QType *getFloatType() const;
  QType *getBoolType() const;
  QType *getStringType() const;
  QType *getNothingType() const;

  QType *getType(llvm::StringRef) const;

  std::unique_ptr<json::JSONNode> toJson();
};

} // namespace quick::type
#endif // QUACK_QTYPEDB_HPP
