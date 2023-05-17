#include <stdio.h>

// 交换数组中两个元素的位置
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

// 调整堆，保证父节点大于子节点
void HeapAdjust(int *arr, int length, int k)
{
  int max = k;
  if (2 * k + 1 < length && arr[2 * k + 1] > arr[max]) // 左子节点存在且大于父节点
    max = 2 * k + 1;                                   // 记录左子节点下标
  if (2 * k + 2 < length && arr[2 * k + 2] > arr[max]) // 右子节点存在且大于当前最大值
    max = 2 * k + 2;                                   // 记录右子节点下标
  if (max != k)                                        // 最大值下标不等于当前节点下标，说明需要交换
  {
    swap(&arr[k], &arr[max]);     // 交换当前节点与最大值节点
    HeapAdjust(arr, length, max); // 继续向下调整
  }
}

// 建立初始堆
void BuildMaxHeap(int *arr, int length)
{
  for (int i = length / 2 - 1; i >= 0; i--) // 从最后一个非叶子节点开始向上调整
  {
    HeapAdjust(arr, length, i);
  }
}

// 堆排序算法
void HeapSort(int *arr, int length)
{
  BuildMaxHeap(arr, length);              // 建立初始堆
  for (int i = length - 1; i > 0; i--) // 依次取出最大值，放到数组后面
  {
    swap(&arr[0], &arr[i]); // 将堆顶元素与当前最后一个元素交换位置
    HeapAdjust(arr, i, 0);  // 继续向下调整堆
  }
}

int main()
{
  int arr[] = {53, 17, 78, 9, 45, 65, 87, 32};
  int length = sizeof(arr) / sizeof(*arr);
  HeapSort(arr, length);
  for (int i = 0; i < length; i++)
  {
    printf("%d ", arr[i]); // 输出排序结果
  }
}