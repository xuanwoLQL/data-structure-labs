#include<stdio.h>
#include<stdlib.h>
#include"Sq_Stack.h"
#include"Sq_List.h"
//构造一个空的顺序栈
int InitStack(SqStack &S)
{
    S.base=new SElemType[MAXSIZE];
    if(!S.base)exit(OVERFLOW);
    S.base=S.top;
    S.stacksize=MAXSIZE;
    return OK;
}
//入栈操作
int Push(SqStack &S,SElemType e)
{
    if(S.top-S.base==S.stacksize)return ERROR;
    *S.top++=e;
    return OK;
}
//出栈操作
int Pop(SqStack &S,SElemType &e)
{
    if(S.top==S.base)return ERROR;
    e=*(S.top--);
    return OK;
}
//取栈顶元素
int GetTop(SqStack S,SElemType &e)
{
    if(S.top==S.base)return ERROR;
    e=*(S.top-1);
    return OK;
}
