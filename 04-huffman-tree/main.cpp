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
            case 1:idjmhafumjuu();break;
            case 2:hafumjbmma();break;
            case 3:dljrrujnihdu();break;
            case 0:printf("谢谢操作\n");break;
            default: printf("输入错误，请重新输入");
        }
        if(choice!=0){Wait();}
    }while(choice!=0);
}
