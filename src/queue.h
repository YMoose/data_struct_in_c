#ifndef __INCLUDED_QUEUE_H__
#define __INCLUDED_QUEUE_H__

#include "util.h"
// #include <types.h>
#include <stdint.h>

// refer to kfifo in kernel
typedef struct _queue_node_t
{
    uint64_t struct_size;
} queue_node_t;

typedef struct
{
    uint8_t *buffer;
    uint64_t size;
    uint64_t in;
    uint64_t out;
} queue_t;



#endif /* __INCLUDED_LIST_H__ */