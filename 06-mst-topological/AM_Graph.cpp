#include"AM_Graph.h"
#include<stdio.h>
#include<stdlib.h>
fuzu closeedge[MVNum];
//确定v在G中的位置
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
//采用邻接矩阵表示法，创建无向图G
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
