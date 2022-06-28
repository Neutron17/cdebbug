#define MEM_DEBUG 1

#include <stdio.h>
#include "ntr/debug.h"

void func() {
	puts("func");
	char *x = malloc(1);
	free(x);
}

int main() {
	int *x = malloc_m(sizeof(int), "hi");
	func();
	func();
	int *y = malloc(sizeof(int));
	free_m(x, "freed");
	memdeb_print(true);
	memdeb_destroy();
	return 0;
}
