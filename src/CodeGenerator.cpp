//
// Created by Parsa Bagheri on 3/24/21.
//

#include "CodeGenerator.hpp"
#include "ClassesChecker.hpp"
#include "ClassesCodeGen.hpp"
#include "TypeCodeGen.hpp"

#include "Type.hpp"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar.h"
//#include <llvm/ExecutionEngine/ExecutionEngine.h>
//#include <llvm/IR/Function.h>
#include "llvm/Support/TargetRegistry.h"
//#include <llvm/Target/TargetOptions.h>
#include "llvm/Transforms/IPO/StripDeadPrototypes.h"

namespace quack::codegen {

llvm::Function *CodeGenerator::createFunction(
    llvm::FunctionType *fnType, const std::string &name,
    llvm::GlobalValue::LinkageTypes linkageType) const {

  return llvm::Function::Create(fnType, linkageType, name, _module.get());
}

llvm::BasicBlock *
CodeGenerator::createBBandSetInsertionPoint(llvm::IRBuilder<> &builder,
                                            llvm::Function *fn) {
  const char *bbName = "entry";
  auto basicBlock = llvm::BasicBlock::Create(_globalContext, bbName, fn);
  builder.SetInsertPoint(basicBlock);
  return basicBlock;
}

CodeGenerator::CodeGenerator(const TranslationUnit &root,
                             const char *moduleName)
    : ASTVisitor<CodeGenerator>(root), _root(root), _globalContext(),
      _scopeStack() {
  _module = std::make_unique<llvm::Module>(moduleName, _globalContext);

  auto targetTriple = LLVMGetDefaultTargetTriple();

  llvm::InitializeNativeTarget();

  std::string error;
  auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

  if (!target) {
    logError(error);
    std::exit(1);
  }

  auto CPU = "generic";
  auto features = "";

  llvm::TargetOptions opt;
  auto RM = llvm::Optional<llvm::Reloc::Model>();
  _targetMachine =
      target->createTargetMachine(targetTriple, CPU, features, opt, RM);

  _module->setDataLayout(_targetMachine->createDataLayout());
  _module->setTargetTriple(targetTriple);

  _mainFunction = createFunction(
      llvm::FunctionType::get(llvm::Type::getInt64Ty(_globalContext), false),
      "main", llvm::GlobalValue::LinkOnceODRLinkage);

  //  llvm::SMDiagnostic diagnostic;
  //  auto m = llvm::parseIRFile(
  //      "/Users/parsabagheri/Desktop/quack-builtins/quack_runtime.ll",
  //      diagnostic, _globalContext);
  //  if (m) {
  //    llvm::DataLayout dataLayout(_module.get());
  //    m->setDataLayout(dataLayout);
  //    m->setTargetTriple(_module->getTargetTriple());
  //    llvm::Linker linker(*_module);
  //    linker.linkInModule(std::move(m));
  //  }

  //  _module->print(llvm::outs() , nullptr);
  //  constructBuiltInTypes(_types, _globalContext);

  tdb = TypeDataBase::getTypeDB();
  tdb->initializeBuiltinTypes(_globalContext, _module.get());
}

bool CodeGenerator::generate() {

  TypeCodeGen typeCodeGen(_root, this, _globalContext);
  typeCodeGen.generateBuiltins();

  auto &classes = _root.getClasses();
  auto &compoundStmt = _root.getCompoundStmt();

  EnvironmentStack envStack;
  semant::TypeChecker typeChecker(_root, envStack);
  semant::ClassesChecker classesSemantChecker(_root, typeChecker, this);

  if (!classesSemantChecker.traverseAST())
    return false;

  envStack.push_back(Environment());
  semant::CompoundStmtChecker semantChecker(_root, envStack, typeChecker);
  if (!semantChecker.traverseCompoundStmt(_root.getCompoundStmt()))
    return false;

  for (auto &it : compoundStmt)
    if (it.getKind() == Statement::Kind::Return) {
      auto &ret = static_cast<Return &>(it);
      if (ret.getRetVal() == nullptr)
        break;

      if (typeChecker.traverseExpression(*ret.getRetVal())) {
        Type *returnValType = typeChecker.getCurType();
        if (returnValType->getName() != "Int") {
          logError(ret, "program's return value is not a < Int >");
          return false;
        }
      }
    }

  _scopeStack.push_back(Scope());
  llvm::IRBuilder<> builder(_globalContext);

  ClassesCodeGen classCodeGen(_root, *_module, _globalContext, builder, this);
  if (!classCodeGen.traverseClasses(_root.getClasses()))
    return false;

  auto *basicBlock = createBBandSetInsertionPoint(builder, _mainFunction);
  CompoundStmtCodeGen codeGen(_root, this, _scopeStack, envStack, builder,
                              basicBlock);
  if (!codeGen.traverseCompoundStmt(compoundStmt))
    return false;

  envStack.pop_back();
  _scopeStack.pop_back();

  // must have a return statement at the end, if we don't emit a return 0;
  auto &lastBlock = _mainFunction->getBasicBlockList().back();
  auto *terminatingInst = lastBlock.getTerminator();

  if (terminatingInst == nullptr) {
    auto &builder = codeGen.getBuilder();
    builder.SetInsertPoint(&lastBlock);
    builder.CreateRet(
        llvm::ConstantInt::get(llvm::Type::getInt64Ty(_globalContext), 0));
  }

  if (llvm::verifyModule(*_module, &llvm::errs())) {
    logError("failed to verify module");
    _module->print(llvm::errs(), nullptr);
    return false;
  }

  return true;
}

bool CodeGenerator::toBitCode(const std::string &output) const {
  std::error_code error;
  llvm::raw_fd_ostream outfile(output, error);
  if (error) {
    logError(error.message());
    return false;
  }
  //        _module->print(llvm::outs(), nullptr);

  llvm::StripDeadPrototypesPass stripDeadFNPass;
  llvm::ModuleAnalysisManager analysisManager;
  stripDeadFNPass.run(*_module, analysisManager);
  _module->print(outfile, nullptr);
  return true;
}

llvm::Function *CodeGenerator::getNoOp() const {
  if (_noOp != nullptr)
    return _noOp;

  auto *ftype =
      llvm::FunctionType::get(llvm::Type::getVoidTy(_globalContext), false);
  _noOp = llvm::Function::Create(ftype, llvm::Function::ExternalLinkage,
                                 "llvm.donothing", _module.get());
  return _noOp;
}

} // namespace quack::codegen