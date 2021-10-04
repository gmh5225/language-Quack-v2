//
// Created by Parsa Bagheri on 7/28/21.
//

#ifndef QUACK_INCLUDE_CLASSESCODEGEN_HPP
#define QUACK_INCLUDE_CLASSESCODEGEN_HPP

#include "ASTVisitor.hpp"
#include "CodeGenerator.hpp"
#include "CompoundStmtChecker.hpp"
#include "CompoundStmtCodeGen.hpp"
#include "Type.hpp"
#include "TypeChecker.hpp"
#include "Utils.hpp"

#include "llvm/IR/Module.h"
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <map>
#include <memory>
#include <string>

namespace quack::codegen {

using namespace quack::ast;

class ClassesCodeGen : public ASTVisitor<ClassesCodeGen> {
  mutable llvm::Value *_curValue = nullptr;
  llvm::IRBuilder<> &_builder;
  llvm::LLVMContext &_context;
  llvm::Module &_module;

  std::unique_ptr<semant::TypeChecker> _typeChecker;

  CodeGenerator *_codeGen; /* reference to the calling code generator */

  //  ScopeStack &_scopeStack; /* variables stored in previous blocks */

  TypeDataBase *tdb;

public:
  ClassesCodeGen(const quack::ast::TranslationUnit &tu, llvm::Module &module,
                 llvm::LLVMContext &context, llvm::IRBuilder<> &builder,
                 CodeGenerator *codeGen)
      : ASTVisitor<ClassesCodeGen>(tu), _builder(builder), _context(context),
        _module(module), _codeGen(codeGen), tdb(TypeDataBase::getTypeDB()) {}

  bool traverseClass(const Class &) const override;

  bool traverseMethod(const ast::Method &) const override;

  bool traverseParameters(const Parameters &) const override;

  bool traverseMethod(const ast::Method &method, quack::Type *type,
                      llvm::Value *allocationInst) const;

  llvm::IRBuilder<> &getBuilder() { return _builder; }

  llvm::Value *getCurVal() const { return _curValue; }
};

} // namespace quack::codegen

#endif // QUACK_INCLUDE_CLASSESCODEGEN_HPP
