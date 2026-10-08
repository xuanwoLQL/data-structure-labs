#ifndef LINK_LIST_H_INCLUDED
#define LINK_LIST_H_INCLUDED
#include<stdio.h>
#include"Sq_List.h"

// 单链表结点结构
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

// 多项式单链表结点结构
typedef struct PNode {
    float coef; // 系数
    int expn;   // 指数
    struct PNode *next;
} PNode, *Polynomial;
// 单链表操作
int InitList_L(LinkList &L);
int ListInsert_L(LinkList &L, int i, ElemType e);
void MergeList_L(LinkList La, LinkList Lb, LinkList &Lc);

// 多项式单链表操作
void CreatePolyn(Polynomial &P, int n);
void SubtractPolynomials(Polynomial &A, Polynomial B);
void PrintPolynomial(Polynomial P);

#endif // LINK_LIST_H_INCLUDED
