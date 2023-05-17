#include <stdio.h>
#include <stdlib.h>

#define InitSize 5 // 宏定义初始化数组的大小

typedef int ElemType; // 指定元素类型为 int
typedef struct				// 定义顺序表结构体
{
	ElemType *data; // 指向存储元素的数组指针
	int maxSize;		// 顺序表的最大空间
	int length;			// 顺序表的实际长度
} SeqList;

// 初始化数组
void InitList(SeqList *list)
{
	list->data = (ElemType *)malloc(sizeof(ElemType) * InitSize); // 申请内存空间，大小为 InitSize
	list->maxSize = InitSize;
	list->length = 0; // 初始化长度为 0
}

// 动态增加顺序表的长度
void IncreaseSize(SeqList *list, int len)
{
	ElemType *p = list->data; // p 用于保存原有数据的指针
	list->maxSize += len;			// 扩大最大空间
	// 申请新的内存空间
	list->data = (ElemType *)malloc(sizeof(ElemType) * list->maxSize);
	// 之后，需要把原来的内存空间内存储的值转移过来
	for (int i = 0; i < list->length; i++)
	{
		list->data[i] = p[i]; // 把原来的元素存放到新空间中
	}
	// 释放掉原来的内存空间
	free(p);
}

// 在顺序表的第 i 位插入元素 e
void ListInsert(SeqList *list, int i, ElemType e)
{
	if (i < 1 || i > list->length + 1) // 判断插入位置是否合法
	{
		return; // 不合法则直接返回
	}

	if (list->length == list->maxSize) // 如果当前长度已经达到了最大空间
	{
		return; // 则不再增加
	}

	for (int j = list->length; j >= i; j--) // 把第 i 个位置及之后的元素后移一位
	{
		list->data[j] = list->data[j - 1];
	}
	list->data[i - 1] = e; // 在第 i 个位置插入元素 e
	list->length++;				 // 长度加 1
}

// 删除顺序表第 i 个元素并返回值
ElemType ListDelete(SeqList *list, int i)
{
	if (i < 1 || i > list->length + 1)		 // 判断删除位置是否合法
		return -1;													 // 不合法则返回 -1
	ElemType e = list->data[i - 1];				 // 保存被删除的元素
	for (int j = i; j < list->length; j++) // 把第 i+1 到最后一个元素前移一位
	{
		list->data[j - 1] = list->data[j];
	}
	list->length--; // 长度减 1
	return e;				// 返回被删除的元素
}

// 获取顺序表第 i 位元素
ElemType GetElem(SeqList list, int i)
{
	if (i < 1 || i > list.length + 1) // 判断获取位置是否合法
		return -1;											// 不合法则返回 -1

	return list.data[i - 1]; // 返回第 i 个元素的值
}

// 获取 n 在顺序表中的位置
int LocateElem(SeqList list, ElemType n)
{
	for (int i = 0; i < list.length; i++) // 遍历顺序表中的所有元素
	{
		if (list.data[i] == n) // 如果找到了值为 n 的元素
		{
			return i + 1; // 返回该元素的下标加一
		}
	}
	return -1; // 如果遍历完整个顺序表都没有找到，则返回 -1
}

// 打印顺序表元素
void PrintList(SeqList list)
{
	for (int i = 0; i < list.length; i++) // 遍历顺序表中的所有元素
	{
		printf("%d ", list.data[i]); // 输出该元素
	}
	printf("\n"); // 换行
}

// 销毁链表
void DestroyList(SeqList *list)
{
	if (list == NULL)
		return;

	free(list->data);	 // 释放内存空间
	list->length = 0;	 // 将长度清零
	list->data = NULL; // 释放指针
}

int main()
{
	SeqList L;
	InitList(&L);					// 初始化顺序表
	ListInsert(&L, 1, 1); // 插入元素
	ListInsert(&L, 2, 2);
	ListInsert(&L, 3, 3);
	ListInsert(&L, 4, 4);
	ListInsert(&L, 5, 5);
	IncreaseSize(&L, 5);	// 扩大顺序表大小
	ListInsert(&L, 6, 6); // 继续插入元素
	ListInsert(&L, 7, 7);
	ListInsert(&L, 1, 0);							// 在第一位插入元素
	PrintList(L);											// 输出顺序表中的所有元素
	printf("%d\n", GetElem(L, 5));		// 获取第五个元素并输出
	ListDelete(&L, 1);								// 删除第一个元素
	PrintList(L);											// 输出删除后的顺序表中的所有元素
	printf("%d\n", LocateElem(L, 6)); // 查找值为 6 的元素在顺序表中的位置并输出
	DestroyList(&L);									// 销毁顺序表
	return 0;
}
