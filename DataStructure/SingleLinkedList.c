#include <stdio.h>
#include <stdlib.h>

// 定义结点类型和链表类型
typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkedList;

// 链表初始化
void InitList(LinkedList *list)
{
    // 申请头结点空间
    *list = (LNode *)malloc(sizeof(LNode));
    // 头结点的指针域置空
    (*list)->next = NULL;
}

// 获取链表第 i 位元素
LNode *GetElem(LinkedList list, int i)
{
    if (i < 0)
        return NULL;

    int j = 0;
    LNode *p = list;
    while (p != NULL && j < i)
    {
        p = p->next;
        j++;
    }

    return p;
}

// 在链表的第 i 位插入元素 e
void ListInsert(LinkedList list, int i, ElemType e)
{
    if (i < 1) // 如果插入的位置小于 1，直接插入到第一个位置
        i = 1;

    // 获取第 i 位元素的前驱结点
    LNode *p = GetElem(list, i - 1);

    if (p == NULL)
        return;

    // 为插入元素申请新的内存
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    // 插入元素的后继指针指向前驱结点指向的后继结点
    s->next = p->next;
    // 前驱结点的后继指针指向插入元素，完成插入操作
    p->next = s;
}

// 删除链表的第 i 个元素
ElemType ListDelete(LinkedList list, int i)
{
    if (i < 1)
        return -1;

    // 获取第 i 位元素的前驱结点
    LNode *p = GetElem(list, i - 1);
    if (p == NULL)
        return -1;

    // 获取第 i 位元素的后继结点
    LNode *q = p->next;
    ElemType e = q->data;
    // 令第 i 位元素的前驱结点的后继指针指向第 i 位元素的后继结点
    p->next = q->next;
    // 释放第 i 位元素的内存，完成删除操作
    free(q);
    return e;
}

// 找到在链表中的值等于 n 的结点
LNode *LocateElem(LinkedList list, ElemType n)
{
    LNode *p = list->next;
    while (p != NULL && p->data != n)
    {
        p = p->next;
    }
    return p;
}

// 获取链表的长度
int GetLength(LinkedList list)
{
    int length = 0;
    LNode *p = list;
    while (p->next != NULL)
    {
        p = p->next;
        length++;
    }
    return length;
}

// 打印链表元素
void PrintList(LinkedList list)
{
    LNode *p = list->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 销毁链表
void DestroyList(LinkedList list)
{
    if (list == NULL)
        return;
    LNode *p = list;
    while (p != NULL)
    {
        LNode *q = p;
        p = p->next;
        free(q);
    }
}

int main()
{
    // 初始化链表
    LinkedList L;
    InitList(&L);

    // 在链表中插入元素
    ListInsert(L, 1, 1);
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    ListInsert(L, 4, 4);
    ListInsert(L, 5, 5);

    // 打印链表元素并获取链表长度
    PrintList(L);
    printf("Single Linked List Length is %d\n", GetLength(L));

    // 删除链表中的元素
    ListDelete(L, 2);
    PrintList(L);
    printf("Single Linked List Length is %d\n", GetLength(L));

    // 获取链表第三个元素的值并查找值为 3 的元素结点
    printf("%d\n", GetElem(L, 3)->data);
    printf("%d\n", LocateElem(L, 3)->data);

    // 销毁链表
    DestroyList(L);
    return 0;
}
