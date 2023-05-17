#include <stdio.h>
#include <limits.h>  // INT_MAX
#include <stdbool.h> // bool

#define V 6 // 顶点数

// 找到 cost[] 中未加入树中的最小值并返回其下标
int minCost(int cost[], bool isJoined[])
{
  int min = INT_MAX, minIndex;
  for (int i = 0; i < V; i++)
  {
    if (!isJoined[i] && cost[i] < min) // 如果 i 未加入树中，且 i 的cost值比当前最小值还小
    {
      min = cost[i];
      minIndex = i;
    }
  }
  return minIndex;
}

void prim(int graph[V][V], int src)
{
  bool isJoined[V]; // 记录每个顶点是否已经加入树中
  int cost[V];      // 记录从树中某个顶点到每个顶点的最小权值

  // 初始化
  for (int i = 0; i < V; i++)
  {
    isJoined[i] = false; // 初始时所有顶点都未加入树中
    cost[i] = graph[src][i] ? graph[src][i]
                            : INT_MAX; // 源节点到自己的cost为0，到其他节点的cost初始值为该边权值（如果有），否则为无穷大
  }
  isJoined[src] = true; // 将源节点加入树中
  cost[src] = 0;

  for (int j = 0; j < V - 1; j++) // 最多进行 V-1 次循环
  {
    int u = minCost(cost, isJoined); // 找到未加入树中的cost最小的节点
    isJoined[u] = true;              // 标记该节点已经加入树中
    for (int k = 0; k < V; k++)
    {
      if (isJoined[k]) // 如果节点 k 已经加入树中，则跳过
        continue;
      if (graph[u][k] != 0 && graph[u][k] < cost[k]) // 如果 u 到 k 存在边，并且 u 到 k 的权值比从树中某个顶点到 k 的权值更小
        cost[k] = graph[u][k];                       // 更新从树中某个顶点到 k 的最小权值为 u 到 k 的权值
    }
  }
  // 计算最小生成树的总权值并打印
  int c = 0;
  for (int s = 0; s < V; s++)
  {
    c += cost[s];
  }
  printf("Prim cost: %d", c);
}

int main()
{
  int graph[V][V] = {{0, 6, 5, 1, 0, 0},
                     {6, 0, 0, 5, 3, 0},
                     {5, 0, 0, 4, 0, 2},
                     {1, 5, 4, 0, 6, 4},
                     {0, 3, 0, 6, 0, 6},
                     {0, 0, 2, 4, 6, 0}};
  prim(graph, 0); // 求解以顶点0为源点的最小生成树的总权值
  return 0;
}
