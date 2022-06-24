#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "boolean.h"

struct DebNode *memnodes = NULL;
unsigned size = 0, used = 0;
boolean inited = false;

void meminit() {
	memnodes = malloc(sizeof(struct DebNode) * 10);
	if(!memnodes) {
		fprintf(stderr, "Couldn't allocate memory for ntr memory debugger: %s\n", strerror(errno));
		exit(1);
	}
	size = 10;
	inited = true;
}
/** Allocate SZ bytes of memory. */
void *_ntr_malloc(size_t sz, const char *file, const char *func, unsigned line) {
	if(!inited)
		meminit();
	if(used == size)
		memnodes = realloc(memnodes, size * 2);
	void *buff = malloc(sz);
	char *fil = malloc(16);
	strncpy(fil, file, 16);
	char *fun = malloc(16);
	strncpy(fun, func, 16);
	memnodes[used] = (struct DebNode){ line, fil, fun, buff, false };
	used++;
	return buff;
}

void *_ntr_realloc(void *buff, size_t sz, const char *file, const char *func, unsigned line) {
	for(unsigned i = 0; i < used; i++) {
		if(buff == memnodes[i].buff) {
			return realloc(buff, sz);
		}
	}
	return NULL;
}

void _ntr_free(void *buff, const char *file, const char *func, unsigned line) {
	if(buff == NULL)
		return;
	for(unsigned i = 0; i < used; i++) {
		if(buff == memnodes[i].buff) {
			memnodes[i].isFreed = true;
			free((void*)memnodes[i].buff);
			memnodes[i].buff = NULL;
			return;
		}
	}
}

__attribute__((destructor(), used)) void finalize() {
	for(int i = 0; i < used; i++) {
		if(memnodes[i].isFreed)
			continue;
		printf("%d: \n\tline: %d\n\tfile: %s\n\tfunc: %s\n\tisFreed: %d\n",
			   i, memnodes[i].line, memnodes[i].file, memnodes[i].func, memnodes[i].isFreed);
		free((void *) memnodes[i].file);
		free((void *) memnodes[i].func);
	}
	free((void*)memnodes);
}