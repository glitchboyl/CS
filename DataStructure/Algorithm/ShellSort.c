#include <stdio.h>

// 希尔排序算法实现
void ShellSort(int *arr, int length)
{
  for (int d = length / 2; d > 0; d /= 2) // 步长不断缩小，直到为1
  {
    for (int i = d; i < length; i++) // 对每个步长进行插入排序
    {
      int temp = arr[i]; // 取出当前待插入的元素
      int j;
      for (j = i - d; j >= 0 && arr[j] > temp; j -= d) // 在有序区间中查找合适的位置并插入
      {
        arr[j + d] = arr[j];
      }
      arr[j + d] = temp; // 将待插入元素放到正确的位置上
    }
  }
}

int main()
{
  int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
  int length = sizeof(arr) / sizeof(int);
  ShellSort(arr, length); // 调用希尔排序算法进行排序
  for (int i = 0; i < length; i++)
  {
    printf("%d ", arr[i]); // 输出排序结果
  }
}
