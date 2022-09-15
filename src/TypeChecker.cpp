//
// Created by parsab on 6/12/22.
//

#include "TypeChecker.hpp"
#include "ClassVerifier.hpp"
#include "StmtVerifier.hpp"

namespace quick {
namespace sema {

static int registerClasses(std::fstream &file, type::QTypeDB &tdb,
                           const Classes &clsses) {
  int numErrors = 0;
  // Registering all classes
  for (auto &clss : clsses) {
    auto &className = clss->getClassIdent().getName();
    if (tdb.getType(className)) {
      logError(file, clss->getClassIdent().getLocation(),
               "redefinition of class <" + className + ">");
      numErrors++;
    } else {
      tdb.registerNewType(className, nullptr);
    }
  }
  return numErrors;
}

// static int processMembers(std::fstream &file, type::QTypeDB &tdb, const
// Classes &clsses) {
//   for (auto &clss : clsses) {
//     auto curType = tdb.getType(clss->getClassIdent().getName());
//     for (auto &stmt: clss->getConstructor().getBody()) {
//       if (auto assignment = stmt->as_a<Assignment>()) {
//         if (auto memberAccess = assignment->getLHS().as_a<MemberAccess>()) {
//           if (auto identExpr =
//           memberAccess->getObject().as_a<IdentifierExpression>()) {
//             if (identExpr->getVarName() == "this") {
//               memberAccess->getVarName()
//             }
//           }
//         }
//       } else if (auto staticAssign = stmt->as_a<StaticAssignment>()) {
//
//       }
//     }
//   }
// }

static int processMembers(std::fstream &file, type::QTypeDB &tdb,
                          const Classes &clsses) {
  int numErrors = 0;
  for (auto &clss : clsses) {
    auto type = tdb.getType(clss->getClassIdent().getName());
    assert(type);
//    auto members = type->getParent()->getMembers();
//    int cntr = members.size();
//    auto &body = clss->getConstructor().getBody();
//    for (auto &stmt: body) {
//      if (auto *assignment = stmt->as_a<Assignment>()) {
//        if (auto *memAccess = assignment->getLHS().as_a<MemberAccess>()) {
//          if (auto *identExpr = memAccess->getObject().as_a<IdentifierExpression>()) {
//            if (identExpr->getVarName() == "this") {
//              if (members.count(memAccess->getVarName()))
//                continue ;
//
//              assignment->getRHS();
//              members.insert({memAccess->getVarName(), {cntr++, }})
//            }
//          }
//        }
//      } else if (auto *staticAssign = stmt->as_a<StaticAssignment>()) {
//
//      }
//    }

    sema::Env env;
    auto &scope = env.addNewScope();
    scope.insert({"this", type});
    for (auto &params: clss->getConstructor().getParams()) {
      auto &pt = params->getType().getName();
      auto &v = params->getVar().getName();
      auto *pQtype  = tdb.getType(pt);
      scope.insert({v, pQtype});
    }
    StmtVerifier constructorVerifier(file, clss->getConstructor().getBody(),
                                     env, type, type, true);
    if (!constructorVerifier.visitCompoundStmt(clss->getConstructor().getBody()))
      numErrors++;
  }
  return numErrors;
}

static int processSuperTypes(std::fstream &file, type::QTypeDB &tdb,
                             const Classes &clsses) {
  int numErrors = 0;
  for (auto &clss : clsses) {
    auto super = clss->getSuper();
    auto &className = clss->getClassIdent().getName();
    type::QType *superType = nullptr;
    if (super) {
      auto &superName = super->getName();
      superType = tdb.getType(superName);
      if (!superType) {
        numErrors++;
        logError(file, clss->getSuper()->getLocation(),
                 "type not found <" + superName + ">");
      }
    } else {
      superType = tdb.getType("Object");
    }

    if (superType) {
      auto type = tdb.getType(className);
      type->setParent(superType);
    }
  }
  return numErrors;
}

static int processMethods(std::fstream &file, type::QTypeDB &tdb,
                          const Classes &clsses) {
  int numErrors = 0;
  for (auto &clss : clsses) {
    auto super = clss->getSuper();
    auto &className = clss->getClassIdent().getName();
    auto type = tdb.getType(className);
    auto process = [&](const Method *m){
      std::vector<type::QVarDecl> formals;
      bool status = true;
      for (auto &p : m->getParams()) {
        auto pType = tdb.getType(p->getType().getName());
        if (!pType) {
          numErrors++;
          logError(file, p->getLocation(),
                   "parameter type <" + p->getType().getName() +
                       "> does not exist.");
          status = false;
        } else {
          formals.push_back({pType, p->getVar().getName()});
        }
      }

      auto retType = tdb.getType(m->getReturnType().getName());
      if (!retType) {
        logError(file, m->getReturnType().getLocation(),
                 "return does not exist");
        status = false;
        numErrors++;
      }

      if (status)
        type->insertMethod(m->getMethodIdent().getName(), retType, formals);
    };
    process(&clss->getConstructor());
    for (auto &m : clss->getMethods()) {
      process(m.get());
    }
  }

  return numErrors;
}

static bool hasCircularInheritance(const Class &clss, type::QTypeDB &tdb) {
  auto *superIdent = clss.getSuper();
  if (!superIdent)
    return false;

  auto &superName = superIdent->getName();
  auto *qtype = tdb.getType(superName);
  auto &typeName = clss.getClassIdent().getName();
  while (qtype) {
    if (qtype->getName() == typeName)
      return true;
    qtype = qtype->getParent();
  }
  return false;
}

bool TypeChecker::verify() {
  Env environment;
  int numErrors = 0;
  auto &tdb = type::QTypeDB::get();

  numErrors += registerClasses(file, tdb, tu.getClasses());
  numErrors += processSuperTypes(file, tdb, tu.getClasses());
  numErrors += processMethods(file, tdb, tu.getClasses());
  numErrors += processMembers(file, tdb, tu.getClasses());
  for (auto &clss : tu.getClasses()) {
    if (hasCircularInheritance(*clss, tdb)) {
      logError(file, clss->getSuper()->getLocation(),
               "circular inheritance detected");
      return false;
    }
  }

  if (numErrors) {
    std::cerr << "total errors: " << numErrors << "\n";
    return false;
  }

  // Checking classes
  for (auto &clss : tu.getClasses()) {
    ClassVerifier cv(file, *clss);
    if (!cv.verify())
      numErrors++;
  }

  // Checking main
  StmtVerifier stmtTypeChecker(file, tu.getCompoundStmt(), environment, nullptr,
                               tdb.getIntegerType());
  if (!stmtTypeChecker.isLegal())
    numErrors++;

  if (!numErrors)
    return true;

  std::cerr << "total errors: " << numErrors << "\n";
  return false;
}

} // namespace sema
} // namespace quick