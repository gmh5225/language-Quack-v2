//
// Created by parsab on 6/12/22.
//

#ifndef QUACK_FNCODEGEN_HPP
#define QUACK_FNCODEGEN_HPP

#include "llvm/IR/IRBuilder.h"

#include "ASTVisitor.hpp"
#include "Environment.hpp"
#include "EnvironmentBuilder.hpp"
#include "ExprTypeChecker.hpp"
#include "IRType.hpp"
#include "QTypeDB.hpp"

namespace quick::codegen {

constexpr char MainFn[] = "main";

/// ===-------------------------------------------------------------------=== //
/// An expression visitor that generates code for a given expression
/// ===-------------------------------------------------------------------=== //
class ExprCodeGen : public ast::ASTVisitor<ExprCodeGen, llvm::Value *> {
  llvm::Module &module;
  llvm::IRBuilder<> &builder;
  llvm::LLVMContext &llvmCntx;
  LLVMTypeRegistry &typeRegistery;
  LLVMEnv &llvmEnv;
  type::QTypeDB &tdb;
  sema::ExprTypeChecker exprTC;

public:
  ExprCodeGen(llvm::Module &module, llvm::IRBuilder<> &b, LLVMTypeRegistry &tr,
              sema::Env &env, LLVMEnv &llvmEnv)
      : module(module), builder(b), llvmCntx(b.getContext()), typeRegistery(tr),
        llvmEnv(llvmEnv), tdb(type::QTypeDB::get()), exprTC(tdb, env) {}
  llvm::Value *visitTranslationUnit(const TranslationUnit &) = delete;
  llvm::Value *visitStatement(const Statement &) = delete;
#define STMT_NODE_HANDLER(NODE) llvm::Value *visit##NODE(const NODE &) = delete;
#define EXPR_NODE_HANDLER(NODE) llvm::Value *visit##NODE(const NODE &);
#include "ASTNodes.def"
};

/// ===-------------------------------------------------------------------=== //
/// A statement visitor that generates code for every given function/method
/// ===-------------------------------------------------------------------=== //
class FnCodeGen : public ASTVisitor<FnCodeGen, bool> {
  llvm::StringRef fnName;
  llvm::Module &module;
  llvm::IRBuilder<> &builder;
  LLVMTypeRegistry &tr;
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
            const ast::CompoundStmt &cmpStmt, LLVMTypeRegistry &tr,
            type::QType *parentType = nullptr, llvm::StringRef fnName = MainFn)
      : fnName(fnName), module(module), builder(builder), tr(tr),
        exprCG(module, builder, tr, env, llvmEnv), fnBody(cmpStmt),
        tdb(type::QTypeDB::get()), parentType(parentType), exprTC(tdb, env) {}

  bool visitTranslationUnit(const TranslationUnit &) = delete;
  bool visitExpression(const Expression &) = delete;
#define EXPR_NODE_HANDLER(NODE) llvm::Value *visit##NODE(const NODE &) = delete;
#define STMT_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &);
#include "ASTNodes.def"

  bool generate();
  bool isMain() { return fnName == MainFn; }
};

} // namespace quick::codegen
#endif // QUACK_FNCODEGEN_HPP
