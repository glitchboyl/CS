#include <stdio.h>
#include <limits.h>  // INT_MAX
#include <stdbool.h> // bool

#define V 5 // 顶点数

// 找到 dist[] 中未确定最短路径的最小值并返回其下标
int minDistance(int dist[], bool final[])
{
  int min = INT_MAX, minIndex;
  for (int i = 0; i < V; i++)
  {
    // 如果 i 未确定最短路径，且 i 的距离值比当前最小值还小
    if (!final[i] && dist[i] < min)
    {
      min = dist[i];
      minIndex = i;
    }
  }
  return minIndex;
}

void dijkstra(int graph[V][V], int start, int end)
{
  if (start < 0 || start > V - 1 || end < 0 || end > V - 1)
    return;

  bool final[V]; // 记录每个顶点是否已经确定最短路径
  int dist[V],   // 记录源顶点与每个顶点的最短路径长度
      path[V];   // 记录每个顶点的最短路径的前驱顶点下标

  // 初始化
  for (int i = 0; i < V; i++)
  {
    final[i] = false; // 初始时所有顶点都未确定最短路径
    dist[i] = graph[start][i] ? graph[start][i]
                              : INT_MAX; // 源顶点到自己的距离为0，到其他顶点的距离初始值为该边权值（如果有），否则为无穷大
    path[i] = graph[start][i] ? start
                              : -1; // 记录每个顶点在最短路径上的前一个顶点，如果直接到达，则记录为 start；否则标记为 -1。
  }
  final[start] = true; // 将源顶点加入已确定最短路径集合中
  dist[start] = 0;     // 源顶点到自己的距离为0

  for (int j = 0; j < V - 1; j++) // 最多进行 V-1 次循环
  {
    int u = minDistance(dist, final); // 找到未确定最短路径的距离最小的顶点
    final[u] = true;                  // 标记该顶点已经确定最短路径
    for (int k = 0; k < V; k++)
    {
      if (final[k]) // 如果顶点 k 已经确定最短路径，则跳过
        continue;
      if (graph[u][k]) // 如果 u 到 k 存在边
      {
        int d = dist[u] + graph[u][k]; // 计算从源顶点到 k 的距离
        if (d < dist[k])               // 如果从 u 经过 k 到达的距离比当前记录的距离还要小
        {
          dist[k] = d; // 更新 k 的距离值
          path[k] = u; // 修改 k 在最短路径上的前一个顶点
        }
      }
    }
  }
  // 打印从 start 到 end 的最短路径
  printf("path is: ");
  int p = end;
  while (p != -1)
  {
    printf("%d ", p);
    p = path[p];
    if (p != -1)
      printf("<-- ");
  }
  printf("\nits distance is %d", dist[end]);
}

int main()
{
  int graph[V][V] = {{0, 10, 0, 0, 5},
                     {0, 0, 1, 0, 2},
                     {0, 0, 0, 4, 0},
                     {7, 0, 6, 0, 0},
                     {0, 3, 9, 2, 0}};
  dijkstra(graph, 0, 2); // 求解从顶点0到顶点2的最短路径
  return 0;
}