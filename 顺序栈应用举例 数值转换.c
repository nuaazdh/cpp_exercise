//˳��ջ��ʹ��
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
#define BASE    8 //����

typedef int Status; //��������״̬
typedef int SElemType;  //ջԪ������
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
Status ConvertScale(SqStack *S,int orgin,int base);
    //������orginת��Ϊbase���ƣ�����˳��ջS��

int main()
{
    //��ֵת��
    int origin;
    SElemType e;
    SqStack stack;
    printf("������һ��������");
    scanf("%d",&origin);
    ConvertScale(&stack,origin,BASE);
    printf("%d��Ӧ�İ˽�����Ϊ��",origin);
    while(!StackEmpty(stack)){
        Pop(&stack,&e);
        printf("%d",e);
    }
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
        printf("ջΪ��.\n");
        return FALSE;
    }else{
        *e=*(S.top-1);
        printf("ջ��Ԫ�أ�%c\n",*e);
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
        printf("%d",*p++);
    }
    printf("\n");
    return OK;
}

Status ConvertScale(SqStack *S,int origin,int base){
    //������orginת��Ϊbase���ƣ�����˳��ջS��
    if(origin<0)
        return FALSE;
    InitStack(S);
    while(origin){
        Push(S,origin%base);
        origin=origin/base;
    }//while
    return OK;
}

