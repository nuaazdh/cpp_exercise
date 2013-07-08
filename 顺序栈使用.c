//�������������ݹ�ͷǵݹ�����ʵ��
//���ߣ�nuaazdh
//ʱ�䣺2012��5��31��

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
typedef char ElemType;  // ���������Ԫ������
typedef struct BiTNode{ // ���������ṹ
	char data;            // �������
	struct BiTNode *lchild;        // ����
	struct BiTNode *rchild;        // �Һ���
}BiTNode,*BiTree;

typedef BiTree SElemType;
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

BiTree CreateBiTree(BiTree T);
// ���Ⱥ��������������н���ֵ��һ���ַ������ո��ʾ����
// ������������ʾ�Ķ�����T
Status PreOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
// ���ö�������洢��ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
// �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
Status InOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
// ���ö�������洢��ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
// �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
Status PostOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
// ���ö�������洢��ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
// �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
Status PreOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
// ���ö�������洢��ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
// �������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
Status InOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
// ���ö�������洢��ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
// �������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
Status PostOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e));
// ���ö�������洢��ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
// �������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
Status Visit(ElemType e);
// �Զ������е�����Ԫ�ط���

int main()
{
	BiTree T=NULL;
	Status(*visit)(ElemType e)=Visit;
	printf("�밴����������������Ԫ�أ�ÿ�����һ���ַ����ս��Ϊ'#'��:\n");
	T=CreateBiTree(T);
	printf("\n�ݹ����������\n");
	PreOrderRecursionTraverse(T,visit);
	printf("\n�ݹ����������\n");
	InOrderRecursionTraverse(T,visit);
	printf("\n�ݹ���������\n");
	PostOrderRecursionTraverse(T,visit);
	printf("\n�ǵݹ����������\n");
	PreOrderNonRecursionTraverse(T,visit);
	printf("\n�ǵݹ����������\n");
	InOrderNonRecursionTraverse(T,visit);
	printf("\n�ǵݹ���������\n");
	PostOrderNonRecursionTraverse(T,visit);
	return 0;
}

BiTree CreateBiTree(BiTree T){
	// ���Ⱥ��������������н���ֵ��һ���ַ������ո��ʾ����
	// ������������ʾ�Ķ�����T
	char ch;
	scanf("%c",&ch);
	if(ch=='#') T=NULL;
	else{
		if(!(T=(BiTNode *)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data=ch;                 // ���ɸ��ڵ�
		T->lchild=CreateBiTree(T->lchild);    // ����������
		T->rchild=CreateBiTree(T->rchild);    // ����������
	}
	return T;
}

Status PreOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e))
{   // ��������ݹ��㷨

	if(T){
		if(!Visit(T->data)) return ERROR;
		PreOrderRecursionTraverse(T->lchild,Visit);
		PreOrderRecursionTraverse(T->rchild,Visit);
	}
	return OK;
}

Status InOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e))
{   // ��������ݹ��㷨
	if(T){
		InOrderRecursionTraverse(T->lchild,Visit);
		if(!Visit(T->data)) return ERROR;;
		InOrderRecursionTraverse(T->rchild,Visit);
	}
	return OK;
}


Status PostOrderRecursionTraverse(BiTree T,Status (*Visit)(ElemType e))
{   //��������ݹ��㷨
	if(T){
		PostOrderRecursionTraverse(T->lchild,Visit);
		PostOrderRecursionTraverse(T->rchild,Visit);
		if(!Visit(T->data)) return ERROR;;
	}
	return OK;
}

Status PreOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e)){
	// �������������T�ķǵݹ��㷨
	SqStack S;
	SElemType p;
	InitStack(&S);      Push(&S,T); // ��ָ����ջ
	while(!StackEmpty(S)){
		Pop(&S,&p);	//���ʸ��ڵ�
		if(!Visit(p->data)) return ERROR;
		if (p->rchild)
			Push(&S,p->rchild);
		if(p->lchild)
			Push(&S,p->lchild);
	}//while
	DestroyStack(&S);
	return OK;
}

Status InOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e)){
	// �������������T�ķǵݹ��㷨
	SqStack S;
	SElemType p;
	InitStack(&S);      Push(&S,T); // ��ָ����ջ
	while(!StackEmpty(S)){
		while(GetTop(S,&p)&&p)   Push(&S,p->lchild);    //�����ߵ���ͷ
		Pop(&S,&p);     //��ָ���ջ
		if(!StackEmpty(S)){//���ʽ�㣬����һ��
			Pop(&S,&p);
			if(!Visit(p->data)) return ERROR;
			Push(&S,p->rchild);
		}//if
	}//while
	DestroyStack(&S);
	return OK;

}

Status PostOrderNonRecursionTraverse(BiTree T,Status (*Visit)(ElemType e)){
	// �������������T�ķǵݹ��㷨
	SqStack S;
	SElemType p;
	InitStack(&S);      Push(&S,T); // ��ָ����ջ
	while(!StackEmpty(S)){
		Pop(&S,&p);	//���ʸ��ڵ�
		if(!Visit(p->data)) return ERROR;
		if (p->lchild)
			Push(&S,p->lchild);
		if(p->rchild)
			Push(&S,p->rchild);
	}//while
	DestroyStack(&S);
	return OK;
}

Status Visit(ElemType e){
	// �Զ������е�����Ԫ�ط���
	if(e=='\0'){
		return ERROR;
	}else{
		printf("%c",e);
	}
	return OK;
}

//-----------˳��ջ����--------------//

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
	free(S->base);
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
		return FALSE;
	}else{
		*e=*(S.top-1);
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
