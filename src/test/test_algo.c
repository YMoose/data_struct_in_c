#include "unity.h"
#include "algorithm/algo.h"

void setUp(void)
{

}

void tearDown(void)
{

}

void test_max_sub_seq_sum(void)
{
    int max = 0;
    int start = 0;
    int end = 0;
    int test1[8] = {4, -3, 5, -2, -1, 2, 6, -2};
    max = max_sub_sequence_sum1(test1, 8, &start, &end);
    TEST_ASSERT(max == 11);
    TEST_ASSERT(start == 0);
    TEST_ASSERT(end == 6);
    max = max_sub_sequence_sum2(test1, 8, &start, &end);
    TEST_ASSERT(max == 11);
    TEST_ASSERT(start == 0);
    TEST_ASSERT(end == 6);
}

int main(void) 
{
    UNITY_BEGIN();
    RUN_TEST(test_max_sub_seq_sum);
    return UNITY_END();
}
