// 已知由n (n ≥ 2) 个正整数构成的集合 A = {a_k|O≤k<n}，
// 将其划分为两个不相交的子集A_1和A_2，元素个数分别是n_1和n_2, A_1和A_2中元素之和分别为S_1和S_2。
// 设计一个尽可能高效的划分算法，满足|n_1-n_2|最小且|S_1-S_2|最大。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void SplitSet(int set[], int length)
{
  bool flag = true;
  int start = 0, middle = length / 2, end = length - 1;
  while (flag)
  {
    int pivot = set[start], left = start, right = end;
    while (left < right)
    {
      while (left < right && set[right] >= pivot)
        right--;
      set[left] = set[right];
      while (left < right && set[left] <= pivot)
        left++;
      set[right] = set[left];
    }
    set[left] = pivot;
    if (left == middle - 1)
      flag = false;
    else if (left < middle - 1)
      start = left + 1;
    else
      end = left - 1;
  }

  int n1 = middle, n2 = length - n1, S1 = 0, S2 = 0;
  for (int i = 0; i < length; i++)
  {
    if (i < n1)
      S1 += set[i];
    else
      S2 += set[i];
  }
  printf("the minimal result of |n_1-n_2| is equals %d\n", abs(n1 - n2));
  printf("and the maximal result of |S_1-S_2| is equals %d", abs(S1 - S2));
}

int main()
{
  int A[] = {0, 2, 4, 6, 8, 1, 3, 5, 7};
  SplitSet(A, sizeof(A) / sizeof(int));
  return 0;
}