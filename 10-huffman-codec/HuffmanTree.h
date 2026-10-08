#ifndef HUFFMANTREE_H_INCLUDED
#define HUFFMANTREE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============== 数据结构定义 ==============

// 哈夫曼树节点
typedef struct HTNode {
    int weight;           // 权值
    int parent;           // 父节点索引
    int lchild;           // 左孩子索引
    int rchild;           // 右孩子索引
    char data;            // 字符
    char* code;           // 哈夫曼编码
} HTNode, *HuffmanTree;

// 编码表
typedef char** HuffmanCode;

// 字符频率项
typedef struct {
    char ch;
    int freq;
} FreqItem;

// 字符频率表
typedef struct {
    FreqItem* items;
    int size;
    int capacity;
} FrequencyTable;

// 编码表项
typedef struct {
    char ch;
    char* code;
    int freq;
} CodeTableItem;

// 编码表
typedef struct {
    CodeTableItem* items;
    int size;
    int capacity;
} CodeTable;

// 性能指标
typedef struct {
    double encodingTime;
    double decodingTime;
    double treeBuildTime;
    size_t originalSize;
    size_t encodedSize;
    double compressionRatio;
} PerformanceMetrics;
//打印哈夫曼树
//内部使用的打印节点结构
typedef struct{
    int weight;
    int index;
    char data;
    int rank;
}PrintInfo;
// ============== 核心算法函数声明 ==============

// 选择最小权值节点
int HT_Select(HuffmanTree HT, int n, int* s1, int* s2);

// 构建哈夫曼树
void HT_BuildTree(HuffmanTree* HT, int n, int weights[]);

// 生成哈夫曼编码
void HT_GenerateCodes(HuffmanTree HT, HuffmanCode* HC, int n);

// 计算带权路径长度
int HT_CalculateWPL(HuffmanTree HT, int n);

// 打印哈夫曼树
void HT_PrintTree(HuffmanTree HT, int n);
void HT_PrintTreeGraphical(HuffmanTree HT,int n);//哈夫曼树图形打印

// 保存哈夫曼树到文件
void HT_SaveToFile(HuffmanTree HT, int n, const char* filename);

// ============== 频率统计函数 ==============

// 创建频率表
FrequencyTable* HT_CreateFrequencyTable();

// 统计字符频率
FrequencyTable* HT_CountFrequency(const char* text, size_t length);

// 打印频率表
void HT_PrintFrequencyTable(FrequencyTable* table);

// 释放频率表
void HT_FreeFrequencyTable(FrequencyTable* table);

// ============== 编码表函数 ==============

// 构建编码表
CodeTable* HT_BuildCodeTable(HuffmanTree HT, int n);

// 打印编码表
void HT_PrintCodeTable(CodeTable* table);

// 保存编码表到文件
void HT_SaveCodeTable(CodeTable* table, const char* filename);

// 墮秘園鷹燕↙仟奐⇄
CodeTable* HT_LoadCodeTable(const char* filename);

// 旋喘隠贋園鷹燕園鷹↙仟奐⇄
char* HT_EncodeTextWithSavedTable(const char* text, const char* codeTableFile);


// 释放编码表
void HT_FreeCodeTable(CodeTable* table);

// ============== 编码/译码函数 ==============

// 编码文本
char* HT_EncodeText(const char* text, CodeTable* table);

// 译码文本
char* HT_DecodeText(const char* encoded, HuffmanTree HT, int n);
//加密//
char* HT_EncryptText(const char* text, const char* key);
char* HT_DecryptText(const char* encryptedText, const char* key);

// ============== 性能分析函数 ==============

// 初始化性能指标
void PM_Init(PerformanceMetrics* metrics);

// 计算压缩比
void PM_CalculateRatio(PerformanceMetrics* metrics,
                      size_t originalBits, size_t encodedBits);

// 打印性能报告
void PM_PrintReport(PerformanceMetrics* metrics);

// 保存性能报告
void PM_SaveReport(PerformanceMetrics* metrics, const char* filename);

// ============== 工具函数 ==============

// 读取文本文件
char* HT_ReadTextFile(const char* filename, size_t* length);

// 保存文本到文件
int HT_SaveTextFile(const char* filename, const char* content);

// 保存编码文本（格式化为每行固定宽度）
void HT_SaveEncodedText(const char* encoded, const char* filename, int lineWidth);
// HuffmanTree.h
void HT_FreeTree(HuffmanTree HT);


#endif // HUFFMANTREE_H_INCLUDED
