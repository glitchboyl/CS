// 已知一个带有表头结点的单链表，假设该链表只给出了头指针list，
// 在不改变链表的前提下，请设计一个尽可能高效的算法，查找链表中倒数第k个位置上的结点(k为正整数)
// 若查找成功，算法输出该结点的data域的值，并返回1: 否则，只返回0。

#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode
{
  int data;
  struct LinkedNode *link;
} LinkedNode, *LinkedList;

void InitLinkedList(LinkedList *list)
{
  *list = (LinkedList)malloc(sizeof(LinkedNode));
  (*list)->link = NULL;
}

void Insert(LinkedList list, int data)
{
  LinkedNode *p = list;
  LinkedNode *node = (LinkedNode *)malloc(sizeof(LinkedNode));
  node->data = data;
  node->link = NULL;
  while (p->link)
  {
    p = p->link;
  }
  p->link = node;
}

int FindTheKthFromLast(LinkedList list, int k)
{
  LinkedNode *p = list->link, *q = list->link;
  if (!p || k < 1)
    return 0;
  int i = 0;
  while (p)
  {
    if (i < k)
      i++;
    else
      q = q->link;
    p = p->link;
  }
  if (i != k)
    return 0;
  printf("the result is %d when k equals %d", k, q->data);
  return 1;
}

int main()
{
  LinkedList L;
  InitLinkedList(&L);
  int insertList[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int insertLength = sizeof(insertList) / sizeof(insertList[0]);
  for (int i = 0; i < insertLength; i++)
  {
    Insert(L, insertList[i]);
  }
  FindTheKthFromLast(L, 1);
  return 0;
}