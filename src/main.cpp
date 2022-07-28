#include "FnCodeGen.hpp"
#include "ParserDriver.hpp"
#include "PrintVisitor.hpp"
#include "QType.hpp"
#include "TypeChecker.hpp"
#include "Utils.hpp"
#include <iostream>

bool CodeGen(const CompoundStmt &cmpstmt) {
  llvm::LLVMContext cntx;
  llvm::Module module("module", cntx);
  llvm::IRBuilder<> builder(cntx);
  quack::codegen::LLVMTypeRegistery tr(cntx);
  quack::codegen::FnCodeGen fnCodeGen(builder, module, cmpstmt,
                                      quack::type::QTypeDB::get(), tr);
  if (!fnCodeGen.generate())
    return false;

  module.print(llvm::errs(), nullptr);
  return true;
}

int main(int argc, char **argv) {
  int programError = 0;
  bool printAST = false;
  quack::parser::ParserDriver drv;

  if (argc < 2) {
    std::cerr << "usage: quack [options] <file.qk>\n";
    std::exit(1);
  }

  auto &db = quack::type::QTypeDB::get();

  for (int i = 1; i < argc; ++i) {
    if (argv[i] == std::string("-p"))
      drv.setTraceParsing(true);
    else if (argv[i] == std::string("-s"))
      drv.setTraceScanning(true);
    else
      programError = drv.parse(argv[i]);
  }

  if (!programError) {
    const auto &root = drv.getRoot();

    if (printAST) {
      PrintVisitor printVisitor(root);
      //      printVisitor.traverseAST();
      std::exit(0);
    }

    quack::sema::TypeChecker tc;
    if (!tc.visitTranslationUnit(root))
      std::exit(1);

    if (!CodeGen(root.getCompoundStmt()))
      std::exit(1);
    //    quack::codegen::CodeGenerator codeGen(root, argv[argc - 1]);
    //    if (!codeGen.generate()) {
    //      quack::logError("compilation failed");
    //      //            std::exit(1);
    //    }
    //
    //    if (!codeGen.toBitCode()) {
    //      quack::logError("failed to write bit-code");
    //      std::exit(1);
    //    }
  }

  std::exit(0);
}