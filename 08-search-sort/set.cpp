#include<stdio.h>
#include<stdlib.h>
#include"set.h"
#include"plxu.h"
void menu(){
    printf("=====请输入你的选择=====\n");
    printf("1.输入n个整数，可排序可查找\n");
    printf("2.输出排序后的书籍信息\n");
    printf("0.退出操作\n");
    printf("========================\n");
}
void wait(){
    printf("按回车继续\n");
    getchar();
    getchar();
}
//可进行排序和查找算法
void plxuiavk(){
    int n;
    printf("请输入n(1<n<=10): ");
    scanf("%d", &n);

    if (n <= 1 || n > 10) {
        printf("n必须在1到10之间\n");
        return;
    }

    SqList L;
    InputList(L, n);

    printf("排序前: ");
    PrintList(L);

    ChooseSort(L);

    printf("排序后: ");
    PrintList(L);

    ChooseSearch(L);
}
//按单价从小到大排序并输出排序后的书籍信息
void uujixnxi(){
    int n;
    printf("请输入书籍数量n(n<10): ");
    scanf("%d", &n);
    getchar();  // 读取换行符

    if (n <= 0 || n >= 10) {
        printf("n必须在1到9之间\n");
        return;
    }

    Book books[10];

    // 输入书籍信息
    for (int i = 0; i < n; i++) {
        printf("请输入第%d本书的书名: ", i + 1);
        fgets(books[i].name, 50, stdin);
        books[i].name[strcspn(books[i].name, "\n")] = 0;  // 去除换行符

        printf("请输入第%d本书的单价: ", i + 1);
        scanf("%f", &books[i].price);
        getchar();  // 读取换行符
    }

    // 使用选择排序按单价从小到大排序
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (books[j].price < books[min].price) {
                min = j;
            }
        }
        if (min != i) {
            Book temp = books[i];
            books[i] = books[min];
            books[min] = temp;
        }
    }

    // 输出排序结果
    printf("\n排序后的书籍信息:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %.1f\n", books[i].name, books[i].price);
    }
}
