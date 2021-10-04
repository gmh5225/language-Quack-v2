//
// Created by Parsa Bagheri on 3/24/21.
//

#ifndef QUACK_CODEGENERATOR_HPP
#define QUACK_CODEGENERATOR_HPP

#include "ASTVisitor.hpp"
#include "CompoundStmtCodeGen.hpp"
#include "Type.hpp"
#include "TypeInfo.hpp"
#include "Utils.hpp"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/Target/TargetMachine.h"

namespace quack::codegen {

class CompoundStmtCodeGen; // Forward ref
class ClassesCodeGen;

using namespace ast;

class CodeGenerator : public ASTVisitor<CodeGenerator> {
  friend class CompoundStmtCodeGen;
  friend class ClassesCodeGen;

  mutable llvm::LLVMContext _globalContext;
  mutable llvm::BasicBlock *_currentBlock = nullptr;
  mutable llvm::Value *_curValue = nullptr;
  mutable llvm::Function *_mainFunction = nullptr;
  mutable llvm::TargetMachine *_targetMachine = nullptr;

  mutable ScopeStack _scopeStack;

  /// Intrinsics
  mutable llvm::Function *_noOp = nullptr;

  mutable std::unique_ptr<llvm::Module> _module;

  //  mutable Types _types;

  const TranslationUnit &_root;

  TypeDataBase *tdb{};
  //  Types &getTypes() const { return _types; }

public:
  CodeGenerator(const TranslationUnit &root, const char *moduleName);
  ~CodeGenerator() = default;

  llvm::Function *
  createFunction(llvm::FunctionType *, const std::string &name,
                 llvm::GlobalValue::LinkageTypes linkageType =
                     llvm::GlobalValue::LinkageTypes::InternalLinkage)
      const; // changes the module, but module is mutable

  llvm::BasicBlock *createBBandSetInsertionPoint(llvm::IRBuilder<> &,
                                                 llvm::Function *);

  bool generate();

  bool traverseAST() const = delete; /* use generate instead */

  bool toBitCode(const std::string &output = "output.bc") const;

  llvm::LLVMContext &getContext() const { return _globalContext; }

  llvm::Value *getCurrentValue() const { return _curValue; }

  llvm::BasicBlock *getCurrentBasicBlock() const { return _currentBlock; }

  llvm::Module *getModule() const { return _module.get(); }

  llvm::Function *getNoOp() const;
};

} // namespace quack::codegen
#endif // QUACK_CODEGENERATOR_HPP
