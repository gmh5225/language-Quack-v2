//
// Created by Parsa Bagheri on 3/23/21.
//

#ifndef QUACK_COMPOUNDSTMTCODEGEN_HPP
#define QUACK_COMPOUNDSTMTCODEGEN_HPP

#include "ASTVisitor.hpp"
#include "CodeGenerator.hpp"
#include "CompoundStmtChecker.hpp"
#include "TypeChecker.hpp"
#include "Type.hpp"
#include "Utils.hpp"

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include "llvm/IR/Module.h"
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <map>
#include <memory>
#include <string>

namespace quack::codegen {

using namespace ast;

class CodeGenerator;//Forward ref

class CompoundStmtCodeGen : public ASTVisitor<CompoundStmtCodeGen> {

  mutable llvm::Value *_curValue = nullptr;
  llvm::IRBuilder<> &_builder;
  llvm::Function *_parentFunction; /* reference to calling function */
  llvm::BasicBlock *_basicBlock;   /* the basic block that will be constructed */
  llvm::LLVMContext &_context;
  llvm::Module &_module;
  const std::string _bbName;

  EnvironmentStack &_envStack;

  std::unique_ptr<semant::TypeChecker> _typeChecker;

  CodeGenerator *_codeGen; /* reference to the calling code generator */

  ScopeStack &_scopeStack; /* variables stored in previous blocks */

  TypeDataBase *tdb{};

public:
//  CompoundStmtCodeGen(const TranslationUnit &root,
//                      CodeGenerator *codeGen,
//                      ScopeStack &allocaStack,
//                      EnvironmentStack &envStack,
//                      llvm::LLVMContext &context,
//                      llvm::Function *parentFunction,
//                      const std::string &bbName = "entry");

  CompoundStmtCodeGen(const TranslationUnit &root,
                      CodeGenerator *codeGen,
                      ScopeStack &allocaStack,
                      EnvironmentStack &envStack,
                      llvm::IRBuilder<> &builder,
                      llvm::BasicBlock *basicBlock);

  ~CompoundStmtCodeGen() = default;

  bool traverseAssignment(const Assignment &) const override;

  bool traverseVarDecl(const VarDecl &) const override;

  bool traverseIntegerLiteral(const IntegerLiteral &) const override;

  bool traverseFloatLiteral(const FloatLiteral &) const override;

  bool traverseBoolLiteral(const BoolLiteral &) const override;

  bool traverseStringLiteral(const StringLiteral &) const override;

  bool traverseBinaryOperator(const BinaryOperator &) const override;

  bool traverseReturn(const Return &) const override;

  bool traverseLValueIdent(const LValueIdent &) const override;

  bool traverseIf(const If &) const override;

  bool traverseWhile(const While &) const override;

  bool traverseCompoundStmt(const CompoundStmt &) const override;

  bool traverseCall(const Call &) const override;

  bool traverseMemberAccess(const MemberAccess &) const override;

  llvm::IRBuilder<> &getBuilder() { return _builder; }

  llvm::Value *getCurVal() const { return _curValue; }

private:
  void setCurValue(llvm::Value *value) const { _curValue = value; }

  bool declareVar(const std::string &symbol, Type *) const;
};

}// namespace quack::codegen
#endif//QUACK_COMPOUNDSTMTCODEGEN_HPP
