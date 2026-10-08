#include"plxu.h"
#include<stdio.h>
#include<stdlib.h>
//初始化一个顺序表
int InitList(SqList &L){
    L.length=0;
    return 1;
}
//顺序表插入操作
int ListInsert(SqList &L,int i,int e)
{
    if((i<1)||(i>L.length+1))return -1;
    if(L.length==MAX)return -1;
    for(int j=L.length;j>=i;j--){
        L.r[j+1]=L.r[j];
    }
    L.r[i].key=e;
    ++L.length;
    return 1;
}
// 3. 打印顺序表
void PrintList(SqList L) {
    for (int i = 1; i <= L.length; i++) {
        printf("%d ", L.r[i].key);
    }
    printf("\n");
}

// 4. 输入n个整数到顺序表
void InputList(SqList &L, int n) {
    InitList(L);
    printf("请输入%d个整数: ", n);
    for (int i = 0; i < n; i++) {
        int e;
        scanf("%d", &e);
        ListInsert(L, i + 1, e);
    }
}

// 5. 直接插入排序（升序）- 原函数
void InsertSort(SqList &L) {
    int i, j;
    for (i = 2; i <= L.length; i++) {  // 修改：应该是i <= L.length
        if (L.r[i].key < L.r[i - 1].key) {
            L.r[0] = L.r[i];
            for (j = i - 1; L.r[0].key < L.r[j].key; --j) {
                L.r[j + 1] = L.r[j];
            }
            L.r[j + 1] = L.r[0];
        }
    }
}

// 6. 直接插入排序（降序）
void InsertSortDesc(SqList &L) {
    int i, j;
    for (i = 2; i <= L.length; i++) {
        if (L.r[i].key > L.r[i - 1].key) {  // 修改比较符号
            L.r[0] = L.r[i];
            for (j = i - 1; j > 0 && L.r[0].key > L.r[j].key; --j) {
                L.r[j + 1] = L.r[j];
            }
            L.r[j + 1] = L.r[0];
        }
    }
}

// 7. 选择排序（升序）
void SelectSortAsc(SqList &L) {
    int i, j, min;
    for (i = 1; i < L.length; i++) {
        min = i;
        for (j = i + 1; j <= L.length; j++) {
            if (L.r[j].key < L.r[min].key) {
                min = j;
            }
        }
        if (min != i) {
            RedType temp = L.r[i];
            L.r[i] = L.r[min];
            L.r[min] = temp;
        }
    }
}

// 8. 冒泡排序（升序）
void BubbleSortAsc(SqList &L) {
    int i, j;
    for (i = 1; i < L.length; i++) {
        for (j = 1; j <= L.length - i; j++) {
            if (L.r[j].key > L.r[j + 1].key) {
                RedType temp = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = temp;
            }
        }
    }
}

// 9. 快速排序（降序）辅助函数
int PartitionDesc(SqList &L, int low, int high) {
    L.r[0] = L.r[low];
    while (low < high) {
        while (low < high && L.r[high].key <= L.r[0].key) high--;
        L.r[low] = L.r[high];
        while (low < high && L.r[low].key >= L.r[0].key) low++;
        L.r[high] = L.r[low];
    }
    L.r[low] = L.r[0];
    return low;
}

void QuickSortDescHelper(SqList &L, int low, int high) {
    if (low < high) {
        int pivot = PartitionDesc(L, low, high);
        QuickSortDescHelper(L, low, pivot - 1);
        QuickSortDescHelper(L, pivot + 1, high);
    }
}

void QuickSortDesc(SqList &L) {
    QuickSortDescHelper(L, 1, L.length);
}

// 10. 希尔排序（升序）
void ShellSortAsc(SqList &L) {
    int i, j, d;
    for (d = L.length / 2; d > 0; d /= 2) {
        for (i = d + 1; i <= L.length; i++) {
            if (L.r[i].key < L.r[i - d].key) {
                L.r[0] = L.r[i];
                for (j = i - d; j > 0 && L.r[0].key < L.r[j].key; j -= d) {
                    L.r[j + d] = L.r[j];
                }
                L.r[j + d] = L.r[0];
            }
        }
    }
}

// 11. 顺序查找
int SeqSearch(SqList L, int key) {
    int i;
    for (i = 1; i <= L.length; i++) {
        if (L.r[i].key == key) {
            return i;
        }
    }
    return -1;
}

// 12. 折半查找（要求表有序，升序）
int BinSearch(SqList L, int key) {
    int low = 1, high = L.length, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (key == L.r[mid].key) {
            return mid;
        } else if (key < L.r[mid].key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}
// 15. 选择排序算法
void ChooseSort(SqList &L) {
    int choice;
    printf("请选择排序算法:\n");
    printf("1.直接插入排序(升序)\n");
    printf("2.直接插入排序(降序)\n");
    printf("3.选择排序(升序)\n");
    printf("4.冒泡排序(升序)\n");
    printf("5.快速排序(降序)\n");
    printf("6.希尔排序(升序)\n");
    printf("请输入选择(1-6): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: InsertSort(L); break;
        case 2: InsertSortDesc(L); break;
        case 3: SelectSortAsc(L); break;
        case 4: BubbleSortAsc(L); break;
        case 5: QuickSortDesc(L); break;
        case 6: ShellSortAsc(L); break;
        default:
            printf("无效选择，使用默认插入排序(升序)\n");
            InsertSort(L);
            break;
    }
}

// 16. 选择查找算法
void ChooseSearch(SqList L) {
    int key, result;
    printf("请输入要查找的数: ");
    scanf("%d", &key);

    int choice;
    printf("请选择查找算法:\n");
    printf("1.顺序查找\n");
    printf("2.折半查找(要求表有序)\n");
    printf("请输入选择(1-2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            result = SeqSearch(L, key);
            break;
        case 2:
            result = BinSearch(L, key);
            break;
        default:
            printf("无效选择，使用顺序查找\n");
            result = SeqSearch(L, key);
            break;
    }

    if (result != -1) {
        printf("找到元素，下标为: %d\n", result);
    } else {
        printf("Not Found\n");
    }
}
