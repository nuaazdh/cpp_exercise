/**
    �Զѷ���洢��ʾ��������������
    ���ߣ�nuaazdh
    ʱ�䣺2012��5��28��
*/
#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1


typedef int Status;
typedef struct{//���ĶѴ洢��ʾ
    char *ch;   //���ǿմ����򰴴�������洢���򣬷���chΪNULL
    int length; // ������
}HString;

//------------������������ԭ��-------------//
Status StrAssign(HString *T,char *chars);
    //����һ����ֵ���ڴ�����chars�Ĵ�T
int StrLength(HString S);
    //���ش�S��Ԫ�ظ����������ĳ���
int StrCompare(HString S,HString T);
    //��S>T���򷵻�ֵ>0����S==T���򷵻�ֵ=0����S<T���򷵻�ֵ<0
Status ClearString(HString *S);
    //��S��Ϊ�մ������ͷ�S�Ŀռ�
Status Concat(HString *T,HString S1,HString S2);
    //��T������S1��S2���Ӷ��ɵ��´�
Status SubString(HString *Sub,HString S,int pos,int len);
    //1<=pos<=StrLength(S)��0<=len<=StrLength(S)-pos-1
    //���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���ִ�

void PrintString(HString S);
    //��ӡ��S����Ϣ�����Ⱥ�ch����
HString NullString();
    //����һ���µĿմ�������Ϊ0��chΪ��

//===============main()����=================//
int main(){
    char *str1="Hello world!",*str2="Hello,I'm nuaazdh";
    int len,comp;
    HString S1=NullString(),S2=NullString(),S3=NullString();
    // StrAssign()��������
    StrAssign(&S1,str1);
    StrAssign(&S2,str2);
    // StrLength()��������
    printf("Length of S1: %d\n",StrLength(S1));
    // Concat()��������
    Concat(&S3,S1,S2);
    PrintString(S3);
    // StrCompare()��������
    comp=StrCompare(S1,S2);
    printf("The compare result of S1 & S2: %d\n",comp);
    // SubString()��������
    SubString(&S3,S1,1,5);
    PrintString(S3);
    // ClearString()��������
    ClearString(&S3);
    PrintString(S3);
    return 0;
}


//-------------�����������㷨����-----------//
Status StrAssign(HString *T,char *chars){
    //����һ����ֵ���ڴ�����chars�Ĵ�T
    int i=0,j;char *c;
    if(T->ch) free(T->ch);  //�ͷ�T��ԭ�пռ�
    for(i=0,c=chars;*c!='\0';i++,c++); //��chars�ĳ���i
    if(!i){ //chars����Ϊ0
        T->ch=NULL;
        T->length=0;
    }else{
        if(!(T->ch=(char *)malloc(i*sizeof(char))))
            exit(OVERFLOW);
        for(j=0;j<i;j++){
            T->ch[j]=chars[j];
        }
        T->length=i;
    }
    return OK;
}

int StrLength(HString S){
    //���ش�S��Ԫ�ظ����������ĳ���
    return S.length;
}

int StrCompare(HString S,HString T){
    //��S>T���򷵻�ֵ>0����S==T���򷵻�ֵ=0����S<T���򷵻�ֵ<0
    int i;
    for(i=0;i<S.length && i<T.length;i++)// ѭ���Ƚ�
        if(S.ch[i]!=T.ch[i])
            return S.ch[i]-T.ch[i];
    return S.length-T.length;
    return OK;
}

Status ClearString(HString *S){
    //��S��Ϊ�մ������ͷ�S�Ŀռ�
    if(S->ch){
        free(S->ch);    //�ͷſռ�
        S->ch=NULL;
    }
    S->length=0;
    return OK;
    return OK;
}

Status Concat(HString *T,HString S1,HString S2){
    //��T������S1��S2���Ӷ��ɵ��´�
    int i;
    if(T->ch) free(T->ch);//�ͷ�T�Ĵ��ռ�
    if(!(T->ch=(char*)malloc((S1.length+S2.length)*sizeof(char)))){
        exit(OVERFLOW);
    }
    T->length=S1.length+S2.length;
    for(i=0;i<S1.length;i++){
        T->ch[i]=S1.ch[i];
    }
    for(;i<T->length;i++){
        T->ch[i]=S2.ch[i-S1.length];
    }
    return OK;
}

Status SubString(HString *Sub,HString S,int pos,int len){
    //1<=pos<=StrLength(S)��0<=len<=StrLength(S)-pos-1
    //���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���ִ�
    int i=0;
    if(pos<1 || pos>S.length || len<0 || pos+len>S.length+1)
        return ERROR;
    if(Sub->ch) free(Sub->ch);  // �ͷ�Sԭ�пռ�
    if(!len){
        Sub->ch=NULL;
        Sub->length=0;
    }else{
        Sub->ch=(char*)malloc(len*sizeof(char));
        Sub->length=len;
        for(i=0;i<len;i++)
            Sub->ch[i]=S.ch[pos+i-1];
    }
    return OK;
}


void PrintString(HString S){
    //��ӡ��S����Ϣ�����Ⱥ�ch����
    int i;
    printf("Length of the String: %d\n",S.length);
    if(0!=S.length){
        printf("Context of the String: ");
        for(i=0;i<S.length;i++){
            printf("%c",S.ch[i]);
        }
        printf("\n");
    }
}

HString NullString(){
    //����һ���µĿմ�������Ϊ0��chΪ��
    HString S;
    S.length=0;
    S.ch=NULL;
    return S;
}
