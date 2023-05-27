// 给定一个含 n(n≥1) 个整数的数组，请设计一个在时间上尽可能高效的算法，找出数组中未出现的最小正整数。
// 例如，数组{-5, 3, 2, 3}中未出现的最小正整数是1；数组{1, 2, 3}中未出现的最小正整数是4。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int FirstMissingPositiveInt(int arr[], int length)
{
  bool *flags = (bool *)malloc(length * sizeof(bool));
  for (int i = 0; i < length; i++)
  {
    if (arr[i] > 0 && !flags[arr[i] - 1])
      flags[arr[i] - 1] = true;
  }
  for (int i = 0; i < length; i++)
  {
    if (!flags[i])
    {
      free(flags);
      return i + 1;
    }
  }
  return length + 1;
}

int main()
{
  int A[] = {-5, 3, 2, 3};
  int B[] = {1, 2, 3};
  printf("the first missing positive int of A is equals %d\n", FirstMissingPositiveInt(A, sizeof(A) / sizeof(int)));
  printf("the first missing positive int of B is equals %d\n", FirstMissingPositiveInt(B, sizeof(B) / sizeof(int)));
  return 0;
}