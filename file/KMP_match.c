/**
    �Զѷ���洢��ʾ����KMP��ƥ���㷨
    ���ߣ�nuaazdh
    ʱ�䣺2012��5��29��
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
int Index(HString S,HString T,int pos,int *next);
    //����ģʽ��T��next������T������S�еĵ�pos���ַ�֮���
    //KMP�㷨������T�ǿգ�1<=pos<=StrLength(S)
int *get_next(HString T,int *next);
    //��ģʽ��T��next����ֵ��������ֵnext��
int *get_nextval(HString T,int *next);
    //��ģʽ��T��next��������ֵ����������nextval

void PrintString(HString S);
    //��ӡ��S����Ϣ�����Ⱥ�ch����
HString NullString();
    //����һ���µĿմ�������Ϊ0��chΪ��

//===============main()����=================//
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

int Index(HString S,HString T,int pos,int *next){
    //����ģʽ��T��next������T������S�еĵ�pos���ַ�֮���
    //KMP�㷨������T�ǿգ�1<=pos<=StrLength(S)
    int i=pos,j=1,k;
    while(i<=S.length && j<=T.length){
        if(j==0 || S.ch[i-1]==T.ch[j-1]){
            i++;    j++;        // �����ȽϺ����ַ�
        }else{
            j=next[j-1];          //ģʽ�������ƶ�
        }
    }//while
    if(j>T.length)
            return i-T.length;  //ƥ��ɹ�
        else
            return 0;   //
}

int *get_next(HString T,int *next){
    //��ģʽ��T��next����ֵ��������ֵnext��
    int i,j;
    if(next) free(next);    //�ͷ�ԭ�пռ�
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
    //��ģʽ��T��next��������ֵ����������nextval
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
