// 用单链表保存m个整数，结点的结构为: [data|link] ，且 |data| ≤ n(n为正整数)。
// 现要求设计一个时间复杂度尽可能高效的算法，对于链表中data的绝对值相等的结点，仅保留第一次出现的结点而删除其余绝对值相等的结点。
// 例如，若给定的单链表head如: [head]->[21]->[-15]->[-15]->[-7]->[-15]
// 则删除结点后的head为：[head]->[21]->[-15]->[-7]

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LinkedNode
{
  int data;
  struct LinkedNode *link;
} LinkedNode, *LinkedList;

void Init(LinkedList *list)
{
  *list = (LinkedList)malloc(sizeof(LinkedNode));
  LinkedNode *p = *list;
  int insertData[] = {21, -15, -15, -7, -15};
  int length = sizeof(insertData) / sizeof(int);
  for (int i = 0; i < length; i++)
  {
    LinkedNode *node = (LinkedNode *)malloc(sizeof(LinkedNode));
    node->data = insertData[i];
    node->link = NULL;
    p->link = node;
    p = p->link;
  }
}

void DropDuplicates(LinkedList list, int n)
{
  bool *presence = (bool *)malloc(sizeof(bool) * (n + 1));
  LinkedNode *p = list, *q = list->link;
  while (q)
  {
    int d = abs(q->data);
    if (presence[d])
    {
      p->link = q->link;
      free(q);
      q = p->link;
    }
    else
      presence[d] = true;
    p = p->link;
    if (q)
      q = q->link;
  }
}

void Print(LinkedList list)
{
  LinkedNode *p = list->link;
  while (p)
  {
    printf("%d ", p->data);
    p = p->link;
  }
  printf("\n");
}

int main()
{
  LinkedList head;
  Init(&head);
  Print(head);
  DropDuplicates(head, 22); // because |data| ≤ n, and the maximal data is equals 21, therefore assuming n equals 22
  Print(head);
  return 0;
}