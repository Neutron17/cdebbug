#define MEM_DEBUG 1

#include <stdio.h>
#include "ntr/debug.h"

void func() {
	puts("func");
	char *x = malloc(1);
	free(x);
}

int main() {
	meminit();
	printf("Hello, World!\n");
	int *x = malloc(sizeof(int));
	func();
	func();
	int *y = malloc(sizeof(int));
	//free(x);
	//free(y);
	return 0;
}
