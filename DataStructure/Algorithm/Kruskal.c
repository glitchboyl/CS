#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool

#define V 6 // 顶点数

// 边数组进行归并排序
void MergeSort(int *sides[], int start, int end)
{
  if (start < end)
  {
    int mid = (start + end) / 2;
    int length = end - start + 1;

    // 递归调用 MergeSort 对左右两个数组进行排序
    MergeSort(sides, start, mid);
    MergeSort(sides, mid + 1, end);

    int *temp[length];
    int i, j, k;

    // 将要归并的两个有序数组合并到 temp 数组中
    for (i = 0; i < length; i++)
    {
      temp[i] = sides[start + i];
    }
    for (i = 0, j = mid - start + 1, k = start; i <= mid - start && j <= end - start; k++)
    {
      sides[k] = temp[temp[j][2] < temp[i][2] ? j++ : i++]; // 按照边权从小到大进行归并排序
    }

    // 将剩余的元素复制回 sides 数组
    while (i <= mid - start)
      sides[k++] = temp[i++];
    while (j <= end - start)
      sides[k++] = temp[j++];
  }
}

// 查找元素index所在的树的根节点
int Find(int parent[V], int index)
{
  if (index >= V) // 判断index是否越界
    return index;
  int root = index;
  while (parent[root] > -1) // 如果当前节点不是根节点，则继续向上查找其父节点，直到找到根节点
  {
    root = parent[root];
  }
  while (index != root) // 路径压缩，将查找路径上的所有节点都直接与根节点相连，减小树的深度
  {
    int p = parent[index];
    parent[index] = root;
    index = p;
  }
  return root; // 返回根节点
}

// 将两个连通分量合并，使用按秩合并优化
bool Union(int parent[V], int p, int q)
{
  if (p >= V || q >= V) // 判断p和q是否越界
    return false;

  int pp = Find(parent, p); // 查找p所在的树的根节点
  int qp = Find(parent, q); // 查找q所在的树的根节点

  if (pp == qp) // 如果p和q已经在同一个连通分量中，则无需合并
    return false;

  // 按秩合并，将深度小的树作为深度大的树的子树
  if (parent[qp] < parent[pp])
  {
    parent[qp] += parent[pp];
    parent[pp] = qp;
  }
  else
  {
    parent[pp] += parent[qp];
    parent[qp] = pp;
  }

  return true;
}

// Kruskal 算法求解最小生成树
void kruskal(int graph[V][V])
{
  int parent[V];

  // 初始化每个结点的父节点为 -1 表示该节点是根节点，且秩为 0
  for (int i = 0; i < V; i++)
  {
    parent[i] = -1;
  }

  // 将所有边保存在数组 sides 中，并对它们按权重从小到大排序（调用 MergeSort 函数）
  int *sides[15];
  int s = 0;
  for (int i = 0; i < V; i++)
  {
    for (int j = i + 1; j < V; j++)
    {
      if (graph[i][j] > 0) // 如果两个节点之间有边，则将该边保存在 sides 数组中
      {
        int *side = (int *)malloc(sizeof(int) * 3); // 分配一个大小为 3 的 int 型数组，用来保存边的信息
        side[0] = i;                                // 保存边的起点
        side[1] = j;                                // 保存边的终点
        side[2] = graph[i][j];                      // 保存边的权重
        sides[s++] = side;                          // 将边添加到 sides 数组中
      }
    }
  }
  MergeSort(sides, 0, s - 1); // 按边权从小到大对边数组进行归并排序

  int cost = 0;               // 最小生成树的总权值
  for (int i = 0; i < s; i++) // 遍历所有的边
  {
    // 如果该边的两个端点不在同一个连通分量中，则将它们合并，并将边权加入最小生成树的总权值 cost 中
    if (Union(parent, sides[i][0], sides[i][1]))
      cost += sides[i][2];

    // 如果所有结点都已经在同一个连通分量中，则退出循环
    if (Find(parent, sides[i][0]) + V == 0)
      break;
  }
  printf("Kruskal cost: %d", cost); // 输出最小生成树的总权值
}

int main()
{
  int graph[V][V] = {{0, 6, 5, 1, 0, 0},
                     {6, 0, 0, 5, 3, 0},
                     {5, 0, 0, 4, 0, 2},
                     {1, 5, 4, 0, 6, 4},
                     {0, 3, 0, 6, 0, 6},
                     {0, 0, 2, 4, 6, 0}};

  kruskal(graph); // 调用 kruskal 函数，求解最小生成树
  return 0;
}
