#include <stdlib.h>

typedef struct x {
	int a;
	int c;
} X;

void f() {
	static X x;
	x.a = 3;
	x.c = 4;
}

int main () {
  f();
  return 0;
}
