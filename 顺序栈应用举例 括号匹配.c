//顺序栈的使用举例：括号的匹配
//作者：nuaazdh
//时间：2011年12月5日
#include <stdio.h>
#include <stdlib.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define BUFFERSIZE 256

typedef int Status; //函数返回状态
typedef char SElemType;  //栈元素类型
typedef struct{//栈结构定义
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

Status InitStack(SqStack *S);
    //构造一个空栈S
Status DestroyStack(SqStack *S);
    //销毁栈S，S不再存在
Status ClearStack(SqStack *S);
    //把栈S置为空栈
Status StackEmpty(SqStack S);
    //若栈S为空栈，则返回TRUE，否则返回FALSE
int StackLength(SqStack S);
    //返回S元素的个数，即栈的长度
Status GetTop(SqStack S,SElemType *e);
    //若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
Status Push(SqStack *S,SElemType e);
    //插入元素e为新的栈顶元素
Status Pop(SqStack *S,SElemType *e);
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR
Status StackTraverse(const SqStack *S);
    //从栈底到栈顶依次对每个元素进行访问
Status BracketMatch(SqStack *S,const char *string);
    //输入字符串string中的括号匹配，返回TRUE；否则返回FALSE

int main()
{
    char *string;
    SqStack stack;
    string=(char*)malloc(sizeof(char)*BUFFERSIZE);
    if(!string){
        printf("分配内存失败.\n");
        exit(0);
    }
    while(1){
        printf("请输入一行含括号的表达式（输入\"!\"退出）：");
        gets(string);
        if(string[0]=='!')//退出
            break;
        if(TRUE==BracketMatch(&stack,string)){
            printf("\n能  正确匹配.\n\n");
        }else{
            printf("\n不能 正确匹配.\n\n");
        }
    }//while
    return 0;
}

Status InitStack(SqStack *S){
    //构造一个空栈S
    S->base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base)//分配失败
    {
        printf("分配内存失败.\n");
        exit(0);
    }
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

Status DestroyStack(SqStack *S){
    //销毁栈S，S不再存在
    if(!S)//S为空
    {
        printf("指针为空，释放失败.\n");
        exit(0);
    }
    free(S);
    return OK;
}

Status ClearStack(SqStack *S){
    //把栈S置为空栈
    if(!S)//S不存在
        return FALSE;
    S->top=S->base;//直接将栈顶指针指向栈底
    return OK;
}

Status StackEmpty(SqStack S){
    //若栈S为空栈，则返回TRUE，否则返回FALSE
    if(S.top==S.base)
        return TRUE;
    else
        return FALSE;
}

int StackLength(SqStack S){
    //返回S元素的个数，即栈的长度
    return S.stacksize;
}

Status GetTop(SqStack S,SElemType *e){
    //若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
    if(S.top==S.base){
        //printf("栈为空.\n");
        return FALSE;
    }else{
        *e=*(S.top-1);
        //printf("%c",*e);
        return OK;
    }
}

Status Push(SqStack *S,SElemType e){
    //插入元素e为新的栈顶元素
    if(S->top-S->base>=S->stacksize){//栈已满，追加存储空间
        S->base=(SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!S->base)
        {
            printf("重新申请空间失败.\n");
            exit(0);
        }
        S->top=S->base+S->stacksize;//更改栈顶指针
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}

Status Pop(SqStack *S,SElemType *e){
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR
    if(S->top==S->base){//栈为空
        printf("栈为空.\n");
        return ERROR;
    }
    *e=*(--S->top);
    return OK;
}

Status StackTraverse(const SqStack *S){
    //从栈底到栈顶依次对每个元素进行访问
    SElemType *p=S->base;
    if(S->base==S->top)
    {
        printf("栈为空.\n");
        return FALSE;
    }
    //printf("栈中元素：");
    while(p!=S->top)
    {
        printf("%c",*p++);
    }
    printf("\n");
    return OK;
}

Status BracketMatch(SqStack *S,const char *string){
    //输入字符串string中的括号匹配，返回TRUE；否则返回FALSE
    const char *p=string;
    SElemType e;
    InitStack(S);
    while(*p!='\0'){//遍历字符串
        switch(*p){//判断p的值
            case '('://左括号，入栈
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
    if(!StackEmpty(*S))//字符串遍历完，栈非空，不匹配
        return FALSE;
    return TRUE;
}
