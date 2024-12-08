#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "my_struct_in_c.h"

const char test_str[] = "this is a string for test";

void setUp(void)
{

}

void tearDown(void)
{

}

void queue_test(void)
{
    // init
    queue_t test_queue;
    uint64_t buffer_size = 32;
    uint8_t* buffer = malloc(buffer_size);
    uint8_t* out_buf = malloc(buffer_size);
    memset(out_buf, 0, buffer_size);
    queue_init(&test_queue, buffer, buffer_size);
    TEST_ASSERT_TRUE(buffer_size == queue_size(&test_queue));
    TEST_ASSERT_TRUE(0 == queue_len(&test_queue));

    queue_in_byte(&test_queue, test_str, sizeof(test_str));
    TEST_ASSERT_TRUE(sizeof(test_str) == queue_len(&test_queue));
    queue_in_byte(&test_queue, test_str, sizeof(test_str));
    TEST_ASSERT_TRUE(queue_len(&test_queue) == queue_size(&test_queue));

    queue_out_byte(&test_queue, out_buf, sizeof(test_str));
    printf("%ld %s\n",queue_len(&test_queue), out_buf);

}

int main(void) 
{
    UNITY_BEGIN();
    RUN_TEST(queue_test);
    return UNITY_END();
}