//
// Created by Parsa Bagheri on 7/21/21.
//

#include "Type.hpp"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"

#include <vector>

namespace quack {

int currentTypeID = 0;

using VTableTemplate = std::vector<std::pair<
    std::string,
    std::pair<std::string, std::vector<std::pair<std::string, std::string>>>>>;

static auto
createVTable(const VTableTemplate &methodTable,
             std::unordered_map<std::string, std::unique_ptr<Type>> &types) {

  std::vector<Method> methods;
  for (const auto &method : methodTable) {
    const auto &methodName = method.first;
    const auto &methodReturnType = method.second.first;
    std::vector<Parameter> parameters;
    for (const auto &parameter : method.second.second) {
      const auto &parameterName = parameter.first;
      const auto &parameterType = parameter.second;
      parameters.emplace_back(parameterName, types[parameterType].get());
    }
    methods.emplace_back(methodName, types[methodReturnType].get(),
                         std::move(parameters), MethodKind::New);
  }
  return std::move(methods);
}

static auto createHeader(llvm::LLVMContext &context) {
  static auto header = llvm::StructType::create(
      context,
      {llvm::Type::getInt64Ty(context), llvm::Type::getInt64Ty(context)},
      "header");
  return header;
}

void Type::setMembers(std::vector<Parameter> m) {
  this->members = std::move(m);
  // create type
  std::vector<llvm::Type *> fieldMemberTypes;
  fieldMemberTypes.push_back(createHeader(llvmContext));
  fieldMemberTypes.push_back(
      llvm::PointerType::get(this->llvmVTable, 0)); // add vtable
  for (auto &member : members) {
    auto *llvmT = member.type->getLLVMType();
    fieldMemberTypes.push_back(llvmT);
    memberTable.insert({member.name, {&member, llvmT}});
  }
  llvmType->setBody(fieldMemberTypes);
}

void Type::setMethods(std::vector<Method> m) {
  this->methods = std::move(m);
  llvm::SmallVector<llvm::Type *> vtableMethodTypes;
  for (auto &method : methods) {
    llvm::SmallVector<llvm::Type *> fnParamLLVMTypes;
    //    fnParamLLVMTypes.push_back(llvm::PointerType::get(llvmType, 0));
    for (auto &param : method.parameters) {
      fnParamLLVMTypes.push_back(
          llvm::PointerType::getUnqual(param.type->getLLVMType()));
    }
    auto retType = llvm::PointerType::get(method.returnType->getLLVMType(), 0);
    auto fnType = llvm::FunctionType::get(retType, fnParamLLVMTypes, false);
    auto fnPtrType = llvm::PointerType::get(fnType, 0);
    vtableMethodTypes.push_back(fnPtrType);
    methodTable.insert({method.name, {&method, fnType}});
    nameToMethodTableMap.insert({method.getNameWithoutPostfix(), method.name});
  }
  this->llvmVTable->setBody(vtableMethodTypes);
}

Type::Type(std::vector<Parameter> members, std::vector<Method> methods,
           Type *super, std::string n, llvm::LLVMContext &context)
    : name(std::move(n)), llvmContext(context),
      llvmType(llvm::StructType::create(context, name)),
      llvmVTable(llvm::StructType::create(context, name + "VTable")),
      methodTable(), super(super) {
  setMethods(std::move(methods));
  setMembers(std::move(members));
}

std::pair<llvm::FunctionType *, llvm::LoadInst *>
Type::loadFunction(llvm::IRBuilder<> &builder, const std::string &methodName,
                   llvm::Value *object) {

  // getting the index of the method in the v-table
  int idx = getMethodsIdxInVTable(methodName);
  if (idx < 0)
    return {nullptr, nullptr};

  // loading the v-table
  auto *vtableType =
      llvm::StructType::getTypeByName(llvmContext, name + "VTable");

  auto *vtableAddr = builder.CreateStructGEP(object, 1);
  auto *vtable =
      builder.CreateLoad(llvm::PointerType::getUnqual(vtableType), vtableAddr);

  // loading the function
  auto *fnAddr = builder.CreateStructGEP(vtable, idx);
  auto *fn = builder.CreateLoad(vtableType->getElementType(idx), fnAddr);
  auto *fnType = methodTable.at(methodName).second;

  return {fnType, fn};
}

llvm::LoadInst *Type::loadMember(llvm::IRBuilder<> &builder,
                                 const std::string &memberName,
                                 llvm::Value *object) {
  auto *addr = getMemberAddr(builder, memberName, object);
  auto *type = llvm::StructType::getTypeByName(llvmContext, name);
  auto *member = builder.CreateLoad(llvm::PointerType::getUnqual(type), addr);
  return member;
}

llvm::Value *Type::getMemberAddr(llvm::IRBuilder<> &builder,
                                 const std::string &memberName,
                                 llvm::Value *object) {

  // getting the index of the member
  int idx = getMemberIdx(memberName);
  if (idx < 0)
    return nullptr;

  // loading the member
  //  auto *type =
  //      llvm::StructType::getTypeByName(llvmContext, name);
  auto *type = getMemberType(memberName);
  auto *llvmType = llvm::PointerType::getUnqual(
      llvm::StructType::getTypeByName(llvmContext, type->getName()));
  if (!type)
    return nullptr;
  auto *addr = builder.CreateStructGEP(object, idx);
  return builder.CreateBitCast(addr, llvm::PointerType::getUnqual(llvmType));
//  auto *load = builder.CreateLoad(llvm::PointerType::getUnqual(llvmType), addr);
//  return load;
}

const std::vector<Parameter> *
Type::getMethodParams(const std::string &methodName) const {
  if (hasMethod(methodName)) {
    return &(methodTable.at(methodName).first->parameters);
  }
  return nullptr;
}

const std::vector<Parameter> *
Type::getMethodWithoutPostFixParams(const std::string &methodName) const {
  if (hasMethodWithoutPostfix(methodName)) {
    return &(methodTable.at(nameToMethodTableMap.at(methodName))
                 .first->parameters);
  }
  return nullptr;
}

llvm::FunctionType *Type::getMethodType(const std::string &methodName) const {
  if (hasMethod(methodName))
    return methodTable.at(methodName).second;
  return nullptr;
}

llvm::Type *Type::getMemberLLVMType(const std::string &memberName) const {
  if (hasMember(memberName))
    return memberTable.at(memberName).second;
  return nullptr;
}

quack::Type *Type::getMemberType(const std::string &memberName) const {
  if (hasMember(memberName))
    return memberTable.at(memberName).first->type;
  return nullptr;
}

// FIXME think of a better way to search/store indexes
int Type::getMethodsIdxInVTable(const std::string &methodName) const {
  for (int i = 0, end = methods.size(); i < end; i++) {
    if (methods[i].name == methodName) {
      return i;
    }
  }
  return -1;
}

int Type::getMemberIdx(const std::string &memberName) const {
  for (int i = 0, end = members.size(); i < end; i++) {
    if (members[i].name == memberName) {
      return i + 2; // add 2 because idx=0 is __header and idx=1 is __vtable
    }
  }
  return -1;
}

namespace builtin_type {

// Creating objects representing builtin types
void createObject(std::unordered_map<std::string, std::unique_ptr<Type>> &types,
                  llvm::Module *module) {

  auto &objectType = types["Object"];

  objectType->setMethods(
      createVTable({{"equals_Object",
                     {"Boolean", {{"this", "Object"}, {"other", "Object"}}}},
                    {"print_Object", {"Nothing", {{"this", "Object"}}}},
                    {"destroy_Object", {"Nothing", {{"this", "Object"}}}}},
                   types));

  objectType->setMembers(std::vector<Parameter>());

  // Creating the constructor function
  auto fnType = llvm::FunctionType::get(
      llvm::PointerType::getUnqual(objectType->getLLVMType()), {}, false);

  llvm::Function::Create(fnType,
                         llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                         "newObject", module);
}

void createBoolean(
    std::unordered_map<std::string, std::unique_ptr<Type>> &types,
    llvm::Module *module) {

  auto &booleanType = types["Boolean"];
  auto &objectType = types["Object"];

  booleanType->super = objectType.get();

  booleanType->setMethods(
      createVTable({{"equals_Boolean",
                     {"Boolean", {{"this", "Boolean"}, {"other", "Boolean"}}}},
                    {"print_Boolean", {"Nothing", {{"this", "Boolean"}}}},
                    {"destroy_Boolean", {"Nothing", {{"this", "Boolean"}}}}},
                   types));

  std::vector<llvm::Type *> fieldMemberTypes;
  fieldMemberTypes.push_back(createHeader(booleanType->llvmContext));
  fieldMemberTypes.push_back(
      llvm::PointerType::get(booleanType->llvmVTable, 0)); // add vtable
  fieldMemberTypes.push_back(llvm::Type::getInt64Ty(booleanType->llvmContext));
  booleanType->llvmType->setBody(fieldMemberTypes);

  // Creating the constructor function
  auto fnType = llvm::FunctionType::get(
      llvm::PointerType::getUnqual(booleanType->getLLVMType()),
      {llvm::Type::getInt64Ty(booleanType->llvmContext)}, false);

  llvm::Function::Create(fnType,
                         llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                         "newBoolean", module);
}

void createNothing(
    std::unordered_map<std::string, std::unique_ptr<Type>> &types,
    llvm::Module *module) {

  auto &nothingType = types["Nothing"];
  auto &objectType = types["Object"];

  nothingType->super = objectType.get();

  nothingType->setMethods(
      createVTable({{"equals_Nothing",
                     {"Boolean", {{"this", "Nothing"}, {"other", "Nothing"}}}},
                    {"print_Nothing", {"Nothing", {{"this", "Nothing"}}}},
                    {"destroy_Nothing", {"Nothing", {{"this", "Nothing"}}}}},
                   types));

  nothingType->setMembers(std::vector<Parameter>());

  // Creating the constructor function
  auto fnType = llvm::FunctionType::get(
      llvm::PointerType::getUnqual(nothingType->getLLVMType()), {}, false);

  llvm::Function::Create(fnType,
                         llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                         "newNothing", module);
}

void createInteger(
    std::unordered_map<std::string, std::unique_ptr<Type>> &types,
    llvm::Module *module) {

  auto &integerType = types["Integer"];
  auto &objectType = types["Object"];

  integerType->super = objectType.get();

  integerType->setMethods(createVTable(
      {
          {"equals_Integer",
           {"Boolean", {{"this", "Integer"}, {"other", "Integer"}}}},
          {"print_Integer", {"Nothing", {{"this", "Integer"}}}},
          {"destroy_Object", {"Nothing", {{"this", "Object"}}}},
          {"lt_Integer",
           {"Boolean", {{"this", "Integer"}, {"other", "Integer"}}}},
          {"lte_Integer",
           {"Boolean", {{"this", "Integer"}, {"other", "Integer"}}}},
          {"gt_Integer",
           {"Boolean", {{"this", "Integer"}, {"other", "Integer"}}}},
          {"gte_Integer",
           {"Boolean", {{"this", "Integer"}, {"other", "Integer"}}}},
          {"add_Integer",
           {"Integer", {{"this", "Integer"}, {"other", "Integer"}}}},
          {"mul_Integer",
           {"Integer", {{"this", "Integer"}, {"other", "Integer"}}}},
          {"sub_Integer",
           {"Integer", {{"this", "Integer"}, {"other", "Integer"}}}},
          {"div_Integer",
           {"Integer", {{"this", "Integer"}, {"other", "Integer"}}}},
          {"mod_Integer",
           {"Integer", {{"this", "Integer"}, {"other", "Integer"}}}},
      },
      types));
  std::vector<llvm::Type *> fieldMemberTypes;
  fieldMemberTypes.push_back(createHeader(integerType->llvmContext));
  fieldMemberTypes.push_back(
      llvm::PointerType::get(integerType->llvmVTable, 0)); // add vtable
  fieldMemberTypes.push_back(llvm::Type::getInt64Ty(integerType->llvmContext));
  integerType->llvmType->setBody(fieldMemberTypes);

  // Creating the constructor function
  auto fnType = llvm::FunctionType::get(
      llvm::PointerType::getUnqual(integerType->getLLVMType()),
      {llvm::Type::getInt64Ty(integerType->llvmContext)}, false);

  llvm::Function::Create(fnType,
                         llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                         "newInteger", module);
}

void createFloat(std::unordered_map<std::string, std::unique_ptr<Type>> &types,
                 llvm::Module *module) {

  auto &floatType = types["Float"];
  auto &objectType = types["Object"];

  floatType->super = objectType.get();

  floatType->setMethods(createVTable(
      {
          {"equals_Float",
           {"Boolean", {{"this", "Float"}, {"other", "Float"}}}},
          {"print_Float", {"Nothing", {{"this", "Float"}}}},
          {"destroy_Object", {"Nothing", {{"this", "Object"}}}},
          {"lt_Float", {"Boolean", {{"this", "Float"}, {"other", "Float"}}}},
          {"lte_Float", {"Boolean", {{"this", "Float"}, {"other", "Float"}}}},
          {"gt_Float", {"Boolean", {{"this", "Float"}, {"other", "Float"}}}},
          {"gte_Float", {"Boolean", {{"this", "Float"}, {"other", "Float"}}}},
          {"add_Float", {"Float", {{"this", "Float"}, {"other", "Float"}}}},
          {"mul_Float", {"Float", {{"this", "Float"}, {"other", "Float"}}}},
          {"sub_Float", {"Float", {{"this", "Float"}, {"other", "Float"}}}},
          {"div_Float", {"Float", {{"this", "Float"}, {"other", "Float"}}}},
      },
      types));
  std::vector<llvm::Type *> fieldMemberTypes;
  fieldMemberTypes.push_back(createHeader(floatType->llvmContext));
  fieldMemberTypes.push_back(
      llvm::PointerType::get(floatType->llvmVTable, 0)); // add vtable
  fieldMemberTypes.push_back(llvm::Type::getDoubleTy(floatType->llvmContext));
  floatType->llvmType->setBody(fieldMemberTypes);

  // Creating the constructor function
  auto fnType = llvm::FunctionType::get(
      llvm::PointerType::getUnqual(floatType->getLLVMType()),
      {llvm::Type::getDoubleTy(floatType->llvmContext)}, false);

  llvm::Function::Create(fnType,
                         llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                         "newFloat", module);
}

void createString(std::unordered_map<std::string, std::unique_ptr<Type>> &types,
                  llvm::Module *module) {

  auto &stringType = types["String"];
  auto &objectType = types["Object"];

  stringType->super = objectType.get();
  stringType->setMethods(createVTable(
      {{"equals_String", {"Boolean", {{"other", "String"}}}},
       {"print_String", {"Nothing", {{"this", "String"}}}},
       {"destroy_String", {"Nothing", {{"this", "String"}}}},
       {"add_String", {"String", {{"this", "String"}, {"other", "String"}}}}},
      types));

  // create type
  std::vector<llvm::Type *> fieldMemberTypes;
  fieldMemberTypes.push_back(createHeader(stringType->llvmContext));
  fieldMemberTypes.push_back(llvm::PointerType::get(stringType->llvmVTable, 0));
  fieldMemberTypes.push_back(llvm::PointerType::get(
      llvm::Type::getInt8Ty(stringType->llvmContext), 0));

  stringType->llvmType->setBody(fieldMemberTypes);

  // Creating the constructor function
  auto fnType = llvm::FunctionType::get(
      llvm::PointerType::getUnqual(stringType->getLLVMType()),
      {llvm::PointerType::getUnqual(
          llvm::Type::getInt8Ty(stringType->llvmContext))},
      false);

  llvm::Function::Create(fnType,
                         llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                         "newString", module);

}

} // namespace builtin_type

} // namespace quack