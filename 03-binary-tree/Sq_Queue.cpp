#include"Sq_Queue.h"
#include<stdio.h>
#include<stdlib.h>
int InitQueue(SqQueue &Q)
{
    //构造一个空的队列
    Q.base=new QElemType[MAXSIZE];
    if(!Q.base)exit(OVERFLOW);
    Q.front=Q.rear=0;
    return OK;
}
int EnQueue(SqQueue &Q,QElemType e)
{
    //入队
    if((Q.rear+1)%MAXSIZE==Q.front)
        return ERROR;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXSIZE;
    return OK;
}
int DeQueue(SqQueue &Q,QElemType &e)
{
    if(Q.front==Q.rear)return ERROR;
    e=Q.base[Q.front];
    Q.front=(Q.front+1)%MAXSIZE;
    return OK;
}
