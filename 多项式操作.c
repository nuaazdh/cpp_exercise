//多项式操作
//作者：nuaazdh
//时间：2011年12月1日 12:52:00
#include <stdio.h>

#define OK 1
#define ERROR 0

typedef int Status;//函数状态代码

typedef struct{ //项的表示
    float coeff;//系数
    int expn;   //指数
}term,ElemType;

typedef struct LNode{//结点类型
    ElemType data;
    struct LNode *next;
}LNode,*Link;

typedef struct{//链表类型
    Link head,tail;//分别指向链表的头结点和尾结点
    int len;//链表的长度
}LinkList;

typedef LinkList polynomial;

//创建多项式,m为多项式中x的最高次幂
void CreatePolyn(polynomial *P,int m)
{
    int i=0;//循环变量
    float input;//用户输入
    for(i=0;i<=m;i++)
    {
        printf("请输入x^%d项的系数：",i);
        scanf("%f",&input);
        if(input!=0)
        {
            Link newnode=(Link)malloc(sizeof(LNode));
            if(newnode==NULL)
            {
                printf("申请内存失败.\n");
                exit(0);
            }
            newnode->data.coeff=input;//系数赋值
            newnode->data.expn=i;//幂赋值
            if(i==0)//第一项
                P->tail=newnode;
            newnode->next=P->head;//插入链表头部
            P->head=newnode;//修改头指针
            if(i==0)    //第一个结点
                P->tail=newnode;
            P->len++;//长度加1
        }
    }
}

//销毁多项式
void DestroyPolyn(polynomial *P)
{
    Link ptr=P->head;//指向首结点
    while(ptr!=NULL)
    {
        P->head=ptr->next;
        free(ptr);//释放结点空间
        ptr=P->head;
        P->len--;//链表长度减1
    }
    P->tail=NULL;
    P->len=0;
}

//输出多项式P
void PrintPolyn(const polynomial *P)
{
    Link ptr=P->head;
    if(!(P->len||P->head||P->tail))//链表为空
    {
        printf("多项式没有任何项.\n");
        return;
    }
    printf("表达式为：\n");
    //输出多项式各项
    while(ptr!=NULL)
    {
        if((ptr->data.coeff>0)&&(ptr!=P->head))//系数为正，且不是首项
            printf("+");//输出前置+号
        printf("%g",ptr->data.coeff);//输出系数
        if(ptr->data.expn)
            printf("x");
        if(ptr->data.expn>1)
            printf("^%d",ptr->data.expn);//输出x幂项
        ptr=ptr->next;
    }
    printf("\n");//输出回车
}

//返回多项式P的项数
int PolynLength(const polynomial *P)
{
    return P->len;//返回链表长度
}

//计算base的expn次幂值
float power(float base,int expn)
{
    if(expn==0)
        return 1.0;
    else
        return base*power(base,expn-1);
}

//计算多项式P在变量值为x时的值
float ComputeValue(const polynomial *P,float x)
{
    float sum=0.0;
    Link ptr;
    if(P->head==NULL)
    {
        printf("多项式为空.\n");
    }
    ptr=P->head;
    while(ptr!=NULL)
    {
        sum+=ptr->data.coeff*power(x,ptr->data.expn);
        ptr=ptr->next;
    }
    return sum;
}

//多项式相加运算，Pa=Pa+Pb，并销毁多项式Pb
void AddPolyn(polynomial *Pa,polynomial *Pb)
{
    Link ptr_a,ptr_b,ta,tb,ha;
    ta=NULL;//Pa链表中的临时指针
    tb=NULL;//Pb链表中的临时指针
    ha=NULL;//ha为当前已经合并的链表最后一个结点
    ptr_a=Pa->head;//指向多项式Pa
    ptr_b=Pb->head;//指向多项式Pb
    while(ptr_a&&ptr_b)
    {
        if(ptr_a->data.expn==ptr_b->data.expn)//幂相等，合并同类项
        {
            ptr_a->data.coeff+=ptr_b->data.coeff;//系数相加
            if(ptr_a->data.coeff==0.0)//系数为0
            {
                if(ha==NULL)//Pa的首相相消
                    Pa->head=ptr_a->next;
                free(ptr_a);//删除ptr_a指向结点
                ptr_a=Pa->head;
            }else{  //系数不为0
                if(ha!=NULL)//和多项式项数不为0
                    ha->next=ptr_a;
                ha=ptr_a;
                ptr_a=ptr_a->next;
            }
            tb=ptr_b->next;
            free(ptr_b);
            ptr_b=tb;
        }
        else if(ptr_a->data.expn<ptr_b->data.expn)//Pb当前项幂较高
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
        else//Pa当前项幂较高
        {
            if(ha==NULL)
                ha=ptr_a;
            else
                ha->next=ptr_a;
            ptr_a=ptr_a->next;
        }//if
    }//while
    //链接剩余结点
    if(ha!=NULL)//所有处理过的项均相消
    {
        ha->next=(ptr_a==NULL)?(ptr_b):(ptr_a);
    }
    else
    {
        Pa->head=(ptr_a==NULL)?(ptr_b):(ptr_a);
    }
    Pb->head=Pb->tail=NULL;//修改多项式Pb指针
    Pb->len=0;
    //修正多项式Pa的尾指针和长度
    Pa->len=0;
    Pa->tail=Pa->head;
    if(Pa->tail!=NULL)
        while(Pa->tail->next)
        {
            Pa->tail=Pa->tail->next;
            Pa->len++;
        }
    Pa->len++;
    DestroyPolyn(Pb);//销毁Pb
}

//主函数
int main()
{
    int m;
    float x;
    polynomial p1,p2;//建立新链表
    p1.head=NULL;p1.tail=NULL;p1.len=0;
    p2.head=NULL;p2.tail=NULL;p2.len=0;
    printf("请输入关于x的多项式1中x的最高次幂：");
    scanf("%d",&m);
    if(m<0)
    {
        printf("输入值非法！\n");
    }
    CreatePolyn(&p1,m);//创建多项式
    printf("多项式1");
    PrintPolyn(&p1);//显示多项式1
    printf("请输入关于x的多项式2中x的最高次幂：");
    scanf("%d",&m);
    if(m<0)
    {
        printf("输入值非法！\n");
    }
    CreatePolyn(&p2,m);//创建多项式
    printf("多项式2");
    PrintPolyn(&p2);//显示多项式
    AddPolyn(&p1,&p2);
    printf("和多项式");
    PrintPolyn(&p1);//输出和多项式
    printf("输入x的值：");
    scanf("%f",&x);
    printf("多项式在x=%g时，值为%g",x,ComputeValue(&p1,x));//输出多项式求值
    DestroyPolyn(&p1);//销毁多项式
    return 0;
}
