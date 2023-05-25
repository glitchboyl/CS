// 设将 (n > 1)个整数存放到一维数组 R 中。试设计一个在时间和空间两方面都尽可能高效的算法。
// 将R中保存的序列循环左移p (o<p<n) 个位置

#include <stdio.h>

void reverse(int *arr, int left, int right)
{
  while (left < right)
  {
    int temp = arr[left];
    arr[left++] = arr[right];
    arr[right--] = temp;
  }
}

void LeftShift(int *arr, int length, int p)
{
  // 对 p 取模，防止左移超过数组长度
  p %= length;
  // 翻转前 p 个元素
  reverse(arr, 0, p - 1);
  // 翻转剩下的 n-p 个元素
  reverse(arr, p, length - 1);
  // // 翻转整个数组
  reverse(arr, 0, length - 1);
}

int main()
{
  int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int length = sizeof(arr) / sizeof(arr[0]);
  LeftShift(arr, length, 4);
  for (int i = 0; i < length; i++)
  {
    printf("%d ", arr[i]);
  }
  return 0;
}