#ifndef __INCLUDED_VECTOR_H__
#define __INCLUDED_VECTOR_H__

#include <stddef.h>
#include <strings.h>
#include <math.h>
#include "mem.h"
#include "util.h"

typedef struct _vector_t 
{
    alc_set* mem_alc_set;
    void* ele_vec;
    uint32_t ele_size;
    uint32_t vec_size;
}vector_t;

static inline vector_t* vec_alloc(alc_set* mem_alc_set, uint32_t ele_size, uint32_t vec_size);
static inline vector_t* vec_realloc(vector_t* vec, uint32_t new_ele_size);
static inline int vec_free(vector_t* vec);

static inline uint32_t vec_size(vector_t* vec);

static inline int vec_append(vector_t* vec, void* data);
// static inline int vec_delete_tail(vector_t* vec);
static inline int vec_traversal(vector_t* vec, data_traversal_func traversal_func);


static inline 
int vec_free(vector_t* vec)
{
    MEM_FREE(vec->mem_alc_set, vec);
    return 0;
}

static inline 
vector_t* vec_alloc(alc_set* mem_alc_set, uint32_t ele_size, uint32_t vec_size)
{
    PRESET_MEM_ALC_SET(mem_alc_set);
    vector_t* new_vec = (vector_t*)MEM_ALLOC(mem_alc_set, sizeof(vector_t));
    if (new_vec == NULL)
    {
        return NULL;
    }
    new_vec->ele_size = ele_size;
    new_vec->vec_size = vec_size;
    new_vec->mem_alc_set = mem_alc_set;
    new_vec->ele_vec = MEM_ALLOC(new_vec->mem_alc_set, ele_size * vec_size);
    if (new_vec->ele_vec == NULL)
    {
        vec_free(new_vec);
        return NULL;
    }
    return new_vec;
}

static inline int vec_append(vector_t* vec, void* data);

#endif /* __INCLUDED_VECTOR_H__ */