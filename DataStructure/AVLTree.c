#include <stdio.h>
#include <stdlib.h>

#define MAX_HEIGHT 5 // AVL树的最大高度

typedef struct AVLTreeNode // AVL树结点结构体
{
  int key;                             // 结点键值
  int height;                          // 结点高度
  struct AVLTreeNode *lchild, *rchild; // 左右子树指针
} AVLTreeNode, *AVLTree;               // AVLTree是AVL树的指针类型，指向根结点

// 获取结点高度
int GetHeight(AVLTreeNode *node)
{
  return node != NULL ? node->height : 0;
}

// 获取结点平衡因子（左右子树高度差）
int GetBalance(AVLTreeNode *node)
{
  return GetHeight(node->lchild) - GetHeight(node->rchild);
}

// 返回a和b中较大的值
int Max(int a, int b)
{
  return a > b ? a : b;
}

// 更新结点高度
void UpdateHeight(AVLTreeNode *node)
{
  node->height = Max(GetHeight(node->lchild), GetHeight(node->rchild)) + 1;
}

// 创建结点
AVLTreeNode *CreateNode(int key)
{
  AVLTreeNode *node = (AVLTreeNode *)malloc(sizeof(AVLTreeNode));
  node->key = key;
  node->height = 1;
  node->lchild = node->rchild = NULL;
  return node;
}

// 插入结点
AVLTreeNode *Insert(AVLTree *tree, int key)
{
  if (!(*tree)) // 如果树为空
  {
    *tree = CreateNode(key); // 创建新结点并作为树的根结点
    return *tree;
  }
  if (key < (*tree)->key) // 如果插入值小于当前结点键值
  {
    (*tree)->lchild = Insert(&((*tree)->lchild), key); // 将其插入左子树
  }
  else // 否则将其插入右子树
  {
    (*tree)->rchild = Insert(&((*tree)->rchild), key);
  }
  int balance = GetBalance(*tree); // 获取当前结点平衡因子
  if (abs(balance) > 1)            // 如果平衡因子超过1，则需要旋转平衡
  {
    AVLTreeNode *q;
    if (balance > 0) // 如果左子树高度大于右子树高度
    {
      int lb = GetBalance((*tree)->lchild); // 获取左子树的平衡因子
      // LL型（左子树的左子树上插入元素）
      if (lb > 0)
      {
        q = (*tree)->lchild;
        (*tree)->lchild = q->rchild;
        q->rchild = (*tree);
      }
      // LR型（左子树的右子树上插入元素）
      else
      {
        q = (*tree)->lchild->rchild;
        (*tree)->lchild->rchild = q->lchild;
        q->lchild = (*tree)->lchild;
        UpdateHeight(q->lchild);
        (*tree)->lchild = q->rchild;
        q->rchild = (*tree);
        UpdateHeight(*tree);
        *tree = q;
      }
    }
    else // 如果右子树高度大于等于左子树高度
    {
      int rb = GetBalance((*tree)->rchild); // 获取右子树的平衡因子
      // RL型（右子树的左子树上插入元素）
      if (rb > 0)
      {
        q = (*tree)->rchild->lchild;
        (*tree)->rchild->lchild = q->rchild;
        q->rchild = (*tree)->rchild;
        UpdateHeight(q->rchild);
        (*tree)->rchild = q->lchild;
        q->lchild = (*tree);
        UpdateHeight(*tree);
        *tree = q;
      }
      // RR型（右子树的右子树上插入元素）
      else
      {
        q = (*tree)->rchild;
        (*tree)->rchild = q->lchild;
        q->lchild = (*tree);
      }
    }
    UpdateHeight(*tree); // 更新当前结点高度
    return q;
  }
  UpdateHeight(*tree); // 更新当前结点高度
  return *tree;
}

