#include"Sq_Stack.h"
#include"Bi_TNode.h"
#include<stdio.h>
#include<stdlib.h>
int InitStack(LinkStack &S)
{
    //创建链栈
    S=new StackNode;
    S->next=NULL;
    return OK;
}
int Push(LinkStack &S,SElemType e)
{
    //压栈
    LinkStack p;
    p=new StackNode;
    p->data=e;
    p->next=S;
    S=p;
    return OK;
}
int Pop(LinkStack &S,SElemType &e)
{
    //出栈
    LinkStack p;
    if(S==NULL)return ERROR;
    e=S->data;
    p=S;
    S=S->next;
    delete p;
    return OK;
}
