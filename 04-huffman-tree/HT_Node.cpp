#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"HT_Node.h"
//选择最小的两个权值
int Select(HuffmanTree HT,int n,int &s1,int &s2)
{
    //初始化最小值和次小值的索引
    int a=-1,b=-1;
    //遍历所有的节点找到最小的两个
    for(int i=1;i<=n;i++)
    {
        if(HT[i].parent==0)
        {
            if(a==-1||HT[i].weight<HT[a].weight)
            {
                b=a;
                a=i;
            }
            else if(b==-1||HT[i].weight<HT[b].weight)
            {
                b=i;
            }
        }
    }
    if(a==-1||b==-1){
        return -1;
    }
    if(HT[a].weight>HT[b].weight)
    {
        int temp=a;
        a=b;
        b=temp;
    }
    //将结果赋值给s1和s2
    s1=a;
    s2=b;
    return 0;
}
//创建哈夫曼树
void CreatHuffmanTree(HuffmanTree &HT,int n)
{
    //HT的初始状态
    if(n<=1)return;
    int m=2*n-1;
    HT=new HTNode[m+1];//0号单元未使用，所以需要动态分配m+1个单元，HT[m]表示根节点
    for(int i=1;i<=m;i++){
        //将1~m号单元中的双亲、左孩子，右孩子的下标初始化为0
        HT[i].parent=0;HT[i].lchild=0;HT[i].rchild=0;
    }
    printf("输入节点权重值(空格隔开)：");
    for(int i=1;i<=n;i++){
        scanf("%d",&HT[i].weight);}
    //初始化结束，下面开始创建哈夫曼树
    for(int i=n+1;i<=m;i++)
    {
        int s1,s2;
        if(Select(HT,i-1,s1,s2)==0)
        {
            HT[s1].parent=i;
            HT[s2].parent=i;
            //得到新节点i,从森林中删除s1,s2,将s1和s2的双亲域由0改为i
            HT[i].lchild=s1;HT[i].rchild=s2;
            HT[i].weight=HT[s1].weight+HT[s2].weight;
        }
    }
    printf("哈夫曼树构造成功\n");

}
void CreatHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n)
{
    //从叶子到跟逆向求每个字符的哈夫曼编码，存储在编码表中
    HC= new char*[n+1];
    char *cd=new char[n];
    cd[n-1]='\0';//编码结束符
    for(int i=1;i<=n;i++)
    {
        int start=n-1;
        int c=i;
        int f=HT[i].parent;
        while(f!=0)
        {
            --start;//回溯一次start向前指一个位置
            if(HT[f].lchild==c)cd[start]='0';//节点c是f的左孩子，则生成代码0
            else cd[start]='1';
            c=f;f=HT[f].parent;//继续上个回溯
        }
        HC[i]=new char[n-start];
        //用string.h来使用
        strcpy(HC[i],&cd[start]);//将求得的编码从临时空间cd复制到HC的当前行中
    }
    delete cd;
}
//带权路径长度
void rujnihdu(HuffmanTree HT,int n)
{
    if(HT==NULL){
        printf("请先创建哈夫曼树!\n");
        return;
    }
    int m=0;//带权初始值
    for(int i=1;i<=n;i++)
    {
        int ugdu=0;//初始深度
        int j=i;
        while(HT[j].parent!=0){
            ugdu++;
            j=HT[j].parent;
        }
        m+=HT[i].weight*ugdu;//计算带权值
    }
    printf("WPL=%d\n",m);
}
