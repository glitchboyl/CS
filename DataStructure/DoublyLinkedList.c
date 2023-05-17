#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// 双向链表结点
typedef struct LNode
{
	ElemType data;						 // 数据域
	struct LNode *prev, *next; // 前驱指针、后继指针
} LNode, *LinkedList;

// 初始化链表
void InitList(LinkedList *list)
{
	*list = (LNode *)malloc(sizeof(LNode)); // 分配内存
	(*list)->prev = NULL;										// 初始化头节点
	(*list)->next = NULL;
}

// 获取指定位置的元素
LNode *GetElem(LinkedList list, int i)
{
	if (i < 0)
		return NULL; // 输入参数错误

	LNode *p = list;
	int j = 0;
	while (p != NULL && j < i) // 从头节点开始往后查找每个结点，直到所需位置或链表末尾
	{
		p = p->next;
		j++;
	}
	return p;
}

// 在链表的第 i 位插入元素 e
void ListInsert(LinkedList list, int i, ElemType e)
{
	if (i < 1)
		return; // 输入参数错误

	LNode *p = GetElem(list, i - 1); // 获取待插入位置的前一个结点
	if (p == NULL)
		return; // 插入位置不合法，直接返回

	LNode *s = (LNode *)malloc(sizeof(LNode)); // 分配内存
	s->data = e;															 // 存储元素
	s->prev = p;															 // 设置结点的前驱指针和后继指针
	s->next = p->next;
	if (p->next != NULL)
		p->next->prev = s; // 修改原链表中相应结点的前驱指针
	p->next = s;				 // 修改原链表中相应结点的后继指针
}

// 删除链表的第 i 个元素
ElemType ListDelete(LinkedList list, int i)
{
	if (i < 1)
		return -1; // 输入参数错误

	LNode *p = GetElem(list, i); // 获取待删除位置的结点
	if (p == NULL)
		return -1; // 删除位置不合法，直接返回

	ElemType e = p->data;		 // 获取待删除结点的值
	p->prev->next = p->next; // 修改原链表中相应结点的前驱指针和后继指针
	if (p->next != NULL)
		p->next->prev = p->prev;
	free(p); // 释放删除结点空间
	return e;
}

// 找到在链表中的值等于 n 的结点
LNode *LocateElem(LinkedList list, ElemType n)
{
	LNode *p = list->next;						// 从第一个结点开始查找
	while (p != NULL && p->data != n) // 查找每个结点，直到找到值等于 n 的结点或链表末尾
	{
		p = p->next;
	}
	return p;
}

// 打印链表数据
void PrintList(LinkedList list)
{
	LNode *p = list->next; // 从第一个结点开始打印
	while (p != NULL)			 // 遍历每个结点，输出结点的数据域
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

// 获取链表长度
int GetLength(LinkedList list)
{
	int length = 0;
	LNode *p = list;
	while (p->next != NULL) // 遍历每个结点，统计链表长度
	{
		p = p->next;
		length++;
	}
	return length;
}

// 销毁链表
void DestroyList(LinkedList list)
{
	if (list == NULL)
		return;

	LNode *p = list;
	while (p != NULL) // 依次删除每个结点
	{
		LNode *q = p;
		p = p->next;
		free(q);
	}
}

int main()
{
	LinkedList L;
	InitList(&L); // 初始化双向链表
	ListInsert(L, 1, 1);
	ListInsert(L, 2, 2);
	ListInsert(L, 3, 3);
	ListInsert(L, 4, 4);
	PrintList(L); // 打印双向链表

	printf("Doubly Linked List Length is %d\n", GetLength(L)); // 输出双向链表长度

	ListDelete(L, 2);																					 // 删除第2个元素
	PrintList(L);																							 // 打印双向链表
	printf("Doubly Linked List Length is %d\n", GetLength(L)); // 输出双向链表长度

	ListDelete(L, 3); // 删除第3个元素
	DestroyList(L);		// 销毁双向链表
	return 0;
}
