#include<stdio.h>
#include"AL_Graph.h"
#include<stdlib.h>
//确定顶点在表的位置
int LocateVex(ALGraph G, char v){
    for(int i = 0; i < G.vexnum; i++) {
        if(G.vertices[i].data == v) {
            return i;
        }
    }
    return -1;
}
//采用邻接表的方式创建有向图
int CreatYXT(ALGraph &G)
{
    printf("输入总顶点数和边数:");
    scanf("%d%d", &G.vexnum, &G.arcnum);
    printf("依次输入顶点编号:\n");
    for(int i = 0; i < G.vexnum; i++) {
        scanf(" %c", &G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    printf("依次输入有连边的两个顶点(起点 终点 权值):\n");
    for(int k = 0; k < G.arcnum; k++) {
        char v1, v2;
        int weight;
        scanf(" %c %c %d",&v1,&v2,&weight);
        int i = LocateVex(G, v1);//起点
        int j = LocateVex(G, v2);//终点
        if(i != -1 && j != -1) {
            // 创建v1->v2的边(有向边)
            ArcNode *p1 = new ArcNode;
            p1->adjvex = j;
            p1->weight=weight;
            p1->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p1;
        }
    }
    printf("有向图邻接表建立成功\n");
    return 1;
}
//拓扑排序算法
int TopologicalOrder(ALGraph G, int topo[]) {
    int indegree[MVNum] = {0};
    int stack[MVNum], top = -1;
    int count = 0;
    // 计算各顶点的入度
    for(int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while(p != NULL) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
    // 入度为0的顶点入栈
    for(int i = 0; i < G.vexnum; i++) {
        if(indegree[i] == 0) {
            stack[++top] = i;
        }
    }
    // 拓扑排序
    while(top != -1) {
        int k = stack[top--];
        topo[count++] = k;

        ArcNode *p = G.vertices[k].firstarc;
        while(p != NULL) {
            int j = p->adjvex;
            if(--indegree[j] == 0) {
                stack[++top] = j;
            }
            p = p->nextarc;
        }
    }
    if(count < G.vexnum) return 0; // 存在环
    return 1;
}
//关键路劲
int CriticalPath(ALGraph G) {
    int topo[MVNum];
    int ve[MVNum] = {0}; // 最早发生时间
    int vl[MVNum] = {0}; // 最迟发生时间

    // 拓扑排序
    if(!TopologicalOrder(G, topo)) {
        printf("图中存在环，无法计算关键路径\n");
        return 0;
    }
    int n = G.vexnum;
    // 计算最早发生时间 ve[]
    for(int i = 0; i < n; i++) {
        int k = topo[i];
        ArcNode *p = G.vertices[k].firstarc;
        while(p != NULL) {
            int j = p->adjvex;
            if(ve[j] < ve[k] + p->weight) {
                ve[j] = ve[k] + p->weight;
            }
            p = p->nextarc;
        }
    }
    // 初始化最迟发生时间 vl[]
    for(int i = 0; i < n; i++) {
        vl[i] = ve[n-1];
    }
    // 计算最迟发生时间 vl[]
    for(int i = n-1; i >= 0; i--) {
        int k = topo[i];
        ArcNode *p = G.vertices[k].firstarc;
        while(p != NULL) {
            int j = p->adjvex;
            if(vl[k] > vl[j] - p->weight) {
                vl[k] = vl[j] - p->weight;
            }
            p = p->nextarc;
        }
    }
    // 输出关键活动
    printf("关键活动:\n");
    printf("项目总工期: %d\n", ve[n-1]);
    for(int i = 0; i < n; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while(p != NULL) {
            int j = p->adjvex;
            int e = ve[i];// 最早开始时间
            int l = vl[j] - p->weight; // 最迟开始时间
            if(e == l) { // 关键活动
                printf("%c -> %c (权重: %d)\n",
                       G.vertices[i].data,
                       G.vertices[j].data,
                       p->weight);
            }
            p = p->nextarc;
        }
    }
    return 1;
}
