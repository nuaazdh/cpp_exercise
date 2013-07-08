//�ݹ�ʵ��ģ�⺺ŵ��
//���ߣ�nuaazdh
//ʱ�䣺2011��12��9�� 08:22:27
#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define ORDER 10 //��ŵ������

typedef int Status;//����ִ��״̬
typedef struct{
    char name;//������
    int count;//��ǰ�����ϵ�Բ����
    int *disk;//��ǰ����Բ������
}Towerfoot;

void InitHanoi(Towerfoot *X,Towerfoot *Y,Towerfoot *Z,int n);
    //��ŵ����ʼ����X��Y��Z����ŵ������Ϊn
Status Find(const Towerfoot *X,int id);
    //������Ϊid��Բ���Ƿ�������X��,�Ƿ���TRUE;���򷵻�FALSE
Status Check(const Towerfoot *X);
    //���Towerfoot�Ƿ��ŷ���ȷ
void move(Towerfoot *X,int id,Towerfoot *Z);
    //��YΪ���������������Ϊid��Բ�̴�����X�Ƶ�����Z
void Hanoi(Towerfoot *X,Towerfoot *Y,Towerfoot *Z,int n);
    //������X�ϵı��Ϊ1��n��Բ�̰������Ƶ�����Z��
void PrintHanoi(const Towerfoot *X,const Towerfoot *Y,const Towerfoot *Z,int n);
    //��ӡ��ŵ����������X��Y��Z�ϵ�Բ��
void PrintTower(const Towerfoot *X);
    //���������ŵ�������ϵ�Բ�����
void Adjust(const Towerfoot **X,const Towerfoot **Y,const Towerfoot **Z);
    //�����������ƣ���������ָ��

int step=0;//ȫ�ֱ�������¼�ƶ�����

int main()
{
    Towerfoot X,Y,Z;
    InitHanoi(&X,&Y,&Z,ORDER);
    PrintHanoi(&X,&Y,&Z,ORDER);
    Hanoi(&X,&Y,&Z,ORDER);
    printf("\nTotal Steps:%d\n",step);
    return 0;
}

void InitHanoi(Towerfoot *X,Towerfoot *Y,Towerfoot *Z,int n){
    //��ŵ����ʼ����X��Y��Z����ŵ������Ϊn
    int i;
    X->count=n;
    Y->count=Z->count=0;
    X->disk=(int*)malloc(sizeof(int)*n);//����Բ������ռ�
    Y->disk=(int*)malloc(sizeof(int)*n);
    Z->disk=(int*)malloc(sizeof(int)*n);
    if(!(X->disk&&Y->disk&&Z->disk)){
        printf("�����ڴ�ʧ��.\n");
        exit(0);
    }
    X->name='X';Y->name='Y';Z->name='Z';//��������
    for(i=0;i<n;i++){//��������X�ϵ�Բ��
        X->disk[i]=i+1;
    }
}

void Hanoi(Towerfoot *X,Towerfoot *Y,Towerfoot *Z,int n){
    //������X�ϵı��Ϊ1��n��Բ�̰������Ƶ�����Z��
    //Y������������
    if(n==1){
        move(X,1,Z);//���1��Բ�̴�X�ƶ���Z
        PrintHanoi(X,Y,Z,ORDER);//�����ǰ��ŵ���ṹ
    }
    else{
        Hanoi(X,Z,Y,n-1);
        move(X,n,Z);//��YΪ������������X���Ϊn���Ƶ�Z��
        PrintHanoi(X,Y,Z,ORDER);//�����ŵ��
        Hanoi(Y,X,Z,n-1);
    }
}

void move(Towerfoot *X,int id,Towerfoot *Z){
    //�����Ϊid��Բ�̴�����X�Ƶ�����Z
    int i;
    if(FALSE==Find(X,id)){
        printf("����X��û�б��Ϊ%d��Բ��.\n",id);
        return;
    }
    if(X->disk[0]!=id){
        printf("���Ϊ%d��Բ�̲�������X�����Ϸ����޷��ƶ�.\n",id);
        return;
    }
    for(i=0;i<X->count-1;i++){//�ƶ�����X�ϵ�Բ��
        X->disk[i]=X->disk[i+1];
    }
    for(i=Z->count-1;i>=0;i--){//�ƶ�����Z����Բ��
        Z->disk[i+1]=Z->disk[i];
    }
    Z->disk[0]=id;
    X->count--;
    Z->count++;
    step++; //ÿ�ƶ�һ�Σ�������1
}

Status Find(const Towerfoot *X,int id){
    //������Ϊid��Բ���Ƿ�������X��,�Ƿ���TRUE;���򷵻�FALSE
    int i;
    if(X->count==0)
        return FALSE;
    for(i=0;i<X->count;i++){
        if(X->disk[i]==id)
            return TRUE;
    }
    return FALSE;
}

Status Check(const Towerfoot *X){
    //���Towerfoot�Ƿ��ŷ���ȷ
    int i=0;
    for(i=0;i<X->count-1;i++){
        if((X->disk[i]<0)||(X->disk[i]>X->disk[i+1]))
            return FALSE;
    }
    return TRUE;
}

void PrintHanoi(const Towerfoot *X,const Towerfoot *Y,const Towerfoot *Z,int n){
    //��ӡ��ŵ����������X��Y��Z�ϵ�Բ��
    int i,j;//ѭ������
    char disc='#',space=' ';
    printf("\nstep %d:\n",step);
    Adjust(&X,&Y,&Z);   //�����������Ƶ�����ŵ��ָ��
    for(i=0;i<n;i++){
        for(j=0;j<3*n+2;j++){
            if((n-X->count<=i)&&(X->disk[i-(n-X->count)]>j)){//X����
                printf("%c",disc);
            }else
            if((n-Y->count<=i)&&(j-n>0)&&(Y->disk[i-(n-Y->count)]>=j-n)){//Y����
                printf("%c",disc);
            }else
            if((n-Z->count<=i)&&(j-2*n-1>0)&&(Z->disk[i-(n-Z->count)]>=j-2*n-1)){//Z����
                printf("%c",disc);
            }else{
                printf("%c",space);
            }
        }
        printf("\n");
    }
    for(j=0;j<4*(n+2)+2;j++){//�����������
        if(0==j)
            printf("%c",X->name,j);
        else if(n+1==j)
            printf("%c",Y->name,j);
        else if(2*(n+1)==j)
            printf("%c",Z->name);
        else printf("%c",space);
    }
    printf("\n");
}

void PrintTower(const Towerfoot *X){
    //���������ŵ�������ϵ�Բ�����
    int i;
    printf("%c:",X->name);
    for(i=0;i<X->count;i++){
        printf("%d ",X->disk[i]);
    }
    printf("\n");
}

void Adjust(const Towerfoot **X,const Towerfoot **Y,const Towerfoot **Z){
    //�����������ƣ���������ָ��
    //�����������ƣ���������ָ��
    const Towerfoot *x,*y,*z;
    switch((*X)->name){//X
        case 'X':
            x=*X;
            break;
        case 'Y':
            y=*X;
            break;
        case 'Z':
            z=*X;
            break;
    }
    switch((*Y)->name){//Y
        case 'X':
            x=*Y;
            break;
        case 'Y':
            y=*Y;
            break;
        case 'Z':
            z=*Y;
            break;
    }
    switch((*Z)->name){//Z
        case 'X':
            x=*Z;
            break;
        case 'Y':
            y=*Z;
            break;
        case 'Z':
            z=*Z;
            break;
    }
    *X=x;*Y=y;*Z=z;
}
