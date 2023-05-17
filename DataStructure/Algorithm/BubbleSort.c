#include <stdio.h>
#include <stdbool.h>

// 冒泡排序算法实现
void BubbleSort(int *arr, int length)
{
  for (int i = 0; i < length - 1; i++) // 外层循环控制排序轮数
  {
    bool flag = false;                       // 标志位，如果一轮下来没有交换过元素，则说明已经排好序，可以提前结束排序
    for (int j = 0; j < length - i - 1; j++) // 内层循环控制每一轮比较次数
    {
      if (arr[j + 1] < arr[j]) // 如果后一个元素比前一个元素小，则交换位置
      {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        flag = true; // 标记为已经交换过元素
      }
    }
    if (!flag) // 如果一轮下来没有交换过元素，则说明已经排好序，可以提前结束排序
      break;
  }
}

int main()
{
  int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
  int length = sizeof(arr) / sizeof(int);
  BubbleSort(arr, length); // 调用冒泡排序算法对数组进行排序
  for (int i = 0; i < length; i++)
  {
    printf("%d ", arr[i]); // 输出排序结果
  }
}
