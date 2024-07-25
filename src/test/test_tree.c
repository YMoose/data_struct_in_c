#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "my_struct_in_c.h"

void setUp(void)
{

}

void tearDown(void)
{

}

int compare_num(void* data, void* base)
{
    return (int)data - (int)base;
}

int print_data(void* data)
{
    printf("%d ",(int)data);
    return 0;
}

void test_tree(void)
{
    bintree_t* tree = bintree_new(NULL, compare_num);
    // add tree node
    int i = 0;
    for (i = 0; i<10; i++)
    {
        bintree_add(tree, (void*)(rand()%40));
    }// iterate tree
    bintree_order_traversal(tree, print_data);
    printf("\n");
    // search tree node in tree
    // delete tree node 
    // iterate tree
    // search tree node in tree
}

int main(void) 
{
    UNITY_BEGIN();
    RUN_TEST(test_tree);
    return UNITY_END();
}