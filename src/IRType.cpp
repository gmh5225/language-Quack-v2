//
// Created by parsab on 6/9/22.
//

#include "IRType.hpp"
#include "llvm/IR/IRBuilder.h"

namespace quick {
namespace codegen {

using namespace llvm;
using namespace quick::type;

static inline llvm::Type *ptr(llvm::Type *t) {
  return llvm::PointerType::get(t, 0);
}

static std::unique_ptr<ObjectType> buildObjectType(llvm::Module &module,
                                                   llvm::StructType *type,
                                                   llvm::Type *strType) {
  auto &cntx = module.getContext();
  auto *vtable = llvm::StructType::create(cntx, "Object_vtable");

  std::vector<llvm::Type *> members;
  members.push_back(ptr(vtable));
  members.push_back(llvm::IntegerType::getInt32Ty(cntx));
  members.push_back(llvm::IntegerType::getInt32Ty(cntx));
  type->setBody(members);

  auto eqFn = llvm::FunctionType::get(llvm::Type::getInt8Ty(cntx),
                                      {ptr(type), ptr(type)}, false);
  auto strFn = llvm::FunctionType::get(strType, {ptr(type)}, false);
  auto delFn =
      llvm::FunctionType::get(llvm::Type::getVoidTy(cntx), {ptr(type)}, false);
  vtable->setBody({ptr(eqFn), ptr(strFn), ptr(delFn)});

  llvm::MapVector<StringRef, FunctionType *> methodTable;
  methodTable.insert({"Object__eq__Object", eqFn});
  methodTable.insert({"Object__str__", strFn});
  methodTable.insert({"Object__del__", delFn});

  FunctionType *constructorTy = FunctionType::get(ptr(type), {}, false);
  auto *constructor = Function::Create(
      constructorTy, GlobalValue::ExternalLinkage, "Object_create", module);
  constructor->setCallingConv(CallingConv::C);

  return std::make_unique<ObjectType>(module, type, std::move(methodTable));
}

static std::unique_ptr<StringType> buildStringType(llvm::Module &module,
                                                   llvm::StructType *type,
                                                   llvm::StructType *objType) {
  auto &cntx = module.getContext();
  auto *vtable = llvm::StructType::create(cntx, "String_vtable");
  std::vector<llvm::Type *> bodyTypes;
  bodyTypes.push_back(ptr(vtable));
  for (unsigned i = 1, end = objType->getNumElements(); i < end; i++) {
    bodyTypes.push_back(objType->getElementType(i));
  }
  bodyTypes.push_back(llvm::Type::getInt8PtrTy(cntx));
  type->setBody(bodyTypes);

  auto eqFn = llvm::FunctionType::get(llvm::Type::getInt8Ty(cntx),
                                      {ptr(type), ptr(type)}, false);
  auto strFn = llvm::FunctionType::get(objType, {ptr(type)}, false);
  auto delFn =
      llvm::FunctionType::get(llvm::Type::getVoidTy(cntx), {ptr(type)}, false);

  vtable->setBody({ptr(eqFn), ptr(strFn), ptr(delFn)});

  llvm::MapVector<StringRef, FunctionType *> methodTable;
  methodTable.insert({"String__eq__String", eqFn});
  methodTable.insert({"String__str__", strFn});
  methodTable.insert({"String__del__", delFn});
  FunctionType *constructorTy =
      FunctionType::get(ptr(type), {llvm::Type::getInt8PtrTy(cntx)}, false);
  auto *constructor = Function::Create(
      constructorTy, GlobalValue::ExternalLinkage, "String_create", module);
  constructor->setCallingConv(CallingConv::C);
  return std::make_unique<StringType>(module, type, std::move(methodTable));
}

static void buildBuiltinComplexTypes(llvm::Module &module) {
  auto &cntx = module.getContext();
  auto *vtable = llvm::StructType::create(cntx);
  auto *type =
      llvm::StructType::get(cntx,
                            {ptr(vtable), llvm::IntegerType::getInt32Ty(cntx),
                             llvm::IntegerType::getInt32Ty(cntx)},
                            false);

  auto *stringType = llvm::StructType::get(cntx);

  auto eqFn =
      llvm::FunctionType::get(llvm::Type::getInt8Ty(cntx), {type, type}, false);
  auto strFn = llvm::FunctionType::get(stringType, {type}, false);
  auto delFn =
      llvm::FunctionType::get(llvm::Type::getVoidTy(cntx), {type}, false);
  vtable->setBody({ptr(eqFn), ptr(strFn), ptr(delFn)});

  llvm::MapVector<StringRef, FunctionType *> methodTable;
  methodTable.insert({"Object__eq__Object", eqFn});
  methodTable.insert({"Object__str__", strFn});
  methodTable.insert({"Object__del__", delFn});
}

template <typename T>
static void registerPrimitive(llvm::Module &module,
                              DenseMap<llvm::Type *, IRType *> &typemap,
                              StringMap<std::unique_ptr<IRType>> &stringmap) {
  auto t = std::make_unique<T>(module.getContext());
  typemap[t->getType()] = t.get();
  stringmap[t->getName()] = std::move(t);
}

template <typename T>
static void registerType(std::unique_ptr<T> t,
                         DenseMap<llvm::Type *, IRType *> &typemap,
                         StringMap<std::unique_ptr<IRType>> &stringmap) {
  typemap[t->getType()] = t.get();
  stringmap[t->getName()] = std::move(t);
}

LLVMTypeRegistry::LLVMTypeRegistry(llvm::Module &module) : module(module) {
  registerPrimitive<IntType>(module, typemap, stringmap);
  registerPrimitive<FloatType>(module, typemap, stringmap);
  registerPrimitive<BoolType>(module, typemap, stringmap);

  auto *objStruct = llvm::StructType::create(module.getContext(), "Object");
  auto *strStruct = llvm::StructType::create(module.getContext(), "String");
  auto objectType = buildObjectType(module, objStruct, strStruct);
  auto stringType = buildStringType(module, strStruct, objStruct);
  registerType(std::move(objectType), typemap, stringmap);
  registerType(std::move(stringType), typemap, stringmap);
  //  registerComplex<StringType>(module, typemap, stringmap);
  //  registerPrimitive<StringType>(module, typemap, stringmap);
}

IRType *LLVMTypeRegistry::get(type::QType *qtype) {
  auto it = this->stringmap.find(qtype->getName());
  if (it == this->stringmap.end())
    return nullptr;
  return it->second.get();
}

IRType *LLVMTypeRegistry::get(llvm::Type *type) {
  auto it = this->typemap.find(type);
  if (it == this->typemap.end())
    return nullptr;
  return it->second;
}

void LLVMTypeRegistry::dump(llvm::raw_ostream &out) {
  out << "StringMap: \n";
  for (auto &p : stringmap) {
    out << "\t{" << p.first() << ", " << p.second->getName() << "}\n";
  }

  out << "TypeMap: \n";
  for (auto &p: typemap) {
    out << "\t{" << p.getFirst() << ", " << p.getSecond()->getName() << "}\n";
  }
}

/// Common dispatches for int/float types
/// creates instructions for primitive operations
static inline llvm::Value *IntOrFloatDispatch(llvm::IRBuilder<> &b,
                                              const char *method,
                                              llvm::Value *self,
                                              llvm::ArrayRef<Value *> args) {
  auto method_is = [&](const char *other) {
    return std::strcmp(method, other) == 0;
  };
  assert(args.size() <= 1 && "binary/unary operator");
  if (args.empty()) {
    if (method_is(op::UnaryOperator[op::NEG])) {
      if (self->getType()->isIntegerTy())
        return b.CreateSub(b.getInt64(0), self);
      else
        return b.CreateMul(llvm::ConstantFP::get(b.getDoubleTy(), -1.0), self);
    }
  }

  auto arg = args.back();
  if (method_is(op::ArithmeticOperator[op::ADD])) {
    return b.CreateAdd(self, arg);
  } else if (method_is(op::ArithmeticOperator[op::SUB])) {
    return b.CreateSub(self, arg);
  } else if (method_is(op::ArithmeticOperator[op::MUL])) {
    return b.CreateMul(self, arg);
  } else if (method_is(op::ArithmeticOperator[op::DIV])) {
    return b.CreateSDiv(self, arg);
  } else if (method_is(op::ComparisonOperator[op::LE])) {
    return b.CreateICmpSLE(self, arg);
  } else if (method_is(op::ComparisonOperator[op::LT])) {
    return b.CreateICmpSLT(self, arg);
  } else if (method_is(op::ComparisonOperator[op::GE])) {
    return b.CreateICmpSGE(self, arg);
  } else if (method_is(op::ComparisonOperator[op::GT])) {
    return b.CreateICmpSGT(self, arg);
  } else if (method_is(op::ComparisonOperator[op::NE])) {
    return b.CreateICmpNE(self, arg);
  } else if (method_is(op::ComparisonOperator[op::EQ])) {
    return b.CreateICmpEQ(self, arg);
  }
  assert(false && "we shouldn't get here");
  return nullptr;
}

/// Handles method calls of an integer object
llvm::Value *IntType::dispatch(llvm::IRBuilder<> &b, const char *method,
                               llvm::Value *self, llvm::ArrayRef<Value *> args,
                               llvm::Module *) {
  assert(args.size() <= 1 && "binary/unary operator");
  auto method_is = [&](const char *other) {
    return std::strcmp(method, other) == 0;
  };
  if (args.empty()) {
    if (method_is(op::UnaryOperator[op::NEG])) {
      return b.CreateNeg(self);
    } else if (method_is(op::UnaryOperator[op::NOT])) {
      return b.CreateICmpEQ(self, b.getInt64(0));
    }
  }

  auto arg = args.back();
  if (method_is(op::ArithmeticOperator[op::ADD])) {
    return b.CreateAdd(self, arg);
  } else if (method_is(op::ArithmeticOperator[op::SUB])) {
    return b.CreateSub(self, arg);
  } else if (method_is(op::ArithmeticOperator[op::MUL])) {
    return b.CreateMul(self, arg);
  } else if (method_is(op::ArithmeticOperator[op::DIV])) {
    return b.CreateSDiv(self, arg);
  } else if (method_is(op::ComparisonOperator[op::LE])) {
    return b.CreateICmpSLE(self, arg);
  } else if (method_is(op::ComparisonOperator[op::LT])) {
    return b.CreateICmpSLT(self, arg);
  } else if (method_is(op::ComparisonOperator[op::GE])) {
    return b.CreateICmpSGE(self, arg);
  } else if (method_is(op::ComparisonOperator[op::GT])) {
    return b.CreateICmpSGT(self, arg);
  } else if (method_is(op::ComparisonOperator[op::NE])) {
    return b.CreateICmpNE(self, arg);
  } else if (method_is(op::ComparisonOperator[op::EQ])) {
    return b.CreateICmpEQ(self, arg);
  } else if (method_is(op::ArithmeticOperator[op::MOD])) {
    return b.CreateSRem(self, args.back());
  }
  assert(false && "we shouldn't get here");
  return nullptr;
}

/// Handles method calls of an float object
llvm::Value *FloatType::dispatch(llvm::IRBuilder<> &b, const char *method,
                                 llvm::Value *self,
                                 llvm::ArrayRef<Value *> args, llvm::Module *) {
  assert(args.size() <= 1 && "binary/unary operator");
  auto method_is = [&](const char *other) {
    return std::strcmp(method, other) == 0;
  };
  if (args.empty()) {
    if (method_is(op::UnaryOperator[op::NEG])) {
      return b.CreateFNeg(self);
    }
  }

  auto arg = args.back();
  if (method_is(op::ArithmeticOperator[op::ADD])) {
    return b.CreateFAdd(self, arg);
  } else if (method_is(op::ArithmeticOperator[op::SUB])) {
    return b.CreateFSub(self, arg);
  } else if (method_is(op::ArithmeticOperator[op::MUL])) {
    return b.CreateFMul(self, arg);
  } else if (method_is(op::ArithmeticOperator[op::DIV])) {
    return b.CreateFDiv(self, arg);
  } else if (method_is(op::ComparisonOperator[op::LE])) {
    return b.CreateFCmpOLE(self, arg);
  } else if (method_is(op::ComparisonOperator[op::LT])) {
    return b.CreateFCmpOLT(self, arg);
  } else if (method_is(op::ComparisonOperator[op::GE])) {
    return b.CreateFCmpOGE(self, arg);
  } else if (method_is(op::ComparisonOperator[op::GT])) {
    return b.CreateFCmpOGT(self, arg);
  } else if (method_is(op::ComparisonOperator[op::NE])) {
    return b.CreateFCmpONE(self, arg);
  } else if (method_is(op::ComparisonOperator[op::EQ])) {
    return b.CreateFCmpOEQ(self, arg);
  }
  assert(false && "we shouldn't get here");
  return nullptr;
}

/// Handles method calls of an boolean object
llvm::Value *BoolType::dispatch(llvm::IRBuilder<> &b, const char *method,
                                llvm::Value *self, llvm::ArrayRef<Value *> args,
                                llvm::Module *) {
  auto method_is = [&](const char *other) {
    return std::strcmp(method, other) == 0;
  };
  assert(args.size() <= 1 && "binary/unary operator");

  if (args.empty()) {
    if (method_is(op::UnaryOperator[op::NEG]))
      return b.CreateNeg(self);
    else if (method_is(op::UnaryOperator[op::NOT])) {
      return b.CreateNot(self);
    }
  }

  if (method_is(op::ComparisonOperator[op::NE])) {
    return b.CreateICmpNE(self, args.back());
  } else if (method_is(op::ComparisonOperator[op::EQ])) {
    return b.CreateICmpEQ(self, args.back());
  }
  return nullptr;
}

/// Handles method calls of a complex object
llvm::Value *ComplexType::dispatch(IRBuilder<> &b, const char *method,
                                   llvm::Value *self,
                                   llvm::ArrayRef<llvm::Value *> args,
                                   llvm::Module *module) {
  return nullptr;
}

llvm::Value *ComplexType::instantiate(IRBuilder<> &b, Value *lvalue,
                                      llvm::ArrayRef<llvm::Value *> args,
                                      llvm::Module *module) {
  auto *val = b.CreateStore(args[0], lvalue);
  val->setAlignment(MaybeAlign(8));
  return val;
}

llvm::Value *ComplexType::alloc(IRBuilder<> &b) {
  static llvm::Type *ptrType = b.getInt8PtrTy();
  auto val = b.CreateAlloca(ptrType);
  val->setAlignment(MaybeAlign(8));
  return val;
}

std::unique_ptr<ComplexType> ComplexType::create(
    Module &module, llvm::StringRef name, ComplexType *super,
    llvm::ArrayRef<llvm::Type *> members,
    llvm::MapVector<llvm::StringRef, llvm::FunctionType *> methodTable) {
  std::vector<llvm::Type *> allMembers;
  auto *superType = super->llvmType;

  // skip v-table and add all supers member types
  for (unsigned i = 1, end = superType->getNumElements(); i < end; i++)
    allMembers.push_back(superType->getElementType(i));

  for (auto *t : members)
    allMembers.push_back(t);

  //  llvm::Type *vtable = superType->getElementType(0);
  //  if (!methodTable.empty()) {
  //    auto &superMethods = super->methodTable;
  //    for (auto &p: methodTable) {
  //      if (superMethods.count(p.first))
  //
  //    }
  //  }

  return std::unique_ptr<ComplexType>(
      new ComplexType(module, nullptr, methodTable, name));
}

/// Creates a 'store' instruction
llvm::Value *Primitive::instantiate(IRBuilder<> &b, Value *lvalue,
                                    llvm::ArrayRef<llvm::Value *> args,
                                    llvm::Module *) {
  assert(args.size() == 1);
  auto val = b.CreateStore(args[0], lvalue);
  val->setAlignment(MaybeAlign(8));
  return val;
}

/// Creates an 'alloca' instruction for the primitive type 't'
llvm::Value *Primitive::alloc(IRBuilder<> &b) {
  auto val = b.CreateAlloca(t);
  // every value is 8 bytes
  val->setAlignment(MaybeAlign(8));
  return val;
}

} // namespace codegen
} // namespace quick
