#include <stdio.h>
#include <stdlib.h>

/* 归并排序 */
void MergeSort(int *arr, int start, int end)
{
  if (start < end) // 子数组长度大于1时继续递归拆分
  {
    int mid = (start + end) / 2;  // 计算中间位置
    
    MergeSort(arr, start, mid);   // 对左半部分子数组进行排序
    MergeSort(arr, mid + 1, end); // 对右半部分子数组进行排序

    int length = end - start + 1;                    // 计算待排序子数组的长度
    int *temp = (int *)malloc(sizeof(int) * length); // 动态分配临时数组
    int i, j, k;
    for (i = 0; i < length; i++) // 将待排序子数组复制到临时数组
    {
      temp[i] = arr[start + i];
    }
    for (i = 0, j = mid - start + 1, k = i; i <= mid - start && j <= end - start; k++) // 合并两个排好序的子数组
    {
      arr[start + k] = temp[temp[i] < temp[j] ? i++ : j++];
    }
    while (i <= mid - start) // 如果左半部分子数组还有剩余元素，直接复制到原数组中
      arr[start + (k++)] = temp[i++];
    while (j <= end - start) // 如果右半部分子数组还有剩余元素，直接复制到原数组中
      arr[start + (k++)] = temp[j++];
    free(temp); // 释放临时数组
  }
}

int main()
{
  int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
  int length = sizeof(arr) / sizeof(int);
  MergeSort(arr, 0, length - 1); // 对整个数组进行排序
  for (int i = 0; i < length; i++)
  {
    printf("%d ", arr[i]); // 输出排序结果
  }
}
