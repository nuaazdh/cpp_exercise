//二叉树遍历
//作者：nuaazdh
//时间：2011年12月1日

#include<stdio.h>
#include<stdlib.h>

#define OK          1
#define ERROR       0
#define TRUE        1
#define FALSE       0
#define OVERFLOW    -1

#define STACK_INIT_SIZE     100
#define STACKINCREMENT      10

typedef int Status;
typedef char ElemType;  // 二叉树结点元素类型
typedef struct BiTNode{ // 二叉树结点结构
    char data;            // 结点数据
    struct BiTNode *lchild;        // 左孩子
    struct BiTNode *rchild;        // 右孩子
}BiTNode,*BiTree;

typedef BiTree SElemType;
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

Status CreateBiTree(BiTree T);
    // 按先后次序输入二叉树中结点的值（一个字符），空格表示空树
    // 构造二叉链表表示的二叉树T
Status PreOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
    // 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
    // 先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
Status InOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
    // 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
    // 中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
Status PostOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
    // 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
    // 后序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
Status PreOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
    // 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
    // 先序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit
Status InOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
    // 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
    // 中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit
Status PostOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
    // 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
    // 后序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit
Status Visit(ElemType e);
    // 对二叉树中的数据元素访问

int main()
{
    BiTree T=NULL;
    printf("Please input the data of a tree in sequence:\n");
    CreateBiTree(T);
    return 0;
}

Status CreateBiTree(BiTree T){
    // 按先后次序输入二叉树中结点的值（一个字符），空格表示空树
    // 构造二叉链表表示的二叉树T
    char ch;
    scanf("%c",&ch);
    if(ch==' ') T=NULL;
    else{
        if(!(T=(BiTNode *)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);
        T->data=ch;                 // 生成根节点
        CreateBiTree(T->lchild);    // 构造左子树
        CreateBiTree(T->rchild);    // 构造右子树
    }
    return OK;
}

Status PreOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e))
{   // 先序遍历递归算法

    if(T){
        if(!Visit(T->data)) return ERROR;
        PreOrderRecursionTraverse(T->lchild,Visit);
        PreOrderRecursionTraverse(T->rchild,Visit);
    }
    return OK;
}

Status InOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e))
{   // 中序遍历递归算法
    if(T){
        InOrderRecursionTraverse(T->lchild,Visit);
        if(!Visit(T->data)) return ERROR;;
        InOrderRecursionTraverse(T->rchild,Visit);
    }
    return OK;
}


Status PostOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e))
{   //后序遍历递归算法
    if(T){
        PostOrderRecursionTraverse(T->lchild,Visit);
        PostOrderRecursionTraverse(T->rchild,Visit);
        if(!Visit(T->data)) return ERROR;;
    }
    return OK;
}

Status PreOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e)){
    // 先序遍历二叉树T的非递归算法
    SqStack S;
    SElemType p;
    InitStack(&S);      Push(&S,T); // 根指针入栈
    while(!StackEmpty(S)){
        while(GetTop(S,&p)&&p)   Push(&S,p->lchild);    //向左走到尽头
        Pop(&S,&p);     //空指针出栈
        if(!StackEmpty(S)){//访问结点，向右一步
            Pop(&S,&p);
            if(!Visit(p->data)) return ERROR;
            Push(&S,p->lchild);
        }//if
    }//while
    return OK;
}

Status InOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e)){
    // 中序遍历二叉树T的非递归算法
    return OK;
}

Status PostOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e)){
    // 后序遍历二叉树T的非递归算法
    return OK;
}

Status Visit(ElemType e){
    // 对二叉树中的数据元素访问
    if(e=='\0'){
        return ERROR;
    }else{
        printf("%c",e);
    }
    return OK;
}

//-----------顺序栈操作--------------//

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
        printf("栈为空.\n");
        return FALSE;
    }else{
        *e=*(S.top-1);
        printf("栈顶元素：%c\n",*e);
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
