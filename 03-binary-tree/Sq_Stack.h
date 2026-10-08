#ifndef SQ_STACK_H_INCLUDED
#define SQ_STACK_H_INCLUDED
#include"Bi_TNode.h"
typedef BiTree SElemType;
typedef struct StackNode{
    SElemType data;//Õ»¶¥Ö¸Õë
    struct StackNode *next;
}StackNode,*LinkStack;
//×Ö·ûÕ»²Ù×÷
int InitStack(LinkStack &S);//Á´Õ»Õ»µÄ³õÊ¼»¯
int Push(LinkStack &S,SElemType e);//Ñ¹Õ»
int Pop(LinkStack &S,SElemType &e);//³öÕ»
#endif // SQ_STACK_H_INCLUDED
