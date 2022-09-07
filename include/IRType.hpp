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

#include "QType.hpp"
#include "QTypeDB.hpp"

namespace quick {
namespace codegen {

/// ===-------------------------------------------------------------------=== //
/// IRType - a class representing a Quick type in llvm ir
/// ===-------------------------------------------------------------------=== //
class IRType {
protected:
  llvm::LLVMContext &cntx;
  llvm::SmallVector<llvm::Function *, 0> methods; // method table

public:
  explicit IRType(llvm::LLVMContext &cntx) : cntx(cntx) {}
  virtual llvm::Type *getType() = 0;
  virtual llvm::StringRef getName() = 0;

  /// Looks up the method in the dispatch table and performs a call
  virtual llvm::Value *dispatch(llvm::IRBuilder<> &b, const char *method,
                                llvm::Value *self,
                                llvm::ArrayRef<llvm::Value *> args,
                                llvm::Module *module = nullptr) = 0;

  /// Automatic allocation on stack
  virtual llvm::Value *alloc(llvm::IRBuilder<> &b) = 0;

  /// Stores object in the allocation "lvalue"
  virtual llvm::Value *instantiate(llvm::IRBuilder<> &b, llvm::Value *lvalue,
                                   llvm::ArrayRef<llvm::Value *> args,
                                   llvm::Module *module = nullptr) = 0;
  virtual ~IRType() = default;
};

/// ===-------------------------------------------------------------------=== //
/// Primitive - a primitive type doesn't have a vtable and dynamic operations
/// ===-------------------------------------------------------------------=== //
class Primitive : public IRType {
protected:
  llvm::Type *t;
  Primitive(llvm::LLVMContext &cntx, llvm::Type *t) : IRType(cntx), t(t) {}

public:
  llvm::Type *getType() override { return t; }
  llvm::Value *alloc(llvm::IRBuilder<> &b) override;
  llvm::Value *instantiate(llvm::IRBuilder<> &b, llvm::Value *lvalue,
                           llvm::ArrayRef<llvm::Value *> args,
                           llvm::Module *module = nullptr) override;
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
                        llvm::Value *self, llvm::ArrayRef<llvm::Value *> args,
                        llvm::Module *module = nullptr) override;
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
                        llvm::Value *self, llvm::ArrayRef<llvm::Value *> args,
                        llvm::Module *module = nullptr) override;
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
                        llvm::Value *self, llvm::ArrayRef<llvm::Value *> args,
                        llvm::Module *module = nullptr) override;
};

class LLVMTypeRegistry; // forward ref

/// ===-------------------------------------------------------------------=== //
/// ComplexType - has zero or more members and zero or more methods
/// ===-------------------------------------------------------------------=== //
class ComplexType : public IRType {
protected:
  LLVMTypeRegistry &tr;
  llvm::Module &module;
  llvm::StructType *llvmType;
  const ComplexType *super;
  llvm::StringMap<std::pair<int, llvm::FunctionType *>> methodTable;
  std::string name;

  ComplexType(LLVMTypeRegistry &tr, llvm::Module &module,
              llvm::StructType *llvmType, const ComplexType *super,
              llvm::StringMap<std::pair<int, llvm::FunctionType *>> methodTable,
              llvm::StringRef name)
      : IRType(module.getContext()), tr(tr), module(module), llvmType(llvmType),
        super(super), methodTable(std::move(methodTable)), name(name) {}

public:
  const auto &getMethodTable() const { return methodTable; }
  llvm::Type *getType() override { return llvm::PointerType::get(llvmType, 0); }
  llvm::StringRef getName() override { return name; }
  llvm::Value *dispatch(llvm::IRBuilder<> &b, const char *method,
                        llvm::Value *self, llvm::ArrayRef<llvm::Value *> args,
                        llvm::Module *module) override;
  llvm::Value *alloc(llvm::IRBuilder<> &b) override;
  llvm::Value *instantiate(llvm::IRBuilder<> &b, llvm::Value *lvalue,
                           llvm::ArrayRef<llvm::Value *> args,
                           llvm::Module *module) override;

  static std::unique_ptr<ComplexType>
  create(LLVMTypeRegistry &tr, llvm::Module &module, llvm::StringRef name,
         ComplexType *super, llvm::ArrayRef<llvm::Type *> members,
         llvm::StringMap<std::pair<int, llvm::FunctionType *>> methodTable);
};

/// ===-------------------------------------------------------------------=== //
/// ObjectType - the root of the Type hierarchy, every other type in Quick
/// inherits from this type. This type defines the default vtable
/// ===-------------------------------------------------------------------=== //
class ObjectType : public ComplexType {
public:
  ObjectType(LLVMTypeRegistry &tr, llvm::Module &module,
             llvm::StructType *llvmType, const ComplexType *super,
             llvm::StringMap<std::pair<int, llvm::FunctionType *>> methodTable)
      : ComplexType(tr, module, llvmType, super, std::move(methodTable), "Object") {
  }
};

class NothingType : public ComplexType {
public:
  NothingType(LLVMTypeRegistry &tr, llvm::Module &module,
             llvm::StructType *llvmType, const ComplexType *super,
             llvm::StringMap<std::pair<int, llvm::FunctionType *>> methodTable)
      : ComplexType(tr, module, llvmType, super, std::move(methodTable), "Nothing") {
  }
};

class StringType : public ComplexType {
public:
  StringType(LLVMTypeRegistry &tr, llvm::Module &module,
             llvm::StructType *llvmType, const ComplexType *super,
             llvm::StringMap<std::pair<int, llvm::FunctionType *>> methodTable)
      : ComplexType(tr, module, llvmType, super, std::move(methodTable), "String") {
  }
};

/// ===-------------------------------------------------------------------=== //
/// LLVMTypeRegistry - mapping from Quick type and llvm type to IRType
/// ===-------------------------------------------------------------------=== //
class LLVMTypeRegistry {
  llvm::Module &module;
  llvm::StringMap<std::unique_ptr<IRType>> stringmap;
  llvm::DenseMap<llvm::Type *, IRType *> typemap;

public:
  explicit LLVMTypeRegistry(llvm::Module &module);
  LLVMTypeRegistry(const LLVMTypeRegistry &) = delete;
  LLVMTypeRegistry &operator=(const LLVMTypeRegistry &) = delete;
  IRType *get(type::QType *qtype);
  IRType *get(llvm::Type *type);
  void dump(llvm::raw_ostream &out = llvm::errs());
};

} // namespace codegen
} // namespace quick
#endif // QUACK_LLVMTYPE_HPP
