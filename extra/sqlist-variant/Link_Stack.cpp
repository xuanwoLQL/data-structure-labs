#include<stdio.h>
#include<stdlib.h>
#include"Link_Stack.h"
int InitStack_L(LinkStack &s)
{
    s=new StackNode;
    s->next=NULL;
    return OK;
}
int Push_L(LinkStack &s,ElemType1 e)
{
    LinkStack p;
    p=new StackNode;
    p->data=e;
    p->next=s->next;
    s->next=p;
    return OK;
}
int Pop_L(LinkStack &s,ElemType1 &e)
{
    if(s->next==NULL)return ERROR;
    LinkStack p;
    p=new StackNode;
    p=s->next;
    e=p->data;
    s->next=p->next;
    return OK;
}
int GetTop_L(LinkStack s,ElemType &e)
{
    if(s->next==NULL)return ERROR;
    LinkStack p;
    p=new StackNode;
    p=s->next;
    e=p->data;
    return OK;
}
