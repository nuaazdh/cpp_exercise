//ϡ�����ʵ��
//���ߣ�nuaazdh
//ʱ�䣺2011��12��11�� 12:15:38

#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100

typedef int Status;
typedef float ElemType;
typedef struct{//��Ԫ��ṹ
    int i,j;//����Ԫ�����±�����±�
    ElemType e;//����Ԫ��ֵ
}Triple;
typedef struct{
    Triple data[MAXSIZE+1];//����Ԫ��Ԫ���data[0]����
    int mu,nu,tu;//����������������ͷ���Ԫ�ظ���
}TSMatrix;

TSMatrix NewMatrix(int m,int n);
    //�½�һ����Ԫ���ʾ��ϡ�����
Status InsertElem(TSMatrix *M,int row,int col,ElemType e);
    //����Ԫ���ʾ��ϡ�����M���� row �У��� col ��λ�ò���Ԫ��e
    //����ɹ�������OK�����򷵻�ERROR
Status FindElem(const TSMatrix *M,int row,int col,ElemType *e);
    //������Ԫ���ʾ��ϡ�����M�У��� row �У��� col��Ԫ�أ�����Ϊ0��
    //����e������ֵ��������TRUE�����򷵻�FALSE
Status TransposeSMatrix(const TSMatrix *M,TSMatrix *T);
    //������Ԫ���洢��ʾ����ϡ�����M��ת�þ���T
Status FastTransposeSMatrix(const TSMatrix *M,TSMatrix *T);
    //������Ԫ��˳���洢��ʾ����ϡ�����M��ת�þ���T
Status MultSMatrix(const TSMatrix *M,const TSMatrix *T,TSMatrix *Q);
    //ϡ�����ĳ˷�,������ϳ˷�����Q����M*T�����������OK,���򷵻�ERROR
void PrintSMatrix(const TSMatrix *M);
    //��ӡϡ���������Ԫ��

int main()
{
    TSMatrix M=NewMatrix(3,4);
    TSMatrix T;
    TSMatrix Q;
    InsertElem(&M,3,2,3.65);
    InsertElem(&M,2,2,2.31);
    printf("\nM:");
    PrintSMatrix(&M);
    FastTransposeSMatrix(&M,&T);
    printf("\nT(Transpose of M):");
    PrintSMatrix(&T);
    MultSMatrix(&M,&T,&Q);
    printf("\nM*T=");
    PrintSMatrix(&Q);
    return 0;
}

TSMatrix NewMatrix(int m,int n){
    //�½�һ����Ԫ���ʾ��ϡ�����
    TSMatrix M;
    M.mu=m;
    M.nu=n;
    M.tu=0;
    return M;
}

Status InsertElem(TSMatrix *M,int row,int col,ElemType e){
    //����Ԫ���ʾ��ϡ�����M���� row �У��� col ��λ�ò���Ԫ��e
    //����ɹ�������OK�����򷵻�ERROR
    int i,t,p;
    if(M->tu>=MAXSIZE){//��ǰ��Ԫ�������
        printf("\nError:There is no space in the matrix;\n");
        return ERROR;
    }
    if(row>M->mu||col>M->nu||row<1||col<1){//����λ��Խ�磬����1~mu��1~nu֮��
        printf("\nError:Insert position is beyond the arrange.\n");
        return ERROR;
    }
    p=1;//��־��Ԫ��Ӧ�ò����λ��
    if(M->tu==0){//����ǰ����Mû�з���Ԫ��
        M->data[p].i=row;
        M->data[p].j=col;
        M->data[p].e=e;
        M->tu++;
        return OK;
    }
    for(t=1;t<=M->tu;t++)//Ѱ�Һ��ʵĲ���λ��
        if((row>=M->data[t].i)&&(col>=M->data[t].j))
                p++;
    if(row==M->data[t-1].i && col==M->data[t-1].j){//����ǰ����Ԫ���Ѿ�����
        M->data[t-1].e=e;
        return OK;
    }
    for(i=M->tu;i>=p;i--){//�ƶ�p֮���Ԫ��
        M->data[i+1].i=M->data[i].i;
        M->data[i+1].j=M->data[i].j;
        M->data[i+1].e=M->data[i].e;
    }
    //������Ԫ��
    M->data[p].i=row;
    M->data[p].j=col;
    M->data[p].e=e;
    M->tu++;
    return OK;
}

