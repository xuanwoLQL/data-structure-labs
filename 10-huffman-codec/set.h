#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED
#include <stddef.h>

// 在set.h中添加
typedef struct {
    unsigned char bytes[4];  // UTF-8字节序列
    int length;              // 字节长度
    char* gbk_char;          // 转换后的GBK字符（显示用）
    int freq;                // 频率
} ChineseCharItem;

typedef struct {
    ChineseCharItem* items;
    int size;
    int capacity;
} ChineseCharTable;
// 系统全局数据结构
typedef struct {
    // 哈夫曼树相关
    void* huffmanTree;
    void* frequencyTable;
    void* codeTable;

    // 文本数据
    char* originalText;
    char* encodedText;
    char* decodedText;
    size_t originalLength;  // 已经正确声明
    int charCount;

    // 性能指标
    void* performanceMetrics;
    // 新增中文字符表
    ChineseCharTable* chineseCharTable;  // 直接使用指针，不需要void*
    char* encryptionKey;  // 加密密钥
    int useEncryption;    // 是否使用加密
} SystemState;

// 控制台颜色设置 (Windows)
#ifdef _WIN32
#include <windows.h>
void SetConsoleColor(int color);
#else
#define SetConsoleColor(color)
#endif

// 界面函数
void wait();
void menu();

// 系统功能函数
void loadFile();
void showFrequencyTable();
void buildTree();
void generateCodes();  // 修改：增加保存编码选项
void encode();         // 修改：增加加密功能
void decode();         // 修改：增加解密功能
void saveAllResults();
void showPerformance();
void showTreeGraphical();
void cleanupSystem();

void saveCodeTableToFile();  // 保存编码表
void encodeWithSavedTable(); // 使用已保存的编码表编码
void encryptText();          // 加密文本
// UTF-8转GBK函数声明
#ifdef _WIN32
char* UTF8_to_GBK(const char* utf8_str);
ChineseCharTable* BuildChineseCharTable(const char* text, size_t length);
#endif

#endif // SET_H_INCLUDED
