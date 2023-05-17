#include <stdio.h>

// 快速排序
void QuickSort(int *arr, int start, int end)
{
  if (start < end) // 当待排序的序列长度大于1时
  {
    int pivot = arr[start], left = start, right = end;
    // 基准值为第一个元素，left指向序列起始位置，right指向序列末尾位置

    while (left < right) // 左右指针未相遇时循环
    {
      while (left < right && arr[right] >= pivot)
        right--;              // 从右往左扫描，找到第一个小于基准值的元素
      arr[left] = arr[right]; // 将该元素赋值给左边

      while (left < right && arr[left] <= pivot)
        left++;               // 从左往右扫描，找到第一个大于基准值的元素
      arr[right] = arr[left]; // 将该元素赋值给右边
    }

    arr[left] = pivot; // 将基准值放到最终位置

    // 递归地对左右两部分进行快速排序
    QuickSort(arr, start, left - 1);
    QuickSort(arr, left + 1, end);
  }
}

int main()
{
  int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
  int length = sizeof(arr) / sizeof(int);
  QuickSort(arr, 0, length - 1); // 对数组进行快速排序
  for (int i = 0; i < length; i++)
  {
    printf("%d ", arr[i]); // 输出排序结果
  }
}
