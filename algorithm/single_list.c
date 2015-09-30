//�������ӵ�ʹ��
//���ߣ�nuaazdh
//ʱ�䣺2011��12��9��
#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef char QElemType;

typedef struct QNode{//����Ԫ�ؽṹ
    QElemType data;
    struct QNode* next;
}QNode,*QueuePtr;

typedef struct{//���ӽṹ
    QueuePtr front;//����ָ��
    QueuePtr rear;//��βָ��
}LinkQueue;

Status InitQueue(LinkQueue *Q);
    //����һ���ն���Q
Status DestroyQueue(LinkQueue *Q);
    //���ٶ���Q��Q���ٴ���
Status ClearQueue(LinkQueue *Q);
    //��Q��Ϊ�ն���
Status QueueEmpty(LinkQueue Q);
    //������QΪ�ն��У��򷵻�TRUE,���򷵻�FALSE
int QueueLength(LinkQueue Q);
    //���ض���QԪ�ظ����������г���
Status GetHead(LinkQueue Q,QElemType *e);
    //�����в�Ϊ�գ�����e����Q�Ķ���Ԫ�أ�������OK�����򷵻�ERROR
Status EnQueue(LinkQueue *Q,QElemType e);
    //����Ԫ��eΪQ���µĶ�βԪ��
Status DeQueue(LinkQueue *Q,QElemType *e);
    //�����в�Ϊ�գ���ɾ��Q�Ķ���Ԫ�أ���e���أ�������OK�����򷵻�ERROR
Status QueueTraverse(LinkQueue Q);
    //�Ӷ�������β��������Q�е�Ԫ��

void PrintMenu();
    //��ʾ�˵���ʾ
char getOption();
    //��ȡ�û�����
void NewNodeEnQueue(LinkQueue *Q);
    //�����û����룬����Ԫ�����
void DeleteNode(LinkQueue *Q);
    //Ԫ�س��ӣ�����ʾʣ�����Ԫ��
void ShowHeadNode(LinkQueue *Q);
    //��ʾ����Ԫ��
void ShowBye();
    //��ʾ����
void ShowLength(LinkQueue *Q);
    //��ʾ����Ԫ�ظ���
//=============main()================//
int main()
{
    char option;
    LinkQueue queue;
    InitQueue(&queue);
    PrintMenu();
    option=getOption();
    while(option!='Q'){
        switch(option){
            case 'E'://Ԫ�����
                NewNodeEnQueue(&queue);
                break;
            case 'D'://Ԫ�س���
                DeleteNode(&queue);
                break;
            case 'S'://������������
                if(QueueEmpty(queue))
                    printf("The Queue is empty.\n");
                else
                    QueueTraverse(queue);
                break;
            case 'H':
                ShowHeadNode(&queue);
                break;
            case 'L':
                ShowLength(&queue);
                break;
            case 'A':
                printf("Invalid input.\n");
            default:
                break;
        }
        option=getOption();
    }
    ShowBye();
    return 0;
}


//-------------��������-----------------//
void PrintMenu(){
    //��ʾ�˵���ʾ
    printf("------Welcome------\n");
    printf(" Please input your choice:\n");
    printf(" E: New element enqueue.\n");
    printf(" D: Delete an element from the Queue.\n");
    printf(" S: Show all elements in the Queue.\n");
    printf(" H: Get the first element in the Queue.\n");
    printf(" L: Get the length of the Queue.\n");
    printf(" Q: Quit.\n");
    printf(" ohters: do nothing.\n");
}

void ShowBye(){
    //��ʾ����
    printf("------Bye bye------\n");
}

char getOption(){
    //��ȡ�û�����
    char *input,*op;
    input=(char *)malloc(sizeof(char)*256);
    printf(">>");
    gets(input);
    op=input;
    if(*(op+1)!='\0'){
        return 'A';
    }
    else
        return toupper(*op);
}

void NewNodeEnQueue(LinkQueue *Q){
    //�����û����룬����Ԫ�����
    char *p;
    p=(char *)malloc(sizeof(char)*256);
    printf("Please input a char(only one):");
    gets(p);
    if((*p>='a')&&(*p<='z')||(*p>='A')&&(*p<='Z')){
        EnQueue(Q,*p);
        printf("New element \'%c\' enqueu.\n",*p);
    }else
        printf("Sorry, your input is not accepted.\n");
}

