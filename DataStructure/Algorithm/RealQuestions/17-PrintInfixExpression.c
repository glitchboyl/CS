// 请设计一个算法，将给定的表达式树（二叉树）转换为等价的中缀表达式（通过括号反应操作符的计算次序）并输出。
// 例如，(a+b)*(c*(-d)) 和 (a*b) + (-(c-d))

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
  char data[10];
  struct node *left, *right;
} BTree;

void Insert(BTree *tree, char data, int direction)
{
  BTree *node = (BTree *)malloc(sizeof(BTree));
  node->data[0] = data;
  node->left = NULL;
  node->right = NULL;
  if (direction)
    tree->right = node;
  else
    tree->left = node;
}

void Init(BTree **A, BTree **B)
{
  *A = (BTree *)malloc(sizeof(BTree));
  (*A)->data[0] = '*';
  Insert(*A, '+', 0);
  Insert((*A)->left, 'a', 0);
  Insert((*A)->left, 'b', 1);
  Insert(*A, '*', 1);
  Insert((*A)->right, 'c', 0);
  Insert((*A)->right, '-', 1);
  Insert((*A)->right->right, 'd', 1);
  *B = (BTree *)malloc(sizeof(BTree));
  (*B)->data[0] = '+';
  Insert(*B, '*', 0);
  Insert((*B)->left, 'a', 0);
  Insert((*B)->left, 'b', 1);
  Insert(*B, '-', 1);
  Insert((*B)->right, '-', 1);
  Insert((*B)->right->right, 'c', 0);
  Insert((*B)->right->right, 'd', 1);
}

void InOrderThreading(BTree *node, int deep)
{
  if (node)
  {
    bool brackets = deep && (node->left || node->right);
    if (brackets)
      printf("(");
    InOrderThreading(node->left, deep + 1);
    printf("%c", node->data[0]);
    InOrderThreading(node->right, deep + 1);
    if (brackets)
      printf(")");
  }
}

void PrintInfixExpression(BTree *tree)
{
  InOrderThreading(tree, 0);
  printf("\n");
}

int main()
{
  BTree *A, *B;
  Init(&A, &B);
  PrintInfixExpression(A);
  PrintInfixExpression(B);
  return 0;
}