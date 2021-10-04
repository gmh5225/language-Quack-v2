//
// Created by Parsa Bagheri on 7/28/21.
//

#include "ClassesChecker.hpp"

#include <unordered_set>

namespace quack::semant {
bool ClassesChecker::traverseClasses(const Classes &classes) const {
  // First add the classes to the Type database, fill them in later
  bool success = true;
  for (const auto &clss : classes) {
    const auto &clssName = clss.getClassIdent().getName();
    if (_tdb->hasType(clssName)) {
      logError(clss, "type < " + clssName + " > is already declared");
      success = false;
    }
  }

  if (!success)
    return false;

  for (const auto &clss : classes) {
    const auto &clssName = clss.getClassIdent().getName();
    _tdb->insertType(std::make_unique<Type>(clssName, _codeGen->getContext()));
  }

  // Now visiting each class and defining the corresponding type
  for (const auto &clss : classes) {
    if (!traverseClass(clss))
      success = false;
  }

  return success;
}

static quack::Method parseMethod(const ast::Method &method, quack::Type *type,
                                 MethodKind kind) {

  std::vector<Parameter> params;
  params.emplace_back("this", type);
  auto *tdb = TypeDataBase::getTypeDB();
  auto &retTypeName = method.getReturnType().getName();
  auto *retType = tdb->getType(retTypeName);

  for (const auto &p : method.getParams().getSequence()) {
    if (auto *paramType = tdb->getType(p->getType().getName())) {
      Parameter param(p->getVar().getName(), paramType);
      params.push_back(std::move(param));
    }
  }

  auto &methodName = method.getMethodIdent().getName();
  return quack::Method(methodName + "_" + type->getName(), retType,
                       std::move(params), kind);
}

static std::unique_ptr<quack::Method>
parseConstructor(const ast::Method &method, quack::Type *type) {

  std::vector<Parameter> params;
  auto *tdb = TypeDataBase::getTypeDB();

  for (const auto &p : method.getParams().getSequence()) {
    if (auto *paramType = tdb->getType(p->getType().getName())) {
      Parameter param(p->getVar().getName(), paramType);
      params.push_back(std::move(param));
    }
  }

  auto &methodName = method.getMethodIdent().getName();
  return std::unique_ptr<quack::Method>(
      new quack::Method("new" + type->getName(), type, std::move(params),
                        MethodKind::Constructor));
}

static bool createVTable(const ast::Methods &methods, Type *type) {

  bool status = true;
  auto *superType = type->getSuper();
  auto &superMethods = superType->getMethods();
  std::vector<quack::Method> vtable;

  std::unordered_map<std::string, std::pair<unsigned, const quack::Method *>>
      methodIdxMap;
  for (unsigned idx = 0, end = superMethods.size(); idx < end; idx++) {
    auto *m = &superMethods[idx];
    methodIdxMap.insert({m->getNameWithoutPostfix(), {idx, m}});
  }

  // pushing super's method names to the vtable, fill them in later
  for (const auto &method : superType->getMethods()) {
    vtable.push_back(quack::Method(method.name, method.returnType,
                                   method.parameters, MethodKind::Inherit));
  }

  for (auto &method : methods) {
    auto &curMethodName = method.getMethodIdent().getName();
    MethodKind methodKind = MethodKind::New;

    int idx = -1;
    if (methodIdxMap.count(curMethodName)) {
      methodKind = MethodKind::Override;
      auto &pair = methodIdxMap[curMethodName];
      auto *m = pair.second;
      idx = pair.first;

      // Checking if the return types match
      if (!isACovariantOfB(m->returnType->getName(),
                           method.getReturnType().getName())) {
        logError(method, "return type doesn't match parent functions return "
                         "type");
        status = false;
      }

      // Checking if parameters match
      if (m->parameters.size() != method.getParams().getSequence().size() + 1) {
        logError(method, "number of parameters doesn't match parent classes "
                         "method, overloading is not supported");
        status = false;
      } else {

        for (size_t i = 1, end = m->parameters.size(); i < end; i++) {
          auto &paramA = m->parameters[i];
          auto &paramB = method.getParams().getSequence().at(i - 1);
          if (!isACovariantOfB(paramA.type->getName(),
                               paramB->getType().getName())) {
            logError(method, "parameter at index < " + std::to_string(i) +
                                 " > doesn't match"
                                 "parent classes method, overloading is not "
                                 "supported");
            status = false;
          }
        }
      }

      if (!status)
        return false;
    }

    // Now push overridden method to v table
    quack::Method m(parseMethod(method, type, methodKind));
    if (idx == -1)
      vtable.push_back(std::move(m));
    else {
      vtable[idx] = std::move(m);
    }
  }

  type->setMethods(std::move(vtable));

  return true;
}

/// This visitor will go over the constructor of a class and collects
/// its members and their types
class MemberVariableCollector : public CompoundStmtChecker {
  EnvironmentStack stack;
  TypeChecker typeChecker;
  mutable std::unordered_map<std::string, quack::Type *> members;

public:
  const auto &getMembers() const { return members; }

