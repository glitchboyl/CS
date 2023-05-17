#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 3          // 定义B树的最大度数为5
#define MAX_HEIGHT 5 // 定义B树的最大高度为5

// 定义B树结点结构体
typedef struct BTreeNode
{
  int keywords[M];                   // 结点中存储的关键字数组
  struct BTreeNode *branches[M + 1]; // 分支指针数组
  int keywordLength, branchLength;   // 关键字个数和子结点个数
  bool isLeaf;                       // 是否为叶子结点
} BTreeNode, *BTree;

// 初始化B树
void InitBTree(BTree *t)
{
  *t = (BTree)malloc(sizeof(BTreeNode)); // 分配内存
  for (int i = 0; i < M; i++)            // 初始化子结点指针数组
  {
    (*t)->branches[i] = NULL;
  }
  (*t)->keywordLength = 0; // 初始化关键字个数为0
  (*t)->branchLength = 0;  // 初始化子结点个数为0
  (*t)->isLeaf = true;     // 初始化为叶子结点
}

// 将关键字插入到结点中
int RawInsertKeyword(BTreeNode *node, int keyword)
{
  int i = 0;
  for (; i < node->keywordLength; i++)
  {
    if (keyword < node->keywords[i])
      break;
  }
  for (int j = node->keywordLength; j > i; j--)
  {
    node->keywords[j] = node->keywords[j - 1];
  }
  node->keywords[i] = keyword; // 插入关键字
  node->keywordLength++;       // 关键字个数加1
  return i;                    // 返回插入位置
}

// 将一个B树结点分裂为两个
void SplitBTreeNode(BTreeNode *node)
{
  // 初始化左子树和右子树
  BTree LBT;
  BTree RBT;
  InitBTree(&LBT);
  InitBTree(&RBT);

  // 将原结点的关键字一分为二，前半部分放到左子树中，后半部分放到右子树中
  int mid = node->keywordLength / 2;
  int i = 0;
  for (; i < mid; i++)
  {
    RawInsertKeyword(LBT, node->keywords[i]);
  }
  for (i = mid + 1; i < node->keywordLength; i++)
  {
    RawInsertKeyword(RBT, node->keywords[i]);
  }
  node->keywords[0] = node->keywords[mid]; // 将中间关键字上移一层
  node->keywordLength = 1;

  // 将原结点的分支数组也一分为二，并将左子树的分支指针和右子树的分支指针分别指向这些分支
  mid = node->branchLength / 2;
  int j = 0;
  for (; j < mid; j++)
  {
    LBT->branches[j] = node->branches[j];
    LBT->branchLength++;
    node->branches[j] = NULL;
  }
  for (; j < node->branchLength; j++)
  {
    RBT->branches[j - mid] = node->branches[j];
    RBT->branchLength++;
    node->branches[j] = NULL;
  }

  // 如果原结点有分支，则左子树和右子树也都是非叶子结点
  if (node->branchLength > 0)
  {
    LBT->isLeaf = false;
    RBT->isLeaf = false;
  }

  // 将原结点的第一个分支指针指向左子树，第二个分支指针指向右子树
  node->branches[0] = LBT;
  node->branches[1] = RBT;
  node->branchLength = 2;

  // 如果原结点是叶子结点，则分裂后左子树和右子树也都是叶子结点
  if (node->isLeaf)
    node->isLeaf = false;
}

// 向B树中插入一个关键字
void InsertKeyword(BTree *bt, int keyword)
{
  BTreeNode *p = *bt;
  if (p->isLeaf) // 如果当前结点是叶子结点，则直接将关键字插入到该结点中
  {
    RawInsertKeyword(p, keyword);
    if (p->keywordLength > M - 1) // 如果该结点的关键字个数超过了M-1，则需要进行分裂
    {
      SplitBTreeNode(p);
    }
  }
  else // 如果当前结点不是叶子结点，则需要递归地向下查找应该插入到哪个子树中
  {
    int i;
    for (i = 0; i < p->keywordLength; i++) // 找到第一个大于待插入关键字的关键字位置
    {
      if (keyword < p->keywords[i])
        break;
    }
    BTreeNode *b = p->branches[i]; // 跳到对应的子树
    InsertKeyword(&b, keyword);    // 递归插入关键字

    // 如果子结点分裂后，导致当前结点的某个子结点关键字个数为1且子结点有两个子树指针，则需要将此子结点合并到其他子结点中
    if (b->keywordLength == 1 && b->branchLength == 2)
    {
      int insertIndex = RawInsertKeyword(p, b->keywords[0]);  // 将子结点中的关键字插入到当前结点中
      for (int j = p->branchLength; j > insertIndex + 1; j--) // 将子树指针也插入到当前结点中
      {
        p->branches[j] = p->branches[j - 1];
      }
      p->branchLength++;
      p->branches[insertIndex] = b->branches[0];
      p->branches[insertIndex + 1] = b->branches[1];
      free(b);                      // 释放原来的子结点内存
      if (p->keywordLength > M - 1) // 如果当前结点的关键字个数超过了M-1，则需要进行分裂
      {
        SplitBTreeNode(p);
      }
    }
  }
}

