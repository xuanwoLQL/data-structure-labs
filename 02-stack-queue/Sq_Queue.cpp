#include<stdio.h>
#include<stdlib.h>
#include"Sq_Queue.h"
//构造一个空的队列
int InitQueue(SqQueue &Q)
{
    Q.base=new Person[MAXSIZE];
    if(!Q.base)exit(OVERFLOW);
    Q.front=Q.rear=0;
    return OK;
}
//求队列长度
int QueueLength(SqQueue Q)
{
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}
//入队
int EnQueue(SqQueue &Q,Person e)
{
    if((Q.rear+1)%MAXSIZE==Q.front)return ERROR;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXSIZE;
    return OK;
}
int DeQueue(SqQueue &Q,Person &e)
{
    if(Q.front==Q.rear)return ERROR;
    e=Q.base[Q.front];
    Q.front=(Q.front+1)%MAXSIZE;
    return OK;
}
Person GetHead(SqQueue Q)
{
    if(Q.front!=Q.rear)
    return Q.base[Q.front];
}
