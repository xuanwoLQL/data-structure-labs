#ifndef AL_GRAPH_H_INCLUDED
#define AL_GRAPH_H_INCLUDED

#define MVNum 100
// 边表结点
typedef struct ArcNode {
    int adjvex;//该边所指向的顶点的位置
    int weight;//边的权值
    struct ArcNode *nextarc;//指向下一条边的指针
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
//确定顶点在表的位置
int LocateVex(ALGraph G, char v);
//采用邻接表的方式创建有向图
int CreatYXT(ALGraph &G);
//拓扑排序
int TopologicalOrder(ALGraph G, int topo[]);
//关键活动
int CriticalPath(ALGraph G);
#endif // AL_GRAPH_H_INCLUDED
