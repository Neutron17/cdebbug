#ifndef _NTR_DEBUG_H_
#define _NTR_DEBUG_H_ 1
#include <stddef.h>
#include "boolean.h"

struct DebNode {
	unsigned line;
	const char *file;
	const char *func;
	const char *buff;
	boolean isFreed;
};
void meminit();
void *_ntr_malloc(size_t sz, const char *file, const char *func, unsigned line);
void *_ntr_realloc(void *buff, size_t sz, const char *file, const char *func, unsigned line);
void _ntr_free(void *buff, const char *file, const char *func, unsigned line);

#ifdef MEM_DEBUG

#define malloc(S) _ntr_malloc(S, __FILE__, __func__, __LINE__)
#define realloc(B, S) _ntr_realloc(B, S, __FILE__, __func__, __LINE__)
#define free(B) _ntr_free(B, __FILE__, __func__, __LINE__)

#endif

#endif //_NTR_DEBUG_H_
