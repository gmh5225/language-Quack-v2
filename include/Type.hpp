//
// Created by Parsa Bagheri on 7/21/21.
//

#ifndef QUACK_INCLUDE_TYPE_HPP
#define QUACK_INCLUDE_TYPE_HPP

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

#include "AST.hpp"

#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace quack {

class Type;
class TypeDataBase;

struct Parameter {
  std::string name;
  Type *type;
  Parameter(const std::string &name, Type *type) : name(name), type(type) {}

  static std::vector<Parameter>
  createParametersFromMap(const std::unordered_map<std::string, Type *> &map) {
    std::vector<Parameter> params;
    for (const auto &it : map) {
      params.emplace_back(it.first, it.second);
    }
    return std::move(params);
  }
};

enum class MethodKind { Override, Inherit, New, Constructor };

struct Method {
  MethodKind kind;
  std::string name;
  Type *returnType;
  std::vector<Parameter> parameters;

  Method(std::string name, Type *returnType, std::vector<Parameter> params,
         MethodKind kind)
      : kind(kind), name(std::move(name)), returnType(returnType),
        parameters(std::move(params)) {}

  Method(std::string name, MethodKind kind)
      : kind(kind), name(std::move(name)), returnType(nullptr), parameters() {}

  Method(const Method &other) = delete;

  Method(Method &&other) noexcept
      : name(std::move(other.name)), returnType(other.returnType),
        parameters(std::move(other.parameters)), kind(other.kind) {}

  Method &operator=(Method &&other) noexcept {
    this->name = std::move(other.name);
    this->returnType = other.returnType;
    this->parameters = std::move(other.parameters);
    this->kind = other.kind;
    return *this;
  }

  std::string getNameWithoutPostfix() const {
    return name.substr(0, name.find('_'));
  }
};

namespace builtin_type {
void createObject(std::unordered_map<std::string, std::unique_ptr<Type>> &types,
                  llvm::Module *module);
void createString(std::unordered_map<std::string, std::unique_ptr<Type>> &types,
                  llvm::Module *module);
void createInteger(
    std::unordered_map<std::string, std::unique_ptr<Type>> &types,
    llvm::Module *module);
void createFloat(std::unordered_map<std::string, std::unique_ptr<Type>> &types,
                 llvm::Module *module);
void createBoolean(
    std::unordered_map<std::string, std::unique_ptr<Type>> &types,
    llvm::Module *module);
void createNothing(
    std::unordered_map<std::string, std::unique_ptr<Type>> &types,
    llvm::Module *module);

static const std::unordered_set<std::string> builtinTypes{
    "Object", "Nothing", "Boolean", "String", "Integer", "Float"};

} // namespace builtin_type

extern int currentTypeID; // will be incremented each time a type is created

class Type {
  friend class TypeDataBase;
  friend void builtin_type::createObject(
      std::unordered_map<std::string, std::unique_ptr<Type>> &types,
      llvm::Module *module);
  friend void builtin_type::createString(
      std::unordered_map<std::string, std::unique_ptr<Type>> &types,
      llvm::Module *module);
  friend void builtin_type::createInteger(
      std::unordered_map<std::string, std::unique_ptr<Type>> &types,
      llvm::Module *module);
  friend void builtin_type::createFloat(
      std::unordered_map<std::string, std::unique_ptr<Type>> &types,
      llvm::Module *module);
  friend void builtin_type::createBoolean(
      std::unordered_map<std::string, std::unique_ptr<Type>> &types,
      llvm::Module *module);
  friend void builtin_type::createNothing(
      std::unordered_map<std::string, std::unique_ptr<Type>> &types,
      llvm::Module *module);

  std::string name;
  llvm::LLVMContext &llvmContext;
  llvm::StructType *llvmType{};
  llvm::StructType *llvmVTable{};
  std::unique_ptr<Method> constructor = nullptr;
  llvm::FunctionType *constructorLlvmType = nullptr;
  std::vector<Method> methods;
  std::vector<Parameter> members;
  std::map<std::string, std::pair<Parameter *, llvm::Type *>> memberTable;
  std::map<std::string, std::pair<Method *, llvm::FunctionType *>>
      methodTable; // will be filled with methods and their corresponding llvm
                   // types
  std::unordered_map<std::string, std::string> nameToMethodTableMap;
  Type *super{};
  int typeID;

public:
  int getID() const { return typeID; }

