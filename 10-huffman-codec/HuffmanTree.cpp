#include<ctype.h>
#include<locale.h>
#include"HuffmanTree.h"
#include<queue>
#include<vector>
#include<string>
#include<cstdio>
#include<sstream>
#include<stdint.h>
static int rank_counter=0;//全局变量，用于计算位置
// ============== 哈夫曼树核心算法 ==============

int HT_Select(HuffmanTree HT, int n, int* s1, int* s2) {
    int min1 = -1, min2 = -1;

    for (int i = 1; i <= n; i++) {
        if (HT[i].parent == 0) {
            if (min1 == -1 || HT[i].weight < HT[min1].weight) {
                min2 = min1;
                min1 = i;
            } else if (min2 == -1 || HT[i].weight < HT[min2].weight) {
                min2 = i;
            }
        }
    }

    if (min1 == -1 || min2 == -1) {
        return -1;
    }

    *s1 = min1;
    *s2 = min2;
    return 0;
}
void HT_BuildTree(HuffmanTree* HT, int n, int weights[]) {
    if (n <= 1) {
        *HT = NULL;
        return;
    }

    int m = 2 * n - 1;
    *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));

    // 初始化所有节点
    for (int i = 1; i <= m; i++) {
        (*HT)[i].parent = 0;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].weight = 0;
        (*HT)[i].data = '\0';
        (*HT)[i].code = NULL;
    }

    // 设置叶子节点权值
    for (int i = 1; i <= n; i++) {
        (*HT)[i].weight = weights[i - 1];
    }

    // 构建哈夫曼树
    for (int i = n + 1; i <= m; i++) {
        int s1, s2;
        if (HT_Select(*HT, i - 1, &s1, &s2) == 0) {
            (*HT)[s1].parent = i;
            (*HT)[s2].parent = i;
            (*HT)[i].lchild = s1;
            (*HT)[i].rchild = s2;
            (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
        }
    }
}
void HT_GenerateCodes(HuffmanTree HT, HuffmanCode* HC, int n) {
    *HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
    char* cd = (char*)malloc((n + 1) * sizeof(char));
    cd[n] = '\0';

    for (int i = 1; i <= n; i++) {
        int start = n;
        int c = i;
        int f = HT[i].parent;

        while (f != 0) {
            --start;
            if (HT[f].lchild == c) {
                cd[start] = '0';
            } else {
                cd[start] = '1';
            }
            c = f;
            f = HT[f].parent;
        }

        (*HC)[i] = (char*)malloc((n - start + 1) * sizeof(char));
        strcpy((*HC)[i], &cd[start]);
    }

    free(cd);
}
int HT_CalculateWPL(HuffmanTree HT, int n) {
    int wpl = 0;
    for (int i = 1; i <= n; i++) {
        int depth = 0;
        int j = i;
        while (HT[j].parent != 0) {
            depth++;
            j = HT[j].parent;
        }
        wpl += HT[i].weight * depth;
    }
    return wpl;
}
void HT_PrintTree(HuffmanTree HT, int n) {
    if(!HT){
        printf("哈夫曼树未构建！\n");
        return;
    }
    //调用图形化打印函数
    HT_PrintTreeGraphical(HT,n);
}
void HT_SaveToFile(HuffmanTree HT, int n, const char* filename) {
    FILE* file = fopen(filename, "w");
    if(!file){
        printf("无法创建文件：%s\n",filename);
        return;
    }
    fprintf(file,"哈夫曼树结构\n");
    fprintf(file,"================================\n");
    fprintf(file,"索引\t权值\t父节点\t左孩子\t右孩子\t字符\n");
    int m = 2 * n - 1;
    for (int i = 1; i <= m; i++) {
        fprintf(file, "%d\t%d\t%d\t%d\t%d\t%c\n",
                i, HT[i].weight, HT[i].parent,
                HT[i].lchild, HT[i].rchild,
                (HT[i].data ? HT[i].data : ' '));
    }
    fprintf(file,"\n带权路径长度(WPL):%d\n",HT_CalculateWPL(HT, n));
    fclose(file);
    printf("哈夫曼树已保存到：%s\n",filename);
}

