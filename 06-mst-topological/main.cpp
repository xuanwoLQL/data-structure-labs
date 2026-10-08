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
            case 1:gbzkzvxcuu();break;
            case 2:ybxdtukopu();break;
            case 0:printf("谢谢操作\n");break;
            default:printf("输入错误，请重新输入\n");
        }
        if(choice!=0){
            wait();
        }
    }while(choice!=0);
    return 0;
}
