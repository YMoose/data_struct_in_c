#ifndef __INCLUDE_BITMAP_H__
#define __INCLUDE_BITMAP_H__

#include "util.h"
#include "vec.h"

#define BITMAP_MASK (0b111)

static inline uint8_t* bitmap_alloc(uint32_t size);
static inline uint32_t bitmap_size(uint8_t* bitmap) {return ((uint32_t*)(vec_userdata(bitmap)))[0];}
static inline void bitmap_free(uint8_t* bitmap) {vec_free(bitmap);}
static inline uint8_t bitmap_set(uint8_t* bitmap, uint32_t index);
static inline uint8_t bitmap_unset(uint8_t* bitmap, uint32_t index);

static inline 
uint8_t* bitmap_alloc(uint32_t size)
{
    uint8_t* ret = NULL;
    ret = (uint8_t*)vec_alloc(sizeof(uint8_t),((size >> 3) + 1));
    ((uint32_t*)(vec_userdata(ret)))[0] = 0;
    memset(ret, 0, ((size >> 3) + 1));
    return ret;
}

static inline 
uint8_t bitmap_set(uint8_t* bitmap, uint32_t index)
{
    uint32_t idx = index >> 3;
    uint32_t offset = index & BITMAP_MASK;
    uint8_t ret = bitmap[idx] & (1 << offset);
    bitmap[idx] = bitmap[idx] | (1 << offset);
    return ret;
}

static inline
uint8_t bitmap_unset(uint8_t* bitmap, uint32_t index)
{
    uint32_t idx = index >> 3;
    uint32_t offset = index & BITMAP_MASK;
    uint8_t ret = bitmap[idx] & (1 << offset);
    bitmap[idx] = bitmap[idx] & (~(1 << offset));
    return ret;
}

#endif /* __INCLUDE_BITMAP_H__ */