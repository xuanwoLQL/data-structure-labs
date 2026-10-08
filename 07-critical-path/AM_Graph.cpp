#include<stdio.h>
#include<stdlib.h>
#include"AM_Graph.h"
//确定顶点v在表中的位置
int LocateVex_AM(AMGraph G,char v)
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(G.vexs[i]==v){
            return i;
        }
    }
}
//创建一个无向网
int CreatUDN(AMGraph &G)
{
    printf("输入总顶点数和边数:");
    scanf("%d%d",&G.vexnum,&G.arcnum);
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            //初始化邻接矩阵，边的权值为最大值
            G.arcs[i][j]=MaxInt;
        }
    }
    printf("依次输入顶点编号\n");
    for(int i=0;i<G.vexnum;i++){
        scanf(" %c",&G.vexs[i]);
    }
    printf("依次输入有连边的两个顶点和权值:\n");
    for(int k=0;k<G.arcnum;k++){
        char v1,v2;
        int w;
        scanf(" %c %c%d",&v1,&v2,&w);
        //确定v1,v2在G中的位置
        int i=LocateVex_AM(G,v1);
        int j=LocateVex_AM(G,v2);
        if(LocateVex_AM(G,v1)!=-1&&LocateVex_AM(G,v2)!=-1){
            G.arcs[i][j]=w;
            G.arcs[j][i]=G.arcs[i][j];
        }else{
            printf("输入错误\n");return 0;
        }
    }
    printf("无向网建立成功\n");
    return 1;
}
//迪杰斯卡尔算法
void Dijkstra(AMGraph G,int v0){
    int n=G.vexnum;
    int dist[MVNum];//最短距离
    int path[MVNum];//前驱顶点
    int visited[MVNum];//访问标记
    //初始化
    for(int i=0;i<n;i++){
        dist[i]=G.arcs[v0][i];
        if(dist[i]<MaxInt){path[i]=v0;}
        else{path[i]=-1;}
        visited[i]=0;
    }
    visited[v0]=-1;
    dist[v0]=0;
    //主循环
    for(int i=1;i<n;i++){
        int min=MaxInt;
        int u=v0;
        //选择未访问顶点中距离最小的
        for(int j=0;j<n;j++){
            if(!visited[j]&&dist[j]<min){
                min=dist[j];
                u=j;
            }
        }
        visited[u]=1;
        //更新距离
        for(int w=0;w<n;w++){
            if(!visited[w]&&G.arcs[u][w]<MaxInt&&
            dist[u]+G.arcs[u][w]<dist[w]){
                dist[w]=dist[u]+G.arcs[u][w];
                path[w]=u;
            }
        }
    }
    //输出结果
    printf("从顶点%c到其他顶点的最短路径:\n",G.vexs[v0]);
    for(int i=0;i<n;i++){
        if(i!=v0){
            printf("到顶点%c:",G.vexs[i]);
            printf(" 路径:");
            if(dist[i]==MaxInt){
                printf("无路径\n");
            }else{
                //反向输出路径
                int stack[MVNum],top=-1;
                int p=i;
                while(p!=v0){
                    stack[++top]=p;
                    p=path[p];
                }
                printf("%c",G.vexs[v0]);
                while(top>=0){
                    printf("->%c",G.vexs[stack[top--]]);
                }
                printf(" 距离=%d",dist[i]);
                printf("\n");
            }
        }
    }

}
