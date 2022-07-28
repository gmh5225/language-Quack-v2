//
// Created by parsab on 6/9/22.
//

#include "QType.hpp"
#include "ASTVisitor.hpp"

using namespace llvm;

namespace quack {
namespace type {

using namespace json;

bool QMethod::operator==(const QMethod &other) {
  return *type == *other.type && name == other.name;
}

std::unique_ptr<JSONNode> QMethod::toJson() {
  auto m = make<DictionaryNode>();
  m->insert({"name", make<StringNode>(name)});

  std::string k;
  switch (kind) {
  case Kind::Constructor:
    k = "Constructor";
    break;
  case Kind::New:
    k = "New";
    break;
  case Kind::Override:
    k = "Override";
    break;
  }

  m->insert({"kind", make<StringNode>(k)});
  m->insert({"return_type", make<StringNode>(returnType->getName())});

  if (!actuals.empty()) {
    auto l = make<ListNode>();
    for (auto &it : actuals)
      l->push_back(make<StringNode>(it.type->getName()));

    m->insert({"args", std::move(l)});
  }

  return m;
}

std::unique_ptr<JSONNode> QType::toJson() {
  auto t = make<DictionaryNode>();
  t->insert({"name", make<StringNode>(name)});
  if (parent)
    t->insert({"parent", make<StringNode>(parent->name)});

  if (!members.empty()) {
    auto mmL = make<ListNode>();
    for (auto &m : members) {
      mmL->push_back(make<StringNode>(m.second->name));
    }
    t->insert({"members", std::move(mmL)});
  }

  if (!methods.empty()) {
    auto mtdsL = make<ListNode>();
    for (auto &m : methods) {
      mtdsL->push_back(m.second.toJson());
    }
    t->insert({"methods", std::move(mtdsL)});
  }

  return t;
}

bool QType::insertMember(const NamedVar &namedVar) {
  if (members.count(namedVar.name) != 0)
    return false;

  members.insert({namedVar.name, namedVar.type});
  return true;
}

bool QType::insertMethod(const std::string &mName, QType *retType,
                         llvm::ArrayRef<NamedVar> args) {
  if (methods.count(mName) != 0)
    return false;

  auto isConstructor = [&] { return name == mName; };

  auto isOverride = [&]() -> Optional<QMethod *> {
    QType *p = parent;
    while (p != nullptr) {
      auto it = p->methods.find(mName);
      if (it != p->methods.end())
        return &it->second;

      p = p->parent;
    }
    return None;
  };

  QMethod::Kind kind = QMethod::Kind::New;
  if (isConstructor())
    kind = QMethod::Kind::Constructor;
  else if (auto opt = isOverride()) {
    auto *method = opt.getValue();
    if (method->getActuals().size() != args.size())
      return false;

    for (auto [actualArg, arg] : llvm::zip(method->getActuals(), args)) {
      if (actualArg.type != arg.type &&
          !arg.type->isDescendentOf(actualArg.type))
        return false;
    }
    kind = QMethod::Kind::Override;
  }

  methods.insert({mName, QMethod(this, args, retType, mName, kind)});
  return true;
}

QType *QType::lowestCommonAncestor(const QType *other) const {
  auto *t = const_cast<QType *>(this);
  while (other != t && !other->isDescendentOf(t)) {
    if (!t)
      return nullptr;
    t = t->parent;
  }
  return t;
}

bool QType::isDescendentOf(const QType *other) const {
  auto *p = parent;
  while (p) {
    if (p == other)
      return true;

    p = p->parent;
  }
  return false;
}

// class TypeRegisterer : public ast::ASTVisitor<TypeRegisterer, bool> {
// public:
//   using ast::ASTVisitor<TypeRegisterer, bool>::ASTVisitor;
//
//   bool visitClass(const ast::Class &theClass) {}
// };

} // namespace type
} // namespace quack