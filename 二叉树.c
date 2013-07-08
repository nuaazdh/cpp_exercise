//二叉树创建与遍历
//作者：nuaazdh
//时间：2011年12月23日 19:54:41
#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status; //定义函数结果状态

typedef char TElemType;
typedef struct BiTNode{//二叉树的二叉链表存储结构
    TElemType data; //数据
    struct BiTNode *lchild,*rchild; //左右孩子指针

}BiTNode,*BiTree;
//----------二叉树基本操作-------------//
Status CreateBiTree(BiTree *T);
    //按先序次序输入二叉树中结点的值（一个字符），空格表示空树
    //构造二叉链表表示的二叉树T
Status PreOrderTraverse(BiTree *T);
    //先序遍历二叉链表表示的二叉树T
Status InOrderTraverse(BiTree *T);
    //中序遍历二叉链表表示的二叉树T
Status PostOrderTraverse(BiTree *T);
    //后序遍历二叉链表表示的二叉树T
Status IsLetter(char c);
    //判断字符c是否是子母，是返回TRUE，否则返回FALSE

//--------------主函数---------------//
int main()
{
    BiTree T;
    char c[256];
    printf("请输入根结点数据:");
    scanf("%s",c);
    if(TRUE==IsLetter(c[0])){
        T=(BiTree)malloc(sizeof(BiTNode));
        T->data=c[0];
        T->lchild=NULL;
        T->rchild=NULL;
        CreateBiTree(&T);
    }
    printf("\n先序遍历结果：\n");
    PreOrderTraverse(&T);
    printf("\n中序遍历结果：\n");
    InOrderTraverse(&T);
    printf("\n后序遍历结果：\n");
    PostOrderTraverse(&T);
    return 0;
}

Status CreateBiTree(BiTree *T){
    //按先序次序输入二叉树中结点的值（一个字符），空格表示空树
    //构造二叉链表表示的二叉树T
    char buffer[256];
    if(*T){
        printf("请输入 %c 的左子树根节点(限单个子母，否则视为空)：",(*T)->data);
        scanf("%s",buffer);
        if(TRUE==IsLetter(buffer[0])){
            (*T)->lchild=(BiTree)malloc(sizeof(BiTNode));
            (*T)->lchild->data=buffer[0];
            (*T)->lchild->lchild=NULL;
            (*T)->lchild->rchild=NULL;
        }
        printf("请输入 %c 的右子树根节点(限单个子母，否则视为空)：",(*T)->data);
        scanf("%s",buffer);
        if(TRUE==IsLetter(buffer[0])){
            (*T)->rchild=(BiTree)malloc(sizeof(BiTNode));
            (*T)->rchild->data=buffer[0];
            (*T)->rchild->lchild=NULL;
            (*T)->rchild->rchild=NULL;
        }
        CreateBiTree(&((*T)->lchild));//创建左子树
        CreateBiTree(&((*T)->rchild));//创建右子树
    }
    return OK;
}

Status PreOrderTraverse(BiTree *T){
    //先序遍历二叉链表表示的二叉树T
    if(*T){//T不为空
        printf(" %c ",(*T)->data);
        PreOrderTraverse(&((*T)->lchild));//先序遍历左子树
        PreOrderTraverse(&((*T)->rchild));//先序遍历右子树
    }
    return OK;
}

Status InOrderTraverse(BiTree *T){
    //中序遍历二叉链表表示的二叉树T
    if(*T){
        InOrderTraverse(&((*T)->lchild));
        printf(" %c ",(*T)->data);
        InOrderTraverse(&((*T)->rchild));
    }
    return OK;
}

Status PostOrderTraverse(BiTree *T){
    //后序遍历二叉链表表示的二叉树T
    if(*T){
        PostOrderTraverse(&((*T)->lchild));
        PostOrderTraverse(&((*T)->rchild));
        printf(" %c ",(*T)->data);
    }
    return OK;
}

Status IsLetter(char c){
    //判断字符c是否是子母，是返回TRUE，否则返回FALSE
    if((c>='a')&&(c<='z')||(c>='A')&&(c<='Z'))
        return TRUE;
    else
        return FALSE;
}