// ============== 新增函数：加载编码表 ==============
CodeTable* HT_LoadCodeTable(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("无法打开编码表文件：%s\n", filename);
        return NULL;
    }

    CodeTable* table = (CodeTable*)malloc(sizeof(CodeTable));
    table->capacity = 100;
    table->size = 0;
    table->items = (CodeTableItem*)malloc(table->capacity * sizeof(CodeTableItem));

    char line[256];
    // 跳过表头
    for (int i = 0; i < 3; i++) {
        if (!fgets(line, sizeof(line), file)) {
            fclose(file);
            HT_FreeCodeTable(table);
            return NULL;
        }
    }

    while (fgets(line, sizeof(line), file)) {
        // 跳过空行
        if (strlen(line) <= 1) continue;

        char chStr[20], code[100];
        int freq;

        if (sscanf(line, "%s %d %s", chStr, &freq, code) == 3) {
            // 扩展容量
            if (table->size >= table->capacity) {
                table->capacity *= 2;
                table->items = (CodeTableItem*)realloc(table->items,
                                                      table->capacity * sizeof(CodeTableItem));
            }

            char ch;
            if (strncmp(chStr, "'", 1) == 0 && strlen(chStr) >= 3 && chStr[strlen(chStr)-1] == '\'') {
                // 格式：'c'
                ch = chStr[1];
            } else if (strncmp(chStr, "0x", 2) == 0) {
                // 格式：0xXX
                int hexVal;
                sscanf(chStr + 2, "%x", &hexVal);
                ch = (char)hexVal;
            } else {
                // 其他情况
                ch = chStr[0];
            }

            table->items[table->size].ch = ch;
            table->items[table->size].freq = freq;
            table->items[table->size].code = strdup(code);
            table->size++;
        }
    }

    fclose(file);
    printf("编码表已从 %s 加载，共 %d 个字符\n", filename, table->size);
    return table;
}

// ============== 新增函数：使用保存的编码表编码 ==============
char* HT_EncodeTextWithSavedTable(const char* text, const char* codeTableFile) {
    // 加载编码表
    CodeTable* table = HT_LoadCodeTable(codeTableFile);
    if (!table) {
        return NULL;
    }

    // 编码文本
    char* encoded = HT_EncodeText(text, table);

    // 释放编码表
    HT_FreeCodeTable(table);

    return encoded;
}

// ============== 新增函数：加密 ==============
char* HT_EncryptText(const char* text, const char* key) {
    if (!text || !key) return NULL;

    size_t textLen = strlen(text);
    size_t keyLen = strlen(key);

    if (keyLen == 0) {
        // 如果没有密钥，返回原始文本的副本
        char* result = (char*)malloc(textLen + 1);
        strcpy(result, text);
        return result;
    }

    char* encrypted = (char*)malloc(textLen + 1);

    // 简单异或加密
    for (size_t i = 0; i < textLen; i++) {
        char textChar = text[i];
        char keyChar = key[i % keyLen];

        // 对每个字符进行异或操作
        encrypted[i] = textChar ^ keyChar;

        // 对于二进制文本（0和1），我们需要特殊处理
        // 确保结果仍然是可打印字符
        if (encrypted[i] == '\0') {
            encrypted[i] = 1;  // 避免字符串提前结束
        }
    }
    encrypted[textLen] = '\0';

    return encrypted;
}

// ============== 新增函数：解密 ==============
char* HT_DecryptText(const char* encryptedText, const char* key) {
    // 加密和解密使用相同的算法（异或）
    return HT_EncryptText(encryptedText, key);
}

// ============== 频率统计函数 ==============

