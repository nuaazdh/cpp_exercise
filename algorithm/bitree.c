//���������������
//���ߣ�nuaazdh
//ʱ�䣺2011��12��23�� 19:54:41
#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status; //���庯�����״̬

typedef char TElemType;
typedef struct BiTNode{//�������Ķ�������洢�ṹ
    TElemType data; //����
    struct BiTNode *lchild,*rchild; //���Һ���ָ��

}BiTNode,*BiTree;
//----------��������������-------------//
Status CreateBiTree(BiTree *T);
    //�������������������н���ֵ��һ���ַ������ո��ʾ����
    //������������ʾ�Ķ�����T
Status PreOrderTraverse(BiTree *T);
    //����������������ʾ�Ķ�����T
Status InOrderTraverse(BiTree *T);
    //����������������ʾ�Ķ�����T
Status PostOrderTraverse(BiTree *T);
    //����������������ʾ�Ķ�����T
Status IsLetter(char c);
    //�ж��ַ�c�Ƿ�����ĸ���Ƿ���TRUE�����򷵻�FALSE

//--------------������---------------//
int main()
{
    BiTree T;
    char c[256];
    printf("��������������:");
    scanf("%s",c);
    if(TRUE==IsLetter(c[0])){
        T=(BiTree)malloc(sizeof(BiTNode));
        T->data=c[0];
        T->lchild=NULL;
        T->rchild=NULL;
        CreateBiTree(&T);
    }
    printf("\n������������\n");
    PreOrderTraverse(&T);
    printf("\n������������\n");
    InOrderTraverse(&T);
    printf("\n������������\n");
    PostOrderTraverse(&T);
    return 0;
}

Status CreateBiTree(BiTree *T){
    //�������������������н���ֵ��һ���ַ������ո��ʾ����
    //������������ʾ�Ķ�����T
    char buffer[256];
    if(*T){
        printf("������ %c �����������ڵ�(�޵�����ĸ��������Ϊ��)��",(*T)->data);
        scanf("%s",buffer);
        if(TRUE==IsLetter(buffer[0])){
            (*T)->lchild=(BiTree)malloc(sizeof(BiTNode));
            (*T)->lchild->data=buffer[0];
            (*T)->lchild->lchild=NULL;
            (*T)->lchild->rchild=NULL;
        }
        printf("������ %c �����������ڵ�(�޵�����ĸ��������Ϊ��)��",(*T)->data);
        scanf("%s",buffer);
        if(TRUE==IsLetter(buffer[0])){
            (*T)->rchild=(BiTree)malloc(sizeof(BiTNode));
            (*T)->rchild->data=buffer[0];
            (*T)->rchild->lchild=NULL;
            (*T)->rchild->rchild=NULL;
        }
        CreateBiTree(&((*T)->lchild));//����������
        CreateBiTree(&((*T)->rchild));//����������
    }
    return OK;
}

Status PreOrderTraverse(BiTree *T){
    //����������������ʾ�Ķ�����T
    if(*T){//T��Ϊ��
        printf(" %c ",(*T)->data);
        PreOrderTraverse(&((*T)->lchild));//�������������
        PreOrderTraverse(&((*T)->rchild));//�������������
    }
    return OK;
}

Status InOrderTraverse(BiTree *T){
    //����������������ʾ�Ķ�����T
    if(*T){
        InOrderTraverse(&((*T)->lchild));
        printf(" %c ",(*T)->data);
        InOrderTraverse(&((*T)->rchild));
    }
    return OK;
}

Status PostOrderTraverse(BiTree *T){
    //����������������ʾ�Ķ�����T
    if(*T){
        PostOrderTraverse(&((*T)->lchild));
        PostOrderTraverse(&((*T)->rchild));
        printf(" %c ",(*T)->data);
    }
    return OK;
}

Status IsLetter(char c){
    //�ж��ַ�c�Ƿ�����ĸ���Ƿ���TRUE�����򷵻�FALSE
    if((c>='a')&&(c<='z')||(c>='A')&&(c<='Z'))
        return TRUE;
    else
        return FALSE;
}
