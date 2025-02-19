#ifndef __INCLUDE_ALGO_H__
#define __INCLUDE_ALGO_H__

#include <assert.h>
#include <stddef.h>

int
max_sub_sequence_sum1 (const int *numbs, int len, int *start_index,
                       int *end_index)
{
  assert (numbs != NULL && len > 0);
  int i = 0, j = 0, k = 0;
  int max = numbs[0], sum = 0;

  for (i = 0; i < len; i++)
    {
      for (j = i; j < len; j++)
        {
          sum += numbs[j];
          if (sum > max)
            {
              max = sum;
              if (start_index != NULL)
                *start_index = i;
              if (end_index != NULL)
                *end_index = j;
            }
        }
      sum = 0;
    }

  return max;
}

int
max_sub_sequence_sum2 (const int *numbs, int len, int *start_index,
                       int *end_index)
{
  // base case
  assert (numbs != NULL && len > 0);
  if (len == 1)
    return numbs[0];

  int max = 0;
  int sum = 0;
  int i = 0;
  int mid = len >> 1;
  int cross_start = mid - 1, cross_end = mid;
  int left_start = 0, left_end = 0;
  int right_start = 0, right_end = 0;
  int left_max = max_sub_sequence_sum2 (numbs, mid, &left_start, &left_end);
  int right_max = max_sub_sequence_sum2 (numbs + mid, len - mid, &right_start,
                                         &right_end);

  right_start += mid;
  right_end += mid;

  // get max cross the mid
  max = numbs[mid];
  for (i = mid; i < len; i++)
    {
      sum += numbs[i];
      if (sum > max)
        {
          max = sum;
          cross_end = i;
        }
    }

  sum = max;
  max += numbs[mid - 1];
  for (i = mid - 1; i >= 0; i--)
    {
      sum += numbs[i];
      if (sum > max)
        {
          max = sum;
          cross_start = i;
        }
    }

  if (left_max > right_max && left_max > max)
    {
      if (start_index != NULL)
        *start_index = left_start;

      if (end_index != NULL)
        *end_index = left_end;

      return left_max;
    }

  if (max > right_max)
    {
      if (start_index != NULL)
        *start_index = cross_start;

      if (end_index != NULL)
        *end_index = cross_end;

      return max;
    }

  if (start_index != NULL)
    *start_index = right_start;

  if (end_index != NULL)
    *end_index = right_end;

  return right_max;
}

#endif /* __INCLUDE_ALGO_H__ */