FrequencyTable* HT_CreateFrequencyTable() {
    FrequencyTable* table = (FrequencyTable*)malloc(sizeof(FrequencyTable));
    table->capacity = 256;
    table->size = 0;
    table->items = (FreqItem*)calloc(table->capacity, sizeof(FreqItem));

    // 初始化所有ASCII字符
    for (int i = 0; i < 256; i++) {
        table->items[i].ch = (char)i;
        table->items[i].freq = 0;
    }

    return table;
}
FrequencyTable* HT_CountFrequency(const char* text, size_t length) {
    FrequencyTable* table = HT_CreateFrequencyTable();

    // 统计频率
    for (size_t i = 0; i < length; i++) {
        unsigned char ch = (unsigned char)text[i];
        table->items[ch].freq++;
    }

    // 计算实际使用的字符数
    for (int i = 0; i < 256; i++) {
        if (table->items[i].freq > 0) {
            table->size++;
        }
    }

    return table;
}
void HT_PrintFrequencyTable(FrequencyTable* table) {
    if (!table || table->size == 0) {
        printf("频率表为空!\n");
        return;
    }
    printf("字符频率统计表: \n");
    printf("================================\n");
    printf("%-10s %-10s %-10s\n", "字符", "ASCII码", "频率");
    printf("---------- ---------- ----------\n");
    int count = 0;
    for (int i = 0; i < 256; i++) {
        if (table->items[i].freq > 0) {
            if (isprint(i)) {
                printf("%-10c %-10d %-10d\n",
                       (char)i, i, table->items[i].freq);
            } else {
                printf("0x%-8X %-10d %-10d\n",
                       i,i,table->items[i].freq);
            }
            count++;
            if(count>=30){
                printf("...(显示前30个字符)\n");
                break;
            }
        }
    }
}
void HT_FreeFrequencyTable(FrequencyTable* table) {
    if (table) {
        free(table->items);
        free(table);
    }
}
// ============== 编码表函数 ==============

CodeTable* HT_BuildCodeTable(HuffmanTree HT, int n) {
    CodeTable* table = (CodeTable*)malloc(sizeof(CodeTable));
    table->capacity = n;
    table->size = n;
    table->items = (CodeTableItem*)malloc(n * sizeof(CodeTableItem));

    // 生成哈夫曼编码
    HuffmanCode HC;
    HT_GenerateCodes(HT, &HC, n);

    // 填充编码表
    for (int i = 0; i < n; i++) {
        table->items[i].ch = HT[i + 1].data;
        table->items[i].code = strdup(HC[i + 1]);
        table->items[i].freq = HT[i + 1].weight;

        // 释放临时编码内存
        free(HC[i + 1]);
    }

    free(HC);
    return table;
}
void HT_PrintCodeTable(CodeTable* table) {
    if(!table||table->size==0){
        printf("编码表为空!\n");
        return;
    }
    printf("哈夫曼编码表:\n");
    printf("================================\n");
    printf("%-10s %-10s %-20s %-10s\n",
           "字符","频率","编码","长度");
    printf("---------- ---------- -------------------- ----------\n");
    for (int i = 0; i < table->size; i++) {
        char chStr[10];
        if (isprint(table->items[i].ch)) {
            snprintf(chStr, sizeof(chStr), "'%c'", table->items[i].ch);
        } else {
            snprintf(chStr, sizeof(chStr), "0x%02X", (unsigned char)table->items[i].ch);
        }

        printf("%-10s %-10d %-20s %-10u\n",
            chStr, table->items[i].freq,
            table->items[i].code,
            (unsigned int)strlen(table->items[i].code));
    }
}
void HT_SaveCodeTable(CodeTable* table, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("无法创建文件：%s\n",filename);
        return;
    }
    fprintf(file,"哈夫曼编码表\n");
    fprintf(file,"================================\n");
    fprintf(file,"字符\t频率\t编码\t长度\n");
    for (int i = 0; i < table->size; i++) {
        char chStr[10];
        if (isprint(table->items[i].ch)) {
            snprintf(chStr, sizeof(chStr), "'%c'", table->items[i].ch);
        } else {
            snprintf(chStr, sizeof(chStr), "0x%02X", (unsigned char)table->items[i].ch);
        }

        fprintf(file, "%s\t%d\t%s\t%u\n",  // 修改 %zu 为 %u
        chStr, table->items[i].freq,
        table->items[i].code,
        (unsigned int)strlen(table->items[i].code));
    }
    fclose(file);
    printf("编码表已保存到：%s\n",filename);
}
void HT_FreeCodeTable(CodeTable* table) {
    if (table) {
        for (int i = 0; i < table->size; i++) {
            free(table->items[i].code);
        }
        free(table->items);
        free(table);
    }
}

// ============== 编码/译码函数 ==============

