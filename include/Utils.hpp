//
// Created by Parsa Bagheri on 3/26/21.
//

#ifndef QUACK_UTILS_HPP
#define QUACK_UTILS_HPP

#include <map>
#include <string>
#include <vector>

#include "llvm/IR/IRBuilder.h"

#include "AST.hpp"
#include "TypeInfo.hpp"
#include "Type.hpp"

namespace quack {

using Environment = std::map<std::string, Type *>;
using EnvironmentStack = std::vector<Environment>;
using Scope = std::map<std::string, llvm::Value *>;
using ScopeStack = std::vector<Scope>;
using Types = std::map<std::string, TypeInfo>;

/// Returns true if var in envStack, false otherwise
bool isInEnvironmentStack(EnvironmentStack &envStack, const std::string &var);

/// Returns true if var in allocaStack, false otherwise
bool isInScopeStack(ScopeStack &allocaStack, const std::string &var);

/// Returns true if type A is a covariant of type B, they are looked up in
/// the TypeDataBase
bool isACovariantOfB(const std::string &A, const std::string &B);

/// Writes the type of variable 'var' inside 'type' from the environment stack 'envStack'
/// Returns true if successful, false otherwise (var not in envStack)
bool getVariableType(EnvironmentStack &envStack, const std::string &var, Type **type);

/// Writes the allocation of variable 'var' inside 'type' from the allocation stack 'allocaStack'
/// Returns true if successful, false otherwise (var not in envStack)
bool getVariableAllocation(ScopeStack &allocaStack, const std::string &var,
                           llvm::Value **);

/// finds the intersection of environments 'a' and 'b' and writes it to 'intersection'
void getIntersectionOf(Environment &a, Environment &b, Environment &intersection);

/// finds the Union of environments 'a' and 'b' and writes it to 'a'
void getUnionOf(Environment &a, Environment &b);

/// finds the lowest common ancestor of types 'a' and 'b'
Type *getCommonParentType(Type *a, Type *b);

bool hasBuiltInTypes(Types &types);

bool isSpecialTypeAssignment(TypeInfo *a, TypeInfo *b, Types &types);

void logError(const ast::ASTNode &, const std::string &message);
void logError(const std::string &message);

}// namespace quack

#endif//QUACK_UTILS_HPP
