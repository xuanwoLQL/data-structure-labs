#include<stdio.h>
#include<stdlib.h>
#include"set.h"
#include"AL_Graph.h"
#include"AM_Graph.h"
void wait(){
    printf("按回车继续");
    getchar();
    getchar();
}
//系统菜单
void menu()
{
    printf("=====请输入你的选择=====\n");
    printf("1.图以邻接表或邻接矩阵的形式存储\n");
    printf("2.图的深度优先，广度优先遍历\n");
    printf("3.求一个连通图的最小生成树\n");
    printf("4.求一个图中给定点到其他各个顶点的最短路径\n");
    printf("5.求一个 AOE 网的关键路径\n");
    printf("6.求一个 AOV 网的拓扑排序\n");
    printf("========================\n");
}
void lnjxbc_or_juvg()
{
    //将图以邻接表或邻接矩阵的形式存储
    int choice;
    printf("=====图的存储结构=====\n");
    printf("1.邻接表存储\n");
    printf("2.邻接矩阵存储\n");
    printf("请选择: ");
    scanf("%d", &choice);

    if(choice == 1) {
        ALGraph G;
        if(CreateALGraph(G)) {
            PrintALGraph(G);
        }
    } else if(choice == 2) {
        AMGraph G;
        if(CreatUDN(G)) {
            printf("邻接矩阵为：\n");
            printf("   ");
            for(int i = 0; i < G.vexnum; i++) {
                printf("%c ", G.vexs[i]);
            }
            printf("\n");

            for(int i = 0; i < G.vexnum; i++) {
                printf("%c: ", G.vexs[i]);
                for(int j = 0; j < G.vexnum; j++) {
                    if(G.arcs[i][j] == MaxInt)
                        printf("∞ ");
                    else
                        printf("%d ", G.arcs[i][j]);
                }
                printf("\n");
            }
        }
    } else {
        printf("输入错误！\n");
    }
}
void ufdu_or_gddu(){
    //图的深度优先，广度优先遍历
    int choice;
    printf("=====图的遍历=====\n");
    printf("1.邻接表遍历\n");
    printf("2.邻接矩阵遍历\n");
    printf("请选择: ");
    scanf("%d", &choice);

    if(choice == 1) {
        ALGraph G;
        if(CreateALGraph(G)) {
            int visited[MVNum] = {0};
            printf("深度优先遍历: ");
            DFS_AL(G, 0, visited);
            printf("\n广度优先遍历: ");
            BFS_AL(G, 0);
            printf("\n");
        }
    } else if(choice == 2) {
        AMGraph G;
        if(CreatUDN(G)) {
            int visited[MVNum] = {0};
            printf("深度优先遍历: ");
            DFS_AM(G, 0, visited);
            printf("\n广度优先遍历: ");
            BFS_AM(G, 0);
            printf("\n");
        }
    } else {
        printf("输入错误！\n");
    }
}
void zvxcugiguu(){
    //求一个连通图的最小生成树
    AMGraph G;
    if(CreatUDN(G)) {
        char start;
        printf("请输入起始顶点: ");
        scanf(" %c", &start);
        MiniSpanTree_Prim(G, start);
    }
}
void zvdrrujn(){
    //求一个图中给定点到其他各个顶点的最短路径
    AMGraph G;
    if(CreatUDN(G)) {
        char start;
        printf("请输入起始顶点: ");
        scanf(" %c", &start);
        int v0 = LocateVex(G, start);
        if(v0 != -1) {
            Dijkstra(G, v0);
        } else {
            printf("顶点不存在！\n");
        }
    }
}
void AOE_grjmlujn(){
    //求一个 AOE 网的关键路径
    printf("=====AOE网关键路径=====\n");
    ALGraph G;
    printf("创建AOE网(带权有向图):\n");
    printf("输入总顶点数和边数:");
    scanf("%d%d", &G.vexnum, &G.arcnum);
    printf("依次输入顶点编号:\n");
    for(int i = 0; i < G.vexnum; i++) {
        scanf(" %c", &G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    printf("依次输入有向边和权值(起点 终点 权值):\n");
    for(int k = 0; k < G.arcnum; k++) {
        char v1, v2;
        int weight;
        scanf(" %c %c %d", &v1, &v2, &weight);
        int i = LocateVex_AL(G, v1);
        int j = LocateVex_AL(G, v2);
        if(i != -1 && j != -1) {
            ArcNode *p = new ArcNode;
            p->adjvex = j;
            p->weight = weight;  // 需要修改ArcNode结构以存储权重
            p->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p;
        }
    }
    CriticalPath(G);

}
void AOV_topuplxu(){
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