  Type(std::string typeName, llvm::LLVMContext &context)
      : name(std::move(typeName)), llvmContext(context),
        llvmType(llvm::StructType::create(context, name)),
        llvmVTable(llvm::StructType::create(context, name + "VTable")),
        typeID(++currentTypeID) {
    for (auto &p : methodTable) {
      auto &name = p.first;
      nameToMethodTableMap.insert({name.substr(0, name.find('_')), name});
    }
  }

  Type(std::vector<Parameter> members, std::vector<Method> methods, Type *super,
       std::string name, llvm::LLVMContext &context);

  Type(Type *super, std::string typeName, llvm::LLVMContext &context)
      : name(std::move(typeName)), llvmContext(context),
        llvmType(llvm::StructType::create(context, name)),
        llvmVTable(llvm::StructType::create(context, name + "VTable")),
        methodTable(), super(super), typeID(++currentTypeID) {}

  Type(const Type &) = delete;

  Type(Type &&other) noexcept
      : name(std::move(other.name)), llvmContext(other.llvmContext),
        llvmType(other.llvmType), llvmVTable(other.llvmVTable),
        constructor(std::move(other.constructor)),
        constructorLlvmType(other.constructorLlvmType),
        members(std::move(other.members)), methods(std::move(other.methods)),
        methodTable(std::move(other.methodTable)),
        memberTable(std::move(other.memberTable)), super(other.super),
        typeID(other.typeID) {}

  const std::string &getName() const { return name; }

  const Method *getConstructor() const {
    return constructor ? constructor.get() : nullptr;
  }

  llvm::FunctionType *getConstructorType() const { return constructorLlvmType; }

  void setSuper(Type *type) { super = type; }

  Type *getSuper() const { return super; }

  void setConstructor(std::unique_ptr<quack::Method> method) {
    constructor = std::move(method);
  }

  void setLLVMType(llvm::StructType *type) { llvmType = type; }

  void setLLVMVTableType(llvm::StructType *type) { llvmVTable = type; }

  void setConstructorType(llvm::FunctionType *type) {
    constructorLlvmType = type;
  }

  void setMethods(std::vector<Method> m);

  void setMembers(std::vector<Parameter> m);

  llvm::StructType *getLLVMType() const { return llvmType; }

  llvm::StructType *getLLVMVTableType() const { return llvmVTable; }

  bool hasMethod(const std::string &methodName) const {
    return methodTable.count(methodName) != 0;
  }

  bool hasMethodWithoutPostfix(const std::string &methodName) const {
    return nameToMethodTableMap.count(methodName) != 0;
  }

  const Method *getMethodWithoutPostFix(const std::string &name) const {
    if (hasMethodWithoutPostfix(name)) {
      return methodTable.at(nameToMethodTableMap.at(name)).first;
    }
    return nullptr;
  }

  const Method *getMethod(const std::string &name) const {
    if (hasMethod(name)) {
      return methodTable.at(name).first;
    }
    return nullptr;
  }

  const std::vector<Method> &getMethods() const { return methods; }

  const std::vector<Parameter> &getMembers() const { return members; }

  bool hasMember(const std::string &methodName) const {
    return memberTable.count(methodName) != 0;
  }

  const std::string adjustMethodName(const std::string &methodName) const {
    if (nameToMethodTableMap.count(methodName) > 0)
      return nameToMethodTableMap.at(methodName);
    return "";
  }

  const std::vector<Parameter> *
  getMethodParams(const std::string &methodName) const;

  const std::vector<Parameter> *
  getMethodWithoutPostFixParams(const std::string &methodName) const;

  llvm::FunctionType *getMethodType(const std::string &methodName) const;

  llvm::Type *getMemberLLVMType(const std::string &memberName) const;

  quack::Type *getMemberType(const std::string &memberName) const;

  int getMethodsIdxInVTable(const std::string &methodName) const;

  int getMemberIdx(const std::string &memberName) const;

  std::pair<llvm::FunctionType *, llvm::LoadInst *>
  loadFunction(llvm::IRBuilder<> &builder, const std::string &methodName,
               llvm::Value *object);

  llvm::LoadInst *loadMember(llvm::IRBuilder<> &builder,
                             const std::string &memberName,
                             llvm::Value *object);

  llvm::Value *getMemberAddr(llvm::IRBuilder<> &builder,
                             const std::string &memberName,
                             llvm::Value *object);

