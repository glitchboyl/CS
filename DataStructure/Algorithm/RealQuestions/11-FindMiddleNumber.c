// 一个长度为 L 的升序序列 S，处在第 L/2 个位置的数称为 S 的中位数。
// 例如，若序列 S1={11,13,15,17,19}，则 S1 的中位数是 15。
// 两个序列的中位数是含它们所有元素的升序序列的中位数，例如，若 S2={2,4,6,8,20},则 S1 和 S2 的中位数是 11。
// 现在有两个等长升序序列 A 和 B，试设计一个在时间和空间两方面都尽可能高效的算法，找出两个序列 A 和 B 的中位数。

#include <stdio.h>

int FindMiddleNumber(int A[], int B[], int length)
{
  int a = 0, b = 0, result;
  for (int i = 0; i < length; i++)
  {
    result = A[a] < B[b] ? A[a++] : B[b++];
  }
  return result;
}

int main()
{
  int A[] = {11, 13, 15, 17, 19};
  int B[] = {2, 4, 6, 8, 20};
  int length = sizeof(A) / sizeof(A[0]);
  printf("The middle number is %d", FindMiddle(A, B, length));
  return 0;
}