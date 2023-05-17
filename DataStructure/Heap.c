#include <stdio.h>

#define MAX_SIZE 42 // THE ULTAMATE ANSWER TO THE UNIVERSE

typedef struct
{
  int node[MAX_SIZE];
  int length;
} Heap;

// 交换两个数的值
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

// 初始化堆
void InitHeap(Heap *heap)
{
  heap->length = 0; // 堆长度为0
}

// 往堆中插入一个元素
void InsertNode(Heap *heap, int n)
{
  if (heap->length == MAX_SIZE) // 如果堆已满，则直接返回
    return;

  int i = heap->length++;                         // 将新节点插入到堆的末尾，并将堆长度加1
  int j = (i - 1) / 2;                            // 父节点的下标
  heap->node[i] = n;                              // 将新节点赋值
  while (j >= 0 && heap->node[i] < heap->node[j]) // 如果新节点比父节点小，则需要上浮
  {
    swap(&heap->node[i], &heap->node[j]); // 交换新节点和父节点的值
    i = j;                                // 更新新节点的下标
    j = (j - 1) / 2;                      // 更新父节点的下标
  }
}

// 从堆中删除一个元素
void DeleteNode(Heap *heap, int n)
{
  if (heap->length == 0) // 如果堆为空，则直接返回
    return;

  int i = 0;
  for (; i < heap->length; i++) // 找到值为n的节点
  {
    if (heap->node[i] == n)
      break;
  }
  if (i == heap->length) // 如果堆中不存在值为n的节点，则直接返回
    return;

  swap(&heap->node[i], &heap->node[--heap->length]);             // 将最后一个节点替换被删除的节点，并将堆长度减1
  while ((2 * i + 2 < heap->length || 2 * i + 1 < heap->length)) // 如果存在子节点，则需要下沉
  {
    int min = i;
    if (heap->node[2 * i + 1] < heap->node[min]) // 左子节点比当前节点小
    {
      min = 2 * i + 1;
    }
    if (2 * i + 1 < heap->length && heap->node[2 * i + 2] < heap->node[min]) // 右子节点比当前节点和左子节点都小
    {
      min = 2 * i + 2;
    }
    if (min == i) // 如果当前节点已经是最小的了，则不需要继续下沉
      break;
    swap(&heap->node[i], &heap->node[min]); // 交换当前节点和最小子节点的值
    i = min;                                // 更新当前节点的下标
  }
}

// 输出堆中的所有元素
void PrintHeap(Heap heap)
{
  for (int i = 0; i < heap.length; i++)
  {
    printf("%d ", heap.node[i]);
  }
  printf("\n");
}

int main()
{
  Heap H;
  InitHeap(&H); // 初始化堆
  int insertNodes[] = {9, 17, 65, 32, 45, 78, 87, 53};
  int insertLength = sizeof(insertNodes) / sizeof(int);
  for (int i = 0; i < insertLength; i++) // 往堆中插入一些节点
  {
    InsertNode(&H, insertNodes[i]);
  }
  PrintHeap(H);       // 输出当前堆中的元素
  InsertNode(&H, 13); // 插入一个新节点
  PrintHeap(H);       // 输出当前堆中的元素
  InsertNode(&H, 46); // 插入一个新节点
  PrintHeap(H);       // 输出当前堆中的元素
  DeleteNode(&H, 13); // 删除一个节点
  PrintHeap(H);       // 输出当前堆中的元素
  // DeleteNode(&H, 65); // 删除一个节点
  // PrintHeap(H);       // 输出当前堆中的元素

  return 0;
}