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

int print_data(void* data)
{
    printf("%d ",(int)data);
    return 0;
}

void test_vec(void)
{
    // init
    vector_t* vec = vec_alloc(NULL, 10);

    // vec append
    int i = 0;
    for (i = 0; i<10; i++)
    {
        vec_append(vec, (void*)(rand()%40));
    }
    
    // iterate vector
    vec_traversal(vec, print_data);
    printf("\n");

    // search ele in vector

    // delete ele 

    // iterate vector

    // search ele in vector

}

int main(void) 
{
    UNITY_BEGIN();
    RUN_TEST(test_vec);
    return UNITY_END();
}