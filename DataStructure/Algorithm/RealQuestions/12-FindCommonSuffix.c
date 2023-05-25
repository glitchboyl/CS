// 假定采用带头结点的单链表保存单词，当两个单词有相同的后缀时，则可共享相同的后缀存储空间，例如，“loading"和“being”。
// 设str1和str2分别指向两个单词所在单链表的头结点，请设计一个时间上尽可能高效的算法
// 找出由str1和str2所指向两个链表共同后缀的起始位置

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedNode
{
  char ch;
  struct LinkedNode *next;
} LinkedNode, *LinkedList;

LinkedNode *CreateNode(char ch)
{
  LinkedNode *node = (LinkedNode *)malloc(sizeof(LinkedNode));
  node->ch = ch;
  node->next = NULL;
  return node;
};

void Init(LinkedList *str1, LinkedList *str2)
{
  *str1 = (LinkedNode *)malloc(sizeof(LinkedNode));
  *str2 = (LinkedNode *)malloc(sizeof(LinkedNode));
  LinkedNode *p = *str1, *q = *str2;
  char s1[] = "load", s2[] = "be", suffix[] = "ing";
  int length = strlen(s1);
  for (int i = 0; i < length; i++)
  {
    p->next = CreateNode(s1[i]);
    p = p->next;
  }
  length = strlen(s2);
  for (int i = 0; i < length; i++)
  {
    q->next = CreateNode(s2[i]);
    q = q->next;
  }
  length = strlen(suffix);
  for (int i = 0; i < length; i++)
  {
    p->next = q->next = CreateNode(suffix[i]);
    p = p->next;
    q = q->next;
  }
}

void FindCommonSuffix(LinkedList str1, LinkedList str2)
{
  LinkedNode *p = str1, *q = str2;
  int len1 = 0, len2 = 0, i = 0, j = 0;
  while (p->next)
  {
    p = p->next;
    len1++;
  }
  while (q->next)
  {
    q = q->next;
    len2++;
  }
  p = str1;
  q = str2;
  int d = abs(len1 - len2);
  for (int k = 0; k < d; k++)
  {
    if (len1 > len2)
    {
      p = p->next;
      i++;
    }
    else
    {
      q = q->next;
      j++;
    }
  }
  while (p->next != q->next)
  {
    p = p->next;
    q = q->next;
    i++;
    j++;
  }
  printf("the common suffix is begin at %d in str1 and %d in str2", i, j);
}

int main()
{
  LinkedList str1;
  LinkedList str2;
  Init(&str1, &str2);
  FindCommonSuffix(str1, str2);
  return 0;
}