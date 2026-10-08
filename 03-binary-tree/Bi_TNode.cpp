#include<stdio.h>
#include<stdlib.h>
#include"Bi_TNode.h"
#include"Sq_Stack.h"
#include"Sq_Queue.h"
#include"set.h"
//创建二叉树
void CreatBiTree(BiTree &T)
{
    char ch;
    scanf(" %c",&ch);
    if(ch=='.'){T=NULL;}
    else{
        T=new BiTNode;
        T->data=ch;
        CreatBiTree(T->lchild);
        CreatBiTree(T->rchild);
    }
}
//先序遍历
void xmxubmli(BiTree T){
    if(T){
        printf("%c",T->data);
        xmxubmli(T->lchild);
        xmxubmli(T->rchild);
    }
}
//中序遍历
void vsxubmli(BiTree T)
{
    if(T){
        vsxubmli(T->lchild);
        printf("%c",T->data);
        vsxubmli(T->rchild);
    }
}
//后序遍历
void hbxubmli(BiTree T)
{
    if(T){
        hbxubmli(T->lchild);
        hbxubmli(T->rchild);
        printf("%c",T->data);
    }
}
//二叉树深度
int eriauuufdu(BiTree T)
{
    int m,n;
    if(T==NULL)return 0;
    else{
        m=eriauuufdu(T->lchild);
        n=eriauuufdu(T->rchild);
        if(m>n)return(m+1);
        else return(n+1);
    }
}
//叶子节点个数
int NodeCount(BiTree T)
{
    if(T==NULL)return 0;
    if(T->lchild==NULL&&T->rchild==NULL){
        return 1;
    }
    return NodeCount(T->lchild)+NodeCount(T->rchild);
}
//非递归中序遍历
void fzdigvvsxubmli()
{
    if(T==NULL){
        printf("请先创立二叉树!\n");
        return;
    }
    LinkStack S;
    InitStack(S);
    BiTree p;
    p=T;
    BiTree q;
    printf("非递归中序遍历结果为:\n");
    while(p||S->next!=NULL)
    {
        if(p){
            Push(S,p);
            p=p->lchild;
        }
        else{
            Pop(S,q);
            printf("%c",q->data);
            p=q->rchild;
        }
    }
    printf("\n");
}
//层序遍历
void cgxubmli(BiTree T)
{
    if(T==NULL)return;
    SqQueue Q;
    InitQueue(Q);
    BiTree p=T;
    EnQueue(Q,p);
    while(Q.front!=Q.rear){
        DeQueue(Q,p);
        printf("%c",p->data);
        //左孩子入队
        if(p->lchild!=NULL){
            EnQueue(Q,p->lchild);
        }
        //右孩子入队
        if(p->rchild!=NULL){
            EnQueue(Q,p->rchild);
        }
    }
}

