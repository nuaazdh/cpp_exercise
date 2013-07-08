//稀疏矩阵实例
//作者：nuaazdh
//时间：2011年12月11日 12:15:38

#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100

typedef int Status;
typedef float ElemType;
typedef struct{//三元组结构
    int i,j;//非零元素行下标和列下标
    ElemType e;//非零元素值
}Triple;
typedef struct{
    Triple data[MAXSIZE+1];//非零元三元组表，data[0]不用
    int mu,nu,tu;//矩阵的行数、列数和非零元素个数
}TSMatrix;

TSMatrix NewMatrix(int m,int n);
    //新建一个三元组表示的稀疏矩阵
Status InsertElem(TSMatrix *M,int row,int col,ElemType e);
    //在三元组表示的稀疏矩阵M，第 row 行，第 col 列位置插入元素e
    //插入成功，返回OK，否则返回ERROR
Status FindElem(const TSMatrix *M,int row,int col,ElemType *e);
    //查找三元组表示的稀疏矩阵M中，第 row 行，第 col列元素，若不为0，
    //则用e返回其值，并返回TRUE，否则返回FALSE
Status TransposeSMatrix(const TSMatrix *M,TSMatrix *T);
    //采用三元组表存储表示，求稀疏矩阵M的转置矩阵T
Status FastTransposeSMatrix(const TSMatrix *M,TSMatrix *T);
    //利用三元组顺序表存储表示，求稀疏矩阵M的转置矩阵T
Status MultSMatrix(const TSMatrix *M,const TSMatrix *T,TSMatrix *Q);
    //稀疏矩阵的乘法,如果符合乘法规则，Q返回M*T结果，并返回OK,否则返回ERROR
void PrintSMatrix(const TSMatrix *M);
    //打印稀疏矩阵所有元素

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
    //新建一个三元组表示的稀疏矩阵
    TSMatrix M;
    M.mu=m;
    M.nu=n;
    M.tu=0;
    return M;
}

Status InsertElem(TSMatrix *M,int row,int col,ElemType e){
    //在三元组表示的稀疏矩阵M，第 row 行，第 col 列位置插入元素e
    //插入成功，返回OK，否则返回ERROR
    int i,t,p;
    if(M->tu>=MAXSIZE){//当前三元组表已满
        printf("\nError:There is no space in the matrix;\n");
        return ERROR;
    }
    if(row>M->mu||col>M->nu||row<1||col<1){//插入位置越界，不在1~mu或1~nu之间
        printf("\nError:Insert position is beyond the arrange.\n");
        return ERROR;
    }
    p=1;//标志新元素应该插入的位置
    if(M->tu==0){//插入前矩阵M没有非零元素
        M->data[p].i=row;
        M->data[p].j=col;
        M->data[p].e=e;
        M->tu++;
        return OK;
    }
    for(t=1;t<=M->tu;t++)//寻找合适的插入位置
        if((row>=M->data[t].i)&&(col>=M->data[t].j))
                p++;
    if(row==M->data[t-1].i && col==M->data[t-1].j){//插入前，该元素已经存在
        M->data[t-1].e=e;
        return OK;
    }
    for(i=M->tu;i>=p;i--){//移动p之后的元素
        M->data[i+1].i=M->data[i].i;
        M->data[i+1].j=M->data[i].j;
        M->data[i+1].e=M->data[i].e;
    }
    //插入新元素
    M->data[p].i=row;
    M->data[p].j=col;
    M->data[p].e=e;
    M->tu++;
    return OK;
}

Status FindElem(const TSMatrix *M,int row,int col,ElemType *e){
    //查找三元组表示的稀疏矩阵M中，第 row 行，第 col列元素，若不为0，
    //则用e返回其值，并返回TRUE，否则返回FALSE
    int p;
    for(p=1;p<=M->tu;p++)
        if(M->data[p].i==row&&M->data[p].j==col){
            *e=M->data[p].e;
            return TRUE;
        }
    return FALSE;
}

Status TransposeSMatrix(const TSMatrix *M,TSMatrix *T){
    //采用三元组表存储表示，求稀疏矩阵M的转置矩阵T
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
    //利用三元组顺序表存储表示，求稀疏矩阵M的转置矩阵T
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
        //求M中每一列含有非零元素的个数
        for(t=1;t<=M->tu;t++)   ++num[M->data[t].j];
        cpot[1]=1;
        //求第col列中第一个非零元素在b.data中的序号
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
    //稀疏矩阵的乘法,如果符合乘法规则，Q返回M*T结果，并返回OK,否则返回ERROR
    int i,j,k,p;
    ElemType m,t,s;
    if(M->nu!=T->mu){
        printf("Sorry,these two matrice can't multiply.\n");
        return ERROR;
    }
    Q->mu=M->mu;    Q->nu=T->nu;    Q->tu=0;
    p=1;
    if(!M->tu*T->tu){//M和T是全零矩阵
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
            if(s!=0){//Q[i][j]非零
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
    //打印稀疏矩阵所有元素
    int i,j,p=1;
    printf("\nsize:%d × %d\n",M->mu,M->nu);
    if(!M->tu){//0矩阵
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

