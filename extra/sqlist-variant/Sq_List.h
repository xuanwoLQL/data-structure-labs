#ifndef SQ_LIST_H_INCLUDED
#define SQ_LIST_H_INCLUDED

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int ElemType;
//顺序表结构
typedef struct{
    ElemType *elem;
    int length;
}SqList;
//多项式数据项结构
typedef struct{
    float xishu;//多项式每项系数
    int zhishu;//多项式每项指数
}DxsSxb;
//多项式顺序表结构
typedef struct{
    DxsSxb *elem;
    int length;
}DxsSqList;
//顺序表初始化
int InitList(SqList &L);
//顺序表的取值
int GetElem(SqList &L,int i,ElemType &e);
//顺序表数据序号的查找
int LocateElem(SqList &L,ElemType e);
//顺序表的插入
int ListInset(SqList &l,int i,ElemType e);
//顺序表的删除
int ListDelete(SqList &l,int i);
//线性表合并操作
void HbList(SqList &La,SqList &Lb);
//初始化多项式顺序表
int CshDxs(DxsSqList &L);
//多项式顺序表的插入
int DxsCr(DxsSqList &L,int i,DxsSxb e);
//多项式加法
void DxsJf(DxsSqList &A,DxsSqList &B);
#endif // SQ_LIST_H_INCLUDED
