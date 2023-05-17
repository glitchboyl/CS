#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElemType;
// 定义二叉树结点结构体
typedef struct TreeNode
{
	ElemType *value;												 // 值
	struct TreeNode *leftChild, *rightChild; // 左右孩子指针
	int ltag, rtag;
} TreeNode, *Tree;

// 初始化二叉树
void InitTree(Tree *T)
{
	*T = (Tree)malloc(sizeof(TreeNode)); // 分配内存
	(*T)->value = NULL;									 // 值初始为 NULL
	(*T)->leftChild = NULL;							 // 左孩子为 NULL
	(*T)->rightChild = NULL;						 // 右孩子为 NULL
	(*T)->ltag = 0;
	(*T)->rtag = 0;
}

// 查找元素在中序遍历数组中的下标
int indexOf(int val, int *inOrder, int length)
{
	// 遍历中序遍历数组，查找元素下标
	for (int i = 0; i < length; i++)
	{
		if (inOrder[i] == val)
			return i;
	}
	return -1;
}

// 通过先序遍历和中序遍历构造二叉树的辅助函数
void PreOrderConstructHelper(Tree T, ElemType *preOrder, ElemType *inOrder, int length)
{
	if (length < 1)
		return;

	T->value = (ElemType *)malloc(sizeof(ElemType)); // 分配内存
	*(T->value) = preOrder[0];											 // 根结点的值为先序遍历数组的第一个元素

	int rootIndex = indexOf(*(T->value), inOrder, length); // 查找根结点在中序遍历数组中的下标
	int leftLength = rootIndex;														 // 左子树的长度
	int rightLength = length - leftLength - 1;						 // 右子树的长度

	if (leftLength > 0)
	{
		InitTree(&(T->leftChild));																								// 初始化左孩子结点
		PreOrderConstructHelper(T->leftChild, preOrder + 1, inOrder, leftLength); // 递归处理左子树
	}

	if (rightLength > 0)
	{
		InitTree(&(T->rightChild));																																								// 初始化右孩子结点
		PreOrderConstructHelper(T->rightChild, preOrder + leftLength + 1, inOrder + leftLength + 1, rightLength); // 递归处理右子树
	}
}

// 通过先序遍历和中序遍历构造二叉树
Tree ConstructTreeByPreOrder(ElemType *preOrder, ElemType *inOrder, int length)
{
	if (length <= 0)
		return NULL;

	Tree T;
	InitTree(&T); // 初始化二叉树

	PreOrderConstructHelper(T, preOrder, inOrder, length); // 构造二叉树

	return T;
}

// 通过后序遍历和中序遍历构造二叉树的辅助函数
void PostOrderConstructHelper(Tree T, ElemType *postOrder, ElemType *inOrder, int length)
{
	if (length < 1)
		return;

	T->value = (ElemType *)malloc(sizeof(ElemType)); // 分配内存
	*(T->value) = postOrder[length - 1];						 // 根结点的值为后序遍历数组的最后一个元素

	int rootIndex = indexOf(*(T->value), inOrder, length); // 查找根结点在中序遍历数组中的下标
	int leftLength = rootIndex;														 // 左子树的长度
	int rightLength = length - leftLength - 1;						 // 右子树的长度

	if (leftLength > 0)
	{
		InitTree(&(T->leftChild));																							// 初始化左孩子结点
		PostOrderConstructHelper(T->leftChild, postOrder, inOrder, leftLength); // 递归处理左子树
	}

	if (rightLength > 0)
	{
		InitTree(&(T->rightChild));																																							// 初始化右孩子结点
		PostOrderConstructHelper(T->rightChild, postOrder + leftLength, inOrder + leftLength + 1, rightLength); // 递归处理右子树
	}
}

// 通过后序遍历和中序遍历构造二叉树
Tree ConstructTreeByPostOrder(ElemType *postOrder, ElemType *inOrder, int length)
{
	if (length <= 0)
		return NULL;

	Tree T;
	InitTree(&T); // 初始化二叉树

	PostOrderConstructHelper(T, postOrder, inOrder, length); // 构造二叉树

	return T;
}

