#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

struct DebNode *memnodes = NULL;
unsigned size = 0, used = 0;
bool inited = false;

/** Initialize global variables 'memnodes' and 'used'
 *  When successful sets 'inited' true */
void meminit() {
	memnodes = malloc(sizeof(struct DebNode) * 10);
	if(!memnodes) {
		fprintf(stderr, "Couldn't allocate memory for ntr memory debugger: %s\n", strerror(errno));
		exit(1);
	}
	size = 5;
	inited = true;
}
/** Debug wrapper for 'malloc'(stdlib.h) */
void *ntr_memdeb_malloc(size_t sz, const char *file, const char *func, unsigned line, const char *msg) {
	void *buff = malloc(sz);
	ntr_memdeb_add(buff, file, func, line, msg);
	return buff;
}
/** Debug wrapper for 'realloc()'(stdlib.h) */
void *ntr_memdeb_realloc(void *buff, size_t sz, const char *file, const char *func, unsigned line, const char *msg) {
	for(unsigned i = 0; i < used; i++) {
		if(buff == memnodes[i].buff) {
			if(msg != NULL)
				strncpy(memnodes[i].msg, msg, 16);
			return realloc(buff, sz);
		}
	}
	return NULL;
}
/** Debug wrapper for 'free()'(stdlib.h) */
void ntr_memdeb_free(void *buff, const char *file, const char *func, unsigned line) {
	if(buff == NULL)
		return;
	for(unsigned i = 0; i < used; i++) {
		if (buff == memnodes[i].buff) {
			memnodes[i].isFreed = true;
			free((void *) memnodes[i].buff);
			memnodes[i].buff = NULL;
			memdeb_mark_freed(buff);
		}
	}
}
/** Add pointer to 'memnodes'. For example: 'SDL_Init()' -> 'SDL_Quit()' and 'calloc()' */
void ntr_memdeb_add(void *buff, const char *file, const char *func, unsigned line, const char *msg) {
	if(!inited)
		meminit();
	if(used == size)
		memnodes = realloc(memnodes, size * 2);
	//void *buff = malloc(sz);
	char *fil = malloc(16);
	strncpy(fil, file, 16);
	char *fun = malloc(16);
	strncpy(fun, func, 16);
	char *messg = malloc(16);
	if(msg == NULL)
		strcpy(messg, "");
	else
		strncpy(messg, msg, 16);
	memnodes[used] = (struct DebNode)
		{ line, false, messg, fil, fun, buff };
	used++;
}

struct DebNode memdeb_get_node(void *buff) {
	if(buff == NULL)
		return (struct DebNode){ 0, false, NULL, NULL, NULL, NULL };
	for(int i = 0; i < used; i++) {
		if(memnodes[i].buff == buff)
			return memnodes[i];
	}
	return (struct DebNode){ 0, false, NULL, NULL, NULL, NULL };
}

struct DebNode *memdeb_get_node_ref(void *buff) {
	if(buff == NULL)
		return NULL;
	for(int i = 0; i < used; i++) {
		if(memnodes[i].buff == buff)
			return &memnodes[i];
	}
	return NULL;
}

void memdeb_mark_freed(void *buff) {
	if(buff == NULL)
		return;
	for(int i = 0; i < used; i++) {
		if(memnodes[i].buff == buff) {
			memnodes[i].isFreed = true;
			free((void *) memnodes[i].file);
			free((void *) memnodes[i].func);
			free((void *) memnodes[i].msg);
			memnodes[i].file = NULL;
			memnodes[i].func = NULL;
			memnodes[i].msg = NULL;
		}
	}
}

int memdeb_print() {
	int ret = 0;
	for(int i = 0; i < used; i++) {
		if(memnodes[i].isFreed)
			continue;
		printf("%d: \n\tline: %d\n\tisFreed: %d\n\tfile: %s\n\tfunc: %s\n\tmessage: %s\n",
			   i, memnodes[i].line, memnodes[i].isFreed, memnodes[i].file, memnodes[i].func, memnodes[i].msg);
		ret++;
	}
	return ret;
}

void memdeb_destroy() {
	for(int i = 0; i < used; i++) {
		if(memnodes[i].isFreed)
			continue;
		free((void *) memnodes[i].file);
		free((void *) memnodes[i].func);
		free((void *) memnodes[i].msg);
	}
	free((void*)memnodes);
}