//
// Created by parsab on 6/12/22.
//

#include "QTypeDB.hpp"
#include "QType.hpp"

using namespace json;

namespace quick::type {

/// The following functions register builtin types in the type data base upon
/// initialization

/// Registers Boolean
static void registerBoolType(QTypeDB &db) {
  auto *boolType = db.registerNewType(BoolStr, nullptr);
  auto &methodTable = boolType->getMethods();

  methodTable.insert(
      {op::ComparisonOperator[op::EQ],
                      QMethod(boolType, {QVarDecl{boolType, "other"}},
                                              boolType, op::ComparisonOperator[op::EQ])});
  methodTable.insert(
      {op::ComparisonOperator[op::NE],
                      QMethod(boolType, {QVarDecl{boolType, "other"}},
                                              boolType, op::ComparisonOperator[op::NE])});

  methodTable.insert(
      {op::UnaryOperator[op::NEG],
       QMethod(boolType, {}, boolType, op::UnaryOperator[op::NEG])});

  methodTable.insert(
      {op::UnaryOperator[op::NOT],
       QMethod(boolType, {}, boolType, op::UnaryOperator[op::NOT])});
}

/// Registers Nothing
static void registerNothingType(QTypeDB &db) {
  auto *boolType = db.getBoolType();
  auto *nothingType = db.registerNewType(NothingStr, nullptr);
  auto &methodTable = nothingType->getMethods();

  methodTable.insert({op::ComparisonOperator[op::EQ],
                      QMethod(nothingType, {QVarDecl{nothingType, "other"}},
                             boolType, op::ComparisonOperator[op::EQ])});
  methodTable.insert({op::ComparisonOperator[op::NE],
                      QMethod(nothingType, {QVarDecl{nothingType, "other"}},
                             boolType, op::ComparisonOperator[op::NE])});
  methodTable.insert(
      {op::UnaryOperator[op::NOT],
       QMethod(boolType, {}, boolType, op::UnaryOperator[op::NOT])});
}

/// Registers Integer
static void registerIntegerType(QTypeDB &db) {
  auto *boolType = db.getBoolType();
  auto *intType = db.registerNewType(IntegerStr, nullptr);
  auto &methodTable = intType->getMethods();

  // Integer supports all arithmetic operations
  for (const auto &op : op::ArithmeticOperator) {
    methodTable.insert(
        {op, QMethod(intType, {QVarDecl{intType, "other"}}, intType, op)});
  }

  // Integer supports all comparison operations
  for (const auto &op : op::ComparisonOperator) {
    methodTable.insert(
        {op, QMethod(intType, {QVarDecl{intType, "other"}}, boolType, op)});
  }

  methodTable.insert(
      {op::UnaryOperator[op::NEG],
       QMethod(intType, {}, intType, op::UnaryOperator[op::NEG])});
}

/// Registers Float
static void registerFloatType(QTypeDB &db) {
  auto *floatType = db.registerNewType(FloatStr, nullptr);
  auto &methodTable = floatType->getMethods();

  // Float supports all arithmetic operations
  for (const auto &op : op::ArithmeticOperator) {
    methodTable.insert(
        {op, QMethod(floatType, {QVarDecl{floatType, "other"}}, floatType, op)});
  }

  // Bool type must be registered before int
  auto *boolType = db.getBoolType();

  // Float supports all comparison operations
  for (const auto &op : op::ComparisonOperator) {
    methodTable.insert(
        {op, QMethod(floatType, {QVarDecl{floatType, "other"}}, boolType, op)});
  }

  methodTable.insert(
      {op::UnaryOperator[op::NEG],
       QMethod(floatType, {}, floatType, op::UnaryOperator[op::NEG])});
}

/// Registers String
static void registerStringType(QTypeDB &db) {
  auto *objType = db.getObjectType();
  auto *boolType = db.getBoolType();
  auto *strType = db.registerNewType(StringStr, objType);
  auto &methodTable = strType->getMethods();

  methodTable.insert(
      {op::ArithmeticOperator[op::ADD],
                      QMethod(strType, {QVarDecl{strType, "other"}},
                                               strType, op::ArithmeticOperator[op::ADD])});
  methodTable.insert(
      {op::ComparisonOperator[op::EQ],
                      QMethod(strType, {QVarDecl{strType, "other"}},
                                              boolType, op::ComparisonOperator[op::EQ])});
  methodTable.insert(
      {op::ComparisonOperator[op::NE],
                      QMethod(strType, {QVarDecl{strType, "other"}},
                                              boolType, op::ComparisonOperator[op::NE])});
}

/// Initialize the data base and register builtin types
QTypeDB::QTypeDB() {
  this->registerNewType(ObjectStr, nullptr);
  registerBoolType(*this);
  registerNothingType(*this);
  registerIntegerType(*this);
  registerFloatType(*this);
  registerStringType(*this);
}

QType *QTypeDB::getObjectType() const { return this->at(ObjectStr).get(); }

QType *QTypeDB::getIntegerType() const { return this->at(IntegerStr).get(); }

QType *QTypeDB::getFloatType() const { return this->at(FloatStr).get(); }

QType *QTypeDB::getBoolType() const { return this->at(BoolStr).get(); }

QType *QTypeDB::getStringType() const { return this->at(StringStr).get(); }

QType *QTypeDB::getNothingType() const { return this->at(NothingStr).get(); }

bool QType::operator==(const QType &other) { return name == other.name; }

bool QType::operator!=(const QType &other) { return !(*this == other); }

const QMethod *QType::lookUpMethod(llvm::StringRef mname) const {
  if (!methods.count(mname))
    return nullptr;

  return &methods.find(mname)->second;
}
const QType *QType::lookUpMember(llvm::StringRef mname) const {
  if (!members.count(mname))
    return nullptr;

  return members.find(mname)->second;
}

QType *QTypeDB::registerNewType(const std::string &name, QType *parent) {
  assert(this->find(name) == this->end() && "Type is already registered");
  auto newType = std::make_unique<QType>(parent, name);
  this->insert({name, std::move(newType)});
  return this->at(name).get();
}

std::unique_ptr<JSONNode> QTypeDB::toJson() {
  auto l = make<ListNode>();
  for (auto &it : *this) {
    l->push_back(it.second->toJson());
  }
  return l;
}

QType *QTypeDB::getType(llvm::StringRef name) const {
  if (this->count(name) == 0)
    return nullptr;

  return this->at(name).get();
}

}