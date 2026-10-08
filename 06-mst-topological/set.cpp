#include<stdio.h>
#include<stdlib.h>
#include"set.h"
#include"AM_Graph.h"
#include"AL_Graph.h"
void menu(){
    printf("=====请输入你的选择=====\n");
    printf("1.构造最小生成树(Prim算法)\n");
    printf("2.已知有向图，输出其拓扑排序\n");
    printf("0.退出操作\n");
    printf("========================\n");
}
void wait(){
    printf("按回车继续\n");
    getchar();
    getchar();
}
//构造最小生成树(Prim算法)
void gbzkzvxcuu()
{
    AMGraph G;
    CreatUDN(G);
    printf("输入最小生成树的顶点：");
    char start;
    scanf(" %c", &start);
    MiniSpanTree_Prim(G,start);
}
//已知有向图，输出其拓扑排序
void ybxdtukopu()
{
    //求一个 AOV 网的拓扑排序
    ALGraph G;
    printf("=====AOV网拓扑排序=====\n");
    printf("创建有向图进行拓扑排序:\n");
    printf("输入总顶点数和边数:");
    scanf("%d%d", &G.vexnum, &G.arcnum);
    printf("依次输入顶点编号:\n");
    for(int i = 0; i < G.vexnum; i++) {
        scanf(" %c", &G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    printf("依次输入有向边(起点 终点):\n");
    for(int k = 0; k < G.arcnum; k++) {
        char v1, v2;
        scanf(" %c %c", &v1, &v2);
        int i = LocateVex_AL(G, v1);
        int j = LocateVex_AL(G, v2);
        if(i != -1 && j != -1) {
            ArcNode *p = new ArcNode;
            p->adjvex = j;
            p->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p;
        }
    }
    TopologicalSort(G);
}
