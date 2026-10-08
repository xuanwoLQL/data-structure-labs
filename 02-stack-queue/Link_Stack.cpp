#include"Link_Stack.h"
#include<stdio.h>
#include<stdlib.h>
//³õÊ¼»¯Õ»
int InitStack_L(LinkStack &S)
{
    S=new StackNode;
    S->next=NULL;
    return OK;
}
//Ñ¹Õ»
int Push_L(LinkStack &S,ElemType e)
{
    LinkStack p;
    p=new StackNode;
    p->data=e;
    p->next=S->next;
    S->next=p;
    return OK;
}
//³öÕ»
int Pop_L(LinkStack &S,ElemType &e)
{
    if(S->next==NULL)return ERROR;
    LinkStack p;
    p=S->next;
    e=p->data;
    S->next=p->next;
    delete p;
    return OK;
}
//È¡Õ»¶¥ÔªËØ
ElemType GetTop_L(LinkStack &S)
{
    LinkStack p;
    p=S->next;
    if(p!=NULL){
        return p->data;
    }
}
