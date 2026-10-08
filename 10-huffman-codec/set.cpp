#include "set.h"
#include "HuffmanTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<direct.h>
#include<io.h>
#include<ctype.h>
// 系统全局状态
static SystemState g_systemState = {0};

#ifdef _WIN32
void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#endif
void wait(){
    printf("\n按回车键继续...");
    getchar();
    getchar();
}
void menu(){
    SetConsoleColor(5);  // 黄色
    printf("\n");
    printf("╔══════════════════════════════════════╗\n");
    printf("║      哈夫曼编/译码器系统             ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║1.读取文本文件                        ║\n");
    printf("║2.显示字符频率表                      ║\n");
    printf("║3.构建哈夫曼树                        ║\n");
    printf("║4.生成哈夫曼编码                      ║\n");
    printf("║5.编码文本                            ║\n");
    printf("║6.译码文本                            ║\n");
    printf("║7.保存所有结果                        ║\n");
    printf("║8.显示性能报告                        ║\n");
    printf("║9.显示哈夫曼图形                      ║\n");
    printf("║10.保存编码表到文件                   ║\n");
    printf("║11.使用保存的编码表编码文件           ║\n");
    printf("║12.加密文本                           ║\n");
    printf("║0.退出系统                            ║\n");
    printf("╚══════════════════════════════════════╝\n");
    SetConsoleColor(2);  // 绿色
    printf("\n请选择操作(0-9):");
    SetConsoleColor(9);  // 白色
}
//清理系统所占内存
void cleanupSystem(){
    // 释放哈夫曼树
    if (g_systemState.huffmanTree) {
        HT_FreeTree((HuffmanTree)g_systemState.huffmanTree);  // 使用专用释放函数
        g_systemState.huffmanTree = NULL;
    }
    // 释放频率表
    if (g_systemState.frequencyTable) {
        HT_FreeFrequencyTable((FrequencyTable*)g_systemState.frequencyTable);
        g_systemState.frequencyTable = NULL;
    }
    // 释放编码表
    if (g_systemState.codeTable) {
        HT_FreeCodeTable((CodeTable*)g_systemState.codeTable);
        g_systemState.codeTable = NULL;
    }
    // 释放文本数据
    if (g_systemState.originalText) {
        free(g_systemState.originalText);
        g_systemState.originalText = NULL;
    }
    if (g_systemState.encodedText) {
        free(g_systemState.encodedText);
        g_systemState.encodedText = NULL;
    }
    if (g_systemState.decodedText) {
        free(g_systemState.decodedText);
        g_systemState.decodedText = NULL;
    }
    // 释放中文字符表
    if (g_systemState.chineseCharTable) {
        for (int i = 0; i < g_systemState.chineseCharTable->size; i++) {
            free(g_systemState.chineseCharTable->items[i].gbk_char);
        }
        free(g_systemState.chineseCharTable->items);
        free(g_systemState.chineseCharTable);
        g_systemState.chineseCharTable = NULL;
    }
    // 释放性能指标
    if (g_systemState.performanceMetrics) {
        free(g_systemState.performanceMetrics);
        g_systemState.performanceMetrics = NULL;
    }
    // 释放加密密钥
    if (g_systemState.encryptionKey) {
        free(g_systemState.encryptionKey);
        g_systemState.encryptionKey = NULL;
    }

    g_systemState.originalLength = 0;
    g_systemState.charCount = 0;
    g_systemState.useEncryption = 0;
}
// 在set.cpp中添加辅助函数
#ifdef _WIN32
// UTF-8转GBK函数
char* UTF8_to_GBK(const char* utf8_str) {
    if (!utf8_str) return NULL;

    int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, NULL, 0);
    if (wlen <= 0) return NULL;

    wchar_t* wstr = (wchar_t*)malloc(wlen * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, wstr, wlen);

    int glen = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    if (glen <= 0) {
        free(wstr);
        return NULL;
    }

    char* gbk_str = (char*)malloc(glen);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, gbk_str, glen, NULL, NULL);

    free(wstr);
    return gbk_str;
}

