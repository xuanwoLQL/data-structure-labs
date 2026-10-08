#ifndef BI_TNODE_H_INCLUDED
#define BI_TNODE_H_INCLUDED
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef char TElemType;
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void CreatBiTree(BiTree &T);//创建二叉树
void xmxubmli(BiTree T);//先序遍历
void vsxubmli(BiTree T);//中序遍历
void hbxubmli(BiTree T);//后序遍历
//非递归中序遍历
void fzdigvvsxubmli();
//层序遍历
void cgxubmli(BiTree T);
//叶子节点个数
int NodeCount(BiTree T);
//二叉树深度
int eriauuufdu(BiTree T);
#endif // BI_TNODE_H_INCLUDED