  llvm::Value *createConstructorCall(llvm::IRBuilder<> &builder) const;
}; // namespace quack

static const std::unordered_map<quack::ast::BinaryOperator::Operator,
                                std::string>
    operatorMap{
        {quack::ast::BinaryOperator::Operator::Equals, "equals"},
        {quack::ast::BinaryOperator::Operator::Less, "lt"},
        {quack::ast::BinaryOperator::Operator::LessEqual, "lte"},
        {quack::ast::BinaryOperator::Operator::Greater, "gt"},
        {quack::ast::BinaryOperator::Operator::GreaterEqual, "gte"},
        {quack::ast::BinaryOperator::Operator::Plus, "add"},
        {quack::ast::BinaryOperator::Operator::Times, "mul"},
        {quack::ast::BinaryOperator::Operator::Minus, "sub"},
        {quack::ast::BinaryOperator::Operator::Divide, "div"},
        {quack::ast::BinaryOperator::Operator::Modulo, "mod"},
    };

class TypeDataBase {
  bool isInitialized = false;
  llvm::Module *_module = nullptr;
  std::unordered_map<std::string, std::unique_ptr<Type>> types;
  std::unordered_map<std::string, llvm::Function *> functions;

  TypeDataBase() = default;

public:
  static TypeDataBase *getTypeDB() {
    static TypeDataBase tdb;
    return &tdb;
  }

  void initializeBuiltinTypes(llvm::LLVMContext &context,
                              llvm::Module *module) {
    if (!isInitialized) {
      _module = module;
      for (auto &typeName : builtin_type::builtinTypes) {
        types.insert({typeName, std::make_unique<Type>(typeName, context)});
      }

      builtin_type::createObject(types, module);
      builtin_type::createBoolean(types, module);
      builtin_type::createNothing(types, module);
      builtin_type::createInteger(types, module);
      builtin_type::createFloat(types, module);
      builtin_type::createString(types, module);

      // declaring initHeader runtime function
      auto initHeaderFn = llvm::Function::Create(
          llvm::FunctionType::get(
              llvm::Type::getVoidTy(context),
              {llvm::PointerType::getUnqual(types.at("Object")->getLLVMType()),
               llvm::Type::getInt32Ty(context)},
              false),
          llvm::GlobalValue::LinkageTypes::ExternalLinkage, "initHeader",
          _module);

      functions.insert({"initHeader", initHeaderFn});

      isInitialized = true;

      declareBuiltinMethods();
    }
  }

  void insertType(std::unique_ptr<Type> type) {
    types.insert({type->getName(), std::move(type)});
  }

  bool hasType(const std::string &name) const {
    return (types.count(name) > 0);
  }

  Type *getType(const std::string &name) const {
    if (hasType(name)) {
      return types.at(name).get();
    }
    return nullptr;
  }

  const std::string &lookUpOperator(quack::ast::BinaryOperator::Operator op) {
    return operatorMap.at(op);
  }

  void declareBuiltinMethods() {
    assert(isInitialized);

    std::unordered_set<std::string> declaredMethods;
    for (auto &builtinType : builtin_type::builtinTypes) {
      auto *t = getType(builtinType);
      for (auto &m : t->getMethods()) {
        createFunction(t, m, llvm::GlobalValue::LinkageTypes::ExternalLinkage);
      }
    }
  }

  llvm::Function *createFunction(Type *t, const std::string &name,
                                 llvm::GlobalValue::LinkageTypes linkage =
                                     llvm::GlobalValue::InternalLinkage) {
    if (functions.count(name) == 0) {
      auto *methodType = t->getMethodType(name);
      auto *fn = llvm::Function::Create(methodType, linkage, name, _module);
      functions.insert({name, fn});
      return fn;
    }
    return functions.at(name);
  }

  llvm::Function *createFunction(Type *t, const Method &m,
                                 llvm::GlobalValue::LinkageTypes linkage =
                                     llvm::GlobalValue::InternalLinkage) {
    return createFunction(t, m.name, linkage);
  }

  llvm::Function *getFunctionPointer(const std::string &fnName) {
    if (functions.count(fnName) > 0)
      return functions.at(fnName);
    return nullptr;
  }

  llvm::Function *getConstructor(const std::string &typeName) {
    if (types.count(typeName) == 0)
      return nullptr;
    return _module->getFunction("new" + typeName);
  }
};

} // namespace quack

#endif // QUACK_INCLUDE_TYPE_HPP
