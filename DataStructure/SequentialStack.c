#include <stdio.h>
#include <stdlib.h>

#define InitSize 5 // 宏定义初始化栈的大小

typedef int ElemType; // 指定元素类型为 int
typedef struct        // 定义顺序栈结构体
{
  ElemType *data; // 存储元素的数组指针
  int maxSize;    // 栈的最大空间
  int length;     // 栈中元素个数，即栈的当前长度
} SeqStack;

// 初始化栈
void InitStack(SeqStack *stack)
{
  stack->data = (ElemType *)malloc(sizeof(ElemType) * InitSize); // 申请内存空间，大小为 InitSize
  stack->maxSize = InitSize;
  stack->length = 0; // 初始化栈顶指针为 -1，表示栈为空
}

// 动态增加栈的大小
void IncreaseSize(SeqStack *stack, int len)
{
  if (len < 0)
    return;
  ElemType *p = stack->data;                                           // p 用于保存原有数据的指针
  stack->maxSize += len;                                               // 扩大栈空间
  stack->data = (ElemType *)malloc(sizeof(ElemType) * stack->maxSize); // 申请新的内存空间
  for (int i = 0; i < stack->length; i++)
  {
    stack->data[i] = p[i]; // 把原来的元素存放到新空间中
  }
  free(p); // 释放掉原来的内存空间
}

// 进栈
void Push(SeqStack *stack, ElemType e)
{
  if (stack->length == stack->maxSize) // 如果当前长度已经达到了最大空间
    return;                            // 则不再增加
  stack->data[stack->length] = e;      // 栈顶指针加 1，元素入栈
  stack->length++;
}

// 出栈
ElemType Pop(SeqStack *stack)
{
  if (stack->length == 0)                      // 如果栈为空
    return -1;                                 // 则返回一个非法值
  ElemType e = stack->data[stack->length - 1]; // 弹出栈顶元素
  stack->length--;                             // 栈顶指针减 1
  return e;
}

// 打印栈中元素
void PrintStack(SeqStack stack)
{
  for (int i = stack.length - 1; i >= 0; i--) // 从栈顶到栈底，依次输出栈中元素
  {
    printf("%d ", stack.data[i]);
  }
  printf("\n"); // 换行
}

// 销毁栈
void DestroyStack(SeqStack *stack)
{
  stack->length = 0; // 元素个数清零
  free(stack->data); // 释放内存空间
}

int main()
{
  SeqStack S;
  InitStack(&S); // 初始化栈
  Push(&S, 1);   // 压入元素
  Push(&S, 2);
  Push(&S, 3);
  PrintStack(S);                // 输出栈中元素
  printf("Pop: %d\n", Pop(&S)); // 弹出栈顶元素并输出
  PrintStack(S);                // 输出弹出元素后的栈中元素
  DestroyStack(&S);             // 销毁栈
  return 0;
}