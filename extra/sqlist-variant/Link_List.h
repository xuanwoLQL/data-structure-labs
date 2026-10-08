#ifndef LINK_LIST_H_INCLUDED
#define LINK_LIST_H_INCLUDED
#include"Sq_List.h"
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
//多项式单链表结构
typedef struct Dxs{
    float xishu;
    int zhishu;
    struct Dxs *next;
}Dxs,*DxsDlb;
int InitList_L(LinkList &L);//单链表的初始化
int GetElem_L(LinkList L,int i,ElemType &e);//单链表的取值
LNode *LocateElem_L(LinkList L,ElemType e);//单链表的查找
int ListInset_L(LinkList &L,int i,ElemType e);//单链表的插入
int ListDelete_l(LinkList &L,int i);//单链表的删除
void HbYxb(LinkList La,LinkList Lb,LinkList &Lc);//合并有序表
void CjDxs(DxsDlb &L,int n);//创建多项式
void DxsJf_L(DxsDlb &A,DxsDlb &B);//多项式减法
void FreePolynomial(DxsDlb &P);//释放内存操作
#endif // LINK_LIST_H_INCLUDED
