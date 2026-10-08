#include "AL_Graph.h"
#include "Sq_Queue.h"
#include <stdio.h>
#include <stdlib.h>

int LocateVex_AL(ALGraph G, char v) {
    for(int i = 0; i < G.vexnum; i++) {
        if(G.vertices[i].data == v) {
            return i;
        }
    }
    return -1;
}

int CreateALGraph(ALGraph &G) {
    printf("输入总顶点数和边数:");
    scanf("%d%d", &G.vexnum, &G.arcnum);
    printf("依次输入顶点编号:\n");
    for(int i = 0; i < G.vexnum; i++) {
        scanf(" %c", &G.vertices[i].data);
        G.vertices[i].firstarc = NULL;   }
    printf("依次输入有连边的两个顶点:\n");
    for(int k = 0; k < G.arcnum; k++) {
        char v1, v2;
        scanf(" %c %c", &v1, &v2);
        int i = LocateVex_AL(G, v1);
        int j = LocateVex_AL(G, v2);
        if(i != -1 && j != -1) {
            // 创建v1->v2的边
            ArcNode *p1 = new ArcNode;
            p1->adjvex = j;
            p1->weight=1;
            p1->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p1;

            // 创建v2->v1的边（无向图）
            ArcNode *p2 = new ArcNode;
            p2->adjvex = i;
            p2->weight=1;
            p2->nextarc = G.vertices[j].firstarc;
            G.vertices[j].firstarc = p2;
        }
    }
    printf("无向图邻接表建立成功\n");
    return 1;
}

void PrintALGraph(ALGraph G) {
    printf("邻接表为：\n");
    for(int i = 0; i < G.vexnum; i++) {
        printf("%c:", G.vertices[i].data);
        ArcNode *p = G.vertices[i].firstarc;
        while(p != NULL) {
            printf(" %c", G.vertices[p->adjvex].data);
            p = p->nextarc;
        }
        printf("\n");
    }
}
// 拓扑排序
void TopologicalSort(ALGraph G) {
    int indegree[MVNum] = {0};

    // 计算入度
    for(int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while(p != NULL) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }

    // 初始化队列
    SqQueue Q;
    InitQueue(Q);

    // 入度为0的顶点入队
    for(int i = 0; i < G.vexnum; i++) {
        if(indegree[i] == 0) {
            EnQueue(Q, i);
        }
    }

    int count = 0;
    printf("拓扑排序结果: ");

    while(!QueueEmpty(Q)) {
        int u;
        DeQueue(Q, u);
        printf("%c ", G.vertices[u].data);
        count++;

        // 更新邻接顶点的入度
        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL) {
            int v = p->adjvex;
            indegree[v]--;
            if(indegree[v] == 0) {
                EnQueue(Q, v);
            }
            p = p->nextarc;
        }
    }

    if(count != G.vexnum) {
        printf("\n图中存在环，无法完成拓扑排序！\n");
    } else {
        printf("\n拓扑排序成功完成！\n");
    }
}
