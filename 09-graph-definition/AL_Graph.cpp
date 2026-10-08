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
int ve[MVNum] = {0};
int vl[MVNum] = {0};

void CriticalPath(ALGraph G) {
    printf("=====关键路径计算=====\n");

    // 初始化ve和vl数组
    for(int i = 0; i < G.vexnum; i++) {
        ve[i] = 0;
        vl[i] = MaxInt;
    }

    // 计算ve[i] - 事件最早发生时间
    int stack[MVNum];
    int top = -1;
    int indegree[MVNum] = {0};

    // 计算入度
    for(int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while(p != NULL) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }

    // 初始化栈
    for(int i = 0; i < G.vexnum; i++) {
        if(indegree[i] == 0) {
            stack[++top] = i;
        }
    }

    int count = 0;
    int *topoOrder = new int[G.vexnum];

    // 拓扑排序求ve[]
    while(top != -1) {
        int u = stack[top--];
        topoOrder[count++] = u;

        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL) {
            int v = p->adjvex;
            if(--indegree[v] == 0) {
                stack[++top] = v;
            }
            if(ve[u] + p->weight > ve[v]) {
                ve[v] = ve[u] + p->weight;
            }
            p = p->nextarc;
        }
    }

    if(count != G.vexnum) {
        printf("图中存在环，无法计算关键路径！\n");
        delete[] topoOrder;
        return;
    }

    // 计算vl[] - 事件最晚发生时间
    for(int i = 0; i < G.vexnum; i++) {
        vl[i] = ve[topoOrder[G.vexnum-1]];
    }

    for(int i = G.vexnum-2; i >= 0; i--) {
        int u = topoOrder[i];
        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL) {
            int v = p->adjvex;
            if(vl[u] > vl[v] - p->weight) {
                vl[u] = vl[v] - p->weight;
            }
            p = p->nextarc;
        }
    }

    // 输出关键路径
    printf("关键路径: ");
    for(int i = 0; i < G.vexnum-1; i++) {
        int u = topoOrder[i];
        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL) {
            int v = p->adjvex;
            int e = ve[u];
            int l = vl[v] - p->weight;
            if(e == l) {
                printf("%c->%c ", G.vertices[u].data, G.vertices[v].data);
            }
            p = p->nextarc;
        }
    }
    printf("\n");

    printf("工程最短完成时间: %d\n", ve[topoOrder[G.vexnum-1]]);

    delete[] topoOrder;
}
