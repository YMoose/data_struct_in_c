#ifndef __INCLUDE_BINTREE_H__
#define __INCLUDE_BINTREE_H__

#include <stddef.h>
#include <strings.h>
#include "util.h"
#include "mem.h"

typedef struct _bintree_node_t
{
    void* data;
    struct _bintree_node_t* parent;
    struct _bintree_node_t* child[2]; // 0: left; 1: right
    int height;
}bintree_node_t;

#define TREE_NODE_STATURE(p) (((p) == NULL)? -1: (p)->height)

typedef struct _bintree_t
{
    int size;
    bintree_node_t* root;
    alc_set* mem_alc_set;
    data_compare_func comp_func;
}bintree_t;


// export api
static inline bintree_t* bintree_new(alc_set* mem_alc_set, data_compare_func comp_func);
int bintree_size(bintree_t* tree);
int bintree_is_empty(bintree_t* tree);
bintree_node_t* bintree_root(bintree_t* tree);
static inline int bintree_add(bintree_t* tree, void* data);
// traversal
static inline int bintree_order_traversal(bintree_t* tree, data_traversal_func traversal_func);

static inline bintree_node_t* bintree_node_new(bintree_t* tree, void* data);
static inline void bintree_node_insert_as_lc(bintree_t* tree, bintree_node_t* parent, bintree_node_t* node);
static inline void bintree_node_insert_as_rc(bintree_t* tree, bintree_node_t* parent, bintree_node_t* node);
bintree_node_t* bintree_node_succ(bintree_node_t* node);
// int bintree_node_subtree_size(bintree_node_t* node);
static inline int bintree_node_update_height(bintree_t* tree, bintree_node_t* node);
static inline void bintree_node_update_height_above(bintree_t* tree, bintree_node_t* node);


// implements

static inline
void _bintree_node_insert(bintree_t* tree, bintree_node_t* parent, bintree_node_t* node, int child_idx)
{
    // todo: atomic
    tree->size ++;
    parent->child[child_idx] = node;
    node->parent = parent;
    // todo: update height
}

static inline 
void bintree_node_insert_as_lc(bintree_t* tree, bintree_node_t* parent, bintree_node_t* node)
{
    _bintree_node_insert(tree, parent, node, 0);
}

static inline 
void bintree_node_insert_as_rc(bintree_t* tree, bintree_node_t* parent, bintree_node_t* node)
{
    _bintree_node_insert(tree, parent, node, 1);
}

static inline
bintree_t* bintree_new(alc_set* mem_alc_set, data_compare_func comp_func)
{
    PRESET_MEM_ALC_SET(mem_alc_set);
    bintree_t* new_tree = (bintree_t*)MEM_ALLOC(mem_alc_set, sizeof(bintree_t));
    if (new_tree == NULL)
    {
        return NULL;
    }
    new_tree->comp_func = comp_func;
    new_tree->mem_alc_set = mem_alc_set;
    new_tree->root = NULL;
    new_tree->size = 0;
    return new_tree;
}

static inline
int bintree_add(bintree_t* tree, void* data)
{
    // todo read write lock
    bintree_node_t** p_node = &tree->root;
    bintree_node_t** cur_node = &tree->root;
    bintree_node_t* new_node = NULL;
    
    new_node = bintree_node_new(tree, data);
    if (new_node == NULL)
    {
        return -1;
    }
    if (tree->root == NULL)
    {
        tree->root = new_node;
        tree->size = 1;
        return 0;
    }
    
    while(1)
    {
        p_node = cur_node;
        
        if (tree->comp_func != NULL && tree->comp_func(data, (*cur_node)->data) <= 0)
        {
            cur_node = &((*cur_node)->child[0]);
            if (*cur_node == NULL)
            {
                bintree_node_insert_as_lc(tree, *p_node, new_node);
                return 0;
            }
        }
        else
        {
            cur_node = &((*cur_node)->child[1]);
            if (*cur_node == NULL)
            {
                bintree_node_insert_as_rc(tree, *p_node, new_node);
                return 0;
            }
        }
    }

    *cur_node = new_node;

    return 0;
}

static inline
int bintree_node_update_height(bintree_t* tree, bintree_node_t* node)
{
    node->height = 1 + 
                   MAX(TREE_NODE_STATURE(node->child[0]), 
                       TREE_NODE_STATURE(node->child[1]));
    return node->height;
}

static inline
void bintree_node_update_height_above(bintree_t* tree, bintree_node_t* node)
{
    while(node->parent != NULL)
    {
        bintree_node_update_height(tree, node);
        node = node->parent;
    }
    return; 
}

static inline 
bintree_node_t* bintree_node_new(bintree_t* tree, void* data)
{
    bintree_node_t* new_node = (bintree_node_t*)MEM_ALLOC(tree->mem_alc_set, sizeof(bintree_node_t));
    memset(new_node, 0, sizeof(bintree_node_t));
    new_node->data = data;
    return new_node;
}

static inline
int bintree_order_traversal(bintree_t* tree, data_traversal_func traversal_func)
{
    void** node_vec;
    int ret = 0;
    int i = 0;
    int tree_size;
    int back_from = -1;
    bintree_node_t* cur_node;

    if (traversal_func == NULL)
    {
        return 0;
    }

    tree_size = tree->size;
    node_vec = (void**) MEM_ALLOC(tree->mem_alc_set, sizeof(void*) * tree_size);
    cur_node = tree->root;

    while(i < tree_size)
    {
        if (back_from == 1)
        {
            back_from = cur_node == cur_node->parent->child[0]? 0: 1;
            cur_node = cur_node->parent;
            continue;
        }

        if (cur_node->child[0] != NULL && back_from != 0)
        {
            cur_node = cur_node->child[0];
            back_from = -1;
            continue;
        }

        // enqueue mid
        node_vec[i] = cur_node->data;
        i++;

        if (cur_node->child[1] != NULL)
        {
            cur_node = cur_node->child[1];
            back_from = -1;
            continue;
        }

        back_from = 1;
    }

    for (; ret < tree_size; ret++){
        if (traversal_func(node_vec[ret]) > 0){
            break;
        }
    }

    return ret;
}


#endif /* __INCLUDE_BINTREE_H__ */