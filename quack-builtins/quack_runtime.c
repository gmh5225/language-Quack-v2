#include "quack_runtime.h"

#include <assert.h>
#include <stdio.h>


/// Garbage Collection Facility
/// ===------------------------
void incrementRefCounter(Object_t *object) {
  object->__header.__refCount++;
}

int decrementRefCounter(Object_t *object) {
  return --(object->__header.__refCount);
}

/// Initializing the header of each object
/// ===------------------------
void initHeader(Object_t *obj, int typeID) {
  header_t *header = &(obj->__header);
  header->__refCount = 0;
  header->__typeID = typeID;
}

/// Declating the VTables
/// ===---------------------------

static ObjectVTable_t ObjectVTTemplate = {
  equals_Object,
  print_Object,
  destroy_Object
};

static NothingVTable_t NothingVTTemplate = {
  equals_Nothing,
  print_Nothing,
  destroy_Nothing
};

static Nothing_t Nothing = {
  {
    0, // ref counter
    NothingID
  },
  &NothingVTTemplate
};

static BooleanVTable_t BooleanVTTemplate = {
  equals_Boolean,
  print_Boolean,
  destroy_Boolean
};

static Boolean_t True = {
  {
    0, // ref counter
    BooleanID
  }, // header
  &BooleanVTTemplate,
  1 // true
};

static Boolean_t False = {
  {
    0, // ref counter
    BooleanID
  }, // header
  &BooleanVTTemplate,
  0 // false
};

int isFalse(Boolean_t *object) {
  return object->__bool == 0;
}

int isTrue(Boolean_t *object) {
  return object->__bool == 1;
}

static IntegerVTable_t IntegerVTTemplate = {
  equals_Integer,
  print_Integer,
  destroy_Object,
  lt_Integer,
  lte_Integer,
  gt_Integer,
  gte_Integer,
  add_Integer,
  mul_Integer,
  sub_Integer,
  div_Integer,
  mod_Integer
};

static FloatVTable_t FloatVTTemplate = {
  equals_Float,
  print_Float,
  destroy_Object,
  lt_Float,
  lte_Float,
  gt_Float,
  gte_Float,
  add_Float,
  mul_Float,
  sub_Float,
  div_Float
};

static StringVTable_t StringVTTemplate = {
  equals_String,
  print_String,
  destroy_String,
  add_String
};

/// Implementing Objects VTable
/// ===------------------------
Object_t *newObject() {
  Object_t *newObj = (Object_t *)malloc(sizeof(Object_t));
  assert(newObj);
  initHeader((Object_t *)newObj, ObjectID);
  newObj->__vtable = &ObjectVTTemplate;
  return newObj;
}

Boolean_t *equals_Object(Object_t *this, Object_t *other) {
  return (this == other) ? &True : &False;
}

Nothing_t *print_Object(Object_t *object) {
  printf("<Object at %08lx>\n", (unsigned long)object);
  return &Nothing;
}

Nothing_t *destroy_Object(Object_t *this) {
  if (decrementRefCounter(this) == 0)
    free(this);

  return &Nothing;
}

/// Nothing
/// ===-------------------------
Nothing_t *newNothing() {
  return &Nothing;
}

Boolean_t *equals_Nothing(Nothing_t *this, Nothing_t *other) {
  return (this->__header.__typeID == other->__header.__typeID && this->__header.__typeID == NothingID)
    ? &True : &False;
}

Nothing_t *print_Nothing(__attribute__((unused)) Nothing_t *object) {
  printf("Nothing\n");
  return &Nothing;
}

Nothing_t *destroy_Nothing(__attribute__((unused)) Nothing_t *object) {
  // nothing to destroy, it's a singleton
  return &Nothing;
}

/// Boolean 
/// ===---------------------------
Boolean_t *newBoolean(long int theBool) {
  return (theBool == 1) ? &True : &False;
}

Boolean_t *equals_Boolean(Boolean_t *this, Boolean_t *other) {
  return (this->__bool == other->__bool)
    ? &True : &False;
}

Nothing_t *print_Boolean(Boolean_t *object) {
  isTrue(object) ? printf("True\n") : printf("False\n"); 
  return &Nothing;
}

Nothing_t *destroy_Boolean(Boolean_t *object) {
  // we don't destroy booleans, true & false are singletons
  return &Nothing;
}

/// Integer
/// ===---------------------------
Integer_t *newInteger(long int theInt) {
  Integer_t *newObj = (Integer_t *)malloc(sizeof(Integer_t));
  assert(newObj);
  initHeader((Object_t *)newObj, IntegerID);
  newObj->__vtable = &IntegerVTTemplate;
  newObj->__int = theInt;
  return newObj;
}

