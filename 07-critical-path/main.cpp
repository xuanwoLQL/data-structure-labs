#include<stdio.h>
#include<stdlib.h>
#include <iostream>
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
            //已知有向网,输出整个项目所需要的时间及各项关键活动
            case 1:grjmhods();break;
            //计算从特定地点出发到所有城市之间的最短时间
            case 2:zvdrlujn();break;
            case 0:printf("谢谢操作!");break;
            default:printf("输入错误，请重新操作!");
        }
        if(choice!=0){
            wait();
        }
    }while(choice!=0);
    return 0;
}
