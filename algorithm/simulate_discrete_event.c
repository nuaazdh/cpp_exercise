//��ɢ�¼�ģ�⣬ģ������Ӫҵʱ���Ŷ����
//�����ǹ˿���;�뿪���˿͵����¼������ҵ�����ʱ��
//���������ѡ����̵Ķ��Ŷӣ����ٻ���
//���ߣ�nuaazdh
//ʱ�䣺2011��12��10�� 08:52:37
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef struct Event{   //�¼�����
    int OccurTime;  //�¼�����ʱ��
    int NType;      //�¼����ͣ�0��ʾ�����¼���1��4��ʾ�ĸ����ڵ��뿪�¼�
    struct Event *next;
}Event,ElemType;

typedef struct{ //��������ṹ
    ElemType *head;//ͷָ��
    ElemType *tail;//βָ��
    int len;    //����
}LinkList;

typedef LinkList EventList; //�¼�����

typedef struct QElemType{ //����Ԫ��
    int ArriveTime;//����ʱ��
    int Duration;//����ҵ������ʱ��
    struct QElemType *next;
}QElemType;

typedef struct{//���нṹ
    QElemType *head;//ͷָ��
    QElemType *tail;//βָ��
}LinkQueue;

Event NewEvent(int occurT,int nType);
    //����OccurTime��NTypeֵ���������¼�
Status InitList(LinkList *L);
    //��ʼ���¼�����
Status OrderInsert(LinkList *L,Event e);
    //���¼�e������ʱ��˳�������������L��
Status ListEmpty(LinkList *L);
    //�ж�����L�Ƿ�Ϊ�գ�Ϊ�շ���TRUE�����򷵻�FALSE
Status DelFirst(LinkList *L,ElemType *e);
    //����L��Ϊ�գ�ɾ�����׽�㣬��e���أ�������OK�����򷵻�ERROR
Status ListTraverse(LinkList *L);
    //��������
Status InitQueue(LinkQueue *Q);
    //��ʼ������Q
Status EmptyQueue(LinkQueue *Q);
    //������QΪ�գ�����TRUE�����򷵻�FALSE
Status DelQueue(LinkQueue *Q,QElemType *e);
    //������Q��Ϊ�գ��׽����ӣ���e���أ�������OK�����򷵻�ERROR
Status EnQueue(LinkQueue *Q,QElemType e);
    //���e���Q
int QueueLength(LinkQueue Q);
    //���ض���Q�ĳ��ȣ���Ԫ�ظ���
Status GetHead(LinkQueue *Q,QElemType *e);
    //������Q��Ϊ�գ���e�������׽�㣬������OK,���򷵻�ERROR
Status QueueTraverse(LinkQueue *Q);
    //��������Q

//------------------//
int Min(int a[],int n);
    //���س���Ϊn������a��һ����Сֵ���±꣬��1��ʼ
int ShortestQueue();
    //��ȡ��̶��еı��
void OpenForDay();
    //��ʼ������
void CustomerArrived();
    //�˿ʹﵽ�¼�
void CustomerDepature();
    //�˿��뿪�¼�
void Bank_Simulation();
    //�����Ŷ�ģ��
void PrintEventList();
    //����¼�����
void PrintQueue();
    //��ӡ��ǰ����
//----ȫ�ֱ���-----//
EventList ev;
Event en;
LinkQueue q[5];
QElemType customer;
int TotalTime,CustomerNum;
int CloseTime=50;//�ر�ʱ�䣬��Ӫҵʱ�䳤��

//--------------main()------------------//
int main()
{
    Bank_Simulation();
    return 0;
}


//--------------ģ���Ŷ�----------------//
void OpenForDay(){
    //��ʼ������
    int i;
    TotalTime=0;    CustomerNum=0;
    InitList(&ev);//��ʼ���¼�����
    en.OccurTime=0;
    en.NType=0;
    OrderInsert(&ev,en);
    for(i=1;i<=4;i++)
        InitQueue(&q[i]);//��ʼ���ĸ����ڶ���
}//OpenForDay

