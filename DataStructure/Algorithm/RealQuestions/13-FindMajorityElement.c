// 已知一个整数序列A=(a_0, a_1, ..., a_{n-1})，其中 O≤a_i<n (O≤i<n)。
// 若存在 a_{p1}=a_{p2}=...=a_{pm}=x 且 m > n/2 (0≤p_k<n, 1≤k≤m)，则称x为A的主元素。
// 例如 A=(0,5,5,3,5,7,5,5)，则 5 为主元素; 又如 A=(0,5,5,3,5,1,5,7)，则A中没有主元素。
// 假设A中的n个元素保存在一个一维数组中，请设计一个尽可能高效的算法，找出A的主元素。若存在主元素，则输出该元素; 否则输出-1。

#include <stdio.h>
#include <stdlib.h>

int FindMajorityElement(int *arr, int length)
{
  int *temp = (int *)malloc(sizeof(int) * length);
  for (int i = 0; i < length; i++)
  {
    temp[arr[i]]++;
  }
  int count = 0, index = -1;
  for (int i = 0; i < length; i++)
  {
    if (temp[arr[i]] > count)
    {
      count = temp[arr[i]];
      index = i;
    }
  }
  if (count > length / 2)
    return arr[index];
  return -1;
}

void PrintResult(char arr, int r)
{
  if (r != -1)
    printf("the majority element of %c is %d\n", arr, r);
  else
    printf("the majority element of %c doesn't exist\n", arr);
}

int main()
{
  int A[] = {0, 5, 5, 3, 5, 7, 5, 5};
  int B[] = {0, 5, 5, 3, 5, 1, 5, 7};
  int a = FindMajorityElement(A, sizeof(A) / sizeof(int));
  int b = FindMajorityElement(B, sizeof(B) / sizeof(int));
  PrintResult('A', a);
  PrintResult('B', b);
  return 0;
}