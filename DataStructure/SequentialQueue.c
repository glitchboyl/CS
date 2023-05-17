#include <stdio.h>
#include <stdlib.h>

#define InitSize 5 // 定义初始队列大小

typedef int ElemType;

// 定义顺序循环队列结构体
typedef struct
{
  ElemType *data; // 存储队列元素的数组指针
  int maxSize;    // 队列可存储的最大元素个数
  int length;     // 队列当前存储的元素个数
  int front;      // 队首指针，指向队首元素
  int rear;       // 队尾指针，指向下一个待插入元素的位置
} SeqQueue;

// 初始化队列
void InitQueue(SeqQueue *queue)
{
  queue->data = (ElemType *)malloc(sizeof(ElemType) * InitSize); // 动态分配内存
  queue->maxSize = InitSize;                                     // 初始化队列可存储的最大元素个数
  queue->front = 0;                                              // 初始化队首指针
  queue->rear = 0;                                               // 初始化队尾指针
  queue->length = 0;                                             // 初始化队列长度为0
}

// 动态增加队列内存
void IncreaseSize(SeqQueue *queue, int size)
{
  if (size < 1) // 若size小于1则不进行扩容操作
    return;

  ElemType *p = queue->data;                                           // 保存原始数据
  queue->maxSize += size;                                              // 增加队列最大容量
  queue->data = (ElemType *)malloc(sizeof(ElemType) * queue->maxSize); // 重新分配内存
  for (int i = 0; i < queue->length; ++i)
  {
    queue->data[i] = p[(queue->front + i) % queue->maxSize]; // 复制原始数据到新的数组中
  }
  queue->front = 0;            // 新队列的队首指针为0
  queue->rear = queue->length; // 新队列的队尾指针为当前队列长度
  free(p);                     // 释放原有内存
}

// 入队
void EnQueue(SeqQueue *queue, ElemType e)
{
  if (queue->length == queue->maxSize) // 队列已满，不能继续入队
    return;
  queue->data[queue->rear] = e;                     // 存储元素
  queue->rear = (queue->rear + 1) % queue->maxSize; // 修改队尾指针
  queue->length++;                                  // 增加队列长度
}

// 出队
ElemType DeQueue(SeqQueue *queue)
{
  if (queue->length == 0) // 队列为空，返回-1，通常情况下可以抛出异常
    return -1;

  ElemType e = queue->data[queue->front];             // 取出队首元素
  queue->front = (queue->front + 1) % queue->maxSize; // 修改队首指针
  queue->length--;                                    // 减少队列长度
  return e;                                           // 返回队首元素的值
}

// 打印队列元素
void PrintQueue(SeqQueue queue)
{
  int i = queue.front;
  for (int j = 0; j < queue.length; j++)
  {
    printf("%d ", queue.data[i]);
    i = (i + 1) % queue.maxSize; // 循环遍历数组
  }
  printf("\n");
}

// 销毁队列
void DestroyQueue(SeqQueue *queue)
{
  free(queue->data); // 释放内存
  queue->front = 0;  // 初始化队首指针
  queue->rear = 0;   // 初始化队尾指针
  queue->length = 0; // 初始化队列长度为0
}

int main()
{
  SeqQueue Q;
  InitQueue(&Q); // 初始化顺序循环队列
  EnQueue(&Q, 1);
  EnQueue(&Q, 2);
  EnQueue(&Q, 3);
  EnQueue(&Q, 4);
  EnQueue(&Q, 5);
  PrintQueue(Q);                        // 打印队列元素
  printf("DeQueue: %d\n", DeQueue(&Q)); // 出队并输出元素值
  PrintQueue(Q);                        // 再次打印队列元素
  printf("DeQueue: %d\n", DeQueue(&Q)); // 出队并输出元素值
  PrintQueue(Q);                        // 再次打印队列元素
  EnQueue(&Q, 7);                       // 入队
  EnQueue(&Q, 8);
  PrintQueue(Q);                        // 打印队列元素
  printf("DeQueue: %d\n", DeQueue(&Q)); // 出队并输出元素值
  PrintQueue(Q);                        // 再次打印队列元素
  DestroyQueue(&Q);                     // 销毁顺序循环队列
  return 0;
}
