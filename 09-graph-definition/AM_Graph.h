#ifndef AM_GRAPH_H_INCLUDED
#define AM_GRAPH_H_INCLUDED

#define MaxInt 32767 //表示极大值,即无穷
#define MVNum 100 //最大顶点数
typedef char zifuxy;//假设顶点的数据类型为字符型
typedef int vgxy; //假设边的权值类型为整形
typedef struct{
    zifuxy vexs[MVNum];//顶点表
    vgxy arcs[MVNum][MVNum];//邻接矩阵
    int vexnum,arcnum;//图的当前点数和边数
}AMGraph;
int CreatUDN(AMGraph &G);//采用邻接矩阵表示法，创建无向网G
int LocateVex(AMGraph G,char v);//确定v在G中的位置
void DFS_AM(AMGraph G, int v, int visited[]);//深度优先遍历邻接矩阵
void BFS_AM(AMGraph G, int v);//广度优先遍历邻接矩阵
//辅助数组的定义，用来记录从顶点集U到V-U的权值最小的边
typedef struct{
    zifuxy adjvex;//最小边在U中的那个顶点
    vgxy lowcost;//最小边上的权值
}fuzu;
extern fuzu closeedge[MVNum];
//从顶点u出发构造G的最小生成树，输出树的各条边
void MiniSpanTree_Prim(AMGraph G,zifuxy u);
int Min();//寻找连边权值最小的那个顶点
//Dijksstra算法求最短路径
void Dijkstra(AMGraph G, int v0);
#endif // AM_GRAPH_H_INCLUDED
