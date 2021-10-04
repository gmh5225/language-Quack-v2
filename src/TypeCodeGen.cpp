//
// Created by Parsa Bagheri on 4/4/21.
//

#include "TypeCodeGen.hpp"

#include "llvm/IR/DerivedTypes.h"

namespace quack::codegen {

bool TypeCodeGen::generateBuiltins() {

//  llvm::IRBuilder<> builder(_context);
  auto *val = llvm::StructType::create(_context, {llvm::Type::getInt32Ty(_context)}, "Object");
  if (!val)
    return false;

//  builder.Insert(val);
//  _codeGen->getModule()->print(llvm::outs(), nullptr);
  return true;
}

}