Boolean_t *equals_Integer(Integer_t *this, Integer_t *other) {
  return (this->__int == other->__int) ? &True : &False ;
}

Nothing_t *print_Integer(Integer_t *object) {
  printf("%ld\n", object->__int);
  return &Nothing;
}

Boolean_t *lt_Integer(Integer_t *this, Integer_t *other) {
  return this->__int < other->__int ? &True : &False;
}

Boolean_t *lte_Integer(Integer_t *this, Integer_t *other) {
  return this->__int <= other->__int ? &True : &False;
}

Boolean_t *gt_Integer(Integer_t *this, Integer_t *other) {
  return this->__int > other->__int ? &True : &False;
}

Boolean_t *gte_Integer(Integer_t *this, Integer_t *other) {
  return this->__int >= other->__int ? &True : &False;
}

Integer_t *add_Integer(Integer_t *this, Integer_t *other) {
  return newInteger((this->__int) + (other->__int));
}

Integer_t *mul_Integer(Integer_t *this, Integer_t *other) {
  return newInteger((this->__int) * (other->__int));
}

Integer_t *sub_Integer(Integer_t *this, Integer_t *other) {
  return newInteger((this->__int) - (other->__int));
}

Integer_t *div_Integer(Integer_t *this, Integer_t *other) {
  return newInteger((this->__int) / (other->__int));
}

Integer_t *mod_Integer(Integer_t *this, Integer_t *other) {
  return newInteger((this->__int) % (other->__int));
}

/// Float
/// ===--------------------------
Float_t *newFloat(double theFloat) {
  Float_t *newObj = (Float_t *)malloc(sizeof(Float_t));
  assert(newObj);
  initHeader((Object_t *)newObj, FloatID);
  newObj->__vtable = &FloatVTTemplate;
  newObj->__float = theFloat;
  return newObj;
}

Boolean_t *equals_Float(Float_t *this, Float_t *other) {
  return (this->__float == other->__float) ? &True : &False;
}

Nothing_t *print_Float(Float_t *object) {
  printf("%lf\n", object->__float);
  return &Nothing;
}

Boolean_t *lt_Float(Float_t *this, Float_t *other) {
  return this->__float < other->__float ? &True : &False;
}

Boolean_t *lte_Float(Float_t *this, Float_t *other) {
  return this->__float <= other->__float ? &True : &False;
}

Boolean_t *gt_Float(Float_t *this, Float_t *other) {
  return this->__float > other->__float ? &True : &False;
}

Boolean_t *gte_Float(Float_t *this, Float_t *other) {
  return this->__float >= other->__float ? &True : &False;
}

Float_t *add_Float(Float_t *this, Float_t *other) {
  return newFloat((this->__float)+ (other->__float));
}

Float_t *mul_Float(Float_t *this, Float_t *other) {
  return newFloat((this->__float) * (other->__float));
}

Float_t *sub_Float(Float_t *this, Float_t *other) {
  return newFloat((this->__float) - (other->__float));
}

Float_t *div_Float(Float_t *this, Float_t *other) {
  return newFloat((this->__float) / (other->__float));
}

/// String
/// ===----------------------------
String_t *newString(const char *text) {
  String_t *newStr = (String_t *)malloc(sizeof(String_t));
  assert(newStr);
  initHeader((Object_t *)newStr, StringID);
  newStr->__vtable = &StringVTTemplate;
  newStr->__text = strdup(text);
  return newStr;
}

Boolean_t *equals_String(String_t *this, String_t *other) {
  int res = strcmp(this->__text, other->__text);
  return (res == 0) ? &True : &False;
}

Nothing_t *print_String(String_t *this) {
  fprintf(stdout, "%s\n", this->__text);
  return &Nothing;
}

Nothing_t *destroy_String(String_t *this) {
  if (decrementRefCounter((Object_t *)this)) {
    free(this->__text);
    free(this);
  }

  return &Nothing;
}

String_t *add_String(String_t *this, String_t *other) {
  int len1 = strlen(this->__text);
  int len2 = strlen(other->__text);
  int len = len1 + len2;
  char *ptr = (char *)malloc(len + 1);
  assert(ptr);
  strncpy(ptr, this->__text, len1);
  strncpy(ptr + len1, other->__text, len2);
  ptr[len] = '\0';
  String_t *newStr = (String_t *)malloc(sizeof(String_t));
  assert(newStr);
  initHeader((Object_t *)newStr, StringID);
  newStr->__vtable = &StringVTTemplate;
  newStr->__text = ptr;
  return newStr;
}
