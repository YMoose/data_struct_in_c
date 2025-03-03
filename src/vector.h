#ifndef __INCLUDED_VECTOR_H__
#define __INCLUDED_VECTOR_H__

#include "util.h"

#define VEC_ALIGN 8

typedef struct _vector_header_t
{
    uint32_t vec_size;
    uint32_t ele_size;
    uint32_t len;
    uint32_t padding[1];
    uint8_t vector_data[0];
}vector_header_t;

/** \brief Find the vector header

    Given the user's pointer to a vector, find the corresponding
    vector header

    @param v pointer to a vector
    @return pointer to the vector's vector_header_t
*/
#define _vec_find(v)	((vector_header_t *) (v) - 1)

static inline void* vec_alloc(uint32_t ele_size, uint32_t vec_size);
static inline void vec_free(void* vec);
static inline uint32_t vec_size(void* vec);
static inline void* vec_validate(void* vec, uint32_t index);
static inline void* _vec_resize(void* vec, uint32_t new_ele_size);

static inline 
void* vec_alloc(uint32_t ele_size, uint32_t vec_size)
{
    uint32_t req_size = 0;
    
    assert(__builtin_mul_overflow(ele_size, vec_size) == 0);
    req_size = sizeof(vector_header_t) + ele_size * vec_size;
    assert(req_size > sizeof(vector_header_t));

    req_size = round_pow2(req_size, VEC_ALIGN);
    vector_header_t* h = (vector_header_t*)_my_malloc_imp(req_size);

    return h == NULL? NULL: h->vector_data;
}

static inline 
void vec_free(void* vec)
{
    if (vec != NULL)
        _my_mfree_imp(_vec_find(vec));
    return;
}

static inline 
uint32_t vec_size(void* vec)
{
    return vec==NULL ? 0: _vec_find(vec)->vec_size;
}

static inline 
void* vec_validate(void* vec, uint32_t index)
{
    uint32_t req_size = 0;
    vector_header_t* h = _vec_find(vec);
    if (vec != NULL && h->len <= index)
    {
        return _vec_resize(vec, index + 1);
    }
    
    return vec;
}

static inline 
void* _vec_resize(void* vec, uint32_t new_vec_size)
{
    assert(vec != NULL);
    vector_header_t* h = _vec_find(vec);
    if (new_vec_size <= h->len)
        return vec;
    void* new_vec = vec_alloc(h->ele_size, new_vec_size);
    _my_memcpy_imp(new_vec, vec, h->vec_size);

    return new_vec;
}

#endif /* __INCLUDED_VECTOR_H__ */