// 识别中文字符并构建中文字符表
ChineseCharTable* BuildChineseCharTable(const char* text, size_t length) {
    ChineseCharTable* table = (ChineseCharTable*)malloc(sizeof(ChineseCharTable));
    table->capacity = 100;
    table->size = 0;
    table->items = (ChineseCharItem*)malloc(table->capacity * sizeof(ChineseCharItem));

    for (size_t i = 0; i < length; ) {
        unsigned char ch = (unsigned char)text[i];

        // 检查是否是UTF-8中文字符（三字节）
        if ((ch & 0xF0) == 0xE0 && i + 2 < length) {
            unsigned char b1 = ch;
            unsigned char b2 = (unsigned char)text[i+1];
            unsigned char b3 = (unsigned char)text[i+2];

            if ((b2 & 0xC0) == 0x80 && (b3 & 0xC0) == 0x80) {
                // 构建UTF-8字符串
                char utf8_seq[4] = {b1, b2, b3, 0};

                // 转换为GBK
                char* gbk_char = UTF8_to_GBK(utf8_seq);
                if (gbk_char) {
                    // 检查是否已存在
                    int found = -1;
                    for (int j = 0; j < table->size; j++) {
                        if (strcmp(table->items[j].gbk_char, gbk_char) == 0) {
                            found = j;
                            break;
                        }
                    }

                    if (found >= 0) {
                        // 已存在，增加频率
                        table->items[found].freq++;
                        free(gbk_char);
                    } else {
                        // 新增
                        if (table->size >= table->capacity) {
                            table->capacity *= 2;
                            table->items = (ChineseCharItem*)realloc(table->items,
                                                                    table->capacity * sizeof(ChineseCharItem));
                        }

                        ChineseCharItem* item = &table->items[table->size];
                        item->bytes[0] = b1;
                        item->bytes[1] = b2;
                        item->bytes[2] = b3;
                        item->bytes[3] = 0;
                        item->length = 3;
                        item->gbk_char = gbk_char;  // 注意：这里存储了转换后的GBK字符
                        item->freq = 1;
                        table->size++;
                    }
                }
                i += 3;
                continue;
            }
        }
        i++;
    }

    return table;
}
#endif
//读取文本文件
void loadFile(){
    char filename[256];
    char cwd[1024];
    //获取当前工作目录
    if(_getcwd(cwd,sizeof(cwd))!=NULL){
        printf("当前工作目录：%s\n",cwd);
    }
    printf("请输入文件名(默认：file.txt)：");
    fgets(filename,sizeof(filename),stdin);
    filename[strcspn(filename,"\n")]='\0';
    if(strlen(filename)==0){
        strcpy(filename,"file.txt");
    }
    //检查文件是否存在(windows方式)
    if(_access(filename,0)==-1){
        printf("错误：无法找到文件'%s'\n",filename);
        printf("当前目录：%s\n",cwd);
        printf("请确保文件存在或使用绝对路径！\n");
        printf("例如：C:\\\\Users\\\\YourName\\\\Desktop\\\\file.txt\n");
        return;
    }
    // 清理之前的系统数据
    cleanupSystem();
    // 读取文件
    size_t length;
    g_systemState.originalText = HT_ReadTextFile(filename, &length);
    if (!g_systemState.originalText) {
        printf("文件读取失败！\n");
        return;
    }
    g_systemState.originalLength = length;
    // 统计字符频率
    g_systemState.frequencyTable = HT_CountFrequency(g_systemState.originalText, length);
    FrequencyTable* freqTable = (FrequencyTable*)g_systemState.frequencyTable;
    g_systemState.charCount = freqTable->size;
     // 构建中文字符表（仅Windows）
    #ifdef _WIN32
    g_systemState.chineseCharTable = BuildChineseCharTable(g_systemState.originalText, length);
    #else
    g_systemState.chineseCharTable = NULL;
    #endif
    // 初始化性能指标
    g_systemState.performanceMetrics = malloc(sizeof(PerformanceMetrics));
    PM_Init((PerformanceMetrics*)g_systemState.performanceMetrics);
    ((PerformanceMetrics*)g_systemState.performanceMetrics)->originalSize = length;

    printf("\n文件加载成功！\n");
    printf("文件名：%s\n",filename);
    printf("字符总数：%u\n",(unsigned int)length);
    printf("不同字符数：%d\n",g_systemState.charCount);
    printf("文件大小：%.2f KB\n",length/1024.0);
    // 如果有中文字符，显示统计信息
    if (g_systemState.chineseCharTable && g_systemState.chineseCharTable->size > 0) {
        printf("中文字符数：%d\n", g_systemState.chineseCharTable->size);
    }

    printf("文件大小：%.2f KB\n",length/1024.0);
}

