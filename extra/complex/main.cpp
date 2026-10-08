#include <iostream>
#include<stdio.h>
using namespace std;
//结构体定义
typedef struct{
    float shibu;//实部
    float xubu;//虚部
}complex;
//函数声明
void Creat(complex &C,float x,float y);
complex add(complex C1,complex C2);
complex sub(complex C1,complex C2);
float GetReal(complex C);
float Getlmag(complex C);
void PrintComplex(complex C);
int main()
{
    complex C1,C2,sum,chazhi;
    Creat(C1,1.0,2.0);
    Creat(C2,2.0,3.0);
    GetReal(C1);Getlmag(C1);
    GetReal(C2);Getlmag(C2);
    sum=add(C1,C2);
    chazhi=sub(C1,C2);
    PrintComplex(sum);
    printf("\n");
    PrintComplex(chazhi);
    return 0;
}
//函数定义
void Creat(complex &C,float x,float y)
{
    C.shibu=x;
    C.xubu=y;
}
float GetReal(complex C)
{
    return C.shibu;
}
float Getlmag(complex C)
{
    return C.xubu;
}
complex add(complex C1,complex C2)
{
    complex sum;
    sum.shibu=C1.shibu+C2.shibu;
    sum.xubu=C1.xubu+C2.xubu;
    return sum;
}
complex sub(complex C1,complex C2)
{
    complex chazhi;
    chazhi.shibu=C1.shibu-C2.shibu;
    chazhi.xubu=C1.xubu-C2.xubu;
    return chazhi;
}
void PrintComplex(complex C)
{
    printf("%.2f+i*(%.2f)",C.shibu,C.xubu);
}
