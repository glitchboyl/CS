// 定义三元组 (a,b,c)(a,b,c均为正数) 的距离 D=|a-b|+|b-c|+|c-a|。
// 给定3个非空整数集合S1、S2和S3，按升序分别存储在3个数组中，请设计一个尽可能高效的算法，计算并输出所有可能的三元组 (a,b,c)(a ∈ S1,b ∈ S2，C ∈ S3) 中的最小距离。
// 例如 S1={-1,0,9}，S2={-25,-10,10,11}，S3={2,9,17,30,41}，则最小距离为2，相应的三元组为(9,10,9)。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h> // INT_MAX

void TriadMinimalDistance(int S1[], int S2[], int S3[], int l1, int l2, int l3)
{
  int a = 0, b = 0, c = 0, distance = INT_MAX;

  // brute force solution
  // for (int i = a; i < l1; i++)
  // {
  //   for (int j = b; j < l2; j++)
  //   {
  //     for (int k = c; k < l3; k++)
  //     {
  //       int d = abs(S1[i] - S2[j]) + abs(S2[j] - S3[k]) + abs(S3[k] - S1[i]);
  //       if (d < distance)
  //       {
  //         distance = d;
  //         a = i;
  //         b = j;
  //         c = k;
  //       }
  //     }
  //   }
  // }

  // perfect solution?
  int pa = a, pb = b, pc = c;
  while (pa != l1 - 1 || pb != l2 - 1 || pc != l3 - 1)
  {
    int d = abs(S1[pa] - S2[pb]) + abs(S2[pb] - S3[pc]) + abs(S3[pc] - S1[pa]);
    if (d < distance)
    {
      distance = d;
      a = pa;
      b = pb;
      c = pc;
    }

    int min, *m = NULL;
    if (pa + 1 < l1)
    {
      min = S1[pa];
      m = &pa;
    }
    if (pb + 1 < l2 && (!m || S2[pb] < min))
    {
      min = S2[pb];
      m = &pb;
    }
    if (pc + 1 < l3 && (!m || S3[pc] < min))
    {
      min = S3[pc];
      m = &pc;
    }
    (*m)++;
  }
  printf("the triad is (%d, %d, %d) and it's distance equals %d", S1[a], S2[b], S3[c], distance);
}

int main()
{
  int S1[] = {-1, 0, 9}, S2[] = {-25, -10, 10, 11}, S3[] = {2, 9, 17, 30, 41};
  TriadMinimalDistance(S1, S2, S3, sizeof(S1) / sizeof(int), sizeof(S2) / sizeof(int), sizeof(S3) / sizeof(int));
  return 0;
}