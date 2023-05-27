// 设线性表采用带头结点的单链表保存，请设计一个空间复杂度为 O(1) 且时间上尽可能高效的算法，
// 重新排列L中的各结点,得到线性表 L'=(a_1, a_n, a_2, a_{n-1}, ...)

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int data;
  struct Node *next;
} Node;

void Init(Node **head)
{
  *head = (Node *)malloc(sizeof(Node));
  Node *p = *head;
  int insertData[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int length = sizeof(insertData) / sizeof(int);
  for (int i = 0; i < length; i++)
  {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = insertData[i];
    node->next = NULL;
    p->next = node;
    p = p->next;
  }
}

void Rearrange(Node *head)
{
  Node *p = head, *q = head;
  while (q->next)
  {
    p = p->next;
    q = q->next;
    if (q->next)
      q = q->next;
  }
  Node *prev = NULL;
  Node *curr = p->next;
  Node *next = NULL;
  while (curr)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  p->next = prev;
  q = p;
  p = head->next;
  while (p != q)
  {
    prev = p->next;
    next = q->next;
    p->next = next;
    q->next = next->next;
    next->next = prev;
    p = prev;
  }
}

void Print(Node *head)
{
  Node *p = head->next;
  while (p)
  {
    printf("%d ", p->data);
    p = p->next;
  }
  printf("\n");
}

int main()
{
  Node *head;
  Init(&head);
  Print(head);
  Rearrange(head);
  Print(head);
  return 0;
}