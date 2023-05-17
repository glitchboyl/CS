#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 宏定义初始化栈的大小
#define InitSize 10

// 定义顺序栈结构体
typedef struct
{
  char *data;  // 存储元素的数组指针
  int maxSize; // 栈的最大空间
  int length;  // 栈中元素个数，即栈的当前长度
} SeqStack;

// 初始化栈
void InitStack(SeqStack *stack)
{
  // 申请内存空间，大小为 InitSize
  stack->data = (char *)malloc(sizeof(char) * InitSize);
  stack->maxSize = InitSize;
  stack->length = 0; // 初始化栈顶指针为 -1，表示栈为空
}

// 动态增加栈的大小
void IncreaseSize(SeqStack *stack, int len)
{
  if (len < 0)
    return;
  char *p = stack->data; // p 用于保存原有数据的指针
  stack->maxSize += len; // 扩大栈空间
  // 申请新的内存空间
  stack->data = (char *)malloc(sizeof(char) * stack->maxSize);
  for (int i = 0; i < stack->length; i++)
  {
    stack->data[i] = p[i]; // 把原来的元素存放到新空间中
  }
  free(p); // 释放掉原来的内存空间
}

// 进栈
void Push(SeqStack *stack, char e)
{
  // 如果当前长度已经达到了最大空间，则不再增加
  if (stack->length == stack->maxSize)
    return;
  // 栈顶指针加 1，元素入栈
  stack->data[stack->length] = e;

  stack->length++;
}

// 出栈
char Pop(SeqStack *stack)
{
  // 如果栈为空则返回一个非法值
  if (stack->length == 0)

    return '\0';
  // 弹出栈顶元素
  char e = stack->data[stack->length - 1];
  // 栈顶指针减 1
  stack->length--;

  return e;
}

// 处理输入的括号
bool handleBracket(SeqStack *stack, char bracket)
{
  char matchingBracket;
  switch (bracket)
  {
  case '(':
  case '[':
  case '{':
    // 如果当前长度已经达到了最大空间，则返回 false
    if (stack->length == stack->maxSize)
      return false;
    Push(stack, bracket); // 元素入栈
    return true;
  case ')':
    matchingBracket = '(';
    break;
  case ']':
    matchingBracket = '[';
    break;
  case '}':
    matchingBracket = '{';
    break;
  default:
    return false;
  }
  if (stack->length == 0)
  {
    return false;
  }
  char b = Pop(stack);
  if (b != matchingBracket)
  {
    return false;
  }
  return true;
}

// 获取输入括号的长度
int getInputLength(char *input)
{
  int length = 0;
  for (int i = 0; input[i] != '\0'; i++)
  {
    if (input[i] != ' ' && input[i] != '\n' && input[i] != '\r')
    {
      length++;
    }
  }
  return length;
}

// 输入括号
void Input(SeqStack *stack)
{
  char brackets[99];
  printf("Input brackets:");
  fgets(brackets, 99, stdin); // 从标准输入流中读取输入的括号
  int inputLength = getInputLength(brackets);
  // 如果输入长度大于最大栈空间，则动态增加栈的大小
  if (inputLength > stack->maxSize)
  {
    IncreaseSize(stack, inputLength - stack->maxSize);
  }
  for (int i = 0; i < inputLength; i++)
  {
    if (!handleBracket(stack, brackets[i])) // 处理输入的括号
    {
      printf("Not Matching %c\n", brackets[i]);
      return;
    }
  }
  printf("All matching! Congratulations!\n");
}

// 打印栈中元素
void PrintStack(SeqStack stack)
{
  // 从栈顶到栈底，依次输出栈中元素
  for (int i = stack.length - 1; i >= 0; i--)
  {
    printf("%c ", stack.data[i]);
  }
  printf("\n"); // 换行
}

// 销毁栈
void DestroyStack(SeqStack *stack)
{
  stack->length = 0; // 元素个数清零
  free(stack->data); // 释放内存空间
}

// 主函数
int main()
{
  SeqStack S;
  InitStack(&S);    // 初始化栈
  Input(&S);        // 输入括号
  DestroyStack(&S); // 销毁栈
  return 0;
}