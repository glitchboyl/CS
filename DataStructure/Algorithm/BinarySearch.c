#include <stdio.h>

int BinarySearch(int list[], int n, int length)
{
  int left = 0, right = length - 1;
  int mid;
  while (left <= right)
  {
    mid = (left + right) / 2;
    if (list[mid] == n)
      return mid;
    else if (list[mid] < n)
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}

int main()
{
  int orderList[] = {7, 10, 13, 16, 19, 29, 32, 33, 37, 41, 43};
  int length = sizeof(orderList) / sizeof(int);
  int index = BinarySearch(orderList, 33, length);
  printf("%d\n", index);
  return 0;
}
