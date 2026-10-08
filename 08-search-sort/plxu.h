#ifndef PLXU_H_INCLUDED
#define PLXU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20  // 定义顺序表最大存储长度

typedef int KeyType;

typedef struct {
    KeyType key;  // 关键字项
} RedType;        // 记录类型

typedef struct {
    RedType r[MAX + 1];  // r[0]闲置用作哨兵单元
    int length;
} SqList;  // 顺序表存储

// 书籍结构体定义
typedef struct {
    char name[50];  // 书名
    float price;    // 单价
} Book;

// 顺序表基本操作
int InitList(SqList &L);// 初始化顺序表
int ListInsert(SqList &L, int i, int e);// 顺序表插入操作
void PrintList(SqList L);// 打印顺序表
void InputList(SqList &L, int n);// 输入n个整数到顺序表

// 排序算法
void InsertSortAsc(SqList &L);// 直接插入排序（升序）- 原函数
void InsertSortDesc(SqList &L);// 直接插入排序（降序）
void SelectSortAsc(SqList &L);// 选择排序（升序）
void BubbleSortAsc(SqList &L);// 冒泡排序（升序）
void QuickSortDesc(SqList &L);// 快速排序（降序）
void ShellSortAsc(SqList &L);// 希尔排序（升序）

// 查找算法
int SeqSearch(SqList L, int key);// 顺序查找
int BinSearch(SqList L, int key);// 折半查找
void ChooseSearch(SqList L);//对排序算法和查找算法的应用
void ChooseSort(SqList &L);
#endif // PLXU_H_INCLUDED
