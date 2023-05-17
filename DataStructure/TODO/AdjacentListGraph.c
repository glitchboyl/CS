// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// #define MAX_VERTEX_NUM 10
// typedef struct LEdge
// {
//     int vex;
//     struct LEdge *first;
// } LEdge;
// typedef struct LVertex
// {
//     char data;
//     struct LEdge *first;
// } LVertex;
// typedef struct
// {
//     LVertex Vex[MAX_VERTEX_NUM];
//     int vexNum, edgeNum;
// } LGraph;

// void InitGraph(LGraph *graph)
// {
//     graph->vexNum = 0;
//     graph->edgeNum = 0;
// }

// void InsertVertex(LGraph *graph, char x)
// {
//     if (graph->vexNum == MAX_VERTEX_NUM)
//         return;
//     int i;
//     for (i = 0; i < MAX_VERTEX_NUM; i++)
//     {
//         if (graph->Vex[i] == NULL || !graph->Vex[i].data)
//             break;
//     }
//     LVertex *vex = (LVertex *)malloc(sizeof(LVertex));
//     vex->data = x;
//     vex->first = NULL;
//     graph->Vex[i] = vex;
//     graph->vexNum++;
// }

// // void DeleteVertex(LGraph *graph, char x)
// // {
// // }

// void AddEdge(LGraph *graph, char x, char y)
// {
//     if (graph->vexNum < 2 || x == y)
//         return;
//     int xIndex = -1, yIndex = -1;
//     for (int i = 0; i < graph->vexNum; i++)
//     {
//         LVertex *vex = graph->Vex[i];
//         if (vex->data == x)
//             xIndex = i;
//         else if (vex->data == y)
//             yIndex = i;
//         if (xIndex != -1 && yIndex != -1)
//             break;
//     }
//     if (xIndex == -1 || yIndex == -1)
//         return;
//     LVertex *vex = graph->Vex[xIndex];
//     LEdge *edge = (LEdge *)malloc(sizeof(LEdge));
//     edge->vex = yIndex;
//     vex->first = edge;
//     graph->edgeNum++;
// }

// // void RemoveEdge(LGraph *graph, char x, char y)
// // {
// // }

// // 判断两个顶点之间是否存在边
// bool Adjacent(LGraph graph, char x, char y)
// {
//     if (graph.vexNum < 2 || graph.edgeNum < 1 || x == y)
//         return false;
//     int xIndex = -1, yIndex = -1;
//     for (int i = 0; i < graph.vexNum; i++)
//     {
//         LVertex *vex = graph.Vex[i];
//         if (vex->data == x)
//             xIndex = i;
//         else if (vex->data == y)
//             yIndex = i;
//         if (xIndex != -1 && yIndex != -1)
//             break;
//     }
//     if (xIndex == -1 || yIndex == -1)
//         return false;
//     LEdge *p = graph.Vex[xIndex].first;
//     LEdge *q = graph.Vex[yIndex].first;
//     while (p || q)
//     {
//         if (p)
//         {
//             if (graph.Vex[p->vex] && graph.Vex[p->vex].data == y)
//                 return true;
//             p = p->first;
//         }
//         if (q)
//         {
//             if (graph.Vex[q->vex] && graph.Vex[q->vex].data == x)
//                 return true;
//             q = q->first;
//         }
//     }
//     return false;
// }

// int main()
// {
//     LGraph G;
//     InitGraph(&G);
//     char vex1 = 'A', vex2 = 'B';
//     InsertVertex(&G, vex1);
//     InsertVertex(&G, vex2);
//     AddEdge(&G, vex1, vex2);
//     // NeighborsEdge(G, vex1);
//     if (Adjacent(G, vex1, vex2))
//         printf("顶点 %c 与 %c 之间存在边\n", vex1, vex2);
//     else
//         printf("顶点 %c 与 %c 之间不存在边\n", vex1, vex2);
//     // DeleteVertex(G, vex1);
//     if (Adjacent(G, vex1, vex2))
//         printf("顶点 %c 与 %c 之间存在边\n", vex1, vex2);
//     else
//         printf("顶点 %c 与 %c 之间不存在边\n", vex1, vex2);
//     return 0;
// }
