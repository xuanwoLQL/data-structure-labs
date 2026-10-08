#include<stdio.h>
#include<stdlib.h>
#include"Sq_List.h"
//构造一个空的顺序表L
int InitList(SqList &L)
{
    L.elem=new ElemType[MAXSIZE];
    if(!L.elem) exit(OVERFLOW);
    L.length=0;
    return OK;
}
//顺序表的取值
int GetElem(SqList &L,int i,ElemType &e)
{
    if(i<1||i>L.length)return ERROR;
    e=L.elem[i-1];
    return OK;
}
//顺序表的查找
int LocateElem(SqList &L,ElemType e)
{
    for(int i=0;i<L.length;i++)
    {
        if(L.elem[i]==e) return i+1;
    }
    return 0;
}
//顺序表的插入
int ListInset(SqList &L,int i,ElemType e)
{
    if(i<1||i>L.length+1)return ERROR;
    if(L.length==MAXSIZE)return ERROR;
    //1,2,3...i-1,i,i+1...n
    //0,1,2...i-2,i-1,i...n-1
    //1,2,3...i-1,e,i,i+1...n
    //0,1,2...i-2,i-1,i...n-1,n
    for(int j=L.length-1;j>=i-1;j--)
    {
        L.elem[j+1]=L.elem[j];
    }
    L.elem[i-1]=e;
    ++L.length;
    return OK;
}
//顺序表元素的删除
int ListDelete(SqList &L,int i)
{
    if(i<1||i>L.length) return ERROR;
    //1,2,3...i-1,i,i+1...n
    //0,1,2...i-2,i-1,i...n-1
    //1,2,3...i-1,i+1,..n-1,n
    //0,1,2...i-2,i-1,i..n-2
    for(int j=i-1;j<=L.length-2;j++)
    {
        L.elem[j]=L.elem[j+1];
    }
    --L.length;
    return OK;
}
//线性表的合并
void UnionList(SqList &La, SqList Lb)
{
    ElemType e;
    int La_len = La.length;
    int Lb_len = Lb.length;

    for(int i = 1; i <= Lb_len; i++)
    {
        GetElem(Lb, i, e);
        if(!LocateElem(La, e))
        {
            ListInset(La, ++La_len, e);
        }
    }
}
// 初始化多项式顺序表
int InitPolyList(PolySqList &L)
{
    L.elem = new PolyTerm[MAXSIZE];
    if(!L.elem) exit(OVERFLOW);
    L.length = 0;
    return OK;
}

// 多项式顺序表插入
int PolyListInsert(PolySqList &L, int i, PolyTerm e)
{
    if(i < 1 || i > L.length + 1) return ERROR;
    if(L.length == MAXSIZE) return ERROR;

    for(int j = L.length - 1; j >= i - 1; j--)
    {
        L.elem[j+1] = L.elem[j];
    }
    L.elem[i-1] = e;
    ++L.length;
    return OK;
}

// 多项式加法
void AddPolynomials(PolySqList &A, PolySqList B)
{
    for(int i = 0; i < B.length; i++)
    {
        PolyTerm term = B.elem[i];
        int found = 0;

        // 查找是否有相同指数的项
        for(int j = 0; j < A.length; j++)
        {
            if(A.elem[j].expn == term.expn)
            {
                A.elem[j].coef += term.coef;
                found = 1;
                break;
            }
        }

        // 如果没有相同指数的项，则插入新项
        if(!found && A.length < MAXSIZE)
        {
            A.elem[A.length] = term;
            A.length++;
        }
    }
}



