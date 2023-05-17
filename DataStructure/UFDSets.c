// Union-Find Disjoint Sets

#include <stdio.h>

#define MAX_SIZE 5

typedef struct
{
  char data[MAX_SIZE];  // 存储每个元素的值
  int parent[MAX_SIZE]; // 存储每个元素的父节点，-1表示该元素是树根
} UFDSets;

// 初始化并查集，将每个元素的值设置为A、B、C、D、E，将每个元素的父节点设为-1，即每个元素都是独立的一棵树
void InitUFDSets(UFDSets *sets)
{
  for (int i = 0; i < MAX_SIZE; i++)
  {
    sets->data[i] = 65 + i; // 给每个元素赋一个字母值
    sets->parent[i] = -1;   // 将每个元素的父节点设为-1
  }
}

// 查找元素index所在的树的根节点
int Find(UFDSets sets, int index)
{
  if (index >= MAX_SIZE) // 判断index是否越界
    return index;
  int root = index;
  while (sets.parent[root] > -1) // 如果当前节点不是根节点，则继续向上查找其父节点，直到找到根节点
  {
    root = sets.parent[root];
  }
  while (index != root) // 将查找路径上的所有节点都直接连接到根节点上，路径压缩
  {
    int p = sets.parent[index];
    sets.parent[index] = root;
    index = p;
  }
  return root; // 返回根节点的索引
}

// 合并两棵树，p和q是两个要合并的元素的索引
void Union(UFDSets *sets, int p, int q)
{
  if (p >= MAX_SIZE || q >= MAX_SIZE) // 判断索引是否越界
    return;

  int pp = Find(*sets, p); // 获取p所在树的根节点
  int qp = Find(*sets, q); // 获取q所在树的根节点
  if (pp == qp)            // 判断根节点是否相同
    return;

  // 将两棵树合并，将小的树作为大树的子树
  if (sets->parent[qp] < sets->parent[pp])
  {
    sets->parent[qp] += sets->parent[pp];
    sets->parent[pp] = qp;
  }
  else
  {
    sets->parent[pp] += sets->parent[qp];
    sets->parent[qp] = pp;
  }
}

// 根据给定的邻接矩阵构建图，遍历上三角部分，并对每条边进行Union操作，最后得到一个连通分量
int UnionByGraph(UFDSets *sets, int graph[MAX_SIZE][MAX_SIZE])
{
  for (int i = 0; i < MAX_SIZE; i++)
  {
    for (int j = i + 1; j < MAX_SIZE; j++) // 遍历上三角部分，避免重复遍历
    {
      if (graph[i][j] != 0) // 如果两个元素之间有边，则进行Union操作
        Union(sets, i, j);
    }
  }
  int count = 0;
  for (int i = 0; i < MAX_SIZE; i++) // 计算并查集中有多少个连通分量
  {
    if (sets->parent[i] < 0) // 如果一个元素的父节点为-1，则表示该元素是一棵树的根节点，即该元素所在的连通分量
      count++;
  }
  return count; // 返回连通分量的数量
}

// 打印并查集中每个元素及其父节点
void PrintUFDSets(UFDSets sets)
{
  for (int i = 0; i < MAX_SIZE; i++)
  {
    printf("[%c, %d] ", sets.data[i], sets.parent[i]);
  }
  printf("\n");
}

int main()
{
  UFDSets S;
  InitUFDSets(&S);
  PrintUFDSets(S);
  int Graph[MAX_SIZE][MAX_SIZE] = {
      {0, 1, 1, 0, 0},
      {1, 0, 1, 0, 0},
      {1, 1, 0, 0, 0},
      {0, 0, 0, 0, 1},
      {0, 0, 0, 1, 0},
  };
  printf("The Graph have %d connected component(s).\n", UnionByGraph(&S, Graph)); // 输出连通分量的数量
  PrintUFDSets(S);
  return 0;
}