// 二叉树的带权路径长度(WPL)是二叉树中所有叶结点的带权路径长度之和。
// 给定一棵二叉树T，采用二叉链表存储，结点结构如:[left|weight|right]
// 其中叶结点的weight域保存该结点的非负权值。设root为指向T的根结点的指针，请设计求T的WPL的算法

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
  int weight;
  struct TreeNode *left, *right;
} TreeNode, *Tree;

void Insert(TreeNode *node, int weight, int direction)
{
  TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
  p->weight = weight;
  p->left = NULL;
  p->right = NULL;
  if (direction)
    node->right = p;
  else
    node->left = p;
}

int PreOrderThreading(TreeNode *node, int deep)
{
  if (!node->left && !node->right)
    return node->weight * deep;
  int weight = 0;
  if (node->left)
    weight += PreOrderThreading(node->left, deep + 1);
  if (node->right)
    weight += PreOrderThreading(node->right, deep + 1);
  return weight;
}

int GetWPL(Tree T)
{
  int WPL = 0;
  if (T->left)
    WPL += PreOrderThreading(T->left, 1);
  if (T->right)
    WPL += PreOrderThreading(T->right, 1);
  return WPL;
}

int main()
{
  Tree root = (Tree)malloc(sizeof(TreeNode));
  Insert(root, 6, 0);
  Insert(root, 8, 1);
  Insert(root->left, 7, 0);
  Insert(root->left, 2, 1);
  printf("the WPL is %d", GetWPL(root));
  return 0;
}