// 从兄弟结点中偷一个关键字到当前结点中
void StealingKeyword(BTreeNode *bt, BTreeNode *parentNode, int index)
{
  if (parentNode) // 如果有父结点，则进行关键字的“偷取”
  {
    bool way = index == parentNode->branchLength - 1;                       // 确定被“偷取”的分支是在父结点的左边还是右边
    BTreeNode *sibling = parentNode->branches[way ? index - 1 : index + 1]; // 找到被“偷取”的兄弟分支
    if (sibling->keywordLength - 1 >= M / 2)                                // 如果兄弟分支的关键字数量仍然足够，则进行关键字的“偷取”
    {
      bt->keywords[1] = parentNode->keywords[index];      // 将父结点的关键字插入到当前分支中
      parentNode->keywords[index] = sibling->keywords[0]; // 将兄弟分支的最小关键字插入到父结点中
      bt->keywordLength++;                                // 当前分支的关键字数量加1
      sibling->keywordLength--;                           // 兄弟分支的关键字数量减1
      for (int i = 0; i < sibling->keywordLength; i++)    // 将兄弟分支中的剩余关键字往前移动一位
      {
        sibling->keywords[i] = sibling->keywords[i + 1];
      }
    }
    else // 如果兄弟分支的关键字数量不足，则进行合并
    {
      if (index == 0)
        sibling = parentNode->branches[index + 1];
      else if (!way)
        sibling = parentNode->branches[index - 1];

      if (index == 0) // 如果当前分支在父结点的最左边，则将当前分支合并到右侧的兄弟分支中
      {
        bt->keywords[bt->keywordLength] = parentNode->keywords[index]; // 将父结点中的关键字插入到当前分支的最后
        bt->keywordLength++;                                           // 当前分支的关键字数量加1
        int i = 0;
        for (; i < sibling->keywordLength; i++) // 将兄弟分支中的关键字插入到当前分支中
        {
          bt->keywords[bt->keywordLength] = sibling->keywords[i];
          bt->keywordLength++;
        }
        for (i = 0; i < sibling->branchLength; i++) // 将兄弟分支中的子结点插入到当前分支中
        {
          bt->branches[bt->branchLength] = sibling->branches[i];
          bt->branchLength++;
        }
        parentNode->keywordLength--;                    // 父结点的关键字数量减1
        parentNode->branchLength--;                     // 父结点的分支数量减1
        free(sibling);                                  // 释放兄弟分支占用的内存
        for (i = 0; i < parentNode->keywordLength; i++) // 将父结点中的关键字和分支向前移动一位
        {
          parentNode->keywords[i] = parentNode->keywords[i + 1];
          parentNode->branches[i + 1] = parentNode->branches[i + 2];
        }
      }
      else // 如果当前分支不在父结点的最左边，则将当前分支合并到左侧的兄弟分支中
      {
        sibling->keywords[sibling->keywordLength] = parentNode->keywords[index - 1]; // 将父结点中的关键字插入到兄弟分支的最后
        sibling->keywordLength++;                                                    // 兄弟分支的关键字数量加1
        int i;
        for (i = 0; i < bt->keywordLength; i++) // 将当前分支中的关键字插入到兄弟分支中
        {
          sibling->keywords[sibling->keywordLength] = bt->keywords[i];
          sibling->keywordLength++;
        }
        for (i = 0; i < bt->branchLength; i++) // 将当前分支中的子结点插入到兄弟分支中
        {
          sibling->branches[sibling->branchLength] = bt->branches[i];
          sibling->branchLength++;
        }
        parentNode->keywordLength--;                            // 父结点的关键字数量减1
        parentNode->branchLength--;                             // 父结点的分支数量减1
        free(parentNode->branches[index]);                      // 释放当前分支占用的内存
        for (i = index - 1; i < parentNode->keywordLength; i++) // 将父结点中的关键字和分支向前移动一位
        {
          parentNode->keywords[i] = parentNode->keywords[i + 1];
          parentNode->branches[i + 1] = parentNode->branches[i + 2];
        }
      }
    }
  }
  else if (bt->keywordLength == 0 && bt->branchLength == 1) // 如果下移的父结点是根结点，且导致根结点关键字长度为0，则将唯一的分支结点作为新的根节点
  {
    int i = 0;
    BTreeNode *b = bt->branches[0];
    for (; i < b->keywordLength; i++) // 将子结点中的关键字插入到当前结点中
    {
      bt->keywords[i] = b->keywords[i];
      bt->keywordLength++;
    }
    bt->branchLength--;                   // 当前结点的子结点数量减1
    for (i = 0; i < b->branchLength; i++) // 将子结点中的子结点插入到当前结点中
    {
      bt->branches[i] = b->branches[i];
      bt->branchLength++;
    }
    free(b); // 释放子结点占用的内存
  }
}

