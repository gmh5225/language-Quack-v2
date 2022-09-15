//
// Created by parsab on 9/4/22.
//
#include "Runtime.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

extern "C" {

/// ===-------------------------------------------------------------------=== //
/// Object Type
/// ===-------------------------------------------------------------------=== //
Object_vtable_t ObjectVtable = {nullptr, Object__eq__Object, Object__ne__Object,
                                Object__str__, Object__del__};

String_t *Object__str__(Object_t *self) {
  std::stringstream ss;
  ss << self;
  auto s = ss.str();
  return String_create(s.c_str());
}

bool Object__eq__Object(Object_t *self, Object_t *other) {
  return self == other;
}

bool Object__ne__Object(Object_t *self, Object_t *other) {
  return self != other;
}

void Object__del__(Object_t *self) { std::free(self); }

Object_t *Object_create() {
  Object_t *obj = (Object_t *)std::malloc(sizeof(Object_t));
  obj->vtable = &ObjectVtable;
  return obj;
}

Object_vtable_t *Object_get_vtable() { return &ObjectVtable; }

void Object_init(Object_t *) {}

/// ===-------------------------------------------------------------------=== //
/// Nothing Type
/// ===-------------------------------------------------------------------=== //

static Nothing_vtable_t NothingVtable = {
    &ObjectVtable,  Object__eq__Object,   Object__ne__Object,  Nothing__str__,
    Nothing__del__, Nothing__eq__Nothing, Nothing__ne__Nothing};

Nothing_t None = {&NothingVtable};

String_t *Nothing__str__(Nothing_t *) { return String_create("None"); }

void Nothing__del__(Nothing_t *) {}

bool Nothing__ne__Nothing(Nothing_t *a, Nothing_t *b) { return a != b; }

bool Nothing__eq__Nothing(Nothing_t *a, Nothing_t *b) { return a == b; }

Nothing_t *Nothing_create() { return &None; }

Nothing_vtable_t *Nothing_get_vtable() { return &NothingVtable; }

/// ===-------------------------------------------------------------------=== //
/// String Type
/// ===-------------------------------------------------------------------=== //

String_vtable_t StringVtable = {
    &ObjectVtable, Object__eq__Object, Object__ne__Object, String__str__,
    String__del__, String__eq__String, String__ne__String, String__add__String};

String_t *String__str__(String_t *self) { return self; }

bool String__eq__String(String_t *self, String_t *other) {
  auto *s1 = (std::string *)self->__data;
  auto *s2 = (std::string *)other->__data;
  return *s1 == *s2;
}

bool String__ne__String(String_t *self, String_t *other) {
  auto *s1 = (std::string *)self->__data;
  auto *s2 = (std::string *)other->__data;
  return *s1 != *s2;
}

String_t *String__add__String(String_t *self, String_t *other) {
  auto *s1 = (std::string *)self->__data;
  auto *s2 = (std::string *)other->__data;
  std::string tmp;
  tmp.reserve(s1->size() + s2->size());
  tmp += *s1;
  tmp += *s2;
  return String_create(tmp.c_str());
}

void String__del__(String_t *self) {
  auto *str = (std::string *)self->__data;
  delete str;
  std::free(self);
}

const char *String_getData(String_t *str) {
  auto *s = (std::string *)str->__data;
  return s->c_str();
}

String_t *String_create(const char *str) {
  String_t *obj = (String_t *)std::malloc(sizeof(String_t));
  obj->vtable = &StringVtable;
  obj->__data = (void *)new std::string(str);
  return obj;
}

String_vtable_t *String_get_vtable() { return &StringVtable; }

/// ===-------------------------------------------------------------------=== //
/// traverses the v table of a's type hierarchy until we find a match
/// otherwise it's not a subtype
/// ===-------------------------------------------------------------------=== //
bool is_subtype(Object_vtable_t *a, Object_vtable_t *b) {
  if (a == b)
    return true;
  if (a->superVtable == nullptr)
    return false;
  return is_subtype(a->superVtable, b);
}
}

#define STR_SYM(FN) #FN, (void *)&FN

void registerRuntimeFunctions(
    const std::function<void(const std::string &sym, void *addr)> &registerFn) {
  // object
  registerFn(STR_SYM(ObjectVtable));
  registerFn(STR_SYM(Object_get_vtable));
  registerFn(STR_SYM(Object_create));
  registerFn(STR_SYM(Object_init));
  registerFn(STR_SYM(Object__eq__Object));
  registerFn(STR_SYM(Object__ne__Object));
  registerFn(STR_SYM(Object__str__));
  registerFn(STR_SYM(Object__del__));

  // nothing
  registerFn(STR_SYM(NothingVtable));
  registerFn(STR_SYM(Nothing_get_vtable));
  registerFn(STR_SYM(Nothing_create));
  registerFn(STR_SYM(Nothing__str__));
  registerFn(STR_SYM(Nothing__del__));

  // string
  registerFn(STR_SYM(StringVtable));
  registerFn(STR_SYM(String_get_vtable));
  registerFn(STR_SYM(String_getData));
  registerFn(STR_SYM(String_create));
  registerFn(STR_SYM(String__str__));
  registerFn(STR_SYM(String__eq__String));
  registerFn(STR_SYM(String__ne__String));
  registerFn(STR_SYM(String__del__));
  registerFn(STR_SYM(String__add__String));

  // runtime helpers
  registerFn(STR_SYM(is_subtype));
}
