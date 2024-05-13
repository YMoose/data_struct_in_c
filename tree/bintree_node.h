#ifndef __INCLUDE_BINTREE_H__
#define __INCLUDE_BINTREE_H__

#include "mem.h"

typedef struct _bintree_node_t
{
    void* data;
    struct _bintree_node_t* parent;
    struct _bintree_node_t* l_child;
    struct _bintree_node_t* r_child;
    int height;
}bintree_node_t;

#define TREE_NODE_STATURE(p) (p == NULL)? -1: p->height;

typedef int (*data_compare_func)(void* data, void* base);

typedef struct _bintree_t
{
    int size;
    bintree_node_t* root;
    alc_set* mem_alc_set;
    data_compare_func comp_func;
}bintree_t;


// export api
bintree_t* bintree_new(alc_set mem_alc_set, data_compare_func comp_func);
int bintree_size(bintree_t* tree);
bool bintree_is_empty(bintree_t* tree);
bintree_node_t* bintree_root(bintree_t* tree);
int bintree_add(void* data);
// traversal
int bintree_;

bintree_node_t* bintree_node_init(bintree_t* tree, void* data);
bintree_node_t* bintree_node_insert_as_lc(bintree_t* tree, void* data);
bintree_node_t* bintree_node_insert_as_rc(bintree_t* tree, void* data);
bintree_node_t* bintree_node_succ(bintree_node_t* node);
int bintree_node_subtree_size(bintree_node_t* node);
int bintree_node_update_height(bintree_t* tree, bintree_node_t* node);
void bintree_node_update_height_above(bintree_t* tree, bintree_node_t* node);


// implements

static inline
bintree_t* bintree_new(alc_set* mem_alc_set, data_compare_func comp_func)
{
    if (comp_func == NULL)
    {
        return NULL;
    }
    PRESET_MEM_ALC_SET(mem_alc_set);
    bintree_t* new_tree = (bintree_t*)MEM_ALLOC(mem_alc_set, sizeof(bintree_t));
    if (new_tree == NULL)
    {
        return NULL
    }
    new_tree->comp_func = comp_func;
    new_tree->mem_alc_set = mem_alc_set;
    new_tree->root = NULL;
    new_tree->size = 0;
    return new_tree;
}

int bintree_add(bintree_t* tree, void* data)
{
    bintree_node_t* p_node = tree->root;
    while(p_node != NULL)
    {
        if (tree->comp_func(data, p_node->data) <= 0)
        {
            p_node = 
        }
        else
        {

        }
    }
    return 0;
}

static inline
int bintree_node_update_height(bintree_t* tree, bintree_node_t* node)
{
    node->height = 1 + 
                   MAX(TREE_NODE_STATURE(node->l_child), 
                       TREE_NODE_STATURE(node->r_child));
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
bintree_node_t* bintree_node_init(bintree_t* tree, void* data)
{
    bintree_node_t* new_node = (bintree_node_t*)MEM_ALLOC(tree->mem_alc_set, sizeof(bintree_node_t));
    new_node->data = data;
    new_node->parent = NULL;
    new_node->l_child = NULL;
    new_node->r_child = NULL;
    new_node->height = 0;
    return new_node;
}

static inline 
bintree_node_t* bintree_node_insert_as_lc(bintree_t* tree, void* data)
{

}

#endif /* __INCLUDE_BINTREE_H__ */