void CustomerArrived(){
    //�˿ʹﵽ�¼�
    int durtime,intertime,i,t;
    QElemType e;
    ++CustomerNum;
    intertime=rand()%5+1;//���ʱ����5������
    durtime=rand()%30+1;//����ҵ��ʱ����30������
    t=en.OccurTime+intertime;
    if(t<CloseTime){//������δ����
        printf("A new customer will arrive at:%d\n",en.OccurTime);//��һλ�˿ʹﵽʱ��
        OrderInsert(&ev,NewEvent(t,0));
        i=ShortestQueue();//��̶���
        e.ArriveTime=en.OccurTime;
        e.Duration=durtime;
        EnQueue(&q[i],e);
        if(QueueLength(q[i])==1)
            OrderInsert(&ev,NewEvent(en.OccurTime+durtime,i));
    }
}

void CustomerDepature(){
    //�˿��뿪�¼�
    int i=en.NType;
    DelQueue(&q[i],&customer);
    printf("A customer leaves at:%d\n",en.OccurTime);//����˿��뿪ʱ��
    TotalTime+=en.OccurTime-customer.ArriveTime;
    if(!EmptyQueue(&q[i])){
        GetHead(&q[i],&customer);
        OrderInsert(&ev,NewEvent(en.OccurTime+customer.Duration,i));
    }
}

void Bank_Simulation(){
    //�����Ŷ�ģ��
    OpenForDay();
    srand((unsigned)time(NULL));
    while(!ListEmpty(&ev)){
        DelFirst(&ev,&en);
        if(en.NType==0)
            CustomerArrived();
        else
            CustomerDepature();
        //PrintEventList();
        PrintQueue();
    }
    printf("\nTotal time is: %d min,average time is: %g min.\n",TotalTime,(float)TotalTime/CustomerNum);
}

void PrintQueue(){
    //��ӡ��ǰ����
    int i;
    for(i=1;i<=4;i++){
        printf("Queue %d have %d customer(s):",i,QueueLength(q[i]));
        QueueTraverse(&q[i]);
    }
    printf("\n");
}

void PrintEventList(){
    //����¼�����
    printf("Current Eventlist is��\n");
    ListTraverse(&ev);
}
int Min(int a[],int n){
    //���س���Ϊn������a��һ����Сֵ���±꣬��0��ʼ
    int i,tmp,ind=0;
    tmp=a[0];
    for(i=1;i<n;i++){
        if(a[i]<tmp){
            tmp=a[i];
            ind=i;
        }
    }
    return ind;
}

int ShortestQueue(){
    //��ȡ��̶��еı��
    int i,a[4];
    for(i=1;i<=4;i++){
        a[i-1]=QueueLength(q[i]);
        //printf("��%d�ĳ���Ϊ%d\n",i,QueueLength(q[i]));
    }
    return Min(a,4)+1;//���д�1��ʼ���
}

//-----------�Ӻ��������--------------//
Event NewEvent(int occurT,int nType){
    //����OccurTime��NTypeֵ���������¼�
    Event e;
    e.OccurTime=occurT;
    e.NType=nType;
    return e;
}

Status InitList(LinkList *L){
    //��ʼ���¼�����
    L->head=L->tail=(ElemType *)malloc(sizeof(ElemType));
    if(!L->head){
        printf("Apply for memory error.LinkList initialize failed.\n");
        exit(0);
    }
    L->head->next=NULL;
    return OK;
}

