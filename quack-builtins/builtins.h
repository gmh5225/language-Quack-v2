/*
 * The Quack runtime needs a base class Obj and a handful
 * of built-in classes  (Int, String, Nothing, Boolean)
 *
 * 2018 note (FIXME): The class structure needs a field that
 * points to the supertype.
 */
#ifndef Builtins_h
#define Builtins_h

#include <stdbool.h>

/* Naming conventions:
 * class_X means a reference to the class structure for class X,
 * i.e., pointer to the struct that contains the method table.
 *
 * obj_X means the corresponding object structure reference,
 * i.e., a pointer to the struct where instance variables live.
 *
 * For each, we'll define a struct tag with *_struct and
 * and then define a reference to that struct with a typedef,
 * e.g., class_Obj will be typedefed to struct class_Obj_struct *.
 * Each class will have a single instantiation as the_class_X.
 * the_class_X is a pointer to a statically allocated structure.
 *
 * All programmer-visible fields of objects are references to
 * other objects. Boolean, Int, and String have "hidden" fields
 * that contain their unboxed primitives.
 * Classes are essentially vectors of function pointers, but for
 * convenience and checking we declare them as (pointers to)
 * structs containing function pointers with particular signatures.
 * The receiver object ('this' in Quack) is an implicit argument
 * in Quack but an explicit argument in the runtime.
 */

/* The following object types are "known" from Obj, in the
 * sense that there are Obj methods that return these types.
 */
struct obj_String_struct;
typedef struct obj_String_struct* obj_String;

struct obj_Boolean_struct;
typedef struct obj_Boolean_struct* obj_Boolean;

/* ==============
 * Obj
 * Fields: None
 * Methods:
 *    Constructor  (called after allocation)
 *    STR
 *    PRINT
 *    EQUALS
 *
 * ==============
 */

struct class_Obj_struct;
typedef struct class_Obj_struct* class_Obj;

typedef struct obj_Obj_struct {
  struct class_Obj_struct *clazz;
} * obj_Obj;

struct class_Obj_struct {
  class_Obj super_;

  /* Method table */
  obj_Obj (*constructor) ( void );
  obj_Boolean (*EQUALS) (obj_Obj, obj_Obj);
  obj_Obj (*PRINT) (obj_Obj);
  obj_String (*STR) (obj_Obj);
};

extern class_Obj the_class_Obj; /* Initialized in Builtins.c */
extern struct class_Obj_struct the_class_Obj_struct;

/* ================
 * String
 * Fields:
 *    One hidden field, currently holding char*
 *    (change later to a rope for garbage collection)
 * Methods:
 *    Those of Obj, plus ordering, concatenation
 *    (Incomplete for now.)
 * ==================
 */

struct class_String_struct;
typedef struct class_String_struct* class_String;

typedef struct obj_String_struct {
  class_String clazz;
  char *text;     /* FIXME: Make this a garbage-collectable rope */
} * obj_String;

struct class_String_struct {
  class_Obj super_;

  /* Method table: Inherited or overridden */
  obj_String (*constructor) ( void );
  obj_Boolean (*EQUALS) (obj_String, obj_Obj);
  obj_Obj (*PRINT) (obj_Obj); /* Inherit */
  obj_String (*STR) (obj_String);

  /* Method table: Introduced in String */
  obj_Boolean (*ATLEAST) (obj_String, obj_String);
  obj_Boolean (*ATMOST) (obj_String, obj_String);
  obj_Boolean (*LESS) (obj_String, obj_String);
  obj_Boolean (*MORE) (obj_String, obj_String);

  obj_String (*PLUS) (obj_String, obj_String);
};

extern class_String the_class_String;
extern struct class_String_struct the_class_String_struct;

/* Construct an object from a string literal.
 * This is not available to the Quack programmer, but
 * is used by the compiler to create a literal string
 * from a Quack literal string.
 */
extern obj_String str_literal(char *s);

/* ================
 * Boolean
 * Fields:
 *    One hidden field, an int (0 for False, -1 for True)
 * Methods:
 *
 * =================
 */

struct class_Boolean_struct;
typedef struct class_Boolean_struct* class_Boolean;

typedef struct obj_Boolean_struct {
  class_Boolean  clazz;
  int value;
} * obj_Boolean;

struct class_Boolean_struct {
  class_Obj super_;

  /* Method table: Inherited or overridden */
  obj_Boolean (*constructor) ( void );
  obj_Boolean (*EQUALS) (obj_Obj, obj_Obj); /* Inherit */
  obj_Obj (*PRINT) (obj_Obj);               /* Inherit */
  obj_String (*STR) (obj_Boolean);
};

extern class_Boolean the_class_Boolean;
extern struct class_Boolean_struct the_class_Boolean_struct;

/* There are only two instances of Boolean,
 * lit_true and lit_false
 * (i.e., the values of the literals true and false)
 * The constructor should return one of them;
 * maybe lit_false.
 */
extern obj_Boolean lit_false;
extern obj_Boolean lit_true;


