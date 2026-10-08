#ifndef AM_GRAPH_H_INCLUDED
#define AM_GRAPH_H_INCLUDED

#define MaxInt 32767//表示极大值，及无穷
#define MVNum 100//最大顶点数
typedef char zifuxy;//假设顶点的数据类型为字符型
typedef int vgxy;//假设边的权值类型为整形
typedef struct{
    zifuxy vexs[MVNum];//顶点表
    vgxy arcs[MVNum][MVNum];//邻接矩阵
    int vexnum,arcnum;//图的当前点数和边数
}AMGraph;
int CreatUDN(AMGraph &G);//采用邻接矩阵表示法，创建无向网G
int LocateVex_AM(AMGraph G,char v);//确定v在中G的位置
void Dijkstra(AMGraph G,int v0);//迪杰斯特拉算法
#endif // AM_GRAPH_H_INCLUDED
