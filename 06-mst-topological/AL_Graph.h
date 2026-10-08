#ifndef AL_GRAPH_H_INCLUDED
#define AL_GRAPH_H_INCLUDED
#define MaxInt 32767 //表示极大值,即无穷
#define MVNum 100 //最大顶点数
// 边表结点
typedef struct ArcNode {
    int adjvex;
    int weight;
    struct ArcNode *nextarc;
} ArcNode;
// 顶点表结点
typedef struct VNode {
    char data;
    ArcNode *firstarc;
} VNode, AdjList[MVNum];
// 图结构
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;
int CreateALGraph(ALGraph &G);//创建邻接表
int LocateVex_AL(ALGraph G, char v);//寻找邻接表最小两个结点
void PrintALGraph(ALGraph G);//打印邻接表
void TopologicalSort(ALGraph G);//拓扑排序
#endif // AL_GRAPH_H_INCLUDED