// AVL树的删除操作
void Delete(AVLTree *tree, int n)
{
  AVLTreeNode *p = *tree;
  if (!p)
    return;

  // 用数组存储路径上的所有结点
  AVLTreeNode *routes[MAX_HEIGHT + 1];
  int h = 0;

  // 二叉搜索树的查找过程
  while (p)
  {
    if (n == p->key)
      break;
    else
    {
      routes[h++] = p;
      p = n < p->key ? p->lchild : p->rchild;
    }
  }
  if (!p)
    return;
  routes[h] = p;

  // 被删除结点只有一个子结点或没有子结点
  if (p->height == 1)
  {
    if (h > 0)
    {
      if (p == routes[h - 1]->lchild)
      {
        routes[h - 1]->lchild = NULL;
      }
      else
      {
        routes[h - 1]->rchild = NULL;
      }
      free(p);
    }
    else
    {
      free(tree);
      *tree = NULL;
      return;
    }
  }
  // 被删除结点有两个子结点
  else
  {
    int balance = GetBalance(p);
    AVLTreeNode *q;
    if (balance < 0) // 右子树高度更大
    {
      q = p->rchild;
      while (q->lchild)
      {
        routes[++h] = q;
        q = q->lchild;
      }
      // 用前驱结点代替被删除结点
      p->key = q->key;
      if (q == p->rchild)
        p->rchild = q->rchild;
      else
        routes[h]->lchild = NULL;
    }
    else // 左子树高度更大或相等
    {
      q = p->lchild;
      while (q->rchild)
      {
        routes[++h] = q;
        q = q->rchild;
      }
      // 用后继结点代替被删除结点
      p->key = q->key;
      if (q == p->lchild)
        p->lchild = q->lchild;
      else
        routes[h]->rchild = NULL;
    }
    free(q);
  }

  // 自底向上更新结点的高度并恢复平衡
  for (int i = h; i >= 0; i--)
  {
    UpdateHeight(routes[i]);
    int balance = GetBalance(routes[i]);
    if (abs(balance) > 1) // 结点不平衡，需要旋转操作
    {
      AVLTreeNode *p;
      if (balance > 0) // 左子树高度更大
      {
        p = routes[i]->lchild;
        routes[i]->lchild = p->rchild;
        p->rchild = routes[i];
      }
      else // 右子树高度更大
      {
        p = routes[i]->rchild;
        routes[i]->rchild = p->lchild;
        p->lchild = routes[i];
      }
      UpdateHeight(routes[i]);
      UpdateHeight(p);
      if (routes[i] == *tree) // 更新根结点
      {
        *tree = p;
      }
    }
  }
}

// 输出单个结点及其子树
void PrintAVLTreeNode(AVLTreeNode *node)
{
  if (node)
  {
    printf("[%d|%d]", node->key, node->height);
    if (node->lchild || node->rchild)
    {
      printf("(");
      if (node->lchild)
      {
        PrintAVLTreeNode(node->lchild);
        if (node->rchild)
          printf(",");
      }
      if (node->rchild)
        PrintAVLTreeNode(node->rchild);
      printf(")");
    }
  }
}

// 输出整个AVL树
void PrintAVLTree(AVLTree tree)
{
  PrintAVLTreeNode(tree);
  printf("\n");
}

int main()
{
  AVLTree T = NULL;
  int insertKeys[] = {50, 26, 66, 21, 30, 60, 70, 68};
  int insertLength = sizeof(insertKeys) / sizeof(int);

  // 插入结点并输出AVL树
  for (int i = 0; i < insertLength; i++)
  {
    Insert(&T, insertKeys[i]);
  }
  PrintAVLTree(T);

  // 插入新结点并输出AVL树
  Insert(&T, 67);
  PrintAVLTree(T);
  Insert(&T, 90);
  PrintAVLTree(T);
  Insert(&T, 63);
  PrintAVLTree(T);
  Insert(&T, 57);
  PrintAVLTree(T);
  Insert(&T, 22);
  PrintAVLTree(T);
  Insert(&T, 23);
  PrintAVLTree(T);
  Insert(&T, 24);
  PrintAVLTree(T);

  int deleteKeys[] = {50, 24, 21, 68, 90, 67};
  int deleteLength = sizeof(deleteKeys) / sizeof(int);

  // 删除结点并输出AVL树
  for (int i = 0; i < deleteLength; i++)
  {
    Delete(&T, deleteKeys[i]);
    PrintAVLTree(T);
  }
  return 0;
}