//显示字符频率表
void showFrequencyTable(){
    if (!g_systemState.frequencyTable) {
        printf("请先加载文件!\n");
        return;
    }
    printf("╔══════════════════════════════════════╗\n");
    printf("║        字符频率统计表                ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║%-12s %-12s %-10s  ║\n", "字符/描述", "编码", "频率");
    printf("║------------ ---------- ----------    ║\n");

    FrequencyTable* table = (FrequencyTable*)g_systemState.frequencyTable;
    int count = 0;
    // 首先显示所有ASCII字符（包括控制字符）
    for (int i = 0; i < 256; i++) {
        if (table->items[i].freq > 0) {
            // 跳过UTF-8中文字符的起始字节（这些会在后面显示）
            unsigned char ch = (unsigned char)i;
            if (ch >= 0xE0 && ch <= 0xEF) {
                // 这是UTF-8中文起始字节，跳过，后面会显示完整的中文字符
                continue;
            }

            if (i < 128) {
                // ASCII字符
                if (isprint(i)) {
                    char display[20];
                    if (i == ' ') strcpy(display, "' '空格");
                    else if (i == '\t') strcpy(display, "\\t制表符");
                    else if (i == '\n') strcpy(display, "\\n换行符");
                    else if (i == '\r') strcpy(display, "\\r回车符");
                    else snprintf(display, sizeof(display), "'%c'", i);

                    printf("║%-12s %-10d %-10d    ║\n", display, i, table->items[i].freq);
                } else {
                    // 控制字符显示十六进制
                    continue;
                }
            } else if (ch >= 0x80 && ch <= 0xBF) {
                // UTF-8后续字节，显示为十六进制
                continue;
            }

            count++;
            if (count >= 15) break; // 先显示前15个ASCII字符
        }
    }
    // 显示中文字符
    if (g_systemState.chineseCharTable && g_systemState.chineseCharTable->size > 0) {
        ChineseCharTable* chTable = g_systemState.chineseCharTable;

        for (int i = 0; i < chTable->size && count < 30; i++) {
            ChineseCharItem* item = &chTable->items[i];
            // 显示中文字符和频率
            printf("║%-12s 0x%02X%02X%02X   %-10d    ║\n",
                   item->gbk_char ? item->gbk_char : "[中文]",
                   item->bytes[0], item->bytes[1], item->bytes[2],
                   item->freq);
            count++;
        }
    } else {
        // 如果没有构建中文字符表，显示UTF-8起始字节
        for (int i = 0xE0; i <= 0xEF && count < 30; i++) {
            if (table->items[i].freq > 0) {
                printf("[中文起始] %-10d  %-10d  \n", i, table->items[i].freq);
                count++;
            }
        }
    }

    if (count >= 30) {
        printf("...(显示前30个字符)\n");
    }
    printf("╚══════════════════════════════════════╝\n");
}
//创建哈夫曼树
void buildTree(){
    if (!g_systemState.frequencyTable) {
        printf("请先加载文件!\n");
        return;
    }
    printf("正在构建哈夫曼树...\n");
    FrequencyTable* freqTable = (FrequencyTable*)g_systemState.frequencyTable;

    // 提取权重和字符
    int* weights = (int*)malloc(g_systemState.charCount * sizeof(int));
    char* chars = (char*)malloc(g_systemState.charCount * sizeof(char));

    int index = 0;
    for (int i = 0; i < 256; i++) {
        if (freqTable->items[i].freq > 0) {
            weights[index] = freqTable->items[i].freq;
            chars[index] = (char)i;
            index++;
        }
    }

    // 构建哈夫曼树
    clock_t start = clock();
    HT_BuildTree((HuffmanTree*)&g_systemState.huffmanTree,
                g_systemState.charCount, weights);
    clock_t end = clock();

    // 设置字符数据
    HuffmanTree tree = (HuffmanTree)g_systemState.huffmanTree;
    for (int i = 1; i <= g_systemState.charCount; i++) {
        tree[i].data = chars[i - 1];
    }

    PerformanceMetrics* metrics = (PerformanceMetrics*)g_systemState.performanceMetrics;
    metrics->treeBuildTime = (double)(end - start) / CLOCKS_PER_SEC;

    free(weights);
    free(chars);
    // ============ 2. 在控制台输出树结构 ============
    printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║                           哈夫曼树结构                            ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════╣\n");

    int m = 2 * g_systemState.charCount - 1;
    printf("║ 节点总数：%d (叶子节点：%d，内部节点：%d)                         ║ \n",m, g_systemState.charCount, m - g_systemState.charCount);
    printf("║                                                                   ║\n");
    printf("║ %-8s %-8s %-8s %-8s %-8s %-10s           ║ \n","索引","权值","父节点","左孩子","右孩子","字符/类型");
    printf("║ %-8s %-8s %-8s %-8s %-8s %-10s           ║ \n",
           "------", "------", "------", "------", "------", "----------");

    for (int i = 1; i <= m; i++) {
        char typeDesc[20];
        char charDesc[10];

        if (tree[i].lchild == 0 && tree[i].rchild == 0) {
            strcpy(typeDesc,"叶子节点");
            if (tree[i].data == ' ') {
                snprintf(charDesc, sizeof(charDesc), "' '");
            } else if (tree[i].data < 32 || tree[i].data == 127) {
                snprintf(charDesc, sizeof(charDesc), "0x%02X", (unsigned char)tree[i].data);
            } else {
                snprintf(charDesc, sizeof(charDesc), "'%c'", tree[i].data);
            }
        } else {
            strcpy(typeDesc,"内部节点");
            strcpy(charDesc, "-");
        }

        printf("║ %-8d %-8d %-8d %-8d %-8d %-10s (%s)║ \n",
               i, tree[i].weight, tree[i].parent,
               tree[i].lchild, tree[i].rchild,
               charDesc, typeDesc);
    }
    printf("║ 哈夫曼树构建完成！                                                ║ \n");
    printf("║ 构建时间：%.6f 秒                                             ║ \n",metrics->treeBuildTime);
    printf("║ 带权路径长度(WPL):%d                                              ║ \n",HT_CalculateWPL((HuffmanTree)g_systemState.huffmanTree, g_systemState.charCount));
    printf("╚═══════════════════════════════════════════════════════════════════╝\n");
}
//生成哈夫曼编码
void generateCodes(){
    if (!g_systemState.huffmanTree) {
        printf("请先建立哈夫曼树！\n");
        return;
    }
    printf("正在生成哈夫曼编码...\n");

    if (g_systemState.codeTable) {
        HT_FreeCodeTable((CodeTable*)g_systemState.codeTable);
    }

    g_systemState.codeTable = HT_BuildCodeTable((HuffmanTree)g_systemState.huffmanTree,
                                               g_systemState.charCount);

    printf("哈夫曼编码生成完成！\n");
    HT_PrintCodeTable((CodeTable*)g_systemState.codeTable);

    // 新增：询问是否保存编码表
    printf("\n是否保存编码表到文件？(y/n): ");
    char choice;
    scanf("%c", &choice);
    getchar(); // 清除换行符

    if (choice == 'y' || choice == 'Y') {
        char filename[256];
        printf("请输入保存文件名(默认: HuffmanCodeTable.txt): ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';

        if (strlen(filename) == 0) {
            strcpy(filename, "HuffmanCodeTable.txt");
        }

        HT_SaveCodeTable((CodeTable*)g_systemState.codeTable, filename);
        printf("编码表已保存到 %s\n", filename);
    }
}

// 修改后的encode函数，增加加密功能
void encode(){
    if (!g_systemState.originalText) {
        printf("请先加载文件！\n");
        return;
    }

    // 询问是否使用现有编码表
    printf("是否使用现有编码表？(y/n): ");
    char useExisting;
    scanf("%c", &useExisting);
    getchar();

    if (useExisting == 'y' || useExisting == 'Y') {
        char filename[256];
        printf("请输入编码表文件名: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';

        // 释放旧的编码表
        if (g_systemState.codeTable) {
            HT_FreeCodeTable((CodeTable*)g_systemState.codeTable);
        }

        // 加载编码表
        g_systemState.codeTable = HT_LoadCodeTable(filename);
        if (!g_systemState.codeTable) {
            printf("无法加载编码表，将重新生成。\n");
            if (!g_systemState.huffmanTree) {
                printf("请先构建哈夫曼树！\n");
                return;
            }
            g_systemState.codeTable = HT_BuildCodeTable((HuffmanTree)g_systemState.huffmanTree,
                                                       g_systemState.charCount);
        }
    } else {
        if(!g_systemState.codeTable){
            printf("请先生成哈夫曼编码！\n");
            return;
        }
    }

    printf("正在编译文本...\n");
    clock_t start=clock();

    // 编码文本
    g_systemState.encodedText = HT_EncodeText(g_systemState.originalText,
                                             (CodeTable*)g_systemState.codeTable);
    clock_t end = clock();

    PerformanceMetrics* metrics = (PerformanceMetrics*)g_systemState.performanceMetrics;
    metrics->encodingTime = (double)(end - start) / CLOCKS_PER_SEC;
    metrics->encodedSize = strlen(g_systemState.encodedText);

    // 计算压缩比
    PM_CalculateRatio(metrics, metrics->originalSize * 8, metrics->encodedSize);

    printf("文本编译完成！\n");
    printf("编码时间：%.6f 秒\n", metrics->encodingTime);
    printf("原始大小：%u 字符(%u 位)\n",
           (unsigned int)metrics->originalSize,
           (unsigned int)(metrics->originalSize * 8));
    printf("编码后的大小：%u 字符 (%u 位)\n",
           (unsigned int)metrics->encodedSize,
           (unsigned int)metrics->encodedSize);
    printf("压缩比：%.2f%%\n", metrics->compressionRatio);

    // 询问是否加密
    printf("\n是否对编码结果进行加密？(y/n): ");
    char encryptChoice;
    scanf("%c", &encryptChoice);
    getchar();

    if (encryptChoice == 'y' || encryptChoice == 'Y') {
        char key[256];
        printf("请输入加密密钥: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        // 保存密钥
        if (g_systemState.encryptionKey) {
            free(g_systemState.encryptionKey);
        }
        g_systemState.encryptionKey = strdup(key);
        g_systemState.useEncryption = 1;

        // 加密文本
        char* encrypted = HT_EncryptText(g_systemState.encodedText, key);
        if (encrypted) {
            free(g_systemState.encodedText);
            g_systemState.encodedText = encrypted;
            printf("文本已加密！\n");
        }
    } else {
        g_systemState.useEncryption = 0;
    }

    // 显示部分编码结果
    printf("\n编码结果预览(前200位)：\n");
    for (int i = 0; i < 200 && g_systemState.encodedText[i] != '\0'; i++) {
        // 如果是加密文本，可能需要特殊显示
        if (g_systemState.useEncryption &&
            (g_systemState.encodedText[i] < 32 || g_systemState.encodedText[i] > 126)) {
            printf("[0x%02X]", (unsigned char)g_systemState.encodedText[i]);
        } else {
            printf("%c", g_systemState.encodedText[i]);
        }
        if ((i + 1) % 50 == 0) printf("\n");
    }
    if (strlen(g_systemState.encodedText) > 200) printf("\n...\n");
    printf("\n");
}

// 修改后的decode函数，增加解密功能
void decode(){
    if (!g_systemState.encodedText) {
        printf("请先编码文本！\n");
        return;
    }
    if(!g_systemState.huffmanTree) {
        printf("请先构建哈夫曼树！\n");
        return;
    }

    // 检查是否需要解密
    char* textToDecode = g_systemState.encodedText;
    if (g_systemState.useEncryption && g_systemState.encryptionKey) {
        printf("检测到加密文本，正在解密...\n");
        char* decrypted = HT_DecryptText(g_systemState.encodedText,
                                        g_systemState.encryptionKey);
        if (decrypted) {
            textToDecode = decrypted;
            printf("文本已解密！\n");
        }
    }

    printf("正在译码文本...\n");
    clock_t start = clock();

    g_systemState.decodedText = HT_DecodeText(textToDecode,
                                             (HuffmanTree)g_systemState.huffmanTree,
                                             g_systemState.charCount);
    clock_t end = clock();

    // 如果使用了临时解密文本，释放它
    if (textToDecode != g_systemState.encodedText) {
        free(textToDecode);
    }

    PerformanceMetrics* metrics = (PerformanceMetrics*)g_systemState.performanceMetrics;
    metrics->decodingTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("文本译码完成！\n");
    printf("译码时间：%.6f 秒\n", metrics->decodingTime);

    // 显示部分译码结果
    printf("\n译码结果预览(前100字符)：\n");
    #ifdef _WIN32
    // Windows API直接输出，避免编码问题
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD charsWritten;

    // 将UTF-8转换为宽字符
    int wlen = MultiByteToWideChar(CP_UTF8, 0, g_systemState.decodedText, -1, NULL, 0);
    wchar_t* wstr = (wchar_t*)malloc(wlen * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, g_systemState.decodedText, -1, wstr, wlen);

    // 输出前100个字符
    int displayLen = wcslen(wstr) < 100 ? wcslen(wstr) : 100;
    WriteConsoleW(hConsole, wstr, displayLen, &charsWritten, NULL);

    if (wcslen(wstr) > 100) {
        printf("\n...");
    }
    free(wstr);
    #else
    // 非Windows系统直接输出
    for(int i = 0; i < 100 && g_systemState.decodedText[i] != '\0'; i++) {
        printf("%c", g_systemState.decodedText[i]);
    }
    if (strlen(g_systemState.decodedText) > 100) printf("\n...");
    #endif

    printf("\n");

    // 验证译码正确性
    int isCorrect = 1;
    size_t originalLen = strlen(g_systemState.originalText);
    size_t decodedLen = strlen(g_systemState.decodedText);

    if (originalLen != decodedLen) {
        isCorrect = 0;
    } else {
        for (size_t i = 0; i < originalLen; i++) {
            if ((unsigned char)g_systemState.originalText[i] !=
                (unsigned char)g_systemState.decodedText[i]) {
                isCorrect = 0;
                break;
            }
        }
    }

    if (isCorrect) {
        printf("译码验证通过！\n");
    } else {
        printf("译码验证失败! \n");
        printf("原始长度：%u, 译码长度: %u\n",
               (unsigned int)originalLen, (unsigned int)decodedLen);
    }
}
// ============== 新增：保存编码表函数 ==============
void saveCodeTableToFile() {
    if (!g_systemState.codeTable) {
        printf("请先生成编码表！\n");
        return;
    }

    char filename[256];
    printf("请输入保存文件名(默认: HuffmanCodeTable.txt): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    if (strlen(filename) == 0) {
        strcpy(filename, "HuffmanCodeTable.txt");
    }

    HT_SaveCodeTable((CodeTable*)g_systemState.codeTable, filename);
}

// 新增函数：使用保存的编码表编码文件
void encodeWithSavedTable() {
    char filename[256];
    char codeTableFile[256];

    printf("请输入要编码的文件名: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    printf("请输入编码表文件名: ");
    fgets(codeTableFile, sizeof(codeTableFile), stdin);
    codeTableFile[strcspn(codeTableFile, "\n")] = '\0';

    // 读取文件
    size_t length;
    char* text = HT_ReadTextFile(filename, &length);
    if (!text) {
        printf("无法读取文件: %s\n", filename);
        return;
    }

    // 使用保存的编码表编码
    char* encoded = HT_EncodeTextWithSavedTable(text, codeTableFile);
    if (!encoded) {
        printf("编码失败！\n");
        free(text);
        return;
    }

    // 询问是否加密
    printf("是否对编码结果进行加密？(y/n): ");
    char choice;
    scanf("%c", &choice);
    getchar();

    if (choice == 'y' || choice == 'Y') {
        char key[256];
        printf("请输入加密密钥: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        char* encrypted = HT_EncryptText(encoded, key);
        if (encrypted) {
            free(encoded);
            encoded = encrypted;
            printf("文本已加密！\n");
        }
    }

    // 保存结果
    char outputFile[256];
    printf("请输入输出文件名: ");
    fgets(outputFile, sizeof(outputFile), stdin);
    outputFile[strcspn(outputFile, "\n")] = '\0';

    HT_SaveTextFile(outputFile, encoded);
    printf("编码结果已保存到: %s\n", outputFile);

    // 显示统计信息
    printf("\n统计信息:\n");
    printf("原始大小: %u 字符\n", (unsigned int)length);
    printf("编码后大小: %u 字符\n", (unsigned int)strlen(encoded));
    printf("压缩比: %.2f%%\n",
           (1.0 - (double)strlen(encoded) / (length * 8)) * 100.0);

    free(text);
    free(encoded);
}

// 新增函数：单独加密文本
void encryptText() {
    if (!g_systemState.encodedText) {
        printf("请先编码文本！\n");
        return;
    }

    char key[256];
    printf("请输入加密密钥: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    // 加密文本
    char* encrypted = HT_EncryptText(g_systemState.encodedText, key);
    if (encrypted) {
        // 保存密钥
        if (g_systemState.encryptionKey) {
            free(g_systemState.encryptionKey);
        }
        g_systemState.encryptionKey = strdup(key);
        g_systemState.useEncryption = 1;

        // 更新编码文本
        free(g_systemState.encodedText);
        g_systemState.encodedText = encrypted;

        printf("文本加密完成！\n");
        printf("加密预览(前100字符):\n");
        for (int i = 0; i < 100 && encrypted[i] != '\0'; i++) {
            if (encrypted[i] < 32 || encrypted[i] > 126) {
                printf("[0x%02X]", (unsigned char)encrypted[i]);
            } else {
                printf("%c", encrypted[i]);
            }
        }
        printf("\n");
    }
}

//保存所有结果
void saveAllResults(){
    if (!g_systemState.huffmanTree || !g_systemState.codeTable) {
        printf("请先构建完整的系统!\n");
        return;
    }
    printf("正在保存所有结果...\n");
    // 保存哈夫曼树
    HT_SaveToFile((HuffmanTree)g_systemState.huffmanTree,g_systemState.charCount, "HfmTree.txt");
    // 保存编码表
    HT_SaveCodeTable((CodeTable*)g_systemState.codeTable, "CodeFile.txt");

    // 保存编码文本（每行50字符）
    if (g_systemState.encodedText) {
        HT_SaveEncodedText(g_systemState.encodedText, "TextFile.txt", 50);
    }

    // 保存树形显示
    FILE* treeFile = fopen("TreePrint.txt", "w");
    if (treeFile) {
        fprintf(treeFile, "哈夫曼结构\n");
        fprintf(treeFile, "================================\n\n");
        int m = 2 * g_systemState.charCount - 1;
        HuffmanTree tree = (HuffmanTree)g_systemState.huffmanTree;
        for (int i = 1; i <= m; i++) {
            if (tree[i].lchild == 0 && tree[i].rchild == 0) {
                fprintf(treeFile,"叶子节点[%d]:'%c' 权值:%d\n",i, tree[i].data, tree[i].weight);
            }else{
                fprintf(treeFile,"内部节点[%d]:权值:%d 左孩子:%d 右孩子: %d\n",i,tree[i].weight,tree[i].lchild,tree[i].rchild);
            }
        }
        fclose(treeFile);
        printf("树形显示已保存到：TreePrint.txt\n");
    }
    // 保存性能报告
    PM_SaveReport((PerformanceMetrics*)g_systemState.performanceMetrics,
                 "PerformanceReport.txt");

    printf("\n所有结果已保存！\n");
    printf("生成的文件：\n");
    printf(" -HfmTree.txt(哈夫曼树结构)\n");
    printf(" -CodeFile.txt(字符编码表)\n");
    printf(" -TextFile.txt(编码文本)\n");
    printf(" -TreePrint.txt(树形显示)\n");
    printf(" -PerformanceReport.txt(性能报告)\n");
}
//显示性能报告
void showPerformance(){
    if (!g_systemState.performanceMetrics) {
        printf("请先完成编码操作！\n");
        return;
    }
    PM_PrintReport((PerformanceMetrics*)g_systemState.performanceMetrics);
}
//显示哈夫曼图形
void showTreeGraphical(){
    if(!g_systemState.huffmanTree) {
        printf("请先构建哈夫曼树！\n");
        return;
    }
    // 直接调用 HT_PrintTree，它现在是图形化版本
    HT_PrintTree((HuffmanTree)g_systemState.huffmanTree, g_systemState.charCount);
}
