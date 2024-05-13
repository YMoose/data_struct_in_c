#ifndef __INCLUDE_MEM_H__
#define __INCLUDE_MEM_H__

#include <stddef.h>

typedef struct _alc_set {
    /** Same as libc's malloc(size), should not be NULL. */
    void *(*malloc)(void *ctx, size_t size);
    /** Same as libc's realloc(ptr, size), should not be NULL. */
    void *(*realloc)(void *ctx, void *ptr, size_t old_size, size_t size);
    /** Same as libc's free(ptr), should not be NULL. */
    void (*free)(void *ctx, void *ptr);
    /** A context for malloc/realloc/free, can be NULL. */
    void *ctx;
} alc_set;

extern alc_set default_alc_set;

#define PRESET_MEM_ALC_SET(custum_alc_set) (custum_alc_set) = (custum_alc_set)==NULL? (&default_alc_set):(custum_alc_set)

static inline 
void* MEM_ALLOC(alc_set* custum_alc_set, size_t size)
{
    return custum_alc_set->malloc(custum_alc_set->ctx, size);
}

static inline 
void* MEM_REALLOC(alc_set* custum_alc_set, void *ptr, size_t old_size, size_t size)
{
    return custum_alc_set->realloc(custum_alc_set->ctx, ptr, old_size, size);
}

static inline 
void MEM_FREE(alc_set* custum_alc_set, void *ptr)
{
    custum_alc_set->free(custum_alc_set->ctx, ptr);
    return;
}

static inline
alc_set* alc_set_init(void *(*custum_malloc)(void *ctx, size_t size), 
                 void *(*custum_realloc)(void *ctx, void *ptr, size_t old_size, size_t size),
                 void (*custum_free)(void *ctx, void *ptr),
                 void *custum_ctx)
{
    alc_set *new_alc_set = custum_malloc(custum_ctx, sizeof(alc_set));
    if (new_alc_set == NULL)
        return NULL;
    new_alc_set->malloc = custum_malloc;
    new_alc_set->realloc = custum_realloc;
    new_alc_set->free = custum_free;
    new_alc_set->ctx = custum_ctx;
    return new_alc_set;
}

#endif /* __INCLUDE_MEM_H__ */