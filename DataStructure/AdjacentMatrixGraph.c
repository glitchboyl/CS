#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 10
typedef struct
{
    char Vex[MAX_VERTEX_NUM];
    bool Edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexNum, edgeNum;
} MGraph;

bool visited[MAX_VERTEX_NUM];

void InitGraph(MGraph *graph)
{
    graph->vexNum = 0;
    graph->edgeNum = 0;
}

void InsertVertex(MGraph *graph, char x)
{
    if (graph->vexNum == MAX_VERTEX_NUM)
        return;
    int i;
    for (i = 0; i < MAX_VERTEX_NUM; i++)
    {
        if (!graph->Vex[i])
            break;
    }
    graph->Vex[i] = x; // 将该空间的地址存入Vex数组中
    graph->vexNum++;
    // todo: 会有为空的情况
    for (int j = 0; j < graph->vexNum; j++)
    {
        graph->Edge[j][i] = false;
        graph->Edge[i][j] = false;
    }
}

void DeleteVertex(MGraph *graph, char x)
{
    if (graph->vexNum == 0)
        return;
    int xIndex = -1;
    for (int i = 0; i < graph->vexNum; i++)
    {
        if (graph->Vex[i] == x)
        {
            xIndex = i;
            break;
        }
    }
    if (xIndex == -1)
        return;
    for (int j = 0; j < graph->vexNum; j++)
    {
        if (graph->Edge[xIndex][j])
        {
            graph->Edge[xIndex][j] = false;
            graph->Edge[j][xIndex] = false;
            graph->edgeNum--;
        }
    }
    graph->Vex[xIndex] = '\0';
    graph->vexNum--;
}

void AddEdge(MGraph *graph, char x, char y)
{
    if (graph->vexNum < 2 || x == y)
        return;
    int xIndex = -1, yIndex = -1;
    for (int i = 0; i < graph->vexNum; i++)
    {
        if (graph->Vex[i] == x)
            xIndex = i;
        else if (graph->Vex[i] == y)
            yIndex = i;
        if (xIndex != -1 && yIndex != -1)
            break;
    }
    if (xIndex == -1 || yIndex == -1)
        return;
    if (!graph->Edge[xIndex][yIndex])
    {
        graph->Edge[xIndex][yIndex] = true;
        graph->Edge[yIndex][xIndex] = true;
        graph->edgeNum++;
    }
}

void RemoveEdge(MGraph *graph, char x, char y)
{
    if (graph->vexNum < 2 || graph->edgeNum < 1 || x == y)
        return;
    int xIndex = -1, yIndex = -1;
    for (int i = 0; i < graph->vexNum; i++)
    {
        if (graph->Vex[i] == x)
            xIndex = i;
        else if (graph->Vex[i] == y)
            yIndex = i;
        if (xIndex != -1 && yIndex != -1)
            break;
    }
    if (xIndex == -1 || yIndex == -1)
        return;
    if (graph->Edge[xIndex][yIndex])
    {
        graph->Edge[xIndex][yIndex] = false;
        graph->Edge[yIndex][xIndex] = false;
        graph->edgeNum--;
    }
}

// 判断两个顶点之间是否存在边
bool Adjacent(MGraph *graph, char x, char y)
{
    if (graph->vexNum < 2 || graph->edgeNum < 1)
        return false;
    int xIndex = -1, yIndex = -1;
    for (int i = 0; i < graph->vexNum; i++)
    {
        if (graph->Vex[i] == x)
            xIndex = i;
        else if (graph->Vex[i] == y)
            yIndex = i;
        if (xIndex != -1 && yIndex != -1)
            break;
    }
    if (xIndex == -1 || yIndex == -1)
        return false;
    return graph->Edge[xIndex][yIndex];
}

void NeighborsEdge(MGraph graph, char x)
{
    if (graph.vexNum < 2 || graph.edgeNum < 1)
        return;
    int xIndex = -1;
    for (int i = 0; i < graph.vexNum; i++)
    {
        if (graph.Vex[i] == x)
        {
            xIndex = i;
            break;
        }
    }
    if (xIndex == -1)
        return;
    for (int j = 0; j < graph.vexNum; j++)
    {
        if (graph.Edge[xIndex][j])
            printf("(%d, %d)\n", xIndex + 1, j + 1);
    }
}

int NextNeighbor(MGraph graph, char x, int w)
{
    if (graph.vexNum < 2 || graph.edgeNum < 1)
        return -1;
    int xIndex = -1;
    for (int i = 0; i < graph.vexNum; i++)
    {
        if (graph.Vex[i] == x)
        {
            xIndex = i;
            break;
        }
    }
    if (xIndex == -1)
        return -1;
    for (int j = w + 1; j < graph.vexNum; j++)
    {
        if (graph.Edge[xIndex][j])
            return j;
    }
    return -1;
}

void BFS(MGraph graph, int v)
{
    if (v > graph.vexNum)
        return;
    int *queue = (int *)malloc(graph.vexNum * sizeof(int));
    int i = 0, n = 0;
    queue[i] = v - 1;
    visited[v - 1] = true;
    char vertex = graph.Vex[v - 1];
    printf("visit: %c\n", vertex);
    int next;
    while (n < graph.vexNum && (queue[n] == 0 || queue[n]))
    {
        vertex = graph.Vex[queue[n]];
        for (next = NextNeighbor(graph, vertex, -1); next != -1; next = NextNeighbor(graph, vertex, next))
        {
            if (!visited[next])
            {
                queue[++i] = next;
                visited[next] = true;
                printf("visit: %c\n", graph.Vex[next]);
            }
        }
        n++;
    }
    free(queue);
}

void DFS(MGraph graph, int v)
{
    if (v > graph.vexNum)
        return;
    visited[v - 1] = true;
    char vertex = graph.Vex[v - 1];
    printf("visit: %c\n", vertex);
    for (int next = NextNeighbor(graph, vertex, -1); next != -1; next = NextNeighbor(graph, vertex, next))
    {
        if (!visited[next])
        {
            DFS(graph, next + 1);
        }
    }
}

int main()
{
    MGraph G;
    InitGraph(&G);
    char vex1 = 'A', vex2 = 'B', vex3 = 'C', vex4 = 'D', vex5 = 'E', vex6 = 'F';
    InsertVertex(&G, vex1);
    InsertVertex(&G, vex2);
    InsertVertex(&G, vex3);
    InsertVertex(&G, vex4);
    InsertVertex(&G, vex5);
    InsertVertex(&G, vex6);
    AddEdge(&G, vex1, vex2);
    AddEdge(&G, vex1, vex4);
    AddEdge(&G, vex2, vex5);
    AddEdge(&G, vex3, vex5);
    AddEdge(&G, vex3, vex6);
    AddEdge(&G, vex5, vex6);
    // NeighborsEdge(G, vex1);
    if (Adjacent(&G, vex1, vex2))
        printf("顶点 %c 与 %c 之间存在边\n", vex1, vex2);
    else
        printf("顶点 %c 与 %c 之间不存在边\n", vex1, vex2);
    // BFS(G, 3);
    DFS(G, 3);
    // DeleteVertex(&G, vex1);
    // if (Adjacent(&G, vex1, vex2))
    //     printf("顶点 %c 与 %c 之间存在边\n", vex1, vex2);
    // else
    //     printf("顶点 %c 与 %c 之间不存在边\n", vex1, vex2);
    return 0;
}