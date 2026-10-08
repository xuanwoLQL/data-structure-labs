#ifndef SQ_STACK_H_INCLUDED
#define SQ_STACK_H_INCLUDED
#include"Sq_List.h"
#include<stdio.h>
#include<stdlib.h>
typedef  int SElemType;
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;
int InitStack(SqStack &S);
int Push(SqStack &S,SElemType e);
int Pop(SqStack &S,SElemType &e);
int GetTop(SqStack S,SElemType &e);
#endif // SQ_STACK_H_INCLUDED
