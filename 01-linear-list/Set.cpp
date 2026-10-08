#include<stdio.h>
#include<stdlib.h>
#include"Set.h"
#include"Sq_List.h"
void Menu()
{
    printf("*****欢迎使用以下功能*****\n");
    printf("1:线性表合并\n");
    printf("2:有序表合并\n");
    printf("3:稀疏多项式加法(顺序表)\n");
    printf("4:稀疏多项式减法(单链表)\n");
    printf("0:退出\n");
    printf("请输入数据类型:");
}
void ShuruHuiche()
{
    printf("\n按回车键继续");
    getchar();
    getchar();//读取回车键
}
//打印集合操作
void DySxb(SqList L)
{
    printf("(");
    for(int i=0;i<L.length;i++)
    {
        printf("%d",L.elem[i]);
        if(i<L.length-1){printf(",");}
    }
    printf(")\n");
}
//打印有序表集合操作
void DyYxb(LinkList L)
{
    LinkList p=L->next;
    printf("(");
    while(p)
    {
        printf("%d",p->data);
        p=p->next;
        if(p)printf(",");
    }
    printf(")\n");
}
//打印多项式
void DyDxs(DxsSqList L)
{
    for(int i=0;i<L.length;i++)
    {
        if(L.elem[i].zhishu==0)
        {
            printf("%.1f",L.elem[i].xishu);
        }
        else if(L.elem[i].zhishu==1){printf("%.1fx",L.elem[i].xishu);}
        else{
            printf("%.1fx^%d",L.elem[i].xishu,L.elem[i].zhishu);
        }
        if(i<L.length-1){printf("+");}
    }
    printf("\n");
}
//打印单链表多项式
void DyDxs_L(DxsDlb L)
{
    DxsDlb p=L->next;
    if(!p){
        printf("0\n");
        return;
    }
    int z=1;
    while(p){
        if((p->xishu>0)&&!z){printf("+");}
        if(p->zhishu==0){printf("%.1f",p->xishu);}
        else if(p->zhishu==1){printf("%.1fx",p->xishu);}
        else{printf("%.1fx^%d",p->xishu,p->zhishu);}
        z=0;
        p=p->next;
    }
    printf("\n");
}
//线性合并
void Xxhb()
{
    printf("===线性表合并===\n");
    //建立两个需要合并的空顺序表并初始化
    SqList La,Lb;
    InitList(La);
    InitList(Lb);
    int n,m,z=0;
    printf("请输入A集合元素的个数n:");
    scanf("%d",&n);
    printf("请输入A集合中的n个数据(每个数据空格分开):");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&m);
        int k=ListInset(La,i+1,m);
        if(k==OK){z++;}
    }
    if(z==n){printf("A集合输入成功");}
    int x,l,j=0;
    printf("\n请输入B集合元素的个数x:");
    scanf("%d",&x);
    printf("请输入B集合中的x个数据(每个数据空格分开):");
    for(int i=0;i<x;i++)
    {
        scanf("%d",&l);
        int p=ListInset(Lb,i+1,l);
        if(p==OK){j++;}
    }
    if(j==x){printf("B集合输入成功");}
    printf("合并前：\n");
    printf("集合A=");
    DySxb(La);
    printf("集合B=");
    DySxb(Lb);
    HbList(La,Lb);
    printf("合并后:\n");
    printf("A U B=");
    DySxb(La);
}
//有序表合并
void Yxhb()
{
    printf("===有序表合并===\n");
    LinkList La,Lb,Lc;
    InitList_L(La);
    InitList_L(Lb);
    int n,m,z=0;
    printf("请输入有序表A元素的个数n:");
    scanf("%d",&n);
    printf("请输入有序表A的n个数据(每个数用空格隔开):");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&m);
        int k=ListInset_L(La,i+1,m);
        if(k==OK){z++;}
    }
    if(z==n){printf("有序表A输入成功");}
    int x,l,j=0;
    printf("\n请输入B集合元素的个数x:");
    scanf("%d",&x);
    printf("请输入B集合中的x个数据(每个数据空格分开):");
    for(int i=0;i<x;i++)
    {
        scanf("%d",&l);
        int p=ListInset_L(Lb,i+1,l);
        if(p==OK){j++;}
    }
    if(j==x){printf("B集合输入成功");}
    printf("合并前:\n");
    printf("有序表A=");
    DyYxb(La);
    printf("有序表B=");
    DyYxb(Lb);
    InitList_L(Lc);
    HbYxb(La,Lb,Lc);
    printf("C=A U B=");
    DyYxb(Lc);
}
//稀疏多项式加法
void Dxsjiafa()
{
    printf("===稀疏多项式加法===\n");
    DxsSqList A,B;
    CshDxs(A);
    CshDxs(B);
    int n,z=0;
    printf("请输入多项式A(x)项的个数n:");
    scanf("%d",&n);
    printf("请输入多项式A(x)每项的数据\n");
    for(int i=0;i<n;i++)
    {
        DxsSxb m;
        printf("第%d项的系数:",i+1);
        scanf("%f",&m.xishu);
        printf("第%d项的指数:",i+1);
        scanf("%d",&m.zhishu);
        int k=DxsCr(A,i+1,m);
        if(k==OK){z++;}
    }
    if(z==n){printf("多项式A(x)输入成功");}
    int x,j=0;
    printf("\n请输入多项式B(x)项的个数x:");
    scanf("%d",&x);
    printf("请输入多项式B(x)每项的数据\n");
    for(int i=0;i<x;i++)
    {
        DxsSxb l;
        printf("第%d项的系数:",i+1);
        scanf("%f",&l.xishu);
        printf("第%d项的指数:",i+1);
        scanf("%d",&l.zhishu);
        int p=DxsCr(B,i+1,l);
        if(p==OK){j++;}
    }
    if(j==x){printf("多项式B(x)输入成功");}
    printf("\n多项式A(x)=");
    DyDxs(A);
    printf("多项式B(x)=");
    DyDxs(B);
    DxsJf(A,B);
    printf("A(x)+B(x)=");
    DyDxs(A);
}
//稀疏多项式减法
void Dxsjianfa()
{
    printf("===稀疏多项式减法===\n");
    DxsDlb A,B;
    A=new Dxs;
    A->next=NULL;
    B=new Dxs;
    B->next=NULL;
    int n,m;
    printf("请输入多项式A(x)项的个数:");
    scanf("%d",&n);
    CjDxs(A,n);
    printf("请输入多项式B(x)项的个数:");
    scanf("%d",&m);
    CjDxs(B,m);
    printf("多项式A(x)=");
    DyDxs_L(A);
    printf("多项式B(x)=");
    DyDxs_L(B);
    DxsJf_L(A,B);
    printf("A(x)-B(x)=");
    DyDxs_L(A);
    //释放内存
    FreePolynomial(A);
    FreePolynomial(B);
}
