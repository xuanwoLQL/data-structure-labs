#include"set.h"
#include<stdio.h>
#include<stdlib.h>
#include"HT_Node.h"
void menu()
{
    printf("=====请输入你的选择=====\n");
    printf("1.创建哈夫曼树\n");
    printf("2.输出每个字符的哈夫曼编码\n");
    printf("3.计算哈夫曼树的带权路径长度\n");
    printf("0.退出操作\n");
    printf("========================\n");
}
void Wait()
{
    printf("按回车继续\n");
    getchar();
    getchar();
}
//创建哈夫曼树
void idjmhafumjuu()
{
    int n;
    printf("输入n值：");
    scanf("%d",&n);
    HuffmanTree HT;
    CreatHuffmanTree(HT,n);
    printf("此哈夫曼树终极状态为:\n");
    for(int i=1;i<=2*n-1;i++)
    {
        printf("%d %d %d %d",HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
        printf("\n");
    }
}
//输出每个字符的哈夫曼编码
void hafumjbmma()
{
    int n;
    printf("输入n值：");
    scanf("%d",&n);
    char zifu[n];//跟哈夫曼树相对应
    printf("连续输入字符(无空格)：");
    scanf("%s",zifu);
    HuffmanTree HT;
    HuffmanCode HC;
    CreatHuffmanTree(HT,n);
    for(int i=1;i<=n;i++){
        HT[i].data=zifu[i-1];//存储字符
    }
    CreatHuffmanCode(HT,HC,n);
    printf("每个字符的哈夫曼编码：\n");
    for(int i=1;i<=n;i++)
    {
        printf("%c:%s\n",HT[i].data,HC[i]);
    }
}
//计算哈夫曼树的带权路径长度
void dljrrujnihdu()
{
    int n;
    printf("输入n值：");
    scanf("%d",&n);
    HuffmanTree HT;
    CreatHuffmanTree(HT,n);
    rujnihdu(HT,n);
}
