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
#include "NestedEnvironment.hpp"
#include "QTypeDB.hpp"

namespace quack {

namespace codegen {

constexpr char MainFn[] = "main";

class ExprCodeGen : public ast::ASTVisitor<ExprCodeGen, llvm::Value *> {
  llvm::IRBuilder<> &builder;
  llvm::LLVMContext &llvmCntx;
  LLVMTypeRegistery &typeRegistery;
  LLVMEnv &llvmEnv;
  type::QTypeDB &tdb;
  sema::ExprTypeChecker exprTC;

public:
  ExprCodeGen(llvm::IRBuilder<> &b, LLVMTypeRegistery &tr, sema::Env &env,
              LLVMEnv &llvmEnv)
      : builder(b), llvmCntx(b.getContext()), typeRegistery(tr),
        llvmEnv(llvmEnv), tdb(type::QTypeDB::get()), exprTC(tdb, env) {}

#define EXPR_NODE_HANDLER(NODE) llvm::Value *visit##NODE(const NODE &);
#include "ASTNodes.def"
};

class FnCodeGen : public ASTVisitor<FnCodeGen, bool> {
  llvm::StringRef fnName;
  llvm::Module &module;
  llvm::IRBuilder<> &builder;
  LLVMTypeRegistery &tr;
  ExprCodeGen exprCG;
  LLVMEnv llvmEnv;

  const CompoundStmt &fnBody;
  type::QTypeDB &tdb;
  type::QType *parentType; // the type that the compound statement is in the
                           // environment of
  sema::Env env;
  sema::ExprTypeChecker exprTC;

public:
  FnCodeGen(llvm::IRBuilder<> &builder, llvm::Module &module,
            const ast::CompoundStmt &cmpStmt,
            LLVMTypeRegistery &tr, type::QType *parentType = nullptr,
            llvm::StringRef fnName = MainFn)
      : fnName(fnName), module(module), builder(builder), tr(tr),
        exprCG(builder, tr, env, llvmEnv), fnBody(cmpStmt), tdb(type::QTypeDB::get()),
        parentType(parentType), exprTC(tdb, env) {}

#define STMT_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &);
#include "ASTNodes.def"

  bool generate();
  bool isMain() { return fnName == "main"; }
};

} // namespace codegen
} // namespace quack
#endif // QUACK_FNCODEGEN_HPP
