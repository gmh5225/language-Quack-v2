#include "ClassCodeGen.h"
#include "FnCodeGen.hpp"
#include "ParserDriver.hpp"
#include "PrintVisitor.hpp"
#include "QuickTokenizer.hpp"
#include "Runtime.h"
#include "TypeChecker.hpp"
#include "Utils.hpp"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/Support/TargetSelect.h"

#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Mangler.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;
cl::opt<bool> DumpAST("dump-ast",
                      cl::desc("prints the AST of the input program"),
                      cl::init(false));
cl::opt<bool> EmitLLVMIR("emit-llvm-ir",
                         cl::desc("prints the generated llvm ir to stdout"),
                         cl::init(false));
cl::opt<std::string> Filename(cl::Positional, cl::desc("<input-file>"),
                              cl::NumOccurrencesFlag::Required);
namespace llvm::orc {

/// ===-------------------------------------------------------------------=== //
/// A Simple just-in-time compilation engine, copied from Kaleidoscope tutorial
/// ===-------------------------------------------------------------------=== //
class JITEngine {
private:
  ExecutionSession ES;
  RTDyldObjectLinkingLayer ObjectLayer;
  IRCompileLayer CompileLayer;

  DataLayout DL;
  MangleAndInterner Mangle;
  ThreadSafeContext Ctx;

  JITDylib &MainJD;

public:
  JITEngine(JITTargetMachineBuilder JTMB, DataLayout DL)
      : ObjectLayer(ES,
                    []() { return std::make_unique<SectionMemoryManager>(); }),
        CompileLayer(ES, ObjectLayer,
                     std::make_unique<ConcurrentIRCompiler>(std::move(JTMB))),
        DL(std::move(DL)), Mangle(ES, this->DL),
        Ctx(std::make_unique<LLVMContext>()),
        MainJD(ES.createJITDylib("<main>")) {
    MainJD.addGenerator(
        cantFail(DynamicLibrarySearchGenerator::GetForCurrentProcess(
            DL.getGlobalPrefix())));
    SymbolMap map;
    registerRuntimeFunctions([&](const std::string &sym, void *addr) {
      map[Mangle(sym)] =
          JITEvaluatedSymbol(pointerToJITTargetAddress(addr), JITSymbolFlags());
    });
    cantFail(MainJD.define(absoluteSymbols(map)));
  }

  static Expected<std::unique_ptr<JITEngine>> Create() {
    auto JTMB = JITTargetMachineBuilder::detectHost();

    if (!JTMB)
      return JTMB.takeError();

    auto DL = JTMB->getDefaultDataLayoutForTarget();
    if (!DL)
      return DL.takeError();

    return std::make_unique<JITEngine>(std::move(*JTMB), std::move(*DL));
  }

  const DataLayout &getDataLayout() const { return DL; }

  LLVMContext &getContext() { return *Ctx.getContext(); }

  Error addModule(std::unique_ptr<Module> M) {
    return CompileLayer.add(MainJD, ThreadSafeModule(std::move(M), Ctx));
  }

  Expected<JITEvaluatedSymbol> lookup(StringRef Name) {
    return ES.lookup({&MainJD}, Mangle(Name.str()));
  }
};

} // namespace llvm::orc

namespace quick::compiler {

/// ===-------------------------------------------------------------------=== //
/// A Driver class for interfacing with different stages of the compiler
/// ===-------------------------------------------------------------------=== //
class Driver {
  ExitOnError ExitOnErr;
  std::unique_ptr<llvm::orc::JITEngine> engine;

public:
  explicit Driver() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    engine = ExitOnErr(orc::JITEngine::Create());
  }

  bool TypeCheck(const TranslationUnit &root, const std::string &fname) {
    std::fstream file(fname);
    if (!file.is_open()) {
      std::cerr << "can't open file " << fname << "\n";
      return false;
    }
    quick::sema::TypeChecker tc(file, root);
    return tc.verify();
  }

  std::unique_ptr<Module> CodeGen(const TranslationUnit &root,
                                  LLVMContext &cntx, const std::string &name) {
    if (!TypeCheck(root, name))
      return nullptr;

    auto module = std::make_unique<Module>(name, cntx);
    IRBuilder<> builder(cntx);
    quick::codegen::LLVMTypeRegistry tr(*module);

    for (auto &clss : root.getClasses()) {
      quick::codegen::ClassCodeGen classCodeGen(*clss, *module, builder, tr);
      if (!classCodeGen.generate())
        return nullptr;
    }

    codegen::LLVMEnv env;
    codegen::FnCodeGen fnCodeGen(builder, *module, root.getCompoundStmt(), tr,
                                 env);
    if (!fnCodeGen.generate())
      return nullptr;

    return module;
  }

  int JIT(std::unique_ptr<Module> module) {
    std::string err;
    module->setDataLayout(engine->getDataLayout());
    ExitOnErr(engine->addModule(std::move(module)));
    auto MainFn = ExitOnErr(engine->lookup("main"));
    auto FnPtr = (intptr_t)MainFn.getAddress();
    auto Fn = (int (*)())FnPtr;
    return Fn();
  }
};

bool TypeCheck(const TranslationUnit &root, const std::string &fname) {
  std::fstream file(fname);
  if (!file.is_open()) {
    std::cerr << "can't open file " << fname << "\n";
    return false;
  }
  quick::sema::TypeChecker tc(file, root);
  return tc.verify();
}

std::unique_ptr<Module> CodeGen(const TranslationUnit &root, LLVMContext &cntx,
                                const std::string &name) {
  if (!TypeCheck(root, name))
    return nullptr;

  auto module = std::make_unique<Module>(name, cntx);
  IRBuilder<> builder(cntx);
  quick::codegen::LLVMTypeRegistry tr(*module);
  codegen::LLVMEnv env;
  quick::codegen::FnCodeGen fnCodeGen(builder, *module, root.getCompoundStmt(),
                                      tr, env);
  if (!fnCodeGen.generate())
    return nullptr;

  return module;
}

} // namespace quick::compiler

int main(int argc, char **argv) {

  cl::ParseCommandLineOptions(argc, argv, "Quick JIT.\n");
  quick::parser::ParserDriver drv;

  int programError = drv.parse(Filename);
  if (programError)
    std::exit(programError);

  const auto &root = drv.getRoot();

  if (DumpAST) {
    PrintVisitor printVisitor(root);
    printVisitor.visitTranslationUnit(root);
    std::exit(0);
  }

  LLVMContext cntx;
  quick::compiler::Driver compilerDriver;
  auto module = compilerDriver.CodeGen(root, cntx, Filename);
  if (!module)
    std::exit(1);

  if (EmitLLVMIR) {
    module->print(llvm::outs(), nullptr);
    std::exit(0);
  }

  int res = compilerDriver.JIT(std::move(module));
  std::exit(res);
}