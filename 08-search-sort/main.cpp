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
            case 1:plxuiavk();break;
            case 2:uujixnxi();break;
            case 0:printf("谢谢操作");break;
            default:printf("输入错误请重新输入");
        }
        if(choice!=0){
            wait();
        }
    }while(choice!=0);
    return 0;
}
