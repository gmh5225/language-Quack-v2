#include "CodeGenerator.hpp"
#include "ParserDriver.hpp"
#include "PrintVisitor.hpp"
#include "Utils.hpp"
#include <iostream>
#include <memory>

int main(int argc, char **argv) {
  int programError = 0;
  bool printAST = false;
  quack::parser::ParserDriver drv;

  if (argc < 2) {
    std::cerr << "usage: quack [options] <file.qk>\n";
    std::exit(1);
  }

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
      if (!printVisitor.traverseAST()) {
        quack::logError("failed");
        std::exit(1);
      }
      std::exit(0);
    }

    quack::codegen::CodeGenerator codeGen(root, argv[argc - 1]);
    if (!codeGen.generate()) {
      quack::logError("compilation failed");
      //            std::exit(1);
    }

    if (!codeGen.toBitCode()) {
      quack::logError("failed to write bit-code");
      std::exit(1);
    }
  }

  std::exit(0);
}