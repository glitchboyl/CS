#include <stdio.h>

enum Color
{
  Red = 1,
  Black
};

typedef struct RBTreeNode
{
  int key;
  struct RBTreeNode *lchild;
  struct RBTreeNode *rchild;
  struct RBTreeNode *parent;
  enum Color color;
} RBTreeNode, *RBTree;

void InitRBTree(RBTree tree)
{
}

int main()
{
  RBTree T;
  // InitRBTree(&T);
  // int insertKeys[] = {};
  // int length = sizeof(insertKeys) / sizeof(int);
  // for (int i = 0; i < length; i++)
  // {
  // }
  return 0;
}