#include <stdio.h>

// 插入排序算法
void InsertSort(int *arr, int length)
{
  for (int i = 1; i < length; i++) // 遍历整个数组，从第二个元素开始插入
  {
    int temp = arr[i];              // 记录当前待插入元素的值
    int j = i - 1;                  // 初始化内循环指针，比较前一个元素是否大于待插入元素
    while (j >= 0 && temp < arr[j]) // 如果前一个元素大于待插入元素，则将该元素后移一位，继续向前比较
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = temp; // 将待插入元素插入到合适位置
  }
}

// 二分插入排序算法
void BinaryInsertSort(int *arr, int length)
{
  for (int i = 1; i < length; i++) // 从第二个元素开始，逐个将元素插入前面已排好序的数组中
  {
    int temp = arr[i];           // 取出当前待插入的元素
    int left = 0, right = i - 1; // 定义左右指针，初始时整个有序区间为[0,i-1]
    int mid;
    while (left <= right) // 采用二分查找法定位插入位置
    {
      mid = (left + right) / 2; // 计算中间位置
      if (temp < arr[mid])      // 如果待插入元素小于中间位置的值，则在左侧继续查找
        right = mid - 1;
      else // 否则，在右侧继续查找
        left = mid + 1;
    }
    for (int j = i - 1; j >= left; j--) // 将插入位置之后的元素全部向后移动一位
    {
      arr[j + 1] = arr[j];
    }
    arr[left] = temp; // 将待插入元素放到正确的位置上
  }
}

int main()
{
  int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
  int length = sizeof(arr) / sizeof(int);
  // InsertSort(arr, length);         // 调用插入排序算法进行排序
  BinaryInsertSort(arr, length);   // 调用二分插入排序算法进行排序
  for (int i = 0; i < length; i++) // 打印排序后的结果
  {
    printf("%d ", arr[i]);
  }
}
