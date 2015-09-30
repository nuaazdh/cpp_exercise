//˳��ջ��ʹ�þ��������ŵ�ƥ��
//���ߣ�nuaazdh
//ʱ�䣺2011��12��5��
#include <stdio.h>
#include <stdlib.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define BUFFERSIZE 256

typedef int Status; //��������״̬
typedef char SElemType;  //ջԪ������
typedef struct{//ջ�ṹ����
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

Status InitStack(SqStack *S);
    //����һ����ջS
Status DestroyStack(SqStack *S);
    //����ջS��S���ٴ���
Status ClearStack(SqStack *S);
    //��ջS��Ϊ��ջ
Status StackEmpty(SqStack S);
    //��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE
int StackLength(SqStack S);
    //����SԪ�صĸ�������ջ�ĳ���
Status GetTop(SqStack S,SElemType *e);
    //��ջ��Ϊ�գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�FALSE
Status Push(SqStack *S,SElemType e);
    //����Ԫ��eΪ�µ�ջ��Ԫ��
Status Pop(SqStack *S,SElemType *e);
    //��ջS��Ϊ�գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK,���򷵻�ERROR
Status StackTraverse(const SqStack *S);
    //��ջ�׵�ջ�����ζ�ÿ��Ԫ�ؽ��з���
Status BracketMatch(SqStack *S,const char *string);
    //�����ַ���string�е�����ƥ�䣬����TRUE�����򷵻�FALSE

int main()
{
    char *string;
    SqStack stack;
    string=(char*)malloc(sizeof(char)*BUFFERSIZE);
    if(!string){
        printf("�����ڴ�ʧ��.\n");
        exit(0);
    }
    while(1){
        printf("������һ�к����ŵı��ʽ������\"!\"�˳�����");
        gets(string);
        if(string[0]=='!')//�˳�
            break;
        if(TRUE==BracketMatch(&stack,string)){
            printf("\n��  ��ȷƥ��.\n\n");
        }else{
            printf("\n���� ��ȷƥ��.\n\n");
        }
    }//while
    return 0;
}

Status InitStack(SqStack *S){
    //����һ����ջS
    S->base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base)//����ʧ��
    {
        printf("�����ڴ�ʧ��.\n");
        exit(0);
    }
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

Status DestroyStack(SqStack *S){
    //����ջS��S���ٴ���
    if(!S)//SΪ��
    {
        printf("ָ��Ϊ�գ��ͷ�ʧ��.\n");
        exit(0);
    }
    free(S);
    return OK;
}

Status ClearStack(SqStack *S){
    //��ջS��Ϊ��ջ
    if(!S)//S������
        return FALSE;
    S->top=S->base;//ֱ�ӽ�ջ��ָ��ָ��ջ��
    return OK;
}

Status StackEmpty(SqStack S){
    //��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE
    if(S.top==S.base)
        return TRUE;
    else
        return FALSE;
}

int StackLength(SqStack S){
    //����SԪ�صĸ�������ջ�ĳ���
    return S.stacksize;
}

Status GetTop(SqStack S,SElemType *e){
    //��ջ��Ϊ�գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�FALSE
    if(S.top==S.base){
        //printf("ջΪ��.\n");
        return FALSE;
    }else{
        *e=*(S.top-1);
        //printf("%c",*e);
        return OK;
    }
}

Status Push(SqStack *S,SElemType e){
    //����Ԫ��eΪ�µ�ջ��Ԫ��
    if(S->top-S->base>=S->stacksize){//ջ������׷�Ӵ洢�ռ�
        S->base=(SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!S->base)
        {
            printf("��������ռ�ʧ��.\n");
            exit(0);
        }
        S->top=S->base+S->stacksize;//����ջ��ָ��
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}

Status Pop(SqStack *S,SElemType *e){
    //��ջS��Ϊ�գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK,���򷵻�ERROR
    if(S->top==S->base){//ջΪ��
        printf("ջΪ��.\n");
        return ERROR;
    }
    *e=*(--S->top);
    return OK;
}

Status StackTraverse(const SqStack *S){
    //��ջ�׵�ջ�����ζ�ÿ��Ԫ�ؽ��з���
    SElemType *p=S->base;
    if(S->base==S->top)
    {
        printf("ջΪ��.\n");
        return FALSE;
    }
    //printf("ջ��Ԫ�أ�");
    while(p!=S->top)
    {
        printf("%c",*p++);
    }
    printf("\n");
    return OK;
}

Status BracketMatch(SqStack *S,const char *string){
    //�����ַ���string�е�����ƥ�䣬����TRUE�����򷵻�FALSE
    const char *p=string;
    SElemType e;
    InitStack(S);
    while(*p!='\0'){//�����ַ���
        switch(*p){//�ж�p��ֵ
            case '('://�����ţ���ջ
            case '[':
            case '{':
                Push(S,*p);
                //printf("Push %c",*p);
                break;
            case ')':
                if(FALSE==GetTop(*S,&e))
                    return FALSE;
                if(e=='('){
                    if(ERROR==Pop(S,&e))
                        return FALSE;
                    //printf("Push %c",*p);
                }else
                    return FALSE;
                break;
            case ']':
                if(FALSE==GetTop(*S,&e))
                    return FALSE;
                if(e=='['){
                    if(ERROR==Pop(S,&e))
                        return FALSE;
                    //printf("Push %c",*p);
                }else
                    return FALSE;
                break;
            case '}':
                if(FALSE==GetTop(*S,&e))
                    return FALSE;
                if(e=='{'){
                    if(ERROR==Pop(S,&e))
                        return FALSE;
                    //printf("Push %c",*p);
                }else
                    return FALSE;
                break;
            default:
                ;
        }//switch
        p++;
    }//while
    if(!StackEmpty(*S))//�ַ��������꣬ջ�ǿգ���ƥ��
        return FALSE;
    return TRUE;
}
