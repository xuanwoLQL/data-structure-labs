#ifndef SQ_STACK_H_INCLUDED
#define SQ_STACK_H_INCLUDED
//顺序栈
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef char SElemType;
typedef int NElemType;
//字符栈
typedef struct{
    SElemType *top;//栈顶指针
    SElemType *base;//栈底指针
    int stacksize;//栈可用的最大容量
}SqStack;
//整数栈
typedef struct{
    NElemType *top;
    NElemType *base;
    int stacksize;
}NStack;
//字符栈操作
int InitStack(SqStack &S);//顺序栈的初始化
int Push(SqStack &S,char e);//压栈
int Pop(SqStack &S,char &e);//出栈
char GetTop(SqStack S);//取栈顶元素
//整数栈操作
int InitNStack(NStack &S);
int Push_N(NStack &S,int e);
int Pop_N(NStack &S,int &e);
int GetTop_N(NStack S);
#endif // SQ_STACK_H_INCLUDED
