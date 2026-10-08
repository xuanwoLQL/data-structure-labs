#include"AM_Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include"Sq_Queue.h"
int LocateVex(AMGraph G,char v)
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(G.vexs[i]==v){
            return i;
        }
    }
    return -1;
}
int CreatUDN(AMGraph &G)
{
    printf("输入总顶点数和边数:");
    scanf("%d%d",&G.vexnum,&G.arcnum);
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            G.arcs[i][j]=MaxInt;//初始化邻接矩阵，边的权值均为极大值
        }
    }
    printf("依次输入顶点编号\n");
    for(int i=0;i<G.vexnum;i++){
        scanf(" %c",&G.vexs[i]);
    }
    printf("依次输入有连边的两个顶点和权值:\n");
    for(int k=0;k<G.arcnum;k++)
    {
        char v1,v2;
        int w;
        scanf(" %c %c%d",&v1,&v2,&w);
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);//确定v1和v2在G中的位置，即顶点数组的下标
        if(LocateVex(G,v1)!=-1&&LocateVex(G,v2)!=-1){
                G.arcs[i][j]=w;
                G.arcs[j][i]=G.arcs[i][j];}
        else{
            printf("输入错误\n");return 0;
        }
    }
    printf("无向图建立成功\n");
    return 1;
}
//深度优先遍历邻接矩阵
void DFS_AM(AMGraph G, int v, int visited[])
{
    printf("%c ", G.vexs[v]);
    visited[v] = 1;

    for(int w = 0; w < G.vexnum; w++) {
        if(G.arcs[v][w] != MaxInt && !visited[w]) {
            DFS_AM(G, w, visited);
        }
    }
}
//广度优先遍历邻接矩阵
void BFS_AM(AMGraph G, int v)
{
    int visited[MVNum] = {0};
    SqQueue Q;
    InitQueue(Q);

    printf("%c ", G.vexs[v]);
    visited[v] = 1;
    EnQueue(Q, v);

    while(!QueueEmpty(Q)) {
        int u;
        DeQueue(Q, u);

        for(int w = 0; w < G.vexnum; w++) {
            if(G.arcs[u][w] != MaxInt && !visited[w]) {
                printf("%c ", G.vexs[w]);
                visited[w] = 1;
                EnQueue(Q, w);
            }
        }
    }
}
