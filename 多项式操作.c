//����ʽ����
//���ߣ�nuaazdh
//ʱ�䣺2011��12��1�� 12:52:00
#include <stdio.h>

#define OK 1
#define ERROR 0

typedef int Status;//����״̬����

typedef struct{ //��ı�ʾ
    float coeff;//ϵ��
    int expn;   //ָ��
}term,ElemType;

typedef struct LNode{//�������
    ElemType data;
    struct LNode *next;
}LNode,*Link;

typedef struct{//��������
    Link head,tail;//�ֱ�ָ�������ͷ����β���
    int len;//����ĳ���
}LinkList;

typedef LinkList polynomial;

//��������ʽ,mΪ����ʽ��x����ߴ���
void CreatePolyn(polynomial *P,int m)
{
    int i=0;//ѭ������
    float input;//�û�����
    for(i=0;i<=m;i++)
    {
        printf("������x^%d���ϵ����",i);
        scanf("%f",&input);
        if(input!=0)
        {
            Link newnode=(Link)malloc(sizeof(LNode));
            if(newnode==NULL)
            {
                printf("�����ڴ�ʧ��.\n");
                exit(0);
            }
            newnode->data.coeff=input;//ϵ����ֵ
            newnode->data.expn=i;//�ݸ�ֵ
            if(i==0)//��һ��
                P->tail=newnode;
            newnode->next=P->head;//��������ͷ��
            P->head=newnode;//�޸�ͷָ��
            if(i==0)    //��һ�����
                P->tail=newnode;
            P->len++;//���ȼ�1
        }
    }
}

//���ٶ���ʽ
void DestroyPolyn(polynomial *P)
{
    Link ptr=P->head;//ָ���׽��
    while(ptr!=NULL)
    {
        P->head=ptr->next;
        free(ptr);//�ͷŽ��ռ�
        ptr=P->head;
        P->len--;//�����ȼ�1
    }
    P->tail=NULL;
    P->len=0;
}

//�������ʽP
void PrintPolyn(const polynomial *P)
{
    Link ptr=P->head;
    if(!(P->len||P->head||P->tail))//����Ϊ��
    {
        printf("����ʽû���κ���.\n");
        return;
    }
    printf("���ʽΪ��\n");
    //�������ʽ����
    while(ptr!=NULL)
    {
        if((ptr->data.coeff>0)&&(ptr!=P->head))//ϵ��Ϊ�����Ҳ�������
            printf("+");//���ǰ��+��
        printf("%g",ptr->data.coeff);//���ϵ��
        if(ptr->data.expn)
            printf("x");
        if(ptr->data.expn>1)
            printf("^%d",ptr->data.expn);//���x����
        ptr=ptr->next;
    }
    printf("\n");//����س�
}

//���ض���ʽP������
int PolynLength(const polynomial *P)
{
    return P->len;//����������
}

//����base��expn����ֵ
float power(float base,int expn)
{
    if(expn==0)
        return 1.0;
    else
        return base*power(base,expn-1);
}

//�������ʽP�ڱ���ֵΪxʱ��ֵ
float ComputeValue(const polynomial *P,float x)
{
    float sum=0.0;
    Link ptr;
    if(P->head==NULL)
    {
        printf("����ʽΪ��.\n");
    }
    ptr=P->head;
    while(ptr!=NULL)
    {
        sum+=ptr->data.coeff*power(x,ptr->data.expn);
        ptr=ptr->next;
    }
    return sum;
}

//����ʽ������㣬Pa=Pa+Pb�������ٶ���ʽPb
void AddPolyn(polynomial *Pa,polynomial *Pb)
{
    Link ptr_a,ptr_b,ta,tb,ha;
    ta=NULL;//Pa�����е���ʱָ��
    tb=NULL;//Pb�����е���ʱָ��
    ha=NULL;//haΪ��ǰ�Ѿ��ϲ����������һ�����
    ptr_a=Pa->head;//ָ�����ʽPa
    ptr_b=Pb->head;//ָ�����ʽPb
    while(ptr_a&&ptr_b)
    {
        if(ptr_a->data.expn==ptr_b->data.expn)//����ȣ��ϲ�ͬ����
        {
            ptr_a->data.coeff+=ptr_b->data.coeff;//ϵ�����
            if(ptr_a->data.coeff==0.0)//ϵ��Ϊ0
            {
                if(ha==NULL)//Pa����������
                    Pa->head=ptr_a->next;
                free(ptr_a);//ɾ��ptr_aָ����
                ptr_a=Pa->head;
            }else{  //ϵ����Ϊ0
                if(ha!=NULL)//�Ͷ���ʽ������Ϊ0
                    ha->next=ptr_a;
                ha=ptr_a;
                ptr_a=ptr_a->next;
            }
            tb=ptr_b->next;
            free(ptr_b);
            ptr_b=tb;
        }
        else if(ptr_a->data.expn<ptr_b->data.expn)//Pb��ǰ���ݽϸ�
        {
            if(ha==NULL)
            {
                Pa->head=ha=ptr_b;
            }else{
                ha->next=ptr_b;
                ha=ptr_b;
            }
            ptr_b=ptr_b->next;
        }
        else//Pa��ǰ���ݽϸ�
        {
            if(ha==NULL)
                ha=ptr_a;
            else
                ha->next=ptr_a;
            ptr_a=ptr_a->next;
        }//if
    }//while
    //����ʣ����
    if(ha!=NULL)//���д�������������
    {
        ha->next=(ptr_a==NULL)?(ptr_b):(ptr_a);
    }
    else
    {
        Pa->head=(ptr_a==NULL)?(ptr_b):(ptr_a);
    }
    Pb->head=Pb->tail=NULL;//�޸Ķ���ʽPbָ��
    Pb->len=0;
    //��������ʽPa��βָ��ͳ���
    Pa->len=0;
    Pa->tail=Pa->head;
    if(Pa->tail!=NULL)
        while(Pa->tail->next)
        {
            Pa->tail=Pa->tail->next;
            Pa->len++;
        }
    Pa->len++;
    DestroyPolyn(Pb);//����Pb
}

//������
int main()
{
    int m;
    float x;
    polynomial p1,p2;//����������
    p1.head=NULL;p1.tail=NULL;p1.len=0;
    p2.head=NULL;p2.tail=NULL;p2.len=0;
    printf("���������x�Ķ���ʽ1��x����ߴ��ݣ�");
    scanf("%d",&m);
    if(m<0)
    {
        printf("����ֵ�Ƿ���\n");
    }
    CreatePolyn(&p1,m);//��������ʽ
    printf("����ʽ1");
    PrintPolyn(&p1);//��ʾ����ʽ1
    printf("���������x�Ķ���ʽ2��x����ߴ��ݣ�");
    scanf("%d",&m);
    if(m<0)
    {
        printf("����ֵ�Ƿ���\n");
    }
    CreatePolyn(&p2,m);//��������ʽ
    printf("����ʽ2");
    PrintPolyn(&p2);//��ʾ����ʽ
    AddPolyn(&p1,&p2);
    printf("�Ͷ���ʽ");
    PrintPolyn(&p1);//����Ͷ���ʽ
    printf("����x��ֵ��");
    scanf("%f",&x);
    printf("����ʽ��x=%gʱ��ֵΪ%g",x,ComputeValue(&p1,x));//�������ʽ��ֵ
    DestroyPolyn(&p1);//���ٶ���ʽ
    return 0;
}
