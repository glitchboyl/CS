#include <stdio.h>
#include <limits.h>  // INT_MAX
#include <stdbool.h> // bool

#define V 5 // 顶点数

// 通过 path 矩阵递归输出起点到终点的路径
void PrintPath(int path[V][V], int start, int end)
{
  int p = path[start][end];
  while (p != -1)
  {
    if (path[p][end] != -1)
      PrintPath(path, p, end); // 递归打印路径
    printf("<-- %d ", p);
    end = p;
    p = path[start][end];
  }
}

// Floyd算法，计算任意两点之间的最短路径和距离
void floyd(int graph[V][V], int start, int end)
{
  if (start < 0 || start > V - 1 || end < 0 || end > V - 1) // 判断输入是否合法
    return;
  int dist[V][V], path[V][V];
  // 初始化距离矩阵和路径矩阵
  for (int i = 0; i < V; i++)
  {
    for (int j = 0; j < V; j++)
    {
      dist[i][j] = i == j ? 0 : graph[i][j] ? graph[i][j]
                                            : INT_MAX; // 如果有边，则距离为边权值；否则设为无穷大
      path[i][j] = -1;                                 // 无路径
    }
  }

  // Floyd算法核心部分，动态规划地更新距离矩阵和路径矩阵
  for (int i = 0; i < V; i++)
  {
    for (int j = 0; j < V; j++)
    {
      for (int k = 0; k < V; k++)
      {
        if (i == j || j == k) // 跳过无效情况
          continue;
        // 如果经过中转点i的距离比原来更短，则更新
        if (dist[j][i] != INT_MAX && dist[i][k] != INT_MAX && dist[j][k] > dist[j][i] + dist[i][k])
        {
          dist[j][k] = dist[j][i] + dist[i][k];
          path[j][k] = i; // 记录路径
        }
      }
    }
  }

  printf("path is: %d ", end);
  PrintPath(path, start, end); // 输出起点到终点的路径
  printf("<-- %d\n", start);
  printf("its distance is %d", dist[start][end]); // 输出起点到终点的距离
}

int main()
{
  int graph[V][V] = {{0, 0, 1, 0, 10},
                     {0, 0, 0, 1, 5},
                     {0, 1, 0, 0, 7},
                     {0, 0, 0, 0, 1},
                     {0, 0, 0, 0, 0}};
  floyd(graph, 0, 4); // 计算从V0到V4的最短路径和距离
  return 0;
}
