#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_SIZE 99

typedef int ElemType;
typedef struct
{
	ElemType value;
	bool isEmpty;
} TreeNode;
typedef struct
{
	TreeNode tree[MAX_SIZE];
	int length;
} Tree;

void InitTree(Tree *T)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		T->tree[i].value = -1;
		T->tree[i].isEmpty = true;
	}
	T->length = 0;
}

void Insert(Tree *T, int i, int n)
{
	if (i < 1 || i > MAX_SIZE)
		return;
	int index = i - 1;
	T->tree[index].value = n;
	if (T->tree[index].isEmpty)
		T->length++;
	T->tree[index].isEmpty = false;
}

void InsertChild(Tree *T, int i, int n, int direction)
{
	if (i < 1 || i > MAX_SIZE || T->tree[i / 2 - 1].isEmpty)
		return;

	int childIndex = i * 2 + (direction ? 1 : 0) - 1;
	if (childIndex >= MAX_SIZE)
		return;

	if (T->tree[childIndex].isEmpty)
		T->length++;
	T->tree[childIndex].value = n;
	T->tree[childIndex].isEmpty = false;
}

void PrintTree(Tree T)
{
	if (T.length == 0)
		return;
	int j = 0, deep = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (!T.tree[i].isEmpty)
		{
			printf("%d ", T.tree[i].value);
			j++;
		}
		else
			printf("/ ");

		if (deep != (int)log2(i + 2))
		{
			deep++;
			printf("\n");
		}

		if (j == T.length)
			break;
	}
	printf("\n");
}

int main()
{
	Tree T;
	InitTree(&T);
	Insert(&T, 1, 2);
	PrintTree(T);
	InsertChild(&T, 1, 3, 0);
	InsertChild(&T, 2, 6, 1);
	InsertChild(&T, 5, 9, 1);
	PrintTree(T);
	return 0;
}