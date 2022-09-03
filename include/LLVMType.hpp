//
// Created by parsab on 6/9/22.
//

#ifndef QUACK_LLVMTYPE_HPP
#define QUACK_LLVMTYPE_HPP

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

#include "QTypeDB.hpp"

namespace quick {
namespace codegen {

/// ===-------------------------------------------------------------------=== //
/// LLVMType - a class encapsulating a Quick type in llvm
/// ===-------------------------------------------------------------------=== //
class LLVMType {
protected:
  llvm::LLVMContext &cntx;
  llvm::SmallVector<llvm::Function *, 0> methods; // method table

public:
  explicit LLVMType(llvm::LLVMContext &cntx) : cntx(cntx) {}
  virtual llvm::Type *getType() = 0;
  virtual llvm::StringRef getName() = 0;
  virtual llvm::Value *dispatch(llvm::IRBuilder<> &b, const char *method,
                                llvm::Value *self,
                                llvm::ArrayRef<llvm::Value *> args) = 0;
  virtual llvm::Value *alloc(llvm::IRBuilder<> &b) = 0;
  virtual llvm::Value *instantiate(llvm::IRBuilder<> &b, llvm::Value *lvalue,
                                   llvm::ArrayRef<llvm::Value *> args) = 0;
  virtual ~LLVMType() = default;
};

/// ===-------------------------------------------------------------------=== //
/// Primitive - a primitive type doesn't have a vtable and dynamic operations
/// ===-------------------------------------------------------------------=== //
class Primitive : public LLVMType {
protected:
  llvm::Type *t;
  Primitive(llvm::LLVMContext &cntx, llvm::Type *t) : LLVMType(cntx), t(t) {}

public:
  llvm::Type *getType() override { return t; }
  llvm::Value *alloc(llvm::IRBuilder<> &b) override;
  llvm::Value *instantiate(llvm::IRBuilder<> &b, llvm::Value *lvalue,
                           llvm::ArrayRef<llvm::Value *> args) override;
};

/// ===-------------------------------------------------------------------=== //
/// Integer primitive
/// ===-------------------------------------------------------------------=== //
class IntType : public Primitive {
public:
  explicit IntType(llvm::LLVMContext &cntx)
      : Primitive(cntx, llvm::IntegerType::getInt64Ty(cntx)) {}
  llvm::StringRef getName() override { return "Integer"; }
  llvm::Value *dispatch(llvm::IRBuilder<> &b, const char *method,
                        llvm::Value *self,
                        llvm::ArrayRef<llvm::Value *> args) override;
};

/// ===-------------------------------------------------------------------=== //
/// Float primitive
/// ===-------------------------------------------------------------------=== //
class FloatType : public Primitive {
public:
  explicit FloatType(llvm::LLVMContext &cntx)
      : Primitive(cntx, llvm::Type::getDoubleTy(cntx)) {}
  llvm::StringRef getName() override { return "Float"; }
  llvm::Value *dispatch(llvm::IRBuilder<> &b, const char *method,
                        llvm::Value *self,
                        llvm::ArrayRef<llvm::Value *> args) override;
};

/// ===-------------------------------------------------------------------=== //
/// Boolean primitive
/// ===-------------------------------------------------------------------=== //
class BoolType : public Primitive {
public:
  explicit BoolType(llvm::LLVMContext &cntx)
      : Primitive(cntx, llvm::IntegerType::getInt8Ty(cntx)) {}
  llvm::StringRef getName() override { return "Boolean"; }
  llvm::Value *dispatch(llvm::IRBuilder<> &b, const char *method,
                        llvm::Value *self,
                        llvm::ArrayRef<llvm::Value *> args) override;
};

/// ===-------------------------------------------------------------------=== //
/// ComplexType - has zero or more members and zero or more methods
/// ===-------------------------------------------------------------------=== //
class ComplexType : public LLVMType {
  llvm::SmallVector<llvm::Type *, 1> members;
  llvm::StructType *vtable;
  std::string name;

public:
  ComplexType(llvm::LLVMContext &cntx, llvm::ArrayRef<llvm::Type *> members,
              llvm::StructType *vtable, llvm::StringRef name)
      : LLVMType(cntx), members(members.begin(), members.end()), vtable(vtable),
        name(name) {}
  llvm::Type *getType() override { return nullptr; }
  llvm::StringRef getName() override { return name; }
  llvm::Value *dispatch(llvm::IRBuilder<> &b, const char *method,
                        llvm::Value *self,
                        llvm::ArrayRef<llvm::Value *> args) override;
  llvm::Value *alloc(llvm::IRBuilder<> &b) override;
  llvm::Value *instantiate(llvm::IRBuilder<> &b, llvm::Value *lvalue,
                           llvm::ArrayRef<llvm::Value *> args) override;
};

/// ===-------------------------------------------------------------------=== //
/// LLVMTypeRegisterty - mapping from Quick type and llvm type to LLVMType
/// ===-------------------------------------------------------------------=== //
class LLVMTypeRegistry {
  llvm::LLVMContext &cntx;
  llvm::StringMap<std::unique_ptr<LLVMType>> stringmap;
  llvm::DenseMap<llvm::Type *, LLVMType *> typemap;

public:
  explicit LLVMTypeRegistry(llvm::LLVMContext &cntx);
  LLVMTypeRegistry(const LLVMTypeRegistry &) = delete;
  LLVMTypeRegistry &operator=(const LLVMTypeRegistry &) = delete;
  LLVMType *get(type::QType *qtype);
  LLVMType *get(llvm::Type *type);
};

} // namespace codegen
} // namespace quick
#endif // QUACK_LLVMTYPE_HPP
