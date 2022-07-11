#ifndef _NTR_DEBUG_H_
#define _NTR_DEBUG_H_ 1
#include <stddef.h>
#include <stdbool.h>

struct DebNode {
	unsigned line;
	bool isFreed;
	char *msg;
	const char *file;
	const char *func;
	const void *buff;
};
void ntr_memdeb_init();
void memdeb_destroy();

void *ntr_memdeb_malloc(size_t sz, const char *file, const char *func, unsigned line, const char *msg);
void *ntr_memdeb_realloc(void *buff, size_t sz, const char *file, const char *func, unsigned line, const char *msg);
void ntr_memdeb_add(void *buff, const char *file, const char *func, unsigned line, const char *msg);

struct DebNode memdeb_get_node(void *buff);
struct DebNode *memdeb_get_node_ref(void *buff);

void memdeb_mark_freed(void *buff);
void ntr_memdeb_free(void *buff, const char *file, const char *func, unsigned line);

int memdeb_print();

#ifdef MEM_DEBUG

#define malloc(S) ntr_memdeb_malloc(S, __FILE__, __func__, __LINE__, NULL)
#define malloc_m(S, M) ntr_memdeb_malloc(S, __FILE__, __func__, __LINE__, M)

#define realloc(B, S) ntr_memdeb_realloc(B, S, __FILE__, __func__, __LINE__, NULL)
#define realloc_m(B, S, M) ntr_memdeb_realloc(B, S, __FILE__, __func__, __LINE__, M)
#define memdeb_add(S) ntr_memdeb_add(S, __FILE__, __func__, __LINE__, NULL)
#define memdeb_add_m(S, M) ntr_memdeb_add(S, __FILE__, __func__, __LINE__, M)

#define free(B) ntr_memdeb_free(B, __FILE__, __func__, __LINE__)

#define get_node(B) memdeb_get_node(B)
#define get_node_ref(B) memdeb_get_node_ref(B)
#define mark_freed(B) memdeb_mark_freed(B)
#define mark_as_freed(B) mark_freed(B)

#endif

#endif //_NTR_DEBUG_H_
