#ifndef SQ_QUEUE_H_INCLUDED
#define SQ_QUEUE_H_INCLUDED

#define MAXQSIZE 100
typedef struct{
    int *base;
    int front;
    int rear;
}SqQueue;

// 初始化队列
void InitQueue(SqQueue &Q);
// 入队
void EnQueue(SqQueue &Q, int e);
// 出队
void DeQueue(SqQueue &Q, int &e);
// 判断队列是否为空
int QueueEmpty(SqQueue Q);

#endif // SQ_QUEUE_H_INCLUDED