  MemberVariableCollector(const TranslationUnit &translationUnit,
                          Type *parentType)
      : CompoundStmtChecker(translationUnit, stack, typeChecker, parentType,
                            true /* isConstructor */),
        stack(), typeChecker(translationUnit, stack) {
    stack.push_back(Environment());
  }

  //  bool traverseCompoundStmt(const CompoundStmt &compStmt) const override {
  ////    if (!compStmtChecker.traverseCompoundStmt(compStmt))
  ////      return false;
  //
  //    return
  //    ASTVisitor<MemberVariableCollector>::traverseCompoundStmt(compStmt);
  //  }

  bool traverseAssignment(const Assignment &assignment) const override {
    if (auto *lhs =
            dynamic_cast<const MemberAccess *>(&assignment.getLeftHandSide())) {
      if (members.count(lhs->getMember().getName()) == 0) {
        if (typeChecker.traverseExpression(assignment.getRightHandSide())) {
          quack::Type *type = typeChecker.getCurType();
          members.insert({lhs->getMember().getName(), type});
        } else {
          return false;
        }
      }
    } else if (auto *lhs = dynamic_cast<const StaticMemberDecl *>(
                   &assignment.getLeftHandSide())) {
      if (members.count(lhs->getVar().getName()) == 0) {
        auto *tdb = TypeDataBase::getTypeDB();
        quack::Type *type = tdb->getType(lhs->getType().getName());
        if (type == nullptr) {
          logError(*lhs, "type < " + lhs->getType().getName() +
                             " > is not "
                             "defined");
          return false;
        }
        members.insert({lhs->getVar().getName(), type});
      }
    }

    return true;
  }

  bool traverseAST(const TranslationUnit &) const = delete; // shouldn't
                                                            // be used in this
                                                            // class
};

bool ClassesChecker::traverseClass(const Class &clss) const {
  // Grabbing the corresponding type and defining it based on clss
  Type *type = _tdb->getType(clss.getClassIdent().getName());

  // Is inheriting from valid class ?
  const auto &superName =
      (clss.getSuper() != nullptr) ? clss.getSuper()->getName() : "Object";
  if (!_tdb->hasType(superName)) {
    logError(*clss.getSuper(),
             "no type with name < " + superName + " > is defined");
    return false;
  }

  auto *superType = _tdb->getType(superName);

  type->setSuper(superType);

  type->setConstructor(parseConstructor(clss.getConstructor(), type));

  if (!createVTable(clss.getMethods(), type))
    return false;

  MemberVariableCollector mvc(_translationUnit, type);
  if (!mvc.traverseCompoundStmt(clss.getConstructor().getBody()))
    return false;

  auto &members = mvc.getMembers();
  type->setMembers(Parameter::createParametersFromMap(members));

  //  type->setConstructorType()
  auto &constructor = clss.getConstructor();
  std::vector<llvm::Type *> paramLLVMTypes;

  bool status = true;
  for (auto &p : constructor.getParams()) {
    if (auto *t = _tdb->getType(p.getType().getName())) {
      paramLLVMTypes.push_back(t->getLLVMType());
    } else {
      logError(p, "type < " + p.getType().getName() + " > is not defined");
      status = false;
    }
  }

  if (status)
    if (auto *resType = _tdb->getType(constructor.getReturnType().getName())) {
      auto *llvmResType = llvm::PointerType::getUnqual(resType->getLLVMType());
      if (auto *fnType =
              llvm::FunctionType::get(llvmResType, paramLLVMTypes, false))
        type->setConstructorType(fnType);
      else
        status = false;
    }
  return status;
}

} // namespace quack::semant