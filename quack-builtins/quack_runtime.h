#ifndef QUACK_RUNTIME_H
#define QUACK_RUNTIME_H

#include <stdlib.h>
#include <string.h>

#define DISPATCH(OBJ, METHOD) OBJ->__vtable->METHOD

typedef struct Object Object_t;
typedef struct ObjectVTable ObjectVTable_t;

typedef struct Integer Integer_t;
typedef struct IntegerVTable IntegerVTable_t;

typedef struct Float Float_t;
typedef struct FloatVTable FloatVTable_t;

typedef struct Boolean Boolean_t;
typedef struct BooleanVTable BooleanVTable_t;

typedef struct String String_t;
typedef struct StringVTable StringVTable_t;

typedef struct Nothing Nothing_t;
typedef struct NothingVTable NothingVTable_t;

typedef enum TypeID {
  ObjectID = -6,
  IntegerID,
  FloatID,
  BooleanID,
  StringID,
  NothingID = -1
} TypeID_t ;

/// Objects runtime type information
typedef struct header {
  size_t __refCount;
  TypeID_t __typeID;
} header_t;

void initHeader(Object_t *, int typeID);
void incrementRefCounter(Object_t *object);
int decrementRefCounter(Object_t *object);


///
/// Top level object
/// ===-------------------------
///

struct Object {
  header_t __header;
  ObjectVTable_t *__vtable;
};

// Object's v-table(method table)
struct ObjectVTable {
  Boolean_t *(*equals)(Object_t *, Object_t *);
  Nothing_t *(*print)(Object_t *);
  Nothing_t *(*destroy)(Object_t *);
};

Object_t *newObject();

///
/// Integer type and it's v-table
/// ===-------------------------
///

struct Integer {
  header_t __header;
  IntegerVTable_t *__vtable;
  long int __int;
};

struct IntegerVTable {
  Boolean_t *(*equals)(Integer_t *, Integer_t *); // override
  Nothing_t *(*print)(Integer_t *); // override
  Nothing_t *(*destroy)(Object_t *); // inherit

  // new methods
  Boolean_t *(*lt)(Integer_t *, Integer_t *);
  Boolean_t *(*lte)(Integer_t *, Integer_t *);
  Boolean_t *(*gt)(Integer_t *, Integer_t *);
  Boolean_t *(*gte)(Integer_t *, Integer_t *);
  Integer_t *(*add)(Integer_t *, Integer_t *);
  Integer_t *(*mul)(Integer_t *, Integer_t *);
  Integer_t *(*sub)(Integer_t *, Integer_t *);
  Integer_t *(*div)(Integer_t *, Integer_t *);
  Integer_t *(*mod)(Integer_t *, Integer_t *);
};

Integer_t *newInteger(long int theInt);

///
/// Float Type
/// ===-------------------------
///

struct Float {
  header_t __header;
  FloatVTable_t *__vtable;
  double __float;
};

struct FloatVTable {
  Boolean_t *(*equals)(Float_t *, Float_t *); // override
  Nothing_t *(*print)(Float_t *); // override
  Nothing_t *(*destroy)(Object_t *); // inherit

  // new methods
  Boolean_t *(*lt)(Float_t *, Float_t *);
  Boolean_t *(*lte)(Float_t *, Float_t *);
  Boolean_t *(*gt)(Float_t *, Float_t *);
  Boolean_t *(*gte)(Float_t *, Float_t *);
  Float_t *(*add)(Float_t *, Float_t *);
  Float_t *(*mul)(Float_t *, Float_t *);
  Float_t *(*sub)(Float_t *, Float_t *);
  Float_t *(*div)(Float_t *, Float_t *);
};

Float_t *newFloat(double theFloat);

///
/// Boolean Type
/// ===-------------------------
///

struct Boolean {
  header_t __header;
  BooleanVTable_t *__vtable;
  long int __bool;
};

struct BooleanVTable {
  Boolean_t *(*equals)(Boolean_t *, Boolean_t *); // override
  Nothing_t *(*print)(Boolean_t *); // override
  Nothing_t *(*destroy)(Boolean_t *); // override
};

Boolean_t *newBoolean(long int theBool);
int isFalse(Boolean_t *);
int isTrue(Boolean_t *);

///
/// Nothing Type
/// ===-------------------------
///

struct Nothing {
  header_t __header;
  NothingVTable_t *__vtable;
};

struct NothingVTable {
  Boolean_t *(*equals)(Nothing_t *, Nothing_t *); // override
  Nothing_t *(*print)(Nothing_t *); // override
  Nothing_t *(*destroy)(Nothing_t *); // override
};

Nothing_t *newNothing();

///
/// String Type
/// ===-------------------------
///

struct String {
  header_t __header;
  StringVTable_t *__vtable;
  char *__text;
};

struct StringVTable {
  Boolean_t *(*equals)(String_t *, String_t *);
  Nothing_t *(*print)(String_t *);
  Nothing_t *(*destroy)(String_t *);

  // new methods
  String_t *(*add)(String_t *, String_t *);
};

String_t *newString(const char *);


// The builtin methods
// Object
extern Boolean_t *equals_Object(Object_t *, Object_t *);
extern Nothing_t *print_Object(Object_t *);
extern Nothing_t *destroy_Object(Object_t *);

// Nothing
extern Boolean_t *equals_Nothing(Nothing_t *, Nothing_t *);
extern Nothing_t *print_Nothing(Nothing_t *);
extern Nothing_t *destroy_Nothing(Nothing_t *);

// Boolean
extern Boolean_t *equals_Boolean(Boolean_t *, Boolean_t *);
extern Nothing_t *print_Boolean(Boolean_t *);
extern Nothing_t *destroy_Boolean(Boolean_t *);

// Integer
extern Boolean_t *equals_Integer(Integer_t *, Integer_t *);
extern Nothing_t *print_Integer(Integer_t *);
extern Boolean_t *lt_Integer(Integer_t *, Integer_t *);
extern Boolean_t *lte_Integer(Integer_t *, Integer_t *);
extern Boolean_t *gt_Integer(Integer_t *, Integer_t *);
extern Boolean_t *gte_Integer(Integer_t *, Integer_t *);
extern Integer_t *add_Integer(Integer_t *, Integer_t *);
extern Integer_t *mul_Integer(Integer_t *, Integer_t *);
extern Integer_t *sub_Integer(Integer_t *, Integer_t *);
extern Integer_t *div_Integer(Integer_t *, Integer_t *);
extern Integer_t *mod_Integer(Integer_t *, Integer_t *);

// Float
extern Boolean_t *equals_Float(Float_t *, Float_t *);
extern Nothing_t *print_Float(Float_t *);
extern Boolean_t *lt_Float(Float_t *, Float_t *);
extern Boolean_t *lte_Float(Float_t *, Float_t *);
extern Boolean_t *gt_Float(Float_t *, Float_t *);
extern Boolean_t *gte_Float(Float_t *, Float_t *);
extern Float_t *add_Float(Float_t *, Float_t *);
extern Float_t *mul_Float(Float_t *, Float_t *);
extern Float_t *sub_Float(Float_t *, Float_t *);
extern Float_t *div_Float(Float_t *, Float_t *);

// String
extern Boolean_t *equals_String(String_t *, String_t *);
extern Nothing_t *print_String(String_t *);
extern Nothing_t *destroy_String(String_t *);
extern String_t *add_String(String_t *, String_t *);

#endif