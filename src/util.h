#ifndef __INCLUDE_UTIL_H__
#define __INCLUDE_UTIL_H__

#ifndef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif /* __compiler_offsetof */
#endif /* offsetof */

typedef int (*data_compare_func)(void* data, void* base);
typedef int (*data_traversal_func)(void* data);

#endif /* __INCLUDE_UTIL_H__ */