char* HT_EncodeText(const char* text, CodeTable* table) {
    if (!text || !table || table->size == 0) {
        return NULL;
    }

    // 计算最大可能的编码长度
    size_t maxLen = strlen(text) * 50;  // 假设平均编码长度不超过50
    char* encoded = (char*)malloc((maxLen + 1) * sizeof(char));
    encoded[0] = '\0';

    size_t pos = 0;
    for (size_t i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        // 在编码表中查找字符
        int found = 0;
        for (int j = 0; j < table->size; j++) {
            if (table->items[j].ch == ch) {
                char* code = table->items[j].code;
                size_t codeLen = strlen(code);

                // 检查缓冲区是否足够
                if (pos + codeLen >= maxLen) {
                    maxLen = (pos + codeLen) * 2;
                    encoded = (char*)realloc(encoded, maxLen + 1);
                }

                strcpy(encoded + pos, code);
                pos += codeLen;
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("警告：字符'%c' (ASCII: %d) 未在编码表中找到\n",ch,(int)ch);
        }
    }
    encoded[pos]='\0';
    return encoded;

}
char* HT_DecodeText(const char* encoded, HuffmanTree HT, int n) {
    if (!encoded || !HT) {
        return NULL;
    }

    size_t maxLen = strlen(encoded);  // 最大可能字符数
    char* decoded = (char*)malloc((maxLen + 1) * sizeof(char));
    int pos = 0;

    int current = 2 * n - 1;  // 根节点索引
    for (size_t i = 0; i < maxLen; i++) {  // 修改条件判断
        if (encoded[i] == '0') {
            current = HT[current].lchild;
        } else if (encoded[i] == '1') {
            current = HT[current].rchild;
        } else {
            // 跳过非0/1字符
            continue;
        }

        // 到达叶子节点
        if (HT[current].lchild == 0 && HT[current].rchild == 0) {
            if (pos < (int)maxLen) {  // 添加类型转换
                decoded[pos++] = HT[current].data;
                current = 2 * n - 1;  // 回到根节点
            }
        }
    }

    decoded[pos] = '\0';
    return decoded;
}

// ============== 性能分析函数 ==============

void PM_Init(PerformanceMetrics* metrics) {
    metrics->encodingTime = 0;
    metrics->decodingTime = 0;
    metrics->treeBuildTime = 0;
    metrics->originalSize = 0;
    metrics->encodedSize = 0;
    metrics->compressionRatio = 0;
}

void PM_CalculateRatio(PerformanceMetrics* metrics,
                      size_t originalBits, size_t encodedBits) {
    if (originalBits > 0) {
        metrics->compressionRatio =
            (1.0 - (double)encodedBits / originalBits) * 100.0;
    }
}
void PM_PrintReport(PerformanceMetrics* metrics) {
    printf("\n性能分析报告：\n");
    printf("================================\n");
    printf("1.大小信息\n");
    printf("原始文本大小：%u 字符\n",(unsigned int)metrics->originalSize);
    printf("原始比特数：%u 位\n",(unsigned int)(metrics->originalSize * 8));
    printf("编码后大小：%u 字符\n",(unsigned int)metrics->encodedSize);
    printf("编码后比特数：%u 位\n",(unsigned int)metrics->encodedSize);
    printf("\n2.压缩性能\n");
    printf("压缩比：%.2f%%\n",metrics->compressionRatio);
    if (metrics->originalSize * 8 > 0) {
        double savings = ((double)metrics->originalSize * 8 - metrics->encodedSize) /
                        (metrics->originalSize * 8) * 100.0;
        printf("空间节省:%.2f%%\n",savings);
    }
    printf("\n3.时间性能\n");
    printf("哈夫曼树构建时间:%.6f 秒\n",metrics->treeBuildTime);
    printf("编码时间：%.6f 秒\n",metrics->encodingTime);
    printf("译码时间：%.6f 秒\n",metrics->decodingTime);
    if (metrics->encodingTime > 0) {
        printf("编码速度：%.2f 字符/秒\n",metrics->originalSize / metrics->encodingTime);
    }
    if(metrics->decodingTime > 0){
        printf("译码速度：%.2f 字符/秒\n",metrics->originalSize / metrics->decodingTime);
    }
}
void PM_SaveReport(PerformanceMetrics* metrics, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("无法创建文件: %s\n",filename);
        return;
    }
    fprintf(file,"哈夫曼编码性能报告\n");
    fprintf(file,"================================\n\n");
    fprintf(file,"1.大小信息\n");
    fprintf(file,"原始文本大小：%u 字符\n",(unsigned int)metrics->originalSize);
    fprintf(file,"原始比特数：%u 位\n",(unsigned int)(metrics->originalSize * 8));
    fprintf(file,"编码后大小：%u 字符\n",(unsigned int)metrics->encodedSize);
    fprintf(file,"编码后比特数：%u 位\n",(unsigned int)metrics->encodedSize);
    fprintf(file,"\n2.压缩性能\n");
    fprintf(file,"压缩比：%.2f%%\n",metrics->compressionRatio);
    if (metrics->originalSize * 8 > 0) {
        double savings = ((double)metrics->originalSize * 8 - metrics->encodedSize) /
                        (metrics->originalSize * 8) * 100.0;
        fprintf(file,"空间节省:%.2f%%\n",savings);
    }
    fprintf(file,"\n3.时间性能\n");
    fprintf(file,"哈夫曼树构建时间:%.6f 秒\n",metrics->treeBuildTime);
    fprintf(file,"编码时间：%.6f 秒\n",metrics->encodingTime);
    fprintf(file,"译码时间：%.6f 秒\n",metrics->decodingTime);
    if (metrics->encodingTime > 0) {
        fprintf(file,"编码速度：%.2f 字符/秒\n",metrics->originalSize / metrics->encodingTime);
    }
    if(metrics->decodingTime > 0){
        fprintf(file,"译码速度：%.2f 字符/秒\n",metrics->originalSize / metrics->decodingTime);
    }
    fclose(file);
    printf("性能报告已保存到：%s\n",filename);
}
// ============== 工具函数 ==============
char* HT_ReadTextFile(const char* filename, size_t* length) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("无法打开文件：%s\n",filename);
        return NULL;
    }
    // 获取文件大小
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 分配内存
    char* content = (char*)malloc((fileSize + 1) * sizeof(char));
    if (!content) {
        printf("内存分配失败！\n");
        fclose(file);
        return NULL;
    }
    // 读取文件内容
    size_t bytesRead = fread(content, 1, fileSize, file);
    content[bytesRead] = '\0';

    if (length) {
        *length = bytesRead;
    }

    fclose(file);
    return content;
}
int HT_SaveTextFile(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("无法创建文件：%s\n",filename);
        return 0;
    }
    fprintf(file, "%s", content);
    fclose(file);
    return 1;
}
void HT_SaveEncodedText(const char* encoded, const char* filename, int lineWidth) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("无法创建文件: %s\n", filename);
        return;
    }
    int len = strlen(encoded);
    for (int i = 0; i < len; i++) {
        fputc(encoded[i], file);
        if ((i + 1) % lineWidth == 0) {
            fputc('\n', file);
        }
    }
    if (len % lineWidth != 0) {
        fputc('\n', file);
    }
    fclose(file);
    printf("编码文本已保存到：%s\n",filename);
}
void HT_FreeTree(HuffmanTree HT) {
    if (HT) {
        free(HT);
    }
}
// 将整数转换为字符串（替代to_string）
char* intToString(int value) {
    static char buffer[20];
    sprintf(buffer, "%d", value);
    return buffer;
}
// 中序遍历计算每个节点的打印位置
void calculateRanks(HuffmanTree HT, int index, PrintInfo* nodes, int nodeCount) {
    if (index == 0) return;

    // 左子树
    calculateRanks(HT, HT[index].lchild, nodes, nodeCount);

    // 当前节点
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i].index == index) {
            nodes[i].rank = rank_counter;

            // 显示内容：字符(权值) 如：A(5)
            char content[50];  // 在这里声明content
            if (HT[index].data) {
                // 如果是控制字符或空格，特殊处理
                if (HT[index].data == ' ') {
                    sprintf(content, "' '%d", HT[index].weight);
                } else if (HT[index].data < 32 || HT[index].data == 127) {
                    sprintf(content, "0x%02X%d", (unsigned char)HT[index].data, HT[index].weight);
                } else {
                    sprintf(content, "%c%d", HT[index].data, HT[index].weight);
                }
            } else {
                sprintf(content, "I%d", HT[index].weight);  // I表示内部节点
            }

            rank_counter += strlen(content) + 1;  // 内容长度+1个空格
            break;
        }
    }

    // 右子树
    calculateRanks(HT, HT[index].rchild, nodes, nodeCount);
}
// 简单的队列实现（用于C语言）
typedef struct QueueNode {
    int value;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} IntQueue;

