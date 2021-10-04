//
// Created by Parsa Bagheri on 3/29/21.
//

#ifndef QUACK_TYPEINFO_HPP
#define QUACK_TYPEINFO_HPP

#include "AST.hpp"
#include "llvm/IR/Type.h"
#include <set>
#include <string>

namespace quack {

/// Contains info such as name and ast node pointers to user defined types
struct TypeInfo {
  const ast::Identifier *identifier;// If type is user defined, this will point to it's identifier
  const std::string name;
  llvm::Type *LLVMType;

  // Every type has a parent, and if it is not a subclass of any class, Object is its parent
  TypeInfo *parent = nullptr;


  explicit TypeInfo(
      llvm::Type *LLVMType,
      const std::string &name,
      const ast::Identifier *ident = nullptr,
      TypeInfo *parent = nullptr)
      : LLVMType(LLVMType),
        name(name),
        identifier(ident),
        parent(parent) {}

  TypeInfo(TypeInfo &&other) noexcept
      : LLVMType(other.LLVMType),
        name(other.name),
        identifier(other.identifier),
        binOps(std::move(other.binOps)) {}

  bool operator==(TypeInfo &other) { return this->name == other.name; }
  bool operator!=(TypeInfo &other) { return !(*this == other); }
  void addBinOp(ast::BinaryOperator::Operator binOp) { binOps.insert(binOp); }
  bool hasBinOp(ast::BinaryOperator::Operator binOp) { return binOps.find(binOp) != binOps.end(); }
//  void dispatch(llvm::StringRef methodName, llvm::ArrayRef )

private:
  std::set<ast::BinaryOperator::Operator> binOps;// The binary operators that are defined for this type
};

}// namespace quack
#endif//QUACK_TYPEINFO_HPP
