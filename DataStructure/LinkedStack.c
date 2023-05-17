#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// 链式栈结点
typedef struct SNode
{
	ElemType data;			// 数据域
	struct SNode *next; // 指向下一个结点的指针
} SNode, *LinkedStack;

// 初始化链式栈
void InitStack(LinkedStack *stack)
{
	*stack = (LinkedStack)malloc(sizeof(SNode)); // 分配内存空间
	(*stack)->next = NULL;											 // 设置头结点的指针为 NULL
}

// 入栈操作
void Push(LinkedStack stack, ElemType e)
{
	SNode *s = (SNode *)malloc(sizeof(SNode)); // 分配新结点空间
	s->data = e;															 // 将数据存入新结点
	s->next = stack->next;										 // 新结点指向头结点之后的第一个结点
	stack->next = s;													 // 头结点指向新结点
}

// 出栈操作
ElemType Pop(LinkedStack stack)
{
	if (stack->next == NULL)
		return -1; // 栈为空

	SNode *p = stack->next; // p 指向栈顶结点
	ElemType e = p->data;		// 获取栈顶元素
	stack->next = p->next;	// 头结点指向栈顶结点的下一个结点
	free(p);								// 释放栈顶结点
	return e;
}

// 打印栈中元素
void PrintStack(LinkedStack stack)
{
	SNode *p = stack->next; // p 指向第一个元素结点
	while (p != NULL)				// 遍历链表，输出每个元素
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

// 销毁链式栈
void DestroyStack(LinkedStack stack)
{
	if (stack == NULL)
		return;

	SNode *p = stack; // p 指向头结点
	while (p != NULL) // 依次删除每个结点
	{
		SNode *q = p;
		p = p->next;
		free(q); // 释放当前结点的空间
	}
}

int main()
{
	LinkedStack S;
	InitStack(&S); // 初始化链式栈
	Push(S, 1);		 // 入栈操作
	Push(S, 2);
	Push(S, 3);
	PrintStack(S); // 打印栈中元素
	Pop(S);				 // 出栈操作
	PrintStack(S);
	DestroyStack(S); // 销毁链式栈
	return 0;
}
