//
// Created by parsab on 9/4/22.
//

#ifndef QUICK_RUNTIME_H
#define QUICK_RUNTIME_H

#include <cstdint>
#include <functional>

extern "C" {

typedef enum TypeID {
  ObjectID = -6,
  IntegerID,
  FloatID,
  BooleanID,
  StringID,
  NothingID = -1
} TypeID_t;

// typedef struct Q_Bool Bool_t;
// typedef struct Q_Integer Integer_t;
// typedef struct Q_Float Float_t;
typedef struct Q_String String_t;
typedef struct Q_Object Object_t;
typedef struct Q_Nothing Nothing_t;

/// ===-------------------------------------------------------------------=== //
/// Object Type -- every other class inherits its vtable and members
/// ===-------------------------------------------------------------------=== //
typedef struct Q_Object_vtable {
  bool (*__eq__Object)(Object_t *, Object_t *);
  bool (*__ne__Object)(Object_t *, Object_t *);
  String_t *(*__str__)(Object_t *);
  void (*__del__)(Object_t *);
} Object_vtable_t;

struct Q_Object {
  Object_vtable_t *vtable;
  int32_t __ref;
  int32_t __id;
};

bool Object__eq__Object(Object_t *, Object_t *);
bool Object__ne__Object(Object_t *, Object_t *);
String_t *Object__str__(Object_t *);
void Object__del__(Object_t *);

static Object_vtable_t ObjectVtable = {Object__eq__Object, Object__ne__Object,
                                       Object__str__, Object__del__};

Object_t *Object_create();

/// ===-------------------------------------------------------------------=== //
/// Nothing Type
/// ===-------------------------------------------------------------------=== //
typedef struct Q_Nothing_vtable {
  bool (*__eq__Object)(Object_t *, Object_t *);    // inherit
  bool (*__ne__Object)(Object_t *, Object_t *);    // inherit
  String_t *(*__str__)(Nothing_t *);               // override
  void (*__del__)(Nothing_t *);                    // override
  bool (*__eq__Nothing)(Nothing_t *, Nothing_t *); // new method
  bool (*__ne__Nothing)(Nothing_t *, Nothing_t *); // new method
} Nothing_vtable_t;

struct Q_Nothing {
  Nothing_vtable_t *vtable;
  int32_t __ref;
  int32_t __id;
};

String_t *Nothing__str__(Nothing_t *);
void Nothing__del__(Nothing_t *);
bool Nothing__eq__Nothing(Nothing_t *, Nothing_t *);
bool Nothing__ne__Nothing(Nothing_t *, Nothing_t *);

static Nothing_vtable_t NothingVtable = {
    Object__eq__Object, Object__ne__Object,   Nothing__str__,
    Nothing__del__,     Nothing__eq__Nothing, Nothing__ne__Nothing};

Nothing_t *Nothing_create();

/// ===-------------------------------------------------------------------=== //
/// String Type
/// ===-------------------------------------------------------------------=== //
typedef struct Q_String_vtable {
  bool (*__eq__Object)(Object_t *, Object_t *);       // inherit
  bool (*__ne__Object)(Object_t *, Object_t *);       // inherit
  String_t *(*__str__)(String_t *);                   // override
  void (*__del__)(String_t *);                        // override
  bool (*__eq__String)(String_t *, String_t *);       // new method
  bool (*__ne__String)(String_t *, String_t *);       // new method
  String_t *(*__add__String)(String_t *, String_t *); // new method
} String_vtable_t;

struct Q_String {
  String_vtable_t *vtable;
  int32_t __ref;
  int32_t __id;
  void *__data;
};

String_t *String__str__(String_t *);
bool String__eq__String(String_t *, String_t *);
bool String__ne__String(String_t *, String_t *);
void String__del__(String_t *);
String_t *String__add__String(String_t *, String_t *);

static String_vtable_t StringVtable = {
    Object__eq__Object, Object__ne__Object, String__str__,      String__del__,
    String__eq__String, String__ne__String, String__add__String};

String_t *String_create(const char *str);
}

/// ===-------------------------------------------------------------------=== //
/// a function for registering the addresses of runtime functions
/// to be linked in during JIT executing
/// ===-------------------------------------------------------------------=== //
void registerRuntimeFunctions(
    const std::function<void(const std::string &sym, void *addr)> &registerFn);

#endif // QUICK_RUNTIME_H
