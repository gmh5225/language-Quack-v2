//
// Created by parsab on 9/4/22.
//
#include "Runtime.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

#define INIT_OBJ(OBJ, ID)                                                      \
  do {                                                                         \
    OBJ->__ref = 1;                                                            \
    OBJ->__id = ID;                                                            \
  } while (false)

#define DROP_REF(OBJ)                                                          \
  do {                                                                         \
    if (--OBJ->__ref > 0)                                                      \
      return;                                                                  \
  } while (false)

extern "C" {

String_t *Object__str__(Object_t *self) {
  std::stringstream ss;
  ss << self;
  auto s = ss.str();
  return String_create(s.c_str());
}

bool Object__eq__Object(Object_t *self, Object_t *other) {
  return self == other;
}

void Object__del__(Object_t *self) {
  DROP_REF(self);
  std::free(self);
}

Object_t *Object_create() {
  Object_t *obj = (Object_t *)std::malloc(sizeof(Object_t));
  obj->vtable = &ObjectVtable;
  INIT_OBJ(obj, ObjectID);
  return obj;
}

String_t *String__str__(String_t *self) {
  return self;
}

bool String__eq__String(String_t *self, String_t *other) {
  return std::strcmp(self->__data, other->__data) == 0;
}

void String__del__(String_t *self) {
  DROP_REF(self);
  std::free(self->__data);
  std::free(self);
}

String_t *String_create(const char *str) {
  String_t *obj = (String_t *)std::malloc(sizeof(String_t));
  obj->vtable = &StringVtable;
  obj->__data = (char *)std::malloc(sizeof(std::strlen(str)));
  std::strcpy(obj->__data, str);
  INIT_OBJ(obj, StringID);
  return obj;
}
}