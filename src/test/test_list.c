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

void test_list(void)
{
    // init
    list_t* list = list_new(NULL, compare_num);

    // add tree node
    int i = 0;
    for (i = 0; i<10; i++)
    {
        list_add_tail(list, (void*)(rand()%40));
    }
    
    // iterate list
    list_traversal(list, print_data);
    printf("\n");

    // search ele in list

    // delete ele 

    // iterate list

    // search ele in tree

}

int main(void) 
{
    UNITY_BEGIN();
    RUN_TEST(test_list);
    return UNITY_END();
}