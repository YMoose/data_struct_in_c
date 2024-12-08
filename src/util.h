#ifndef __INCLUDE_UTIL_H__
#define __INCLUDE_UTIL_H__

#ifndef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif /* __compiler_offsetof */
#endif /* offsetof */

#define COMPILER_BARRIER() asm volatile ("":::"memory")

#define min(a, b) (a)<(b)?(a):(b)

#endif /* __INCLUDE_UTIL_H__ */