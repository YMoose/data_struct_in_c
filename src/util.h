#ifndef __INCLUDE_MY_STRUCT_UTIL_H__
#define __INCLUDE_MY_STRUCT_UTIL_H__

#include <string.h>
#include <stdint.h>

#ifndef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif /* __compiler_offsetof */
#endif /* offsetof */

#define static_always_inline static inline __attribute__ ((__always_inline__))
#define COMPILER_BARRIER() asm volatile ("":::"memory")

#define min(a, b) (a)<(b)?(a):(b)
static_always_inline void *
_my_memcpy_imp(void *restrict dst, const void *restrict src, size_t n)
{
    return memcpy(dst, src, n);
}

#endif /* __INCLUDE_MY_STRUCT_UTIL_H__ */