#ifndef AL_GRAPH_H_INCLUDED
#define AL_GRAPH_H_INCLUDED

#define MVNum 100
// 边表结点
typedef struct ArcNode {
    int adjvex;
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
#endif // AL_GRAPH_H_INCLUDED
