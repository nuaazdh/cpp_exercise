/**
    ������֮��Ϣ����
    ���ߣ�nuaazdh
    ʱ�䣺2012��5��29��
*/
#include <stdio.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

#define MaxBookNum  1000    // ����ֻ��1000���齨��������
#define MaxKeyNum   2500    // ��������������
#define MaxLineLen  500     // ��Ŀ������󳤶�
#define MaxWordNum  10      // �ʱ���������

typedef int Status;

typedef struct{//���ĶѴ洢��ʾ
    char * ch;   //���ǿմ����򰴴�������洢���򣬷���chΪNULL
    int length; // ������
}HString;

typedef struct{
    char **item; // �ַ���
    int last;   // �ʱ�ĳ���
}WordListType;  // �ʱ����ͣ�˳���

typedef int ElemType;// �������������Ԫ������Ϊ���ͣ�������ͣ�

typedef struct LNode{ //����ṹ
    ElemType data;
    struct LNode* next;
}LNode,*LinkList;

typedef struct {
    HString key;        // �ؼ���
    LinkList bnolist;   // ����������������
}IdxTermType;           // ����������

typedef struct {
    IdxTermType item[MaxKeyNum+1];
    int last;
}IdxListType;   //���������ͣ������

// ��Ҫ����
char *buf;              // ��Ŀ����������
WordListType wdlist;    // �ʱ�

// ��������
void InitIdxList(IdxListType *idxlist);
    // ��ʼ����������������idxlistΪ�ձ�����idxlist.item[0]��һ�մ�
void GetLine(FILE f);
    // ���ļ�f����һ����Ŀ��Ϣ����Ŀ��������buf
void ExtractKeyWord(ElemType *bno);
    // ��buf����ȡ�����ؼ��ʵ��ʱ�wdlist����Ŵ���bno
Status InsIdxList(IdxListType *idxlist, ElemType bno);
    // �����Ϊbno�������ؼ��ʰ��ʵ�˳�����������idxlist
void PutText(FILE g,IdxListType idxlist);
    // �����ɵ�������idxlist������ļ�g��

int main(){
    return 0;
}
