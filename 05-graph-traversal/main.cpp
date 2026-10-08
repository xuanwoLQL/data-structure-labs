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
            case 1:ufdujuvg();break;
            case 2:ufdubc();break;
            case 3:gddujuvg();break;
            case 4:gddubc();break;
            case 0:printf("退出程序\n");break;
            default:printf("输入错误,请重新输入\n");
        }
        if(choice!=0){
            wait();
        }
    }while(choice!=0);
    return 0;
}
