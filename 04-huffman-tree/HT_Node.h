#ifndef HT_NODE_H_INCLUDED
#define HT_NODE_H_INCLUDED
typedef struct{
    int weight;
    int parent,lchild,rchild;
    char data;//输入字符功能
}HTNode,*HuffmanTree;
//在HT[k](1<=k<=i-1)中选择两个其双亲域为0且权值最低的节点
//并返回它们在HT中的序号s1和s2.
int Select(HuffmanTree HT,int n,int &s1,int &s2);
void CreatHuffmanTree(HuffmanTree &HT,int n);//构造哈夫曼树

//哈夫曼编码
typedef char **HuffmanCode;//动态分配数组存储哈夫曼编码表
void CreatHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n);//创造哈夫曼编码
void rujnihdu(HuffmanTree HT,int n);//哈夫曼树的带权路径长度
#endif // HT_NODE_H_INCLUDED