Status OrderInsert(LinkList *L,Event e){
    //���¼�e������ʱ��˳�������������L��
    ElemType *p,*q,*newptr;
    newptr=(ElemType *)malloc(sizeof(ElemType));
    if(!newptr){
        printf("Apply for memory error��new node can't insert intot the Eventlist.\n");
        exit(0);
    }
    *newptr=e;
    if(TRUE==ListEmpty(L)){//����Ϊ��
       L->head->next=newptr;
       L->tail=newptr;
       L->tail->next=NULL;
       return OK;
    }
    q=L->head;
    p=L->head->next;
    while(p){//������������
        if(p->OccurTime>=newptr->OccurTime)
            break;
        q=p;
        p=p->next;
    }
    q->next=newptr;
    newptr->next=p;
    if(!p)//����λ��Ϊ����β��
        L->tail=newptr;
    return OK;
}

Status ListEmpty(LinkList *L){
    //�ж�����L�Ƿ�Ϊ�գ�Ϊ�շ���TRUE�����򷵻�FALSE
    if((L->head==L->tail)&&(L->head!=NULL))
        return TRUE;
    else
        return FALSE;
}

Status DelFirst(LinkList *L,ElemType *e){
    //����L��Ϊ�գ�ɾ�����׽�㣬��e���أ�������OK�����򷵻�ERROR
    ElemType *p=L->head->next;
    if(!p)
        return ERROR;
    L->head->next=p->next;
    *e=*p;
    free(p);
    if(L->head->next==NULL)
        L->tail=L->head;
    return OK;
}

Status ListTraverse(LinkList *L){
    //��������
    Event *p=L->head->next;
    if(!p){
        printf("List is empty.\n");
        return ERROR;
    }
    while(p!=NULL){
        printf("OccurTime:%d,Event Type:%d\n",p->OccurTime,p->NType);
        p=p->next;
    }
    printf("\n");
    return OK;
}

Status InitQueue(LinkQueue *Q){
    //��ʼ������Q
    Q->head=Q->tail=(QElemType *)malloc(sizeof(QElemType));
    if(!Q->head){
        printf("Apply for memory error.LinkQueue initialize failed.\n");
        exit(0);
    }
    Q->head->next=NULL;
    return OK;
}

Status EmptyQueue(LinkQueue *Q){
    //������QΪ�գ�����TRUE�����򷵻�FALSE
    if(Q->head==Q->tail&&Q->head!=NULL)
        return TRUE;
    else
        return FALSE;
}

Status DelQueue(LinkQueue *Q,QElemType *e){
    //������Q��Ϊ�գ��׽����ӣ���e���أ�������OK�����򷵻�ERROR
    QElemType *p=Q->head->next;
    if(!p)
        return ERROR;
    *e=*p;
    Q->head->next=p->next;//��������ָ��
    free(p);
    if(!Q->head->next)//�ӿ�
        Q->tail=Q->head;
    return OK;
}

Status EnQueue(LinkQueue *Q,QElemType e){
    //���e���Q
    QElemType *p=(QElemType *)malloc(sizeof(QElemType));
    if(!p){
        printf("Apply for memory error,new element can't enqueue.\n");
        exit(0);
    }
    *p=e;
    p->next=NULL;
    Q->tail->next=p;//�����β
    Q->tail=p;//�޸Ķ�βָ��
    return OK;
}

int QueueLength(LinkQueue Q){
    //���ض���Q�ĳ��ȣ���Ԫ�ظ���
    int count=0;
    QElemType *p=Q.head->next;
    while(p){
        p=p->next;
        count++;
    }
    return count;
}

Status GetHead(LinkQueue *Q,QElemType *e){
    //������Q��Ϊ�գ���e�������׽�㣬������OK,���򷵻�ERROR
    if(EmptyQueue(Q))
        return ERROR;
    *e=*(Q->head->next);
        return OK;
}

Status QueueTraverse(LinkQueue *Q){
    //��������Q
    QElemType *p=Q->head->next;
    if(!p){
        printf("--Is empty.\n");
        return ERROR;
    }
    while(p){
        printf("(%d,%d) ",p->ArriveTime,p->Duration);
        p=p->next;
    }
    printf("\n");
    return OK;
}
