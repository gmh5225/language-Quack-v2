//
// Created by Parsa Bagheri on 7/28/21.
//

#ifndef QUACK_INCLUDE_CLASSESCHECKER_HPP
#define QUACK_INCLUDE_CLASSESCHECKER_HPP

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

namespace quack::semant {

using namespace quack::ast;

class ClassesChecker : public ASTVisitor<ClassesChecker> {
  const TranslationUnit &_translationUnit;

  semant::TypeChecker &_typeChecker;

  codegen::CodeGenerator
      *_codeGen; /* reference to the calling code generator */

  TypeDataBase *_tdb{};

public:
  ClassesChecker(const TranslationUnit &translationUnit,
                 TypeChecker &typeChecker, codegen::CodeGenerator *codegen)
      : ASTVisitor<ClassesChecker>(translationUnit),
        _translationUnit(translationUnit), _typeChecker(typeChecker),
        _codeGen(codegen), _tdb(TypeDataBase::getTypeDB()) {}

  bool traverseClasses(const Classes &) const override;

  bool traverseClass(const Class &) const override;
};

} // namespace quack::semant

#endif // QUACK_INCLUDE_CLASSESCHECKER_HPP
