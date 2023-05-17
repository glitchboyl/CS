#include <stdio.h>

// 交换数组中两个元素的位置
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

// 选择排序算法
void SelectionSort(int *arr, int length)
{
  for (int i = 0; i < length - 1; i++) // 外层循环控制需要排序的起始位置i
  {
    int min = i;                         // 记录最小值的索引
    for (int j = i + 1; j < length; j++) // 内层循环从i+1到末尾遍历数组
    {
      if (arr[j] < arr[min])
        min = j; // 找到最小值的索引
    }
    swap(&arr[i], &arr[min]); // 将最小值与arr[i]交换
  }
}

int main()
{
  int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
  int length = sizeof(arr) / sizeof(int);
  SelectionSort(arr, length); // 对数组进行选择排序
  for (int i = 0; i < length; i++)
  {
    printf("%d ", arr[i]); // 输出排序结果
  }
}