Status FindElem(const TSMatrix *M,int row,int col,ElemType *e){
    //������Ԫ���ʾ��ϡ�����M�У��� row �У��� col��Ԫ�أ�����Ϊ0��
    //����e������ֵ��������TRUE�����򷵻�FALSE
    int p;
    for(p=1;p<=M->tu;p++)
        if(M->data[p].i==row&&M->data[p].j==col){
            *e=M->data[p].e;
            return TRUE;
        }
    return FALSE;
}

Status TransposeSMatrix(const TSMatrix *M,TSMatrix *T){
    //������Ԫ���洢��ʾ����ϡ�����M��ת�þ���T
    int col,p,q;
    T->mu=M->nu;    T->nu=M->mu; T->tu=M->tu;
    if(T->tu){
        q=1;
        for(col=1;col<=M->mu;col++)
            for(p=1;p<=M->tu;p++)
                if(M->data[p].j==col){
                    T->data[q].i=M->data[p].j;
                    T->data[q].j=M->data[p].i;
                    T->data[q].e=M->data[p].e;
                    q++;
                }
    }
    return OK;
}

Status FastTransposeSMatrix(const TSMatrix *M,TSMatrix *T){
    //������Ԫ��˳���洢��ʾ����ϡ�����M��ת�þ���T
    int col,t,p,q,*num,*cpot;
    T->mu=M->nu;    T->nu=M->mu;    T->tu=M->tu;
    if(T->tu){
        num=(int *)malloc(sizeof(int)*M->tu);
        cpot=(int *)malloc(sizeof(int)*M->tu);
        if(!(num&&cpot)){
            printf("Apply for memory error.\n");
            exit(0);
        }
        for(col=1;col<=M->nu;col++) num[col]=0;
        //��M��ÿһ�к��з���Ԫ�صĸ���
        for(t=1;t<=M->tu;t++)   ++num[M->data[t].j];
        cpot[1]=1;
        //���col���е�һ������Ԫ����b.data�е����
        for(col=2;col<=M->nu;col++)
            cpot[col]=cpot[col-1]+num[col-1];
        for(p=1;p<=M->tu;p++){
            col=M->data[p].j;   q=cpot[col];
            T->data[q].i=M->data[p].j;
            T->data[q].j=M->data[p].i;
            T->data[q].e=M->data[q].e;
            ++cpot[col];
        }//for
    }//if
    return OK;
}

Status MultSMatrix(const TSMatrix *M,const TSMatrix *T,TSMatrix *Q){
    //ϡ�����ĳ˷�,������ϳ˷�����Q����M*T�����������OK,���򷵻�ERROR
    int i,j,k,p;
    ElemType m,t,s;
    if(M->nu!=T->mu){
        printf("Sorry,these two matrice can't multiply.\n");
        return ERROR;
    }
    Q->mu=M->mu;    Q->nu=T->nu;    Q->tu=0;
    p=1;
    if(!M->tu*T->tu){//M��T��ȫ�����
        return OK;
    }
    for(i=1;i<=Q->mu;i++){
        for(j=1;j<=Q->nu;j++){
            s=0;
            for(k=1;k<=M->nu;k++){
                if(FALSE==FindElem(M,i,k,&m))
                    continue;
                if(FALSE==FindElem(T,k,j,&t))
                    continue;
                s+=m*t;
            }
            if(s!=0){//Q[i][j]����
                Q->data[p].i=i;
                Q->data[p].j=j;
                Q->data[p].e=s;
                p++;
                Q->tu++;
            }
        }
    }

    return OK;

}

void PrintSMatrix(const TSMatrix *M){
    //��ӡϡ���������Ԫ��
    int i,j,p=1;
    printf("\nsize:%d �� %d\n",M->mu,M->nu);
    if(!M->tu){//0����
        printf("%g\n",0.0);
        return;
    }
    for(i=1;i<=M->mu;i++){
        for(j=1;j<=M->nu;j++){
            if(i==M->data[p].i && j==M->data[p].j){
                printf("%g\t",M->data[p].e);
                p++;
            }else{
                printf("%g\t",0.0);
            }
        }
        printf("\n");
    }
    printf("\n");
}

