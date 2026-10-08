#include<stdio.h>
#include<stdlib.h>
#include"Link_List.h"
// 初始化单链表
int InitList_L(LinkList &L)
{
    L = new LNode;
    if(!L) return ERROR;
    L->next = NULL;
    return OK;
}

// 单链表插入
int ListInsert_L(LinkList &L, int i, ElemType e)
{
    LinkList p = L;
    int j = 0;

    while(p && j < i - 1)
    {
        p = p->next;
        j++;
    }

    if(!p || j > i - 1) return ERROR;

    LinkList s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

// 有序表合并
void MergeList_L(LinkList La, LinkList Lb, LinkList &Lc)
{
     Lc = new LNode;
    Lc->next = NULL;

    LinkList pa = La->next;  // La的第一个实际节点
    LinkList pb = Lb->next;  // Lb的第一个实际节点
    LinkList pc = Lc;        // 指向新链表的当前节点

    // 逐个比较并添加较小的节点
    while (pa != NULL && pb != NULL)
    {
        // 创建新节点（C++写法）
        LinkList newNode = new LNode;

        if (pa->data <= pb->data)
        {
            // 取La的节点
            newNode->data = pa->data;
            pa = pa->next;
        }
        else
        {
            // 取Lb的节点
            newNode->data = pb->data;
            pb = pb->next;
        }

        // 将新节点添加到结果链表
        newNode->next = NULL;
        pc->next = newNode;
        pc = newNode;
    }

    // 处理剩余节点（La或Lb中可能还有剩余）
    while (pa != NULL)
    {
        LinkList newNode = new LNode;
        newNode->data = pa->data;
        newNode->next = NULL;
        pc->next = newNode;
        pc = newNode;
        pa = pa->next;
    }

    while (pb != NULL)
    {
        LinkList newNode = new LNode;
        newNode->data = pb->data;
        newNode->next = NULL;
        pc->next = newNode;
        pc = newNode;
        pb = pb->next;
    }
    // LinkList pa = La->next;  // pa指向La的第一个实际节点
    //LinkList pb = Lb->next;  // pb指向Lb的第一个实际节点
    //LinkList pc = Lc = La;   // Lc使用La的头节点，pc指向当前合并位置

    // 同时遍历两个链表，直到其中一个遍历完
    //while(pa && pb)
    //{
        //if(pa->data <= pb->data)  // 比较当前节点值
        //{
            //pc->next = pa;  // 将pa节点链接到结果链表
            //pc = pa;        // pc移动到新链接的节点
            //pa = pa->next;  // pa指向La的下一个节点
        //}
        //else
        //{
            //pc->next = pb;  // 将pb节点链接到结果链表
            //pc = pb;        // pc移动到新链接的节点
            //pb = pb->next;  // pb指向Lb的下一个节点
        //}
    //}

    // 将剩余部分直接链接到结果链表
    //pc->next = pa ? pa : pb;

    //delete Lb;
}

// 创建多项式
void CreatePolyn(Polynomial &P, int n)
{
    P = new PNode;
    P->next = NULL;

    for(int i = 1; i <= n; i++)
    {
        Polynomial s = new PNode;
        printf("请输入第%d项的系数和指数: ", i);
        scanf("%f%d", &s->coef, &s->expn);

        Polynomial pre = P;
        Polynomial q = P->next;

        while(q && q->expn < s->expn)
        {
            pre = q;
            q = q->next;
        }

        s->next = q;
        pre->next = s;
    }
}

// 多项式减法
void SubtractPolynomials(Polynomial &A, Polynomial B)
{
    Polynomial pa = A->next;
    Polynomial pb = B->next;
    Polynomial pre = A;

    while(pa && pb)
    {
        if(pa->expn < pb->expn)
        {
            pre = pa;
            pa = pa->next;
        }
        else if(pa->expn > pb->expn)
        {
            Polynomial s = new PNode;
            s->coef = -pb->coef;
            s->expn = pb->expn;
            s->next = pa;
            pre->next = s;
            pre = s;
            pb = pb->next;
        }
        else
        {
            pa->coef -= pb->coef;
            if(pa->coef == 0)
            {
                pre->next = pa->next;
                delete pa;
                pa = pre->next;
            }
            else
            {
                pre = pa;
                pa = pa->next;
            }
            pb = pb->next;
        }
    }

    while(pb)
    {
        Polynomial s = new PNode;
        s->coef = -pb->coef;
        s->expn = pb->expn;
        s->next = NULL;
        pre->next = s;
        pre = s;
        pb = pb->next;
    }
}

// 打印多项式
void PrintPolynomial(Polynomial P)
{
    Polynomial p = P->next;
    if(!p)
    {
        printf("0\n");
        return;
    }

    int first = 1;
    while(p)
    {
        if(p->coef > 0 && !first)
            printf("+");

        if(p->expn == 0)
            printf("%.1f", p->coef);
        else if(p->expn == 1)
            printf("%.1fx", p->coef);
        else
            printf("%.1fx^%d", p->coef, p->expn);

        first = 0;
        p = p->next;
    }
    printf("\n");
}
