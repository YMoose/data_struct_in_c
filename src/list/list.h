#ifndef __INCLUDED_LIST_H__
#define __INCLUDED_LIST_H__

#include <stddef.h>
#include <strings.h>
#include "mem.h"
#include "util.h"

typedef struct _list_node_t
{
    _list_node_t* prev;
    _list_node_t* next;
    void* data;
}list_node_t;

typedef struct _list_t
{
    list_node_t* header;
    list_node_t* tailer;
    alc_set* mem_alc_set;
    data_compare_func comp_func;
}list_t;


static inline list_t* list_new(alc_set* mem_alc_set, data_compare_func comp_func);
static inline int list_free(list_t* list);

static inline int list_add_header(list_t* list, void* data);
static inline int list_add_tail(list_t* list, void* data);
static inline int list_remove_header(list_t* list, );
static inline int list_remove_tail(list_t* list, );

static inline 
list_t* list_new(alc_set* mem_alc_set, data_compare_func comp_func)
{
    PRESET_MEM_ALC_SET(mem_alc_set);
    list_t* new_list = (list_t*)MEM_ALLOC(mem_alc_set, sizeof(list_t));
    if (new_list == NULL)
    {
        return NULL;
    }
    new_list->comp_func = comp_func;
    new_list->mem_alc_set = mem_alc_set;
    new_list->header = NULL;
    new_list->tailer = NULL;
    return new_list;
}

static inline 
int list_add_header(list_t* list, void* data)
{
    
}

#endif /* __INCLUDED_LIST_H__ */