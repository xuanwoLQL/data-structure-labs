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
        if(scanf("%d",&choice)!=1){
            while(getchar()!='\n');//清楚输入缓冲区
            choice=-1;
        }
        getchar();//清楚换行符
        system("cls");
        switch(choice){
            case 1:
                loadFile();
                break;
            case 2:
                showFrequencyTable();
                break;
            case 3:
                buildTree();
                break;
            case 4:
                generateCodes();
                break;
            case 5:
                encode();
                break;
            case 6:
                decode();
                break;
            case 7:
                saveAllResults();
                break;
            case 8:
                showPerformance();
                break;
            case 9:
                showTreeGraphical();
                break;
            case 10:saveCodeTableToFile(); break;
            case 11:encodeWithSavedTable(); break;
            case 12:encryptText(); break;
            case 0:
                printf("感谢使用哈夫曼编/译码器系统\n");
                cleanupSystem();
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;
        }
        if(choice!=0){
            wait();
        }
    }while(choice!=0);
    return 0;
}
