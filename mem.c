#include "mem.h"
#include <string.h>
#include <stdlib.h>

void* default_malloc(void* ctx, size_t size)
{
    return malloc(size);
}

void* default_remalloc(void* ctx, void *ptr, size_t old_size, size_t size)
{
    return realloc(ptr, size);
}

void default_free(void *ctx, void *ptr)
{
    free(ptr);
    return;
}

alc_set default_alc_set = {
    default_malloc,
    default_remalloc,
    default_free,
    NULL,
};