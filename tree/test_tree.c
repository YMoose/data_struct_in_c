#include "unity.h"
#include "bintree_node.h"

void test_tree(void)
{
    bintree_t* tree = bintree_new(NULL);
    // add tree node
    
    // iterate tree
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