#include "quack_runtime.h"

int main() {
  String_t *obj = newString("hello world");
  obj->__vtable->__print(obj);
}
