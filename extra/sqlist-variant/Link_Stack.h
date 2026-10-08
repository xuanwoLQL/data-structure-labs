#ifndef LINK_STACK_H_INCLUDED
#define LINK_STACK_H_INCLUDED
#include"Sq_List.h"
typedef int ElemType1;
typedef struct StackNode{
    ElemType1 data;
    struct StackNode *next;
}StackNode,*LinkStack;
int InitStack_L(LinkStack &s);
int Push_L(LinkStack &s,ElemType1 e);
int Pop_L(LinkStack &s,ElemType1 &e);
int GetTop_L(LinkStack s,ElemType1 &e);

#endif // LINK_STACK_H_INCLUDED
