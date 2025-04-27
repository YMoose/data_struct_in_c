#ifndef __INCLUDED_DVEC_H__
#define __INCLUDED_DVEC_H__

#include "util.h"
#include "vec.h"

#define ADAPTIVE_INIT_CAP 8

static inline void* dvec_alloc (uint32_t ele_size);
static inline void dvec_free(void* dvec) { vec_free(dvec);}
static inline uint32_t dvec_size(void* dvec) {return vec_size(dvec);}

static inline void* dvec_append (void* dvec, void* ele);
static inline uint32_t dvec_len(void* dvec) { return (uint32_t)vec_get_userdata(dvec); }

static inline void* dvec_alloc (uint32_t ele_size)
{
    void* ret = vec_alloc(ele_size, ADAPTIVE_INIT_CAP);
    vec_set_userdata(ret, 0);
    return ret;
}

static inline void* dvec_append (void* dvec, void* ele)
{
    assert(dvec != NULL);
    uint32_t len = (uint32_t)vec_get_userdata(dvec);
    uint32_t cap = vec_size(dvec);
    uint32_t ele_size = _vec_find(dvec)->ele_size;
    void* ret = dvec;
    if (cap < len + 1)
    {
        vec_alloc(ele_size, cap << 1);
        _my_memcpy_imp((uint8_t*)ret , dvec, (len * ele_size));
        vec_free (dvec);
    }

    _my_memcpy_imp((uint8_t*)ret + (len * ele_size), ele, ele_size);
    vec_set_userdata(ret, (void*)(len + 1));
    return ret;
}


#endif /* __INCLUDED_DVEC_H__ */