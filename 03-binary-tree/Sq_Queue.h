#ifndef SQ_QUEUE_H_INCLUDED
#define SQ_QUEUE_H_INCLUDED
#include"Bi_TNode.h"
#include"Bi_TNode.h"
typedef BiTree QElemType;
//创建顺序队
typedef struct{
    QElemType *base;
    int front;
    int rear;
}SqQueue;
int InitQueue(SqQueue &Q);//构建一个空的队列
int EnQueue(SqQueue &Q,QElemType e);//入队
int DeQueue(SqQueue &Q,QElemType &e);//出队
#endif // SQ_QUEUE_H_INCLUDED
