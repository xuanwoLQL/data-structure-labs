#include<stdio.h>
#include<stdlib.h>
#include"set.h"
#include"Bi_TNode.h"
BiTree T=NULL;
//页面清屏功能
void Wait()
{
    printf("按回车键继续..");
    getchar();
    getchar();
}
//主菜单
void menu()
{
    printf("=====请输入你的选择:0~4=====\n");
    printf("1.创建二叉树\n");
    printf("2.遍历二叉树\n");
    printf("3.求二叉树的深度\n");
    printf("4.求二叉树叶子节点的个数\n");
    printf("0.退出操作\n");
    printf("============================\n");
}
//遍历二叉树子菜单
void menu2()
{
    printf("=====请输入你的选择=====\n");
    printf("1.递归遍历,依次输出先序、中序、后序遍历\n");
    printf("2.非递归中序遍历\n");
    printf("3.层序遍历\n");
    printf("0.退出操作\n");
    printf("========================\n");
}
//创建二叉树
void idjmeriauu()
{
    printf("请依次输入字符建立二叉树:\n");
    printf("注意：最后以'.'结束\n");
    CreatBiTree(T);
    printf("二叉树创建成功\n");
    printf("先序遍历依次输出为:\n");
    xmxubmli(T);
}
//遍历二叉树主框架
void bmlieriauu()
{
    if(T==NULL){
        printf("请先创立二叉树!\n");
        return;
    }
    int choice;
    do{
        system("cls");
        menu2();
        scanf("%d",&choice);
        system("cls");
        switch(choice)
        {
            //递归遍历
            case 1:digvbmli();break;
            //非递归中序遍历
            case 2:fzdigvvsxubmli();break;
            //层序遍历
            case 3:cgxubmli1();break;
            case 0:printf("谢谢操作\n");break;
            default:
                printf("输入错误，请重新输入");
        }
        if(choice!=0){Wait();}
    }while(choice!=0);
}
//递归遍历
void digvbmli()
{
    if(T==NULL){
        printf("请先创立二叉树!\n");
        return;
    }
    printf("先序遍历输出为:");
    xmxubmli(T);
    printf("\n");
    printf("中序遍历结果为:");
    vsxubmli(T);
    printf("\n");
    printf("后序遍历结果为:");
    hbxubmli(T);
}
//层序遍历
void cgxubmli1()
{
    if(T==NULL){
        printf("请先创立二叉树!\n");
        return;
    }
    printf("层序遍历结果为:\n");
    cgxubmli(T);
    printf("\n");
}
void eriauuufdu1()
{
    if(T==NULL){
        printf("请先创立二叉树!\n");
        return;
    }
    printf("二叉树深度为:%d",eriauuufdu(T));
    printf("\n");
}
//叶子节点个数
void yezijxdmgeuu()
{
    if(T==NULL){
        printf("请先创立二叉树!\n");
        return;
    }
    printf("叶子节点的个数为：%d",NodeCount(T));
    printf("\n");
}
