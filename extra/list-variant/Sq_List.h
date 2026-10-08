#ifndef SQ_LIST_H_INCLUDED
#define SQ_LIST_H_INCLUDED

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;

// 顺序表结构
typedef struct{
    ElemType *elem;
    int length;
}SqList;

// 多项式数据项结构
typedef struct {
    float coef; // 系数
    int expn;   // 指数
} PolyTerm;

// 多项式顺序表结构
typedef struct {
    PolyTerm *elem;
    int length;
} PolySqList;


// 顺序表基本操作
int InitList(SqList &L);
int GetElem(SqList &L, int i, ElemType &e);
int LocateElem(SqList &L, ElemType e);
int ListInset(SqList &L, int i, ElemType e);
int ListDelete(SqList &L, int i);

// 线性表合并函数
void UnionList(SqList &La, SqList Lb);

// 多项式顺序表操作
int InitPolyList(PolySqList &L);
int PolyListInsert(PolySqList &L, int i, PolyTerm e);
void AddPolynomials(PolySqList &A, PolySqList B);

#endif // SQ_LIST_H_INCLUDED
