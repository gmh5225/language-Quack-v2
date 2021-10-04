//
// Created by Parsa Bagheri on 4/4/21.
//

#ifndef QUACK_INCLUDE_TYPECODEGEN_HPP
#define QUACK_INCLUDE_TYPECODEGEN_HPP

#include "ASTVisitor.hpp"
#include "CodeGenerator.hpp"

#include "llvm/IR/LLVMContext.h"

namespace quack::codegen {

using namespace ast;

class TypeCodeGen : public ASTVisitor<TypeCodeGen> {

  mutable llvm::Value *_curValue = nullptr;
  llvm::LLVMContext &_context;
  CodeGenerator *_codeGen; /* reference to the calling code generator */

public:
  TypeCodeGen(const TranslationUnit &root,
              CodeGenerator *codeGen,
              llvm::LLVMContext &context)
      : ASTVisitor<TypeCodeGen>(root),
        _context(context),
        _codeGen(codeGen) {}

  bool generateBuiltins();
};

}// namespace quack::codegen

#endif//QUACK_INCLUDE_TYPECODEGEN_HPP
