# cdebbug - memory debugger in c

this program records every call to malloc and free, it stores the file, function and line of the call. At the end it prints out every call, 
that has not been freed

## Example

```c
#define MEM_DEBUG 1

#include <stdio.h>
#include "ntr/debug.h"

void func() {
	char *x = malloc(1);
	free(x);
}

int main() {
	meminit();
	int *x = malloc(sizeof(int));
	func();
	func();
	int *y = malloc(sizeof(int));
	//free(x);
	//free(y);
	return 0;
}
```
Output:
```
0: 
        line: 14
        file: test.c
        func: main
        isFreed: 0
3: 
        line: 17
        file: test.c
        func: main
        isFreed: 0
```
these are the were the unfreed allocations
