#ifndef LINK_STACK_H_INCLUDED
#define LINK_STACK_H_INCLUDED
#include"Sq_Stack.h"
#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct StackNode{
    ElemType data;
    struct StackNode *next;
}StackNode,*LinkStack;
int InitStack_L(LinkStack &S);//初始化链栈
int Push_L(LinkStack &S,ElemType e);//压栈
int Pop_L(LinkStack &S,ElemType &e);//出栈
ElemType GetTop_L(LinkStack &S);//取出栈顶元素
#endif // LINK_STACK_H_INCLUDED
