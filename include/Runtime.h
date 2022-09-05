//
// Created by parsab on 9/4/22.
//

#ifndef QUICK_RUNTIME_H
#define QUICK_RUNTIME_H

#include <cstdint>

extern "C" {

typedef enum TypeID {
  ObjectID = -6,
  IntegerID,
  FloatID,
  BooleanID,
  StringID,
  NothingID = -1
} TypeID_t ;

//typedef struct Q_Bool Bool_t;
//typedef struct Q_Integer Integer_t;
//typedef struct Q_Float Float_t;
typedef struct Q_String String_t;
typedef struct Q_Object Object_t;

typedef struct Q_Object_vtable {
  bool (*__eq__Object)(Object_t *, Object_t *);
  String_t *(*__str__)(Object_t *);
  void (*__del__)(Object_t *);
} Object_vtable_t;

struct Q_Object {
  Object_vtable_t *vtable;
  int32_t __ref;
  int32_t __id;
};

String_t *Object__str__(Object_t *);
bool Object__eq__Object(Object_t *, Object_t *);
void Object__del__(Object_t *);

static Object_vtable_t ObjectVtable = {Object__eq__Object, Object__str__,
                                       Object__del__};

Object_t *Object_create();

typedef struct Q_String_vtable {
  bool (*__eq__String)(String_t *, String_t *); // override
  String_t *(*__str__)(String_t *);             // override
  void (*__del__)(String_t *);                  // override
} String_vtable_t;

struct Q_String {
  String_vtable_t *vtable;
  int32_t __ref;
  int32_t __id;
  char *__data;
};

String_t *String__str__(String_t *);
bool String__eq__String(String_t *, String_t *);
void String__del__(String_t *);

static String_vtable_t StringVtable = {String__eq__String, String__str__,
                                       String__del__};

String_t *String_create(const char *str);

};

#endif // QUICK_RUNTIME_H
