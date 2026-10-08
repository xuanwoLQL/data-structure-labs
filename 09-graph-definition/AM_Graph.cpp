#include"AM_Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include"Sq_Queue.h"
fuzu closeedge[MVNum];
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
//Prim算法生成最小生成树
void MiniSpanTree_Prim(AMGraph G,zifuxy u)
{
    int k=LocateVex(G,u);
    int zsqrvs=0;//计算总权重
    for(int j=0;j<G.vexnum;j++){
        if(j!=k){
                closeedge[j].adjvex=u;
                closeedge[j].lowcost=G.arcs[k][j];
        }
    }
    closeedge[k].lowcost=0;
    printf("最小生成树为\n");
    for(int i=1;i<G.vexnum;i++){
        k=Min();
        //求出T的写一个结点:第k个结点，closedge[k]中存有当前最小边
        char u0=closeedge[k].adjvex;
        char v0=G.vexs[k];
        int qrvs = G.arcs[LocateVex(G, u0)][k];  // 获取边的权重

        // 输出格式：(顶点1,顶点2)
        if(i == 1) {
            printf("(%c,%c)", u0, v0);
        } else {
            printf(" (%c,%c)", u0, v0);
        }

        zsqrvs += qrvs;  // 累加权重
        closeedge[k].lowcost=0;
        for(int j=0;j<G.vexnum;j++)
        {
            //新顶点并入U后重新选择最小边
            if(G.arcs[k][j]<closeedge[j].lowcost){
                closeedge[j].adjvex=G.vexs[k];
                closeedge[j].lowcost=G.arcs[k][j];
            }
        }
    }
    printf("\n权重和 = %d\n", zsqrvs);
}
// 寻找最小权值的顶点下标
int Min()
{
    int a = MaxInt;
    int k = -1;

    for(int i = 0; i < MVNum; i++)
    {
        // 只考虑未加入生成树的顶点，权值有效，且不是无穷大
        if(closeedge[i].lowcost != 0 &&
           closeedge[i].lowcost < a &&
           closeedge[i].lowcost != MaxInt)
        {
            a = closeedge[i].lowcost;
            k = i;
        }
    }
    return k;
}
// Dijkstra算法求最短路径
void Dijkstra(AMGraph G, int v0) {
    int n = G.vexnum;
    int dist[MVNum];    // 最短距离
    int path[MVNum];    // 前驱顶点
    int visited[MVNum]; // 访问标记

    // 初始化
    for(int i = 0; i < n; i++) {
        dist[i] = G.arcs[v0][i];
        if(dist[i] < MaxInt)
            path[i] = v0;
        else
            path[i] = -1;
        visited[i] = 0;
    }

    visited[v0] = 1;
    dist[v0] = 0;

    // 主循环
    for(int i = 1; i < n; i++) {
        int min = MaxInt;
        int u = v0;

        // 选择未访问顶点中距离最小的
        for(int j = 0; j < n; j++) {
            if(!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        visited[u] = 1;

        // 更新距离
        for(int w = 0; w < n; w++) {
            if(!visited[w] && G.arcs[u][w] < MaxInt &&
               dist[u] + G.arcs[u][w] < dist[w]) {
                dist[w] = dist[u] + G.arcs[u][w];
                path[w] = u;
            }
        }
    }

    // 输出结果
    printf("从顶点 %c 到其他顶点的最短路径:\n", G.vexs[v0]);
    for(int i = 0; i < n; i++) {
        if(i != v0) {
            printf("到顶点 %c: ", G.vexs[i]);
            if(dist[i] == MaxInt) {
                printf("无路径\n");
            } else {
                printf("距离=%d, 路径: ", dist[i]);

                // 反向输出路径
                int stack[MVNum], top = -1;
                int p = i;
                while(p != v0) {
                    stack[++top] = p;
                    p = path[p];
                }
                printf("%c", G.vexs[v0]);
                while(top >= 0) {
                    printf("->%c", G.vexs[stack[top--]]);
                }
                printf("\n");
            }
        }
    }
}
