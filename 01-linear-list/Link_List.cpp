#include"Link_List.h"
#include<stdio.h>
#include<stdlib.h>
int InitList_L(LinkList &L)
{//构造一个空的单链表
    L=new LNode;
    L->next=NULL;
    return OK;
}
//单链表的取值
int GetElem_L(LinkList L,int i,ElemType &e)
{
    int j;
    LinkList p;
    p=L->next;j=1;
    while(p&&j<i)
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i)return ERROR;
    e=p->data;
    return OK;
}
LNode *LocateElem_L(LinkList L,ElemType e)
{
    LinkList p;
    p=L->next;
    while(p&&p->data!=e)
    {
        p=p->next;
    }
    return p;
}
//单链表的插入
int ListInset_L(LinkList &L,int i,ElemType e)
{
    LinkList p;
    int j;
    p=L;j=0;
    while(p&&(j<i-1))
    {
        p=p->next;++j;
    }
    if(!p||j>i-1)return ERROR;
    LinkList s;
    s=new LNode;
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
}
//单链表的删除
int ListDelete_l(LinkList &L,int i)
{
    LinkList p;
    int j;
    p=L;j=0;
    while((p->next)&&(j<i-1))
    {
        p=p->next;
        ++j;
    }
    if(!(p->next)||(j>i-1))return ERROR;
    LinkList q;
    q=p->next;
    p->next=q->next;
    delete q;
    return OK;
}
void HbYxb(LinkList La,LinkList Lb,LinkList &Lc)
{
    Lc=new LNode;
    Lc->next=NULL;//定义一个新链表
    LinkList pa=La->next;//La的第一个实际节点
    LinkList pb=Lb->next;//Lb的第一个实际节点
    LinkList pc=Lc;//指向新链表当前节点
    //逐个比较并添加较小节点,通过死循环来写
    while(pa!=NULL&&pb!=NULL)
    {
        //创建新节点
        LinkList c=new LNode;
        if(pa->data<=pb->data)
        {
            //取La的节点
            c->data=pa->data;
            pa=pa->next;
        }
        else{
            //取Lb的节点
            c->data=pb->data;
            pb=pb->next;
        }
        //将新节点添加到结果链表
        c->next=NULL;
        pc->next=c;
        pc=c;//指向新链表当前节点
    }
    //比较完成后，La,Lb可能还有剩余节点,
    while(pa!=NULL)
    {
        LinkList a=new LNode;
        a->data=pa->data;
        a->next=NULL;
        pc->next=a;
        pc=a;
        pa=pa->next;
    }
    while(pb!=NULL)
    {
        LinkList b=new LNode;
        b->data=pb->data;
        b->next=NULL;
        pc->next=b;
        pc=b;
        pb=pb->next;
    }
}
//创建多项式
void CjDxs(DxsDlb &L,int n)
{
    L=new Dxs;
    L->next=NULL;
    for(int i=1;i<=n;i++)
    {
        DxsDlb s=new Dxs;
        printf("请输入第%d项的系数和指数:",i);
        scanf("%f%d",&s->xishu,&s->zhishu);
        DxsDlb e=L;
        DxsDlb q=L->next;
        while(q&&((q->zhishu)<(q->zhishu)))
        {
            e=q;
            q=q->next;
        }
        s->next=q;
        e->next=s;//类似于插入操作
    }
}
//多项式减法
void DxsJf_L(DxsDlb &A,DxsDlb &B)
{
    DxsDlb a=A->next;
    DxsDlb b=B->next;
    DxsDlb e=A;
    while(a&&b)
    {
        if((a->zhishu)<(b->zhishu))
        {
            e=a;
            a=a->next;
        }
        else if((a->zhishu)>(b->zhishu))
        {
            DxsDlb s=new Dxs;
            s->xishu=-b->xishu;
            s->zhishu=b->zhishu;
            s->next=a;
            e->next=s;
            e=s;
            b=b->next;
        }
        else{
            a->xishu-=b->xishu;
            if(a->xishu==0){
                e->next=a->next;
                delete a;
                a=e->next;
            }
            else{
                e=a;
                a=a->next;
            }
            b=b->next;
        }
    }
    while(b)
    {
        DxsDlb s=new Dxs;
        s->xishu=-b->xishu;
        s->zhishu=b->zhishu;
        s->next=NULL;
        e->next=s;
        e=s;
        b=b->next;
    }
}
// 释放多项式链表（保留头节点）
void FreePolynomial(DxsDlb &P)
{
    if (P == NULL) return;

    DxsDlb p = P->next;  // 从第一个数据节点开始
    while (p != NULL) {
        DxsDlb temp = p;
        p = p->next;
        delete temp;
    }
    P->next = NULL;  // 头节点的next置为空
}
