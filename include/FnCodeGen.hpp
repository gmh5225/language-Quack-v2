//
// Created by parsab on 6/12/22.
//

#ifndef QUACK_FNCODEGEN_HPP
#define QUACK_FNCODEGEN_HPP

#include "llvm/IR/IRBuilder.h"

#include "ASTVisitor.hpp"
#include "EnvironmentBuilder.hpp"
#include "ExprTypeChecker.hpp"
#include "LLVMType.hpp"
#include "QTypeDB.hpp"

namespace quack {

namespace codegen {

constexpr char MainFn[] = "main";

/// An environment for llvm allocations
using LLVMScope = llvm::StringMap<llvm::Value *>;
class LLVMEnv : public llvm::SmallVector<LLVMScope, 3> {
public:
  LLVMEnv() = default;
  llvm::Value *lookup(llvm::StringRef name) const {
    for (auto it = this->rbegin(); it != this->rend(); it++)
      if (auto t = it->lookup(name))
        return t;
    return nullptr;
  }

};

class ExprCodeGen : public ast::ASTVisitor<ExprCodeGen, llvm::Value *> {
  llvm::IRBuilder<> &builder;
  llvm::LLVMContext &llvmCntx;
  LLVMTypeRegistery &typeRegistery;
  LLVMEnv &llvmEnv;
  type::QTypeDB &tdb;
  sema::ExprTypeChecker exprTC;

public:
  ExprCodeGen(llvm::IRBuilder<> &b, LLVMTypeRegistery &tr, sema::Env &env, LLVMEnv &llvmEnv)
      : builder(b), llvmCntx(b.getContext()), typeRegistery(tr), llvmEnv(llvmEnv),
        tdb(type::QTypeDB::get()), exprTC(tdb, env) {}

#define EXPR_NODE_HANDLER(NODE) llvm::Value *visit##NODE(const NODE &);
#include "ASTNodes.def"
};

class FnCodeGen : public EnvironmentBuilder<FnCodeGen> {
  llvm::StringRef fnName;
  llvm::Module &module;
  llvm::IRBuilder<> &builder;
  LLVMTypeRegistery &tr;
  ExprCodeGen exprCG;
  LLVMEnv llvmEnv;

public:
  FnCodeGen(llvm::IRBuilder<> &builder, llvm::Module &module,
            const ast::CompoundStmt &cmpStmt, type::QTypeDB &typedb,
            LLVMTypeRegistery &tr, type::QType *parentType = nullptr,
            type::QType *returnType = nullptr, bool isConstructor = false,
            llvm::StringRef fnName = MainFn)
      : EnvironmentBuilder<FnCodeGen>(cmpStmt, typedb, parentType, returnType,
                                        isConstructor),
        fnName(fnName), module(module), builder(builder), tr(tr),
        exprCG(builder, tr, env, llvmEnv) {}

#define STMT_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &);
#include "ASTNodes.def"

  bool generate();
  bool isMain() { return fnName == "main"; }
};

} // namespace codegen
} // namespace quack
#endif // QUACK_FNCODEGEN_HPP
