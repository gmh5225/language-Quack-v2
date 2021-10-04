#include "quack_runtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testIntegerAddition() {
    Integer_t *one = newInteger(1);
    Integer_t *two = newInteger(2);

    Integer_t *res = DISPATCH(one, add)(one, two);
    // res = DISPATCH(res, add)(res, three);
    DISPATCH(res, print)(res);
}

// void testStringAddition() {
//     String_t *one = newString("one_");
//     String_t *two = newString("two_");
//     String_t *three = newString("three");

//     String_t *res = DISPATCH(one, add)(one, two);
//     res = DISPATCH(res, add)(res, three);
//     DISPATCH(res, print)(res);
// }

// void testNothing() {
//     Nothing_t *nothing = newNothing();
//     DISPATCH(nothing, print)(nothing);
// }

// void testBoolean() {
//     Boolean_t *b1 = newBoolean(1);
//     Boolean_t *b2 = newBoolean(0);
//     DISPATCH(b1, print)(b1);
//     DISPATCH(b2, print)(b2);
// }

// void testObject() {
//     Object_t *o = newObject();
//     DISPATCH(o, print)(o);
// }

int main() {
    testIntegerAddition();
    // testNothing();
    // testBoolean();
    // testObject();
}