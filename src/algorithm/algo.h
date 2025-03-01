#ifndef __INCLUDE_ALGO_H__
#define __INCLUDE_ALGO_H__

#include <assert.h>
#include <stddef.h>
#include "util.h"

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

int
max_sub_sequence_sum3 (const int *numbs, int len, int *start_index,
                       int *end_index)
{
  assert (numbs != NULL && len > 0);
  int max = numbs[0];
  int sum = 0;
  int start = 0;
  int end = 0;
  int temp_start = 0;
  int i = 0;

  for (i = 0; i < len; i++)
    {
      sum += numbs[i];

      if (sum > max)
        {
          max = sum;
          start = temp_start;
          end = i;
        }

      // 如果前面的块大于0则可以给后面的块提升，则保留，如果小于0则剔除
      if (sum < 0)
        {
          sum = 0;
          temp_start = i + 1;
        }
    }

  if (start_index != NULL)
    *start_index = start;

  if (end_index != NULL)
    *end_index = end;

  return max;
}

static inline void
swap (int *a, int i, int j)
{
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
  return;
}

void
bubblesort (int *a, int len)
{
  assert (a != NULL);
  int unsorted = 1;
  int i = 0;
  while (unsorted)
    {
      unsorted = 0;
      for (i = 0; i < len - 1; i++)
        {
          if (a[i] > a[i + 1])
            {
              swap (a, i, i + 1);
              unsorted = 1;
            }
        }
    }
  return;
}

int
LCS_recursive (char *s1, int len_s1, char *s2, int len_s2)
{
  assert (s1 != NULL && s2 != NULL);
  if (len_s1 == 0 || len_s2 == 0)
    {
      return 0;
    }

  int i;
  int max_lcs = LCS_recursive (s1, len_s1, s2 + 1, len_s2 - 1);

  for (i = 0; i < len_s1; i++)
    {
      if (s1[i] == s2[0])
        {
          max_lcs = max (1
                             + LCS_recursive (s1 + i + 1, len_s1 - i - 1,
                                              s2 + 1, len_s2 - 1),
                         max_lcs);
          break;
        }
    }
  return max_lcs;
}

int
LCS (char *s1, int len_s1, char *s2, int len_s2)
{
  assert (s1 != NULL && s2 != NULL);
  if (len_s1 == 0 || len_s2 == 0)
    {
      return 0;
    }

  int i = 0;
  int j = 0;
  int **temp = _my_malloc_imp (sizeof (int *) * len_s1);
  int temp_max = 0;
  int match = 0;

  assert(temp != NULL);
  DBG ("  ");
  for (i = 0; i < len_s1; i++)
    {
      DBG ("%c ", s1[i]);
      temp[i] = _my_malloc_imp (sizeof (int) * 2);
      temp[i][0] = 0;
      temp[i][1] = 0;
    }
  DBG ("\n");

  for (j = 0; j < len_s2; j++)
    {
      DBG ("%c ", s2[j]);
      for (i = 0; i < len_s1; i++)
        {
          temp[i][0] = temp[i][1];
          match = 0 < i ? temp[i][0] : 0;
          temp_max = 0 < i ? temp[i - 1][1] : 0;
          if (s2[j] == s1[i])
            {
              match++;
            }
          temp[i][1] = max (match, temp_max);

          DBG ("%d ", temp[i][1]);
        }
      DBG ("\n");
    }

    for (i = 0; i < len_s1; i++)
    {
      _my_mfree_imp (temp[i]);
    }
    _my_mfree_imp (temp);
    
    return temp[len_s1 - 1][1];
}

#endif /* __INCLUDE_ALGO_H__ */