void DeleteNode(LinkQueue *Q){
    //Ԫ�س��ӣ�����ʾʣ�����Ԫ��
    QElemType e;
    if(TRUE==QueueEmpty(*Q)){
        printf("The Queue is empty.\n");
        return;
    }
    DeQueue(Q,&e);
    printf("%c delete from the Queue,",e);
    if(QueueEmpty(*Q)==TRUE)
        printf("The Queue is empty now.\n");
    else
        //printf("Current Queue is:");
    QueueTraverse(*Q);

}

void ShowHeadNode(LinkQueue *Q){
    //��ʾ����Ԫ��
    QElemType e;
    if(QueueEmpty(*Q)){
        printf("The Queue is empty.\n");
        return;
    }else{
        GetHead(*Q,&e);
        printf("The first element of the Queue is:%c\n",e);
    }
}

void ShowLength(LinkQueue *Q){
    //��ʾ����Ԫ�ظ���
    if(QueueEmpty(*Q)==TRUE){
        printf("The count of element is 0.\n");
    }else{
        printf("The count of element is��%d\n",QueueLength(*Q));
    }
}

//-------------�Ӳ���ʵ��----------------//
Status InitQueue(LinkQueue *Q){
    //����һ���ն���Q
    Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));
    if(Q->front==NULL){
        printf("Apply for memory failed.\n");
        exit(0);
    }
    Q->rear->next=NULL;
    return OK;
}

Status DestroyQueue(LinkQueue *Q){
    //���ٶ���Q��Q���ٴ���
    while(Q->front){
        Q->rear=Q->front->next;
        free(Q->front);
        Q->front=Q->rear;
    }
    Q->front=Q->rear=NULL;
    return OK;
}

Status ClearQueue(LinkQueue *Q){
    //��Q��Ϊ�ն���
    QueuePtr p;  //��ʱָ��
    Q->rear=Q->front->next;
    while(Q->rear){
        p=Q->rear->next;//ָ����һ�����ͷŵ�Ԫ��
        free(Q->rear);
        Q->rear=p;
    }
    Q->rear=Q->front;//�޸Ķ�βָ��
    return OK;
}

Status QueueEmpty(LinkQueue Q){
    //������QΪ�ն��У��򷵻�TRUE,���򷵻�FALSE
    if(Q.front==Q.rear&&Q.front!=NULL)
        return TRUE;
    else
        return FALSE;

}

int QueueLength(LinkQueue Q){
    //���ض���QԪ�ظ����������г���
    QueuePtr p;//��ʱָ��
    int count=0;//������
    p=Q.front->next;
    while(p!=NULL){
        p=p->next;
        count++;
    }
    return count;
}

Status GetHead(LinkQueue Q,QElemType *e){
    //�����в�Ϊ�գ�����e����Q�Ķ���Ԫ�أ�������OK�����򷵻�ERROR
    if(QueueEmpty(Q)==TRUE)//����Ϊ��
        return ERROR;
    *e=Q.front->next->data;
    return OK;
}

Status EnQueue(LinkQueue *Q,QElemType e){
    //����Ԫ��eΪQ���µĶ�βԪ��
    QueuePtr p;
    if(Q->front==NULL||Q->rear==NULL)
        return ERROR;
    p=(QueuePtr)malloc(sizeof(QNode));
    if(!p){
        printf("Apply for memory error, element enqueue failed.\n");
        exit(0);
    }
    p->data=e;    p->next=NULL;
    Q->rear->next=p;
    Q->rear=p;
    return OK;
}

Status DeQueue(LinkQueue *Q,QElemType *e){
    //�����в�Ϊ�գ���ɾ��Q�Ķ���Ԫ�أ���e���أ�������OK�����򷵻�ERROR
    QueuePtr p;
    if(Q->front==Q->rear)//��Ϊ��
        return ERROR;
    p=Q->front->next;
    *e=p->data;
    Q->front->next=p->next;
    if(Q->rear==p)//����ֻ��һ��Ԫ��
        Q->rear=Q->front;
    free(p);
    return OK;

}

Status QueueTraverse(LinkQueue Q){
    //�Ӷ�������β��������Q�е�Ԫ��
    QueuePtr p;
    p=Q.front->next;
    if(p==NULL){
        return ERROR;
    }
    printf("Elements of the Queue:");
    while(p!=NULL){//������
        printf("%c ",p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}

