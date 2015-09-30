/**
    串操作之信息检索
    作者：nuaazdh
    时间：2012年5月29日
*/
#include <stdio.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

#define MaxBookNum  1000    // 假设只对1000本书建立索引表
#define MaxKeyNum   2500    // 索引表的最大容量
#define MaxLineLen  500     // 书目串的最大长度
#define MaxWordNum  10      // 词表的最大容量

typedef int Status;

typedef struct{//串的堆存储表示
    char * ch;   //若非空串，则按串长分配存储区域，否则ch为NULL
    int length; // 串长度
}HString;

typedef struct{
    char **item; // 字符串
    int last;   // 词表的长度
}WordListType;  // 词表类型（顺序表）

typedef int ElemType;// 定义链表的数据元素类型为整型（书号类型）

typedef struct LNode{ //链表结构
    ElemType data;
    struct LNode* next;
}LNode,*LinkList;

typedef struct {
    HString key;        // 关键词
    LinkList bnolist;   // 存放书号索引的链表
}IdxTermType;           // 索引项类型

typedef struct {
    IdxTermType item[MaxKeyNum+1];
    int last;
}IdxListType;   //索引表类型（有序表）

// 主要变量
char *buf;              // 书目索引缓冲区
WordListType wdlist;    // 词表

// 基本操作
void InitIdxList(IdxListType *idxlist);
    // 初始化操作，置索引表idxlist为空表，且在idxlist.item[0]设一空串
void GetLine(FILE f);
    // 从文件f杜宇一个书目信息到书目串缓冲区buf
void ExtractKeyWord(ElemType *bno);
    // 从buf中提取书名关键词到词表wdlist，书号存入bno
Status InsIdxList(IdxListType *idxlist, ElemType bno);
    // 将书号为bno的书名关键词按词典顺序插入索引表idxlist
void PutText(FILE g,IdxListType idxlist);
    // 将生成的索引表idxlist输出到文件g中

int main(){
    return 0;
}
