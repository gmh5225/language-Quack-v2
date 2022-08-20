//
// Created by parsab on 6/9/22.
//

#include "LLVMType.hpp"
#include "llvm/IR/IRBuilder.h"

namespace quack {
namespace codegen {

using namespace llvm;
using namespace quack::type;

template<typename T>
static void register_builtin_type(llvm::LLVMContext &cntx, DenseMap<llvm::Type *, LLVMType *> &typemap, StringMap<std::unique_ptr<LLVMType>> &stringmap) {
  auto t = std::make_unique<T>(cntx);
  typemap[t->getType()] = t.get();
  stringmap[t->getName()] = std::move(t);
}

LLVMTypeRegistery::LLVMTypeRegistery(llvm::LLVMContext &cntx) : cntx(cntx) {
  register_builtin_type<IntType>(cntx, typemap, stringmap);
  register_builtin_type<FloatType>(cntx, typemap, stringmap);
  register_builtin_type<BoolType>(cntx, typemap, stringmap);
}

LLVMType *LLVMTypeRegistery::get(type::QType *qtype) {
  auto it = this->stringmap.find(qtype->getName());
  if (it == this->stringmap.end())
    return nullptr;
  return it->second.get();
}

LLVMType *LLVMTypeRegistery::get(llvm::Type *type) {
  auto it = this->typemap.find(type);
  if (it == this->typemap.end())
    return nullptr;
  return it->second;
}

/// Common dispatches for int/float types
/// creates instructions for primitive operations
static inline llvm::Value *IntOrFloatDispatch(llvm::IRBuilder<> &b, const char *method,
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
                               llvm::Value *self,
                               llvm::ArrayRef<Value *> args) {
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
  } else if (method_is(op::ArithmeticOperator[op::MOD])){
    return b.CreateSRem(self, args.back());
  }
  assert(false && "we shouldn't get here");
  return nullptr;
}

/// Handles method calls of an float object
llvm::Value *FloatType::dispatch(llvm::IRBuilder<> &b, const char *method,
                                 llvm::Value *self,
                                 llvm::ArrayRef<Value *> args) {
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
                                llvm::Value *self,
                                llvm::ArrayRef<Value *> args) {
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
                                   llvm::ArrayRef<llvm::Value *> args) {
  return nullptr;
}

llvm::Value *ComplexType::instantiate(IRBuilder<> &b, Value *lvalue,
                                      llvm::ArrayRef<llvm::Value *> args) {
  return nullptr;
}

llvm::Value *ComplexType::alloc(IRBuilder<> &b) { return nullptr; }

/// Creates a 'store' instruction
llvm::Value *Primitive::instantiate(IRBuilder<> &b, Value *lvalue,
                                    llvm::ArrayRef<llvm::Value *> args) {
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
} // namespace quack
