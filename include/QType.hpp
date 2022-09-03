//
// Created by parsab on 6/9/22.
//

#ifndef QUACK_QTYPE_HPP
#define QUACK_QTYPE_HPP

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

#include "AST.hpp"
#include "Json.hpp"
#include "Utils.hpp"

#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace quick::type {

class QType;

/// Builtin types
constexpr char ObjectStr[] = "Object";
constexpr char IntegerStr[] = "Integer";
constexpr char FloatStr[] = "Float";
constexpr char StringStr[] = "String";
constexpr char BoolStr[] = "Boolean";
constexpr char NothingStr[] = "Nothing";

/// ===-------------------------------------------------------------------=== //
/// Unary/Binary operation keywords
/// ===-------------------------------------------------------------------=== //
namespace op {
enum ARITH_OP { ADD = 0, SUB, MUL, DIV, MOD };
constexpr const char *ArithmeticOperator[] = {"__add__", "__sub__", "__mul__",
                                              "__div__", "__mod__"};

enum UN_OP { NEG = 0, NOT };
constexpr const char *UnaryOperator[] = {"__neg__", "__not__"};

enum COMP_OP { EQ = 0, NE, LE, LT, GE, GT };
constexpr const char *ComparisonOperator[] = {"__eq__", "__ne__", "__le__",
                                              "__lt__", "__ge__", "__gt__"};
} // namespace op

struct QVarDecl {
  QType *type;
  std::string name;
};

/// ===-------------------------------------------------------------------=== //
/// A Quick type's method internal representation
/// ===-------------------------------------------------------------------=== //
class QMethod {
public:
  enum class Kind { Override, New, Constructor };
  QMethod(QType *type, llvm::ArrayRef<QVarDecl> actuals, QType *retType,
          llvm::StringRef name, Kind kind = Kind::New)
      : type(type), actuals(actuals.begin(), actuals.end()),
        returnType(retType), name(name), kind(kind) {}
  bool operator==(const QMethod &);

  const llvm::SmallVector<QVarDecl, 6> &getActuals() const { return actuals; }
  QType *getReturnType() const { return returnType; }
  std::string getName() const { return name; }
  QType *getType() const { return type; }
  Kind getKind() const { return kind; }

  std::unique_ptr<json::JSONNode> toJson();

private:
  llvm::SmallVector<QVarDecl, 6> actuals;
  QType *returnType;
  std::string name;
  QType *type;
  Kind kind;
};

/// ===-------------------------------------------------------------------=== //
/// A Quick type internal representation
/// ===-------------------------------------------------------------------=== //
class QType {
  QType *parent;
  std::string name;
  llvm::MapVector<llvm::StringRef, QType *> members;
  llvm::MapVector<llvm::StringRef, QMethod> methods;

public:
  QType(QType *parent, llvm::StringRef name) : parent(parent), name(name) {}
  bool operator==(const QType &);
  bool operator!=(const QType &);

  // Getters
  QType *getParent() { return parent; }
  const std::string &getName() const { return name; }
  llvm::MapVector<llvm::StringRef, QType *> &getMembers() { return members; }
  llvm::MapVector<llvm::StringRef, QMethod> &getMethods() { return methods; }

  // Builds types members and methods
  bool insertMethod(const std::string &name, QType *retType,
                    llvm::ArrayRef<QVarDecl> = {});
  bool insertMember(const QVarDecl &);

  // Utility
  QType *lowestCommonAncestor(const QType *) const;
  bool isDescendentOf(const QType *) const;
  const QMethod *lookUpMethod(llvm::StringRef) const;
  const QType *lookUpMember(llvm::StringRef) const;
  std::unique_ptr<json::JSONNode> toJson();
};

} // namespace quick::type

#endif // QUACK_QTYPE_HPP
