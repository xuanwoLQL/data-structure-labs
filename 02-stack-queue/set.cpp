#include"set.h"
#include<stdio.h>
#include<stdlib.h>
#include"Link_Stack.h"
#include"Bdsz.h"
#include"Sq_Queue.h"
void menu()
{
    printf("===请输入你想输入的操作===\n");
    printf("1.实现数制转换\n");
    printf("2.实现表达式的值(多位运算)\n");
    printf("3.实现舞伴配对\n");
    printf("4.舞伴配对升级版(用记事本录入)\n");
    printf("0.退出操作\n");
    printf("===请输入你的选择(0~4)===\n");
}
//实现数制转换
void Szzh()
{
    int choice,a,e;
    do{
        printf("请输入一个十进制数,-1结束操作:");
        scanf("%d",&a);
        if(a==-1)break;
        printf("请输入转换数制:");
        scanf("%d",&choice);
        LinkStack S;
        InitStack_L(S);
        while(a)
        {
            Push_L(S,a%choice);
            a=a/choice;
        }
        while(S->next!=NULL)
        {
            Pop_L(S,e);
            if(e<10)printf("%d",e);
            else printf("%c",'A'+(e-10));
        }
        printf("\n");
    }while(a!=-1);
}
void Bdsz()
{
    char ch;
    char theta;
    int a,b,result;
    SqStack OPTR;
    NStack OPND;
    InitNStack(OPND);
    InitStack(OPTR);
    Push(OPTR,'#');
    printf("请输入表达式(以#结束):");
    scanf(" %c",&ch);
    while(ch!='#'||GetTop(OPTR)!='#')
    {
        if(In(ch)==ERROR){
            int num=0;
            while(ch>='0'&&ch<='9'){
                num=num*10+(ch-'0');
                scanf("%c",&ch);
            }
            Push_N(OPND,num);
        }
        else{
            switch(Precede(GetTop(OPTR),ch))
            {
                case '<':
                    Push(OPTR,ch);
                    scanf(" %c",&ch);
                    break;
                case '>':
                    Pop(OPTR,theta);
                    Pop_N(OPND,b);
                    Pop_N(OPND,a);
                    Push_N(OPND,Operate(a,theta,b));
                    break;
                case '=':
                    Pop(OPTR,theta);
                    scanf(" %c",&ch);
                    break;
            }
        }
    }
    Pop_N(OPND,result);
    printf("表达式结果:%d\n",result);
}
void Wbpd()
{
    int num;
    printf("请输入跳舞的人数:");
    scanf("%d",&num);
    Person dancer[num];
    printf("请输入跳舞的人的姓名和性别(男M,女F)\n");
    for(int i=0;i<num;i++)
    {
        printf("请输入第%d个人",i+1);
        scanf("%s",dancer[i].name);
        scanf(" %c",&dancer[i].sex);
    }
    SqQueue Nan,Nv;//男，女
    InitQueue(Nan);
    InitQueue(Nv);
    for(int i=0;i<num;i++)
    {
        Person p;
        p=dancer[i];
        if(p.sex=='F'||p.sex=='f')EnQueue(Nv,p);
        else if (p.sex=='M'||p.sex=='m')EnQueue(Nan,p);
    }
    printf("配对搭档为:\n");
    while((QueueLength(Nan)!=0)&&(QueueLength(Nv)!=0))
    {
        Person p;
        DeQueue(Nv,p);
        printf("%s ",p.name);
        DeQueue(Nan,p);
        printf("%s",p.name);
        printf("\n");
    }
    if(QueueLength(Nv)!=0)
    {
        Person p;
        p=GetHead(Nv);
        printf("最后由%s女士没有搭档",p.name);
    }
    else if(QueueLength(Nan)!=0)
    {
        Person p;
        p=GetHead(Nan);
        printf("最后由%s男士没有搭档",p.name);
    }
    printf("\n");
}
void Wbpd2()
{
    FILE *file;
    int num;

    // 直接使用固定文件名
    file = fopen("dancer_data.txt", "r");
    if (file == NULL) {
        printf("无法打开文件 dancer_data.txt\n");
        printf("请确保文件存在且格式正确\n");
        printf("请在dancer_data.txt中输入\n");
        printf("舞者的姓名,性别(男M,女F)\n");
        printf("格式如：\n");
        printf("1\n");
        printf("李三 M\n");
        printf("并保存");
        return;
    }

    fscanf(file, "%d", &num);
    Person dancer[num];

    printf("从文件读取 %d 个人的数据...\n", num);

    for(int i = 0; i < num; i++)
    {
        fscanf(file, "%s %c", dancer[i].name, &dancer[i].sex);
    }

    fclose(file);

    SqQueue Nan,Nv;//男，女
    InitQueue(Nan);
    InitQueue(Nv);
    for(int i=0;i<num;i++)
    {
        Person p;
        p=dancer[i];
        if(p.sex=='F'||p.sex=='f')EnQueue(Nv,p);
        else if (p.sex=='M'||p.sex=='m')EnQueue(Nan,p);
    }
    printf("配对搭档为:\n");
    while((QueueLength(Nan)!=0)&&(QueueLength(Nv)!=0))
    {
        Person p;
        DeQueue(Nv,p);
        printf("%s ",p.name);
        DeQueue(Nan,p);
        printf("%s",p.name);
        printf("\n");
    }
    if(QueueLength(Nv)!=0)
    {
        Person p;
        p=GetHead(Nv);
        printf("最后由%s女士没有搭档",p.name);
    }
    else if(QueueLength(Nan)!=0)
    {
        Person p;
        p=GetHead(Nan);
        printf("最后由%s男士没有搭档",p.name);
    }
    printf("想更改,请在dancer_data.txt中修改输入\n");
}
void Wait()
{
    printf("按回车键继续\n");
    getchar();//清除所有残留字符
    getchar();
}
