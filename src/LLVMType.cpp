//
// Created by parsab on 6/9/22.
//

#include "LLVMType.hpp"
#include "llvm/IR/IRBuilder.h"

namespace quack {
namespace codegen {

using namespace llvm;
using namespace quack::type;

LLVMTypeRegistery::LLVMTypeRegistery(llvm::LLVMContext &cntx) : cntx(cntx) {
  this->insert({type::IntegerStr, std::make_unique<IntType>(cntx)});
  this->insert({type::FloatStr, std::make_unique<FloatType>(cntx)});
  this->insert({type::BoolStr, std::make_unique<BoolType>(cntx)});
}

LLVMType *LLVMTypeRegistery::get(type::QType *qtype) {
  auto it = this->find(qtype->getName());
  if (it == this->end())
    return nullptr;
  return it->second.get();
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
    if (method_is(op::UnaryOperator[op::NEG]))
      return b.CreateNeg(self);
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
  if (std::strcmp(method, op::ArithmeticOperator[op::MOD]) == 0) {
    return b.CreateSRem(self, args.back());
  }
  return IntOrFloatDispatch(b, method, self, args);
}

/// Handles method calls of an float object
llvm::Value *FloatType::dispatch(llvm::IRBuilder<> &b, const char *method,
                                 llvm::Value *self,
                                 llvm::ArrayRef<Value *> args) {
  return IntOrFloatDispatch(b, method, self, args);
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
