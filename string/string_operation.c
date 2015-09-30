/**
    以堆分配存储表示串，串基本操作
    作者：nuaazdh
    时间：2012年5月28日
*/
#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1


typedef int Status;
typedef struct{//串的堆存储表示
    char *ch;   //若非空串，则按串长分配存储区域，否则ch为NULL
    int length; // 串长度
}HString;

//------------基本操作函数原型-------------//
Status StrAssign(HString *T,char *chars);
    //生成一个其值等于串常量chars的串T
int StrLength(HString S);
    //返回串S的元素个数，即串的长度
int StrCompare(HString S,HString T);
    //若S>T，则返回值>0；若S==T，则返回值=0，若S<T，则返回值<0
Status ClearString(HString *S);
    //将S清为空串，并释放S的空间
Status Concat(HString *T,HString S1,HString S2);
    //用T返回由S1和S2连接而成的新串
Status SubString(HString *Sub,HString S,int pos,int len);
    //1<=pos<=StrLength(S)且0<=len<=StrLength(S)-pos-1
    //返回串S的第pos个字符起长度为len的字串

void PrintString(HString S);
    //打印串S的信息，长度和ch内容
HString NullString();
    //创造一个新的空串，长度为0，ch为空

//===============main()函数=================//
int main(){
    char *str1="Hello world!",*str2="Hello,I'm nuaazdh";
    int len,comp;
    HString S1=NullString(),S2=NullString(),S3=NullString();
    // StrAssign()函数测试
    StrAssign(&S1,str1);
    StrAssign(&S2,str2);
    // StrLength()函数测试
    printf("Length of S1: %d\n",StrLength(S1));
    // Concat()函数测试
    Concat(&S3,S1,S2);
    PrintString(S3);
    // StrCompare()函数测试
    comp=StrCompare(S1,S2);
    printf("The compare result of S1 & S2: %d\n",comp);
    // SubString()函数测试
    SubString(&S3,S1,1,5);
    PrintString(S3);
    // ClearString()函数测试
    ClearString(&S3);
    PrintString(S3);
    return 0;
}


//-------------基本操作的算法描述-----------//
Status StrAssign(HString *T,char *chars){
    //生成一个其值等于串常量chars的串T
    int i=0,j;char *c;
    if(T->ch) free(T->ch);  //释放T的原有空间
    for(i=0,c=chars;*c!='\0';i++,c++); //求chars的长度i
    if(!i){ //chars长度为0
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
    //返回串S的元素个数，即串的长度
    return S.length;
}

int StrCompare(HString S,HString T){
    //若S>T，则返回值>0；若S==T，则返回值=0，若S<T，则返回值<0
    int i;
    for(i=0;i<S.length && i<T.length;i++)// 循环比较
        if(S.ch[i]!=T.ch[i])
            return S.ch[i]-T.ch[i];
    return S.length-T.length;
    return OK;
}

Status ClearString(HString *S){
    //将S清为空串，并释放S的空间
    if(S->ch){
        free(S->ch);    //释放空间
        S->ch=NULL;
    }
    S->length=0;
    return OK;
    return OK;
}

Status Concat(HString *T,HString S1,HString S2){
    //用T返回由S1和S2连接而成的新串
    int i;
    if(T->ch) free(T->ch);//释放T的串空间
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
    //1<=pos<=StrLength(S)且0<=len<=StrLength(S)-pos-1
    //返回串S的第pos个字符起长度为len的字串
    int i=0;
    if(pos<1 || pos>S.length || len<0 || pos+len>S.length+1)
        return ERROR;
    if(Sub->ch) free(Sub->ch);  // 释放S原有空间
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
    //打印串S的信息，长度和ch内容
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
    //创造一个新的空串，长度为0，ch为空
    HString S;
    S.length=0;
    S.ch=NULL;
    return S;
}
