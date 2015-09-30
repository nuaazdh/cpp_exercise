/**
    以堆分配存储表示串，KMP串匹配算法
    作者：nuaazdh
    时间：2012年5月29日
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
int Index(HString S,HString T,int pos,int *next);
    //利用模式串T的next函数求T在主串S中的第pos个字符之后的
    //KMP算法，其中T非空，1<=pos<=StrLength(S)
int *get_next(HString T,int *next);
    //求模式串T的next函数值并存入数值next中
int *get_nextval(HString T,int *next);
    //求模式串T的next函数修正值并存入数组nextval

void PrintString(HString S);
    //打印串S的信息，长度和ch内容
HString NullString();
    //创造一个新的空串，长度为0，ch为空

//===============main()函数=================//
int main(){
    char *tstr="abaabcac";
    char *sstr="acabaabaabcacaabc";
    int *next=NULL,i=0;
    HString T=NullString();
    HString S=NullString();
    StrAssign(&T,tstr);
    StrAssign(&S,sstr);
    //next=get_next(T,next);
    next=get_nextval(T,next);
    PrintString(T);
    PrintString(S);
    printf("KMP result:%d\n",Index(S,T,1,next));
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

int Index(HString S,HString T,int pos,int *next){
    //利用模式串T的next函数求T在主串S中的第pos个字符之后的
    //KMP算法，其中T非空，1<=pos<=StrLength(S)
    int i=pos,j=1,k;
    while(i<=S.length && j<=T.length){
        if(j==0 || S.ch[i-1]==T.ch[j-1]){
            i++;    j++;        // 继续比较后续字符
        }else{
            j=next[j-1];          //模式串向右移动
        }
    }//while
    if(j>T.length)
            return i-T.length;  //匹配成功
        else
            return 0;   //
}

int *get_next(HString T,int *next){
    //求模式串T的next函数值并存入数值next中
    int i,j;
    if(next) free(next);    //释放原有空间
    next=(int *)malloc((T.length)*sizeof(int));
    if(!next)   exit(OVERFLOW);
    i=0;next[0]=0;j=0;
    while(i<T.length){
        if(j==0 || T.ch[i]==T.ch[j-1]){
            ++i;    ++j;    next[i]=j;
        }else{
            j=next[j-1];
        }
    }
    return next;
}

int *get_nextval(HString T,int *nextval){
    //求模式串T的next函数修正值并存入数组nextval
    int i,j;
    if(nextval)    free(nextval);
    if(!(nextval=(int *)malloc(T.length*sizeof(int))))
        exit(OVERFLOW);
    i=0;nextval[0]=0;j=0;
    while(i<T.length){
        if(j==0||T.ch[i]==T.ch[j-1]){
            i++;    j++;
            if(T.ch[i]!=T.ch[j-1]){
                nextval[i]=j;
            }else{
                nextval[i]=nextval[j-1];
            }
        }else{
            j=nextval[j-1];
        }
    }
    return nextval;

}//get_nextval

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