/* ==============
 * Nothing (really just a singleton Obj)
 * Fields: None
 * Methods:
 *    Constructor  (called after allocation)
 *    STR
 *    PRINT
 *    EQUALS
 *
 * ==============
 */

struct class_Nothing_struct;
typedef struct class_Nothing_struct* class_Nothing;

typedef struct obj_Nothing_struct {
  class_Nothing clazz;
} * obj_Nothing;

/* Although there is little reason to call methods on the none
 * object, the only instance of Nothing, we could call PRINT on
 * it or compare it to something.  It's STR method should return
 * "None".
 */
struct class_Nothing_struct {
  class_Obj super_;

  /* Method table */
  obj_Nothing (*constructor) ( void );
  obj_Boolean (*EQUALS) (obj_Obj, obj_Obj); /* Inherited */
  obj_Obj (*PRINT) (obj_Obj);               /* Inherited */
  obj_String (*STR) (obj_Nothing);
};

extern class_Nothing the_class_Nothing;
extern struct class_Nothing_struct the_class_Nothing_struct;

/* There is a single instance of Nothing,
 * called nothing
 */
extern obj_Nothing none;

/* ================
 * Int
 * Fields:
 *    One hidden field, an int
 * Methods:
 *    STR  (override)
 *    PRINT   (inherit)
 *    EQUALS  (override)
 *    LESS
 *    MORE
 *    ATLEAST
 *    ATMOST
 *    PLUS
 *    MINUS
 *    DIVIDE
 *    TIMES
 * =================
 */

struct class_Int_struct;
typedef struct class_Int_struct* class_Int;

typedef struct obj_Int_struct {
  class_Int  clazz;
  int value;
} * obj_Int;

struct class_Int_struct {
  class_Obj super_;

  /* Method table: Inherited or overridden */
  obj_Int (*constructor) ( void );

  obj_Boolean (*EQUALS) (obj_Int, obj_Obj); /* Overridden */
  obj_Obj (*PRINT) (obj_Obj);      /* Inherited */
  obj_String (*STR) (obj_Int);  /* Overridden */

  obj_Boolean (*ATLEAST) (obj_Int, obj_Int);   /* Introduced */
  obj_Boolean (*ATMOST) (obj_Int, obj_Int);   /* Introduced */
  obj_Int (*DIVIDE) (obj_Int, obj_Int);       /* Introduced */
  obj_Boolean (*LESS) (obj_Int, obj_Int);   /* Introduced */
  obj_Int (*MINUS) (obj_Int, obj_Int);       /* Introduced */
  obj_Boolean (*MORE) (obj_Int, obj_Int);   /* Introduced */
  obj_Int (*PLUS) (obj_Int, obj_Int);       /* Introduced */
  obj_Int (*TIMES) (obj_Int, obj_Int);       /* Introduced */
};

extern class_Int the_class_Int;
extern struct class_Int_struct the_class_Int_struct;

/* Integer literals constructor,
 * used by compiler and not otherwise available in
 * Quack programs.
 */
extern obj_Int int_literal(int n);


/* ===============================
 * Make all the methods we might
 * inherit visible to user code
 *================================
 */
obj_Obj new_Obj();
obj_String Obj_method_STR(obj_Obj this);
obj_Obj Obj_method_PRINT(obj_Obj this);
obj_Boolean Obj_method_EQUALS(obj_Obj this, obj_Obj other);

obj_String new_String();
obj_String String_method_STR(obj_String this);
//obj_String String_method_PRINT(obj_String this);
obj_Boolean String_method_EQUALS(obj_String this, obj_Obj other);
obj_String String_method_PLUS(obj_String this, obj_String other);
obj_Boolean String_method_LESS(obj_String this, obj_String other);
obj_Boolean String_method_MORE(obj_String this, obj_String other);
obj_Boolean String_method_ATLEAST(obj_String this, obj_String other);
obj_Boolean String_method_ATMOST(obj_String this, obj_String other);

obj_String Nothing_method_STR(obj_Nothing this);

obj_Boolean new_Boolean();
obj_String Boolean_method_STR(obj_Boolean this);

obj_Int new_Int();
obj_String Int_method_STR(obj_Int this);
obj_Boolean Int_method_EQUALS(obj_Int this, obj_Obj other);
obj_Boolean Int_method_LESS(obj_Int this, obj_Int other);
obj_Boolean Int_method_MORE(obj_Int this, obj_Int other);
obj_Boolean Int_method_ATLEAST(obj_Int this, obj_Int other);
obj_Boolean Int_method_ATMOST(obj_Int this, obj_Int other);
obj_Int Int_method_PLUS(obj_Int this, obj_Int other);
obj_Int Int_method_MINUS(obj_Int this, obj_Int other);
obj_Int Int_method_DIVIDE(obj_Int this, obj_Int other);
obj_Int Int_method_TIMES(obj_Int this, obj_Int other);

bool is_subtype(class_Obj obj, class_Obj other);
void destroy(class_Obj obj);

#endif
