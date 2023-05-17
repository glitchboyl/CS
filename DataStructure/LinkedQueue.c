#include <stdio.h>
#include <stdlib.h>

#define InitSize 5

// 定义元素类型为int
typedef int ElemType;

// 定义链式队列结构体
typedef struct LNode
{
    ElemType data;      // 队列中存储的数据
    struct LNode *next; // 指向下一个节点的指针
} LNode;

// 定义带有头结点的队列结构体
typedef struct
{
    LNode *front, *rear; // 队列的头和尾
    int length;          // 队列的长度
} LinkedQueue;

// 初始化队列
void InitQueue(LinkedQueue *queue)
{
    queue->front = queue->rear = (LNode *)malloc(sizeof(LNode)); // 生成头结点
    queue->front->next = NULL;
    queue->length = 0; // 初始化队列长度为0
}

// 入队
void EnQueue(LinkedQueue *queue, ElemType e)
{
    // 生成新的结点并为其赋值
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = NULL;

    // 将新结点插入到队列末尾，修改队列尾指针
    queue->rear->next = s;
    queue->rear = s;

    // 修改队列长度
    queue->length++;
}

// 出队
ElemType DeQueue(LinkedQueue *queue)
{
    // 若队列为空，则返回-1
    if (queue->length == 0)
        return -1;

    // 取出队头元素并删除队头结点
    LNode *p = queue->front->next;
    ElemType e = p->data;
    queue->front->next = p->next;

    // 若队列只有一个元素，则修改队列尾指针
    if (queue->rear == p)
        queue->rear = queue->front;

    // 释放空间并修改队列长度
    free(p);
    queue->length--;

    // 返回出队元素的值
    return e;
}

// 打印队列元素
void PrintQueue(LinkedQueue queue)
{
    LNode *p = queue.front->next;
    while (p != NULL)
    {
        printf("%d ", p->data); // 输出结点存储的数据
        p = p->next;            // 指向下一个结点
    }
    printf("\n");
}

// 销毁队列
void DestroyQueue(LinkedQueue *queue)
{
    LNode *p = queue->front->next, *q;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q); // 释放每个结点所占空间
    }
    queue->front = queue->rear = NULL; // 将队头指针和队尾指针指向NULL
    queue->length = 0;                 // 将队列长度设为0
}

int main()
{
    LinkedQueue Q;
    InitQueue(&Q); // 初始化队列
    EnQueue(&Q, 1);
    EnQueue(&Q, 2);
    EnQueue(&Q, 3);
    PrintQueue(Q);                                   // 打印队列元素
    printf("Linked Queue Length is %d\n", Q.length); // 输出队列长度
    printf("DeQueue %d\n", DeQueue(&Q));             // 出队并输出元素值
    printf("DeQueue %d\n", DeQueue(&Q));             // 出队并输出元素值
    PrintQueue(Q);                                   // 再次打印队列元素
    printf("Linked Queue Length is %d\n", Q.length); // 再次输出队列长度
    printf("DeQueue %d\n", DeQueue(&Q));             // 出队并输出元素值
    PrintQueue(Q);                                   // 再次打印队列元素
    printf("Linked Queue Length is %d\n", Q.length); // 输出队列长度
    printf("DeQueue %d\n", DeQueue(&Q));             // 出队并输出元素值
    DestroyQueue(&Q);                                // 销毁队列
    return 0;
}
