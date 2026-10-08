#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include"set.h"
#include"Bi_TNode.h"
using namespace std;

int main()
{
    int choice;
    do{
        system("cls");
        menu();
        scanf("%d",&choice);
        system("cls");
        switch(choice)
        {
            case 1:
                idjmeriauu();
                break;
            case 2:
                bmlieriauu();
                break;
            case 3:
                eriauuufdu1();
                break;
            case 4:
                yezijxdmgeuu();
                break;
            case 0:
                printf("谢谢使用");
                break;
            default:
                printf("输入错误，请重新输入");
        }
        if(choice!=0){
            Wait();
        }
    }while(choice!=0);

    return 0;
}
