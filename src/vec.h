#ifndef __INCLUDED_VEC_H__
#define __INCLUDED_VEC_H__

#include "util.h"

#define VEC_ALIGN 8

typedef struct _vec_header_t
{
    uint32_t vec_size;
    uint32_t ele_size;
    union {
        void* padding_ptr[1];
        uint64_t padding_u64[1];
        uint32_t padding_u32[2];
    };
    uint8_t data[0];
}vec_header_t;

/** \brief Find the vec header

    Given the user's pointer to a vec, find the corresponding
    vec header

    @param v pointer to a vec
    @return pointer to the vec's vec_header_t
*/
#define _vec_find(v)	((vec_header_t *) (v) - 1)

static inline void* vec_alloc(uint32_t ele_size, uint32_t vec_size);
static inline void vec_free(void* vec);
static inline uint32_t vec_size(void* vec);
static inline uint32_t vec_ele_size(void* vec);
static inline void* vec_validate(void* vec, uint32_t ele_size, uint32_t index);
static inline void* _vec_resize(void* vec, uint32_t new_ele_size);
static inline void* vec_userdata(void* vec);

static inline 
void* vec_alloc(uint32_t ele_size, uint32_t vec_size)
{
    uint32_t req_size = 0;
    
    assert(is_mul_overflow(ele_size, vec_size) == 0);
    req_size = sizeof(vec_header_t) + ele_size * vec_size;
    assert(req_size > sizeof(vec_header_t));

    req_size = round_pow2(req_size, VEC_ALIGN);
    vec_header_t* h = (vec_header_t*)_my_malloc_imp(req_size);

    return h == NULL? NULL: h->data;
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
uint32_t vec_ele_size(void* vec)
{
    return vec==NULL ? 0: _vec_find(vec)->ele_size;
}

static inline 
void* vec_validate(void* vec, uint32_t ele_size, uint32_t index)
{
    uint32_t req_size = 0;
    vec_header_t* h = NULL;
    if (vec == NULL)
    {
        return vec_alloc(ele_size, index + 1);
    }

    h = _vec_find(vec);

    if (vec != NULL && h->vec_size <= index)
    {
        return _vec_resize(vec, index + 1);
    }
    
    return vec;
}

static inline 
void* _vec_resize(void* vec, uint32_t new_vec_size)
{
    assert(vec != NULL);
    vec_header_t* h = _vec_find(vec);
    if (new_vec_size <= h->vec_size)
        return vec;
    void* new_vec = vec_alloc(h->ele_size, new_vec_size);
    _my_memcpy_imp(new_vec, vec, h->vec_size);
    vec_free(vec);

    return new_vec;
}

static inline
void* vec_userdata(void* vec)
{
    assert (vec != NULL);
    return _vec_find(vec)->padding_ptr[0];
}

#endif /* __INCLUDED_VEC_H__ */