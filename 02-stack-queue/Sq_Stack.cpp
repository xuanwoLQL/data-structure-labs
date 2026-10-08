#include"Sq_Stack.h"
#include<stdio.h>
#include<stdlib.h>
//字符栈的初始化
int InitStack(SqStack &S)
{
    S.base=new SElemType[MAXSIZE];
    if(!S.base)exit(OVERFLOW);
    S.top=S.base;
    S.stacksize=MAXSIZE;
    return OK;
}
//压栈
int Push(SqStack &S,char e)
{
    if(S.top-S.base==S.stacksize)return ERROR;
    *S.top++=e;
    return OK;
}
//入栈
int Pop(SqStack &S,char &e)
{
    if(S.top==S.base)return ERROR;
    e=*--S.top;
    return OK;
}
//取栈顶元素
char GetTop(SqStack S)
{
    if(S.top!=S.base){
        return *(S.top-1);
    }
    return '\0';
}
//整数栈的初始化
int InitNStack(NStack &S)
{
    S.base=new NElemType[MAXSIZE];
    if(!S.base)exit(OVERFLOW);
    S.top=S.base;
    S.stacksize=MAXSIZE;
    return OK;
}
//整数栈入栈
int Push_N(NStack &S,int e)
{
    if(S.top-S.base==S.stacksize)return ERROR;
    *S.top++=e;
    return OK;
}
//整数栈出栈
int Pop_N(NStack &S,int &e)
{
    if(S.top==S.base)return ERROR;
    e=*--S.top;
    return OK;
}
int GetTop_N(NStack S)
{
    if(S.top!=S.base)return *(S.top-1);
    return 0;
}
