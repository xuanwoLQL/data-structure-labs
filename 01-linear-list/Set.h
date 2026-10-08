#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include"Sq_List.h"
#include"Link_List.h"
void Menu();//最开始页面
void ShuruHuiche();//页面每次刷新时所需按键
void Xxhb();//线性表合并
void Yxhb();//有序表合并
void Dxsjiafa();//稀疏多项式加法
void Dxsjianfa();//稀疏多项式减法
void DySxb(SqList L);//打印顺序表的集合
void DyYxb(LinkList L);//打印有序表的集合操作
void DyDxs(DxsSqList L);//打印多项式
void DyDxs_L(DxsDlb L);//打印单链表多项式
#endif // SET_H_INCLUDED
