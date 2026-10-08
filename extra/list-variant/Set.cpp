#include<stdio.h>
#include<stdlib.h>
#include"Set.h"
void WaitForEnter()
{
    printf("\n按Enter键继续...");
    getchar();
    getchar(); // 读取回车键
}

void PrintList(SqList L)
{
    printf("(");
    for(int i = 0; i < L.length; i++)
    {
        printf("%d", L.elem[i]);
        if(i < L.length - 1)
            printf(",");
    }
    printf(")\n");
}

void PrintLinkList(LinkList L)
{
    LinkList p = L->next;
    printf("(");
    while(p)
    {
        printf("%d", p->data);
        p = p->next;
        if(p) printf(",");
    }
    printf(")\n");
}

void PrintPolyList(PolySqList L)
{
    for(int i = 0; i < L.length; i++)
    {
        if(L.elem[i].expn == 0)
            printf("%.1f", L.elem[i].coef);
        else if(L.elem[i].expn == 1)
            printf("%.1fx", L.elem[i].coef);
        else
            printf("%.1fx^%d", L.elem[i].coef, L.elem[i].expn);

        if(i < L.length - 1)
            printf(" + ");
    }
    printf("\n");
}

void Menu()
{
    printf("*****欢迎使用以下功能*****\n");
    printf("1：线性表合并\n");
    printf("2：有序表合并\n");
    printf("3：稀疏多项式加法（顺序表）\n");
    printf("4：稀疏多项式减法（单链表）\n");
    printf("0：退出\n");
    printf("请选择功能：");
}

void Function1()
{
    printf("\n=== 线性表合并 ===\n");

    SqList La, Lb;
    InitList(La);
    InitList(Lb);

    // 初始化集合A=(7,5,3,11)
    ListInset(La, 1, 7);
    ListInset(La, 2, 5);
    ListInset(La, 3, 3);
    ListInset(La, 4, 11);

    // 初始化集合B=(2,6,3)
    ListInset(Lb, 1, 2);
    ListInset(Lb, 2, 6);
    ListInset(Lb, 3, 3);

    printf("合并前:\n");
    printf("集合A = ");
    PrintList(La);
    printf("集合B = ");
    PrintList(Lb);

    UnionList(La, Lb);

    printf("合并后:\n");
    printf("A ∪ B = ");
    PrintList(La);
}

void Function2()
{
    printf("\n=== 有序表合并 ===\n");

    LinkList La, Lb, Lc;
    InitList_L(La);
    InitList_L(Lb);

    // 初始化有序表A=(3,5,8,11)
    ListInsert_L(La, 1, 3);
    ListInsert_L(La, 2, 5);
    ListInsert_L(La, 3, 8);
    ListInsert_L(La, 4, 11);

    // 初始化有序表B=(2,6,8,9,11,11,15,20)
    ListInsert_L(Lb, 1, 2);
    ListInsert_L(Lb, 2, 6);
    ListInsert_L(Lb, 3, 8);
    ListInsert_L(Lb, 4, 9);
    ListInsert_L(Lb, 5, 11);
    ListInsert_L(Lb, 6, 11);
    ListInsert_L(Lb, 7, 15);
    ListInsert_L(Lb, 8, 20);

    printf("合并前:\n");
    printf("有序表A = ");
    PrintLinkList(La);
    printf("有序表B = ");
    PrintLinkList(Lb);

    InitList_L(Lc);
    MergeList_L(La, Lb, Lc);

    printf("合并后:\n");
    printf("C = A ∪ B = ");
    PrintLinkList(Lc);
}

void Function3()
{
    printf("\n=== 稀疏多项式加法 ===\n");

    PolySqList A, B;
    InitPolyList(A);
    InitPolyList(B);

    // 初始化多项式A(x)=7+3x+9x^8+5x^17
    PolyTerm term;
    term.coef = 7; term.expn = 0;
    PolyListInsert(A, 1, term);
    term.coef = 3; term.expn = 1;
    PolyListInsert(A, 2, term);
    term.coef = 9; term.expn = 8;
    PolyListInsert(A, 3, term);
    term.coef = 5; term.expn = 17;
    PolyListInsert(A, 4, term);

    // 初始化多项式B(x)=8x+22x^7-9x^8
    term.coef = 8; term.expn = 1;
    PolyListInsert(B, 1, term);
    term.coef = 22; term.expn = 7;
    PolyListInsert(B, 2, term);
    term.coef = -9; term.expn = 8;
    PolyListInsert(B, 3, term);

    printf("多项式A(x) = ");
    PrintPolyList(A);
    printf("多项式B(x) = ");
    PrintPolyList(B);

    AddPolynomials(A, B);

    printf("A(x) + B(x) = ");
    PrintPolyList(A);
}

void Function4()
{
    printf("\n=== 稀疏多项式减法 ===\n");

    Polynomial A, B;

    // 使用预定义数据
    A = new PNode;
    A->next = NULL;

    // 创建多项式A(x)=x+5x^4+8x^10
    Polynomial s1 = new PNode;
    s1->coef = 1; s1->expn = 1;
    s1->next = A->next;
    A->next = s1;

    Polynomial s2 = new PNode;
    s2->coef = 5; s2->expn = 4;
    s2->next = A->next;
    A->next = s2;

    Polynomial s3 = new PNode;
    s3->coef = 8; s3->expn = 10;
    s3->next = A->next;
    A->next = s3;

    // 创建多项式B(x)=8x+3x^4+2x^7-9x^10
    B = new PNode;
    B->next = NULL;

    Polynomial s4 = new PNode;
    s4->coef = 8; s4->expn = 1;
    s4->next = B->next;
    B->next = s4;

    Polynomial s5 = new PNode;
    s5->coef = 3; s5->expn = 4;
    s5->next = B->next;
    B->next = s5;

    Polynomial s6 = new PNode;
    s6->coef = 2; s6->expn = 7;
    s6->next = B->next;
    B->next = s6;

    Polynomial s7 = new PNode;
    s7->coef = -9; s7->expn = 10;
    s7->next = B->next;
    B->next = s7;

    printf("多项式A(x) = ");
    PrintPolynomial(A);
    printf("多项式B(x) = ");
    PrintPolynomial(B);

    SubtractPolynomials(A, B);

    printf("A(x) - B(x) = ");
    PrintPolynomial(A);
}
