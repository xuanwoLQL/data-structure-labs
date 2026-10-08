#include<stdio.h>
#include<stdlib.h>
#include"Bdsz.h"
#include"Sq_Stack.h"
int In(char ch)
{
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='#')
    {return OK;}
    else{
        return ERROR;
    }
}
char Precede(char a,char b)
{
    int i,j;
    char Prior[7][7]=
    {//运算符优先级表
        //'+', '-', '*' '/' '(' ')' '#'
    /*'+'*/{'>','>','<','<','<','>','>'},
    /*'-'*/{'>','>','<','<','<','>','>'},
    /*'*'*/{'>','>','>','>','<','>','>'},
    /*'/'*/{'>','>','>','>','<','>','>'},
    /*'('*/{'<','<','<','<','<','=',' '},
    /*')'*/{'>','>','>','>',' ','>','>'},
    /*'#'*/{'<','<','<','<','<',' ','='}
    };
    char m[7]={'+','-','*','/','(',')','#'};
    for(i=0;i<7;i++)
    {
        if(m[i]==a){break;}
    }
    for(j=0;j<7;j++)
    {
        if(m[j]==b)break;}
    if(i>=7||j>=7)return ' ';
    return Prior[i][j];
}
int Operate(int a,char theta,int b)
{
    switch(theta)
    {
        case '+':
            return a+b;
            break;
        case '-':
            return a-b;
            break;
        case '*':
            return a*b;
            break;
        case '/':
            if(b==0){
                printf("错误:除数为零");
                return '0';
            }
            return a/b;
            break;
        default:return 0;
    }
}
