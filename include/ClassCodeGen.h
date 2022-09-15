//
// Created by parsab on 9/8/22.
//

#ifndef QUICK_CLASSCODEGEN_H
#define QUICK_CLASSCODEGEN_H

#include "EnvironmentBuilder.hpp"
#include "FnCodeGen.hpp"

namespace quick {
namespace codegen {

/// ===-------------------------------------------------------------------=== //
/// ClassVerifier - A visitor that visits every class and verifies
/// their legality
/// ===-------------------------------------------------------------------=== //
class ClassCodeGen : public ASTVisitor<ClassCodeGen, bool> {
  const Class &theClass;
  llvm::Module &module;
  llvm::IRBuilder<> &builder;
  LLVMTypeRegistry &tr;
  type::QTypeDB &tdb;
  type::QType *qType;
  const std::string &typeName;
  llvm::StructType *superVtable = nullptr;
  ComplexType *super = nullptr;
  //  ExprCodeGen exprCG;
  //  sema::Env env;
  //  LLVMEnv llvmEnv;

  bool generateInitFunction(llvm::Function *initFn, llvm::Function *superInitFn);
  bool generateCreateFunction(llvm::Function *createFn, llvm::Function *superInitFn,
                              StructType *type, StructType *vtable, MethodTable &methodTable);
  MethodTable generateVTable(IRType *, StructType *);
  type::Table<Type *> generateMemberTable();

public:
  ClassCodeGen(const Class &theClass, llvm::Module &module,
               llvm::IRBuilder<> &builder, LLVMTypeRegistry &tr);
  // only visits classes/methods
  bool visitMethod(const ast::Method &);
  bool visitMethods(const ast::Methods &);
  bool visitClass(const ast::Class &);
  bool visitExpression(const ast::Expression &) = delete;
#define EXPR_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &) = delete;
#define STMT_NODE_HANDLER(NODE) bool visit##NODE(const ast::NODE &) = delete;
#include "ASTNodes.def"

  bool generate();
};

} // namespace codegen
} // namespace quick

#endif // QUICK_CLASSCODEGEN_H
