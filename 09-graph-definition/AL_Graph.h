#ifndef AL_GRAPH_H_INCLUDED
#define AL_GRAPH_H_INCLUDED
#define MVNum 100
#define MaxInt 32767
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
void DFS_AL(ALGraph G, int v, int visited[]);//邻接表深度优先遍历
void BFS_AL(ALGraph G, int v);//邻接表广度优先遍历
void PrintALGraph(ALGraph G);//打印邻接表
void TopologicalSort(ALGraph G);//拓扑排序

// 事件最早发生时间
extern int ve[MVNum];
// 事件最晚发生时间
extern int vl[MVNum];

// 计算关键路径
void CriticalPath(ALGraph G);
#endif // AL_GRAPH_H_INCLUDED
