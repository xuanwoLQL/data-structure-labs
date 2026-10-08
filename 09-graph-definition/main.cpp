#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include"set.h"
using namespace std;

int main()
{
    int choice;
    do{
        system("cls");
        menu();
        scanf("%d",&choice);
        system("cls");
        switch(choice){
            case 1:lnjxbc_or_juvg();break;//将图以邻接表或邻接矩阵的形式存储
            case 2:ufdu_or_gddu();break;//图的深度优先，广度优先遍历
            case 3:zvxcugiguu();break;//求一个连通图的最小生成树
            case 4:zvdrrujn();break;//求一个图中给定点到其他各个顶点的最短路径
            case 5:AOE_grjmlujn();//求一个 AOE 网的关键路径
            case 6:AOV_topuplxu();//求一个 AOV 网的拓扑排序
            case 0:printf("退出程序\n");break;
            default:printf("输入错误,请重新输入\n");
        }
        if(choice!=0){
            wait();
        }
    }while(choice!=0);
    return 0;
}