// 通过层序遍历和中序遍历构造二叉树的辅助函数
void LevelOrderConstructHelper(Tree T, ElemType *levelOrder, ElemType *inOrder, int length)
{
	if (length < 1)
		return;

	T->value = (ElemType *)malloc(sizeof(ElemType)); // 分配内存
	*(T->value) = levelOrder[0];										 // 根结点的值为层序遍历数组的第一个元素

	int rootIndex = indexOf(*(T->value), inOrder, length);													// 查找根结点在中序遍历数组中的下标
	int leftLength = rootIndex;																											// 左子树的长度
	int rightLength = length - leftLength - 1;																			// 右子树的长度
	ElemType *leftLevelOrder = (ElemType *)malloc(sizeof(ElemType) * leftLength);		// 分配内存，左子树的层序遍历数组
	ElemType *rightLevelOrder = (ElemType *)malloc(sizeof(ElemType) * rightLength); // 分配内存，右子树的层序遍历数组
	for (int i = 1, j = 0, k = 0; i < length; i++)
	{
		if (indexOf(levelOrder[i], inOrder, leftLength) != -1)
			leftLevelOrder[j++] = levelOrder[i]; // 将属于左子树的元素放入左子树的层序遍历数组中
		else
			rightLevelOrder[k++] = levelOrder[i]; // 将属于右子树的元素放入右子树的层序遍历数组中
	}

	if (leftLength > 0)
	{
		InitTree(&(T->leftChild));																										// 初始化左孩子结点
		LevelOrderConstructHelper(T->leftChild, leftLevelOrder, inOrder, leftLength); // 递归处理左子树
	}

	if (rightLength > 0)
	{
		InitTree(&(T->rightChild));																																				// 初始化右孩子结点
		LevelOrderConstructHelper(T->rightChild, rightLevelOrder, inOrder + leftLength + 1, rightLength); // 递归处理右子树
	}
	// 释放内存
	free(leftLevelOrder);
	free(rightLevelOrder);
}

// 通过层序遍历和中序遍历构造二叉树
Tree ConstructTreeByLevelOrder(ElemType *levelOrder, ElemType *inOrder, int length)
{
	if (length <= 0)
		return NULL;

	Tree T;
	InitTree(&T); // 初始化二叉树

	LevelOrderConstructHelper(T, levelOrder, inOrder, length); // 构造二叉树

	return T;
}

void InOrderThreading(Tree T, TreeNode **pre, TreeNode **threadHead)
{
	if (!T)
		return;
	InOrderThreading(T->leftChild, pre, threadHead);
	if (!T->leftChild)
	{
		T->ltag = 1;
		T->leftChild = *pre;
		if (!*threadHead)
		{
			*threadHead = T;
		}
	}
	if (*pre != NULL && !(*pre)->rightChild)
	{
		(*pre)->rtag = 1;
		(*pre)->rightChild = T;
	}
	*pre = T;
	InOrderThreading(T->rightChild, pre, threadHead);
	if (T->rightChild == NULL)
	{
		T->rtag = 1;
		T->rightChild = NULL;
	}
}

// 打印二叉树结点值的辅助函数
void PrintTreeNode(TreeNode *T, int orderBy)
{
	if (T->value == NULL) // 结点值为 NULL，输出 null
	{
		printf("null ");
		return;
	}

	if (!orderBy)
		printf("%d ", *(T->value)); // 输出结点值

	if (T->leftChild != NULL)
		PrintTreeNode(T->leftChild, orderBy); // 递归打印左子树

	if (orderBy == 1)
		printf("%d ", *(T->value)); // 输出结点值

	if (T->rightChild != NULL)
		PrintTreeNode(T->rightChild, orderBy); // 递归打印右子树

	if (orderBy == 2)
		printf("%d ", *(T->value)); // 输出结点值
}

// 打印整棵二叉树
void PrintTree(Tree T, int orderBy)
{
	PrintTreeNode(T, orderBy);
	printf("\n");
}

void LinearPrintTree(Tree T)
{
	TreeNode *p = T;
	while (p)
	{
		printf("%d ", *(p->value));
		p = p->rightChild;
	}
	printf("\n");
}

int main()
{
	ElemType preOrder[] = {1, 2, 3, 4, 5, 6};						 // 先序遍历数组
	ElemType inOrder[] = {3, 2, 4, 1, 5, 6};						 // 中序遍历数组
	ElemType postOrder[] = {3, 4, 2, 6, 5, 1};					 // 后序遍历数组
	ElemType levelOrder[] = {1, 2, 5, 3, 4, 6};					 // 层序遍历数组
	int length = sizeof(preOrder) / sizeof(preOrder[0]); // 数组长度

	Tree PreOrderTree = ConstructTreeByPreOrder(preOrder, inOrder, length); // 通过先序遍历和中序遍历构造二叉树
	PrintTree(PreOrderTree, 0);																							// 打印二叉树

	Tree PostOrderTree = ConstructTreeByPostOrder(postOrder, inOrder, length); // 通过后序遍历和中序遍历构造二叉树
	PrintTree(PostOrderTree, 0);																							 // 打印二叉树

	Tree LevelOrderTree = ConstructTreeByLevelOrder(levelOrder, inOrder, length); // 通过层序遍历和中序遍历构造二叉树
	PrintTree(LevelOrderTree, 0);																									// 打印二叉树

	TreeNode *pre = NULL, *threadHead = NULL;
	InOrderThreading(PreOrderTree, &pre, &threadHead);
	LinearPrintTree(threadHead);

	pre = NULL, threadHead = NULL;
	InOrderThreading(PostOrderTree, &pre, &threadHead);
	LinearPrintTree(threadHead);

	pre = NULL, threadHead = NULL;
	InOrderThreading(LevelOrderTree, &pre, &threadHead);
	LinearPrintTree(threadHead);

	return 0;
}