void initQueue(IntQueue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

void enqueue(IntQueue* q, int value) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->value = value;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

int dequeue(IntQueue* q) {
    if (q->front == NULL) return -1;

    QueueNode* temp = q->front;
    int value = temp->value;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->size--;
    return value;
}

int queueSize(IntQueue* q) {
    return q->size;
}

int queueEmpty(IntQueue* q) {
    return q->size == 0;
}

void clearQueue(IntQueue* q) {
    while (!queueEmpty(q)) {
        dequeue(q);
    }
}
void HT_PrintTreeGraphical(HuffmanTree HT, int n) {
    if (!HT || n <= 0) {
        printf("哈夫曼树为空！\n");
        return;
    }
    int m = 2 * n - 1;  // 总节点数
    PrintInfo* nodes = (PrintInfo*)malloc(m * sizeof(PrintInfo));

    if (!nodes) {
        printf("内存分配失败！\n");
        return;
    }
    // 收集所有节点信息
    for (int i = 0; i < m; i++) {
        nodes[i].index = i + 1;  // 索引从1开始
        nodes[i].weight = HT[i + 1].weight;
        nodes[i].data = HT[i + 1].data;
        nodes[i].rank = 0;
    }

    // 重置位置计数器
    rank_counter = 0;

    // 找到根节点（parent=0的节点）
    int root = 0;
    for (int i = 1; i <= m; i++) {
        if (HT[i].parent == 0) {
            root = i;
            break;
        }
    }

    if (root == 0) {
        printf("未找到根节点！\n");
        free(nodes);
        return;
    }
    // 计算所有节点的打印位置
    calculateRanks(HT, root, nodes,m);
    printf("\n\n哈夫曼树形化表示:\n\n");
    IntQueue q, verticalPositions;
    initQueue(&q);
    initQueue(&verticalPositions);

    // 存储每层的节点信息
    typedef struct {
        int nodeIndex;
        int nodeRank;
        int leftChildRank;
        int rightChildRank;
        int hasLeftChild;
        int hasRightChild;
    } LevelNodeInfo;

    // 第一层：根节点
    enqueue(&q, root);

    while (!queueEmpty(&q)) {
        int levelSize = queueSize(&q);
        LevelNodeInfo* levelInfo = (LevelNodeInfo*)malloc(levelSize * sizeof(LevelNodeInfo));

        // 收集当前层所有节点信息
        for (int i = 0; i < levelSize; i++) {
            int nodeIndex = dequeue(&q);
            levelInfo[i].nodeIndex = nodeIndex;

            // 查找节点位置
            for (int j = 0; j < m; j++) {
                if (nodes[j].index == nodeIndex) {
                    levelInfo[i].nodeRank = nodes[j].rank;
                    break;
                }
            }

            // 检查是否有子节点并获取子节点位置
            levelInfo[i].hasLeftChild = (HT[nodeIndex].lchild != 0);
            levelInfo[i].hasRightChild = (HT[nodeIndex].rchild != 0);

            if (levelInfo[i].hasLeftChild) {
                for (int j = 0; j < m; j++) {
                    if (nodes[j].index == HT[nodeIndex].lchild) {
                        levelInfo[i].leftChildRank = nodes[j].rank;
                        break;
                    }
                }
                enqueue(&q, HT[nodeIndex].lchild);
            }

            if (levelInfo[i].hasRightChild) {
                for (int j = 0; j < m; j++) {
                    if (nodes[j].index == HT[nodeIndex].rchild) {
                        levelInfo[i].rightChildRank = nodes[j].rank;
                        break;
                    }
                }
                enqueue(&q, HT[nodeIndex].rchild);
            }

            // 记录垂直连接线位置（父节点位置）
            enqueue(&verticalPositions, levelInfo[i].nodeRank);
        }

        // 打印当前层的节点和横线
        int currentPos = 0;

        for (int i = 0; i < levelSize; i++) {
            LevelNodeInfo* info = &levelInfo[i];

            // 如果有左子节点，打印到左子节点的连接线
            if (info->hasLeftChild) {
                // 填充空格到左子节点开始位置
                while (currentPos < info->leftChildRank) {
                    printf(" ");
                    currentPos++;
                }

                // 打印横线到当前节点
                while (currentPos < info->nodeRank) {
                    printf("-");
                    currentPos++;
                }
            } else {
                // 填充空格到节点位置
                while (currentPos < info->nodeRank) {
                    printf(" ");
                    currentPos++;
                }
            }

            // 打印节点
            char nodeStr[20];
            char data = HT[info->nodeIndex].data;
            int weight = HT[info->nodeIndex].weight;

            if (data) {
                if (data == ' ') {
                    sprintf(nodeStr, "' '%d", weight);
                } else if (data < 32 || data == 127) {
                    sprintf(nodeStr, "0x%02X%d", (unsigned char)data, weight);
                } else {
                    sprintf(nodeStr, "%c%d", data, weight);
                }
            } else {
                sprintf(nodeStr, "I%d", weight);  // 内部节点
            }

            printf("%s", nodeStr);
            currentPos += strlen(nodeStr);

            // 如果有右子节点，打印到右子节点的连接线
            if (info->hasRightChild) {
                // 打印横线到右子节点
                int rightEnd = info->rightChildRank;
                if (info->hasLeftChild) {
                    // 如果还有左子节点，横线应该连接到右子节点开始位置
                    rightEnd = info->rightChildRank;
                }

                while (currentPos < rightEnd) {
                    printf("-");
                    currentPos++;
                }

                // 在右子节点开始位置也标记一个竖线位置
                enqueue(&verticalPositions, info->rightChildRank);
            }
        }

        printf("\n");

        // 打印竖线 - 关键修改部分
        // 打印竖线 - 修正后的逻辑
        if (!queueEmpty(&q)) {
            currentPos = 0;

            // 为下一层的所有节点创建竖线位置数组
            int* childPositions = (int*)malloc(500 * sizeof(int));
            int childCount = 0;

            // 先获取下一层所有节点的位置
            // 我们需要知道队列中有哪些节点（下一层的）
            // 由于我们已经dequeue了当前层，下一层节点已经enqueue到队列中
            // 创建一个临时队列来存储下一层节点信息
            IntQueue tempQueue;
            initQueue(&tempQueue);

            // 复制下一层节点到临时队列
            for (int i = 0; i < queueSize(&q); i++) {
                // 这里需要小心处理，因为我们不能直接访问队列内部
                // 更好的方法是：我们已经有下一层所有节点的rank信息
                // 在收集levelInfo时，我们已经enqueue了子节点
                // 我们可以使用verticalPositions队列来获取子节点位置
            }

            // 其实更简单的方法是：我们已经知道每个子节点的rank
            // 只需要从levelInfo中提取所有子节点的位置
            for (int i = 0; i < levelSize; i++) {
                LevelNodeInfo* info = &levelInfo[i];

                if (info->hasLeftChild) {
                    childPositions[childCount++] = info->leftChildRank;
                }
                if (info->hasRightChild) {
                    childPositions[childCount++] = info->rightChildRank;
                }
            }

            // 排序子节点位置
            for (int i = 0; i < childCount - 1; i++) {
                for (int j = i + 1; j < childCount; j++) {
                    if (childPositions[i] > childPositions[j]) {
                        int temp = childPositions[i];
                        childPositions[i] = childPositions[j];
                        childPositions[j] = temp;
                    }
                }
            }

            // 绘制竖线
            for (int i = 0; i < childCount; i++) {
                int pos = childPositions[i];

                // 填充空格到竖线位置
                while (currentPos < pos) {
                    printf(" ");
                    currentPos++;
                }

                printf("|");
                currentPos++;
            }

            printf("\n");
            free(childPositions);
        }
        free(levelInfo);
    }

    printf("\n图列：\n");
    printf(" -字符后跟数字表示权值(如：A5表示字符A，权值5)\n");
    printf(" -I表示内部节点(无字符)\n");
    printf(" -' '表示空格字符\n");
    printf(" -0xXX表示控制字符的十六进制表示\n");
    free(nodes);
}
