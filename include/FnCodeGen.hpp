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
//  sema::ExprTypeChecker exprTC;

public:
  ExprCodeGen(llvm::Module &module, llvm::IRBuilder<> &b, LLVMTypeRegistry &tr,
              sema::Env &env, LLVMEnv &llvmEnv)
      : module(module), builder(b), llvmCntx(b.getContext()), typeRegistery(tr),
        llvmEnv(llvmEnv), tdb(type::QTypeDB::get()) {}
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
public:
  using Args = llvm::SmallVector<std::pair<llvm::StringRef, Value *>, 4>;
  FnCodeGen(llvm::IRBuilder<> &builder, llvm::Module &module,
            const ast::CompoundStmt &cmpStmt, LLVMTypeRegistry &tr, LLVMEnv &llvmEnv,
            type::QType *parentType = nullptr, llvm::StringRef fnName = MainFn, IRType *returnType = nullptr, Args args = {})
      : fnName(fnName), module(module), builder(builder), tr(tr), llvmEnv(llvmEnv),
        exprCG(module, builder, tr, env, llvmEnv), fnBody(cmpStmt),
        tdb(type::QTypeDB::get()), parentType(parentType), retType(returnType), args(std::move(args)) {}

  bool visitTranslationUnit(const TranslationUnit &) = delete;
  bool visitExpression(const Expression &) = delete;
#define EXPR_NODE_HANDLER(NODE) llvm::Value *visit##NODE(const NODE &) = delete;
#define STMT_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &);
#include "ASTNodes.def"

  auto &getExprCodeGen() { return exprCG; }
  bool generate();
  bool isMain() { return fnName == MainFn; }

private:
  llvm::StringRef fnName;
  llvm::Module &module;
  llvm::IRBuilder<> &builder;
  LLVMTypeRegistry &tr;
  LLVMEnv &llvmEnv;
  ExprCodeGen exprCG;
  Args args;
  IRType *retType;

  const CompoundStmt &fnBody;
  type::QTypeDB &tdb;
  type::QType *parentType; // the type that the compound statement is in the
                           // environment of
  sema::Env env;
  //  sema::ExprTypeChecker exprTC;
};


Function *getOrCreateFnSym(const std::string &functionName,
                           llvm::Module &module, llvm::Type *resultType,
                           llvm::ArrayRef<Type *> params = {},
                           bool isVarArgs = false);

Function *getOrCreateFnSym(const std::string &functionName,
                           llvm::Module &module, FunctionType *FuncTy,
                           bool isVarArgs = false);

} // namespace quick::codegen
#endif // QUACK_FNCODEGEN_HPP