// 从B树中删除一个关键字
void DeleteKeyword(BTree *bt, int keyword)
{
  BTreeNode *p = *bt;
  BTreeNode *routes[MAX_HEIGHT + 1]; // 用于记录走过的结点路径，方便结点找到它的父结点
  routes[0] = NULL;                  // 第一位设为空，因为根结点没有父结点
  int i, j = 1, index;

  // 在B树中查找要删除的关键字，并记录查找路径
  for (i = 0; i < p->keywordLength; i++)
  {
    if (p->keywords[i] == keyword) // 如果找到了要删除的关键字，则直接跳出循环
      break;
    else if (p->branchLength > 0) // 如果当前结点不是叶子结点，则需要向下递归查找
    {
      if (p->keywords[i] > keyword) // 如果当前关键字大于要删除的关键字，则需要向左子树继续查找
      {
        routes[j++] = p;
        index = i;
        p = p->branches[index];
        i = -1; // 因为后面还要执行i++，所以这里先将i设为-1，以便下一轮循环开始时i正确地变为0
      }
      else if (i + 1 == p->keywordLength) // 如果当前关键字是该结点中最后一个关键字，则需要向右子树继续查找
      {
        routes[j++] = p;
        index = i + 1;
        p = p->branches[index];
        i = -1; // 同上
      }
    }
  }
  routes[j] = p;

  // 如果没有找到要删除的关键字，则直接返回
  if (i == p->keywordLength)
    return;

  if (p->isLeaf) // 如果要删除的关键字在叶子结点中，则直接删除即可
  {
    p->keywordLength--;
    for (int j = i; j < p->keywordLength; j++)
    {
      p->keywords[j] = p->keywords[j + 1];
    }

    // 现在需要检查是否需要进行合并或借用操作，以保证B树的平衡性
    while (j > 0 && p->keywordLength < M / 2)
    {
      StealingKeyword(p, routes[j - 1], index); // 首先尝试从兄弟结点中偷取一个关键字
      p = routes[--j];
      int k = 0;
      if (j > 1)
      {
        for (; k < routes[j - 1]->branchLength; k++)
        {
          if (p == routes[j - 1]->branches[k])
            break;
        }
        if (k == routes[j - 1]->branchLength)
          break;
      }
      index = k;
    }
  }
  else // 如果要删除的关键字在非叶子结点中，则需要找到它的后继关键字来替换它
  {
    index = i;
    routes[++j] = p->branches[index];
    BTreeNode *b = routes[j];

    // 找到后继关键字所在的叶子结点，并记录查找路径
    while (!b->isLeaf)
    {
      index = b->branchLength - 1;
      b = routes[++j] = b->branches[index];
    }

    // 将后继关键字替换为要删除的关键字
    int substitution = b->keywords[b->keywordLength - 1];
    p->keywords[i] = substitution;
    b->keywordLength--;

    // 现在需要检查是否需要进行合并或借用操作，以保证B树的平衡性
    if (b->keywordLength < M / 2)
    {
      StealingKeyword(b, routes[j - 1], index);
    }
  }
}

// 打印一个B树结点
void PrintBTreeNode(BTreeNode node)
{
  printf("[");
  for (int i = 0; i < node.keywordLength; i++)
  {
    printf("%d", node.keywords[i]);
    if (i < node.keywordLength - 1)
      printf(",");
  }
  printf("]");

  // 如果当前结点不是叶子结点，则需要递归打印它的所有子结点
  if (!node.isLeaf)
  {
    printf("(");
    for (int i = 0; i <= node.keywordLength; i++)
    {
      PrintBTreeNode(*(node.branches[i]));
      if (i < node.keywordLength)
        printf(",");
    }
    printf(")");
  }
}

// 打印整个B树
void PrintBTree(BTree bt)
{
  PrintBTreeNode(*bt);
  printf("\n");
}

int main()
{
  BTree BT;
  InitBTree(&BT);

  // 往B树中插入一些关键字
  // int insertKeywords[] = {60, 25, 38, 49, 80, 90, 99, 88, 83, 87, 70, 92, 93, 94, 73, 74, 75, 71, 72, 76, 77, 82, 86, 52, 51, 78};
  int insertKeywords[] = {60, 25, 38, 49, 80, 66, 71};
  int insertLength = sizeof(insertKeywords) / sizeof(int);
  for (int i = 0; i < insertLength; i++)
  {
    InsertKeyword(&BT, insertKeywords[i]);
  }

  // 打印插入完关键字后的B树
  PrintBTree(BT);

  // 从B树中删除一些关键字，并打印每次删除后的B树
  // int deleteKeywords[] = {49, 73, 80, 99, 51, 38, 78, 52, 75, 76, 74};
  int deleteKeywords[] = {49, 80, 60};
  int deleteLength = sizeof(deleteKeywords) / sizeof(int);
  for (int j = 0; j < deleteLength; j++)
  {
    DeleteKeyword(&BT, deleteKeywords[j]);
    PrintBTree(BT);
  }

  return 0;
}