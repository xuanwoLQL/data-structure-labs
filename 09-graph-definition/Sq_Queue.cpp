#include "Sq_Queue.h"
#include <stdlib.h>

// 初始化队列
void InitQueue(SqQueue &Q) {
    Q.base = new int[MAXQSIZE];
    if (!Q.base) {
        exit(0);
    }
    Q.front = Q.rear = 0;
}

// 入队
void EnQueue(SqQueue &Q, int e) {
    if ((Q.rear + 1) % MAXQSIZE == Q.front) {
        return; // 队列满
    }
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
}

// 出队
void DeQueue(SqQueue &Q, int &e) {
    if (Q.front == Q.rear) {
        return; // 队列空
    }
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
}

// 判断队列是否为空
int QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}
