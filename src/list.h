#ifndef __INCLUDED_LIST_H__
#define __INCLUDED_LIST_H__

#include "util.h"

// just like list in kernel
typedef struct _list_node_t
{
    struct _list_node_t* prev;
    struct _list_node_t* next;
}list_node_t;

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @list_node:	the name of the list_node_t within the struct.
 */
#define list_entry(list_ptr, type, list_node) \
    (type *)((char *)(list_ptr) - offsetof(type, list_node))

static inline void list_head_init(list_node_t* head);
static inline int list_add(list_node_t* new, list_node_t* head);
static inline int list_add_tail(list_node_t* new, list_node_t* head);
static inline list_node_t* list_del(list_node_t* node);
static inline int list_move(list_node_t* node, list_node_t* dst);
static inline int list_move_tail(list_node_t* node, list_node_t* dst);
static inline int list_empty(list_node_t* head) {return head->next == head;}
static inline int list_splice(list_node_t* src, list_node_t* dst);
static inline int list_splice_tail(list_node_t* src, list_node_t* dst);

#define list_for_each(cur, head) \
    for ((cur) = (head)->next; (cur) != (head); (cur) = (cur)->next)

static inline void list_head_init(list_node_t* head)
{
    head->next = head;
    head->prev = head;
}

static inline int list_add(list_node_t* new, list_node_t* head)
{
    new->next = head->next;
    new->prev = head;
    head->next->prev = new;
    head->next = new;
    return 0;
}

static inline int list_add_tail(list_node_t* new, list_node_t* head)
{
    new->next = head;
    new->prev = head->prev;
    head->prev->next = new;
    head->prev = new;
    return 0;
}

static inline list_node_t* list_del(list_node_t* node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    return node;
}

static inline int list_move(list_node_t* node, list_node_t* dst)
{
    list_del(node);
    return list_add(node, dst);
}
static inline int list_move_tail(list_node_t* node, list_node_t* dst)
{
    list_del(node);
    return list_add_tail(node, dst);
}

static inline int list_splice(list_node_t* src, list_node_t* dst)
{
    list_node_t* src_tail = src->prev;
    src->prev = dst;
    src_tail->next = dst->next;
    dst->next = src;
    dst->next->prev = src_tail;
}

static inline int list_splice_tail(list_node_t* src, list_node_t* dst)
{
    list_node_t* src_tail = src->prev;
    src->prev = dst->prev;
    src_tail->next = dst;
    dst->prev = src_tail;
    dst->prev->next = src;
}

#endif /* __INCLUDED_LIST_H__ */