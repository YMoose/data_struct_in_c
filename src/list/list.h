#ifndef __INCLUDED_LIST_H__
#define __INCLUDED_LIST_H__

#include <stddef.h>
#include <strings.h>
#include "mem.h"
#include "util.h"

typedef struct _list_t
{

}list_t;

static inline list_t* list_new(alc_set* mem_alc_set, data_compare_func comp_func);
static inline int list_free(list_t* list);

static inline int list_add();
static inline int list_delete();


#endif /* __INCLUDED_LIST_H__ */