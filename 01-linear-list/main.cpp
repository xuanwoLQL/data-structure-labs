#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include"Set.h"
#include"Sq_List.h"

using namespace std;

int main()
{
    int choice;
    do{
        system("cls");
        Menu();
        scanf("%d",&choice);
        system("cls");
        switch(choice){
            case 1:Xxhb();break;
            case 2:Yxhb();break;
            case 3:Dxsjiafa();break;
            case 4:Dxsjianfa();break;
            case 5:printf("谢谢使用!\n");break;
            default:printf("输入错误，请重新选择!\n");
        }
        if(choice!=0){
            ShuruHuiche();
        }
    }while(choice!=0);
    return 0;
}
