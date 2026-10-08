#ifndef SQ_QUEUE_H_INCLUDED
#define SQ_QUEUE_H_INCLUDED
#include"Sq_Stack.h"
typedef struct{
    char name[20];
    char sex;
}Person;
typedef struct{
    Person *base;
    int front;
    int rear;
}SqQueue;
int InitQueue(SqQueue &Q);//构造一个空的队列
int QueueLength(SqQueue Q);//求队列长度
int EnQueue(SqQueue &Q,Person e);//入队
int DeQueue(SqQueue &Q,Person &e);//出队
Person GetHead(SqQueue Q);//取队头元素
#endif // SQ_QUEUE_H_INCLUDED
