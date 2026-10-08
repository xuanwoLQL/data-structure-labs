#include<stdio.h>
#include<stdlib.h>
#include"Sq_List.h"
//构建一个空的顺序表
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
//顺序表数位置的查找
int LocateElem(SqList &L,ElemType e)
{
    for(int i=0;i<L.length;i++)
    {
        if(L.elem[i]==e)return i+1;
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
//顺序表的删除
int ListDelete(SqList &L,int i)
{
    if(i<1||i>L.length)return ERROR;
    //1,2,3...i-1,i,i+1...n
    //0,1,2...i-2,i-1,i...n-1
    //1,2,3...i-1,i+1...n-1,n
    //0,1,2...i-2,i-1...n-2
    for(int j=i-1;j<=L.length-2;j++)
    {
        L.elem[j]=L.elem[j+1];
    }
    --L.length;
    return OK;
}
//线性表的合并
void HbList(SqList &La,SqList &Lb)
{
    ElemType e;//建立一个新的变量来为后面吸收Lb的值做准备
    int a=La.length;
    int b=Lb.length;
    for(int i=1;i<=b;i++)
    {
        GetElem(Lb,i,e);//取Lb第i个元素的值
        //查找这个值是否在La中存在
        //不存在就往后一位插入
        if(!LocateElem(La,e))
        {
            ListInset(La,++a,e);
        }
    }
}
//初始化多项式顺序表
int CshDxs(DxsSqList &L)
{
    L.elem=new DxsSxb[MAXSIZE];
    if(!L.elem)exit(OVERFLOW);
    L.length=0;
    return OK;
}
//多项式顺序表的插入
int DxsCr(DxsSqList &L,int i,DxsSxb e)
{
    if(i<1||i>L.length+1)return ERROR;
    if(L.length==MAXSIZE)return ERROR;
    for(int j=L.length-1;j>=i-1;j--)
    {
        L.elem[j+1]=L.elem[j];
    }
    L.elem[i-1]=e;
    ++L.length;
    return OK;
}
//多项式加法
void DxsJf(DxsSqList &A,DxsSqList &B)
{
    for(int i=0;i<B.length;i++)
    {
        DxsSxb b=B.elem[i];
        int z=0;//旗帜变量
        //看是否有相同的指数,找出后加一
        for(int j=0;j<A.length;j++)
        {
            if(A.elem[j].zhishu==b.zhishu)
            {
                A.elem[j].xishu+=b.xishu;
                z=1;
                break;
            }
        }
        //如果没有相同指数的项，就插入到末尾
        if(!z&&A.length<MAXSIZE)
        {
            A.elem[A.length]=b;
            A.length++;
        }
    }
}
