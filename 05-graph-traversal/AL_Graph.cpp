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
            p1->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p1;

            // 创建v2->v1的边（无向图）
            ArcNode *p2 = new ArcNode;
            p2->adjvex = i;
            p2->nextarc = G.vertices[j].firstarc;
            G.vertices[j].firstarc = p2;
        }
    }
    printf("无向图邻接表建立成功\n");
    return 1;
}

void DFS_AL(ALGraph G, int v, int visited[]) {
    printf("%c ", G.vertices[v].data);
    visited[v] = 1;

    ArcNode *p = G.vertices[v].firstarc;
    while(p != NULL) {
        int w = p->adjvex;
        if(!visited[w]) {
            DFS_AL(G, w, visited);
        }
        p = p->nextarc;
    }
}

void BFS_AL(ALGraph G, int v) {
    int visited[MVNum] = {0};
    SqQueue Q;
    InitQueue(Q);

    printf("%c ", G.vertices[v].data);
    visited[v] = 1;
    EnQueue(Q, v);

    while(!QueueEmpty(Q)) {
        int u;
        DeQueue(Q, u);

        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL) {
            int w = p->adjvex;
            if(!visited[w]) {
                printf("%c ", G.vertices[w].data);
                visited[w] = 1;
                EnQueue(Q, w);
            }
            p = p->nextarc;
        }
    }
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
