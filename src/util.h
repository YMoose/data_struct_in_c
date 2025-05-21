#ifndef __INCLUDE_MY_STRUCT_UTIL_H__
#define __INCLUDE_MY_STRUCT_UTIL_H__

#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#ifndef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER) __compiler_offsetof (TYPE, MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)
#endif /* __compiler_offsetof */
#endif /* offsetof */

#define static_always_inline static inline __attribute__ ((__always_inline__))
#define COMPILER_BARRIER() asm volatile ("" ::: "memory")

#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) < (b) ? (b) : (a)

#ifndef MEM_OP_IMP
#define MEM_OP_IMP

#include <stdlib.h>
static_always_inline void *
_my_memcpy_imp (void * dst, const void * src, size_t n)
{
  return memcpy (dst, src, n);
}

static_always_inline void *
_my_malloc_imp (size_t size)
{
  return malloc (size);
}

static_always_inline void
_my_mfree_imp (void *ptr)
{
  return free (ptr);
}

#endif /* MEM_OP_IMP */

#ifndef IS_DBG
#define IS_DBG (1)
#endif /* IS_DBG */

#if IS_DBG
#include <stdio.h>
#define DBG(_fmt, _args...)                                                   \
  printf ((_fmt), ##_args)
#else
#define DBG(_fmt, _args...) 
#endif /* IS_DBG */

static inline
uint32_t round_pow2 (uint32_t x, uint32_t pow2)
{
  return (x + pow2 - 1) & ~(pow2 - 1);
}

static inline 
uint8_t is_mul_overflow(size_t a, size_t b) {
  return (b != 0 && a > SIZE_MAX / b);
}

#endif /* __INCLUDE_MY_STRUCT_UTIL_H__ */