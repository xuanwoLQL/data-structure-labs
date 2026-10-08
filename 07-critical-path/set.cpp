#include<stdio.h>
#include<stdlib.h>
#include"set.h"
#include"AL_Graph.h"
#include"AM_Graph.h"
void menu(){
    printf("=====请输入你的选择=====\n");
    printf("1.已知有向网,输出整个项目\n");
    printf(" 所需要的时间及各项关键活动\n");
    printf("2.计算从特定地点出发到所有\n");
    printf(" 城市之间的最短时间\n");
    printf("0.退出操作\n");
    printf("========================\n");
}
void wait(){
    printf("按回车继续\n");
    getchar();
    getchar();
}
//求关键活动
void grjmhods(){
    //第一步创立有向图
    ALGraph G;
    CreatYXT(G);
    CriticalPath(G);
}
//最短路径
void zvdrlujn(){
    AMGraph G;
    if(CreatUDN(G)){
        char start;
        printf("请输入起始顶点:");
        scanf(" %c",&start);
        int v0=LocateVex_AM(G,start);
        if(v0!=-1){
            Dijkstra(G,v0);
        }else{
            printf("顶点不存在!\n");
        }
    }
}
