#ifndef __INCLUDED_LIST_H__
#define __INCLUDED_LIST_H__

#include <stddef.h>
#include <strings.h>
#include "mem.h"
#include "util.h"
#include "sync.h"

typedef struct _list_node_t
{
    struct _list_node_t* prev;
    struct _list_node_t* next;
    void* data;
}list_node_t;

typedef struct _list_t
{
    list_node_t* header;
    list_node_t* tailer;
    alc_set* mem_alc_set;
    data_compare_func comp_func;
    
    uint32_t is_mp_safe;
    sync_mutex_t* lock;
}list_t;

// export api
static inline list_t* list_new(alc_set* mem_alc_set, data_compare_func comp_func, uint32_t is_mp_safe);
static inline int list_free(list_t* list);

static inline int list_add_header(list_t* list, void* data);
static inline int list_add_tail(list_t* list, void* data);
static inline int list_remove_header(list_t* list);
static inline int list_remove_tail(list_t* list);
static inline int list_traversal(list_t* list, data_traversal_func traversal_func);

static inline 
list_node_t* list_node_new(list_t* list, void* data)
{
    list_node_t* new_node = (list_node_t*)MEM_ALLOC(list->mem_alc_set, sizeof(list_node_t));
    memset(new_node, 0, sizeof(list_node_t));
    new_node->data = data;
    return new_node;
}

static inline 
list_t* list_new(alc_set* mem_alc_set, data_compare_func comp_func, uint32_t is_mp_safe)
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
    new_list->is_mp_safe = is_mp_safe;
    if (new_list->is_mp_safe != 0)
    {
        sync_mutex_init(&(new_list->lock));
    }
    return new_list;
}

static inline 
int list_add_header(list_t* list, void* data)
{
    list_node_t* new_node = NULL;
    new_node = list_node_new(list, data);
    if (new_node == NULL)
    {
        return -1;
    }
    
    new_node->next = list->header;
    
    if (list->is_mp_safe != 0)
    {
        sync_mutex_lock(&(list->lock));
    }
    
    if (list->header != NULL)
    {
        list->header->prev = new_node;
    }
    else
    {
        // first node
        list->tailer = new_node;
    }
    list->header = new_node;
    
    if (list->is_mp_safe != 0)
    {
        sync_mutex_unlock(&(list->lock));
    }
    return 0;
}

static inline 
int list_add_tail(list_t* list, void* data)
{
    list_node_t* new_node = NULL;
    new_node = list_node_new(list, data);
    if (new_node == NULL)
    {
        return -1;
    }
    new_node->prev = list->tailer;
    
    if (list->is_mp_safe != 0)
    {
        sync_mutex_lock(&(list->lock));
    }
    if (list->tailer != NULL)
    {
        list->tailer->next = new_node;
    }
    else 
    {
        list->header = new_node;
    }
    list->tailer = new_node;

    if (list->is_mp_safe != 0)
    {
        sync_mutex_unlock(&(list->lock));
    }
    return 0;
}

static inline 
int list_traversal(list_t* list, data_traversal_func traversal_func)
{
    if (list->is_mp_safe != 0)
    {
        sync_mutex_lock(&(list->lock));
    }
    list_node_t* cur_node = list->header;
    int cnt = 0;
    while (cur_node != NULL)
    {
        cnt ++;
        if (traversal_func != NULL && traversal_func(cur_node->data) > 0)
        {
            break;
        }
        cur_node = cur_node->next;
    }
    if (list->is_mp_safe != 0)
    {
        sync_mutex_unlock(&(list->lock));
    }
    return cnt; 
}

#endif /* __INCLUDED_LIST_H__ */