#include "algorithm/algo.h"
#include "unity.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define TEST_TIME 100
#define NUMBER_RANGE 100

void
setUp (void)
{
}

void
tearDown (void)
{
}

void
test_max_sub_seq_sum (void)
{
  int max1, max2;
  int i, j = 0;
  int start = 0;
  int end = 0;
  int test1[10] = {3,8,12,0,25,41,-5,-34,10,-78 };
  int test_array[TEST_TIME] = {};
  int random_number = 0;
  max1 = max_sub_sequence_sum1 (test1, 10, &start, &end);
  max2 = max_sub_sequence_sum2 (test1, 10, &start, &end);
  TEST_ASSERT (max2 == max1);

  for (i = 1; i < TEST_TIME; i++)
    {
      srand ((unsigned int)time (NULL) + random_number);
      for (j = 0; j < i; j++)
        {
          random_number
              = rand () % (NUMBER_RANGE + 1) - rand () % (NUMBER_RANGE + 1);
          test_array[j] = random_number;
          printf("%d,", random_number);
        }
      printf("\n");
      max1 = max_sub_sequence_sum1 (test_array, i, NULL, NULL);
      max2 = max_sub_sequence_sum2 (test_array, i, NULL, NULL);
      TEST_ASSERT (max2 == max1);
    }
}

int
main (void)
{
  UNITY_BEGIN ();
  RUN_TEST (test_max_sub_seq_sum);
  return UNITY_END ();
}
