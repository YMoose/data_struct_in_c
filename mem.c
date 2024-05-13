#include "mem.h"

void* default_malloc(void* ctx, size_t size)
{
    return malloc(size);
}

void* default_remalloc(void* ctx, size_t size)
{
    return remalloc(size);
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