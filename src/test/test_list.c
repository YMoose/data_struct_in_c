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

typedef struct _test_node_t
{
    list_node_t list;
    int number;
}test_node_t;

typedef struct _test_node_list
{
    test_node_t* header;
}test_node_list_t;

int data_print(test_node_t* node)
{
    printf("%d ",node->number);
    return 0;
}

void list_test(void)
{
    // init
    test_node_list_t test;
    list_node_t *cur = NULL;
    test.header = malloc(sizeof(test_node_t));
    list_head_init(&(test.header->list));

    // add list node
    int i = 0;
    for (i = 0; i<10; i++)
    {
        test_node_t *new_node = malloc(sizeof(test_node_t));
        new_node->number = rand() % 40;
        list_add_tail(&(new_node->list), &(test.header->list));
    }
    
    // iterate list
    list_for_each(cur, &(test.header->list))
    {
        data_print(list_entry(cur, test_node_t, list));
    }
    printf("\n");

    // search ele in list

    // delete ele 

    // iterate list

    // search ele in list

}

int main(void) 
{
    UNITY_BEGIN();
    RUN_TEST(list_test);
    return UNITY_END();
}