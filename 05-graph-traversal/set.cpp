#include"set.h"
#include<stdio.h>
#include<stdlib.h>
#include"AM_Graph.h"
#include"AL_Graph.h"
void wait(){
    printf("按回车继续");
    getchar();
    getchar();
}
void menu()
{
    printf("=====请输入你的选择=====\n");
    printf("1.深度优先遍历(邻接矩阵)\n");
    printf("2.深度优先遍历(邻接表)\n");
    printf("3.广度优先遍历(邻接矩阵)\n");
    printf("4.广度优先遍历(邻接表)\n");
    printf("========================\n");
}
void ufdujuvg()
{
    //深度优先遍历(邻接矩阵
    AMGraph G;
    CreatUDN(G);
    printf("邻接矩阵表示为\n");
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            if(j!=G.vexnum-1){
                if(G.arcs[i][j]!=MaxInt){
                    printf("1\t");
                }
                else{
                    printf("0\t");
                }
            }else{
                if(G.arcs[i][j]!=MaxInt){
                    printf("1\t");
                }else{
                    printf("0\t");
                }
            }
        }
        printf("\n");
    }
    printf("输入初始遍历顶点编号：");
    char start;
    scanf(" %c", &start);
    int startIndex = LocateVex(G, start);

    if(startIndex != -1) {
        int visited[MVNum] = {0};
        printf("深度优先遍历(dfs)：");
        DFS_AM(G, startIndex, visited);
        printf("\n");
    } else {
        printf("顶点不存在！\n");
    }
}
void ufdubc()
{
    //深度优先遍历（邻接表）
    ALGraph G;
    CreateALGraph(G);
    PrintALGraph(G);

    printf("输入初始遍历顶点编号：");
    char start;
    scanf(" %c", &start);
    int startIndex = LocateVex_AL(G, start);

    if(startIndex != -1) {
        int visited[MVNum] = {0};
        printf("深度优先遍历(dfs)：");
        DFS_AL(G, startIndex, visited);
        printf("\n");
    } else {
        printf("顶点不存在！\n");
    }
    printf("\n");
}

void gddujuvg()
{
    //广度优先遍历（邻接矩阵）
    AMGraph G;
    CreatUDN(G);

    printf("输入初始遍历顶点编号：");
    char start;
    scanf(" %c", &start);
    int startIndex = LocateVex(G, start);

    if(startIndex != -1) {
        printf("广度优先遍历(bfs)：");
        BFS_AM(G, startIndex);
        printf("\n");
    } else {
        printf("顶点不存在！\n");
    }
}

void gddubc()
{
    //广度优先遍历（邻接表）
    ALGraph G;
    CreateALGraph(G);

    printf("输入初始遍历顶点编号：");
    char start;
    scanf(" %c", &start);
    int startIndex = LocateVex_AL(G, start);

    if(startIndex != -1) {
        printf("广度优先遍历(bfs)：");
        BFS_AL(G, startIndex);
        printf("\n");
    } else {
        printf("顶点不存在！\n");
    }
}
