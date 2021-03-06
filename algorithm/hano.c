//递归实现模拟汉诺塔
//作者：nuaazdh
//时间：2011年12月9日 08:22:27
#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define ORDER 10 //汉诺塔阶数

typedef int Status;//函数执行状态
typedef struct{
    char name;//塔座名
    int count;//当前塔座上的圆盘数
    int *disk;//当前塔座圆盘数组
}Towerfoot;

void InitHanoi(Towerfoot *X,Towerfoot *Y,Towerfoot *Z,int n);
    //汉诺塔初始化，X，Y，Z，汉诺塔阶数为n
Status Find(const Towerfoot *X,int id);
    //检验编号为id的圆盘是否在塔座X上,是返回TRUE;否则返回FALSE
Status Check(const Towerfoot *X);
    //监测Towerfoot是否排放正确
void move(Towerfoot *X,int id,Towerfoot *Z);
    //以Y为辅助塔基，将编号为id的圆盘从塔座X移到塔座Z
void Hanoi(Towerfoot *X,Towerfoot *Y,Towerfoot *Z,int n);
    //将塔座X上的编号为1到n的圆盘按规则移到塔座Z上
void PrintHanoi(const Towerfoot *X,const Towerfoot *Y,const Towerfoot *Z,int n);
    //打印汉诺塔三个塔座X，Y，Z上的圆盘
void PrintTower(const Towerfoot *X);
    //输出当个汉诺塔塔座上的圆盘序号
void Adjust(const Towerfoot **X,const Towerfoot **Y,const Towerfoot **Z);
    //根据塔座名称，调整塔座指针

int step=0;//全局变量，记录移动步数

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
    //汉诺塔初始化，X，Y，Z，汉诺塔阶数为n
    int i;
    X->count=n;
    Y->count=Z->count=0;
    X->disk=(int*)malloc(sizeof(int)*n);//申请圆盘数组空间
    Y->disk=(int*)malloc(sizeof(int)*n);
    Z->disk=(int*)malloc(sizeof(int)*n);
    if(!(X->disk&&Y->disk&&Z->disk)){
        printf("分配内存失败.\n");
        exit(0);
    }
    X->name='X';Y->name='Y';Z->name='Z';//塔座命名
    for(i=0;i<n;i++){//放置塔座X上的圆盘
        X->disk[i]=i+1;
    }
}

void Hanoi(Towerfoot *X,Towerfoot *Y,Towerfoot *Z,int n){
    //将塔座X上的编号为1到n的圆盘按规则移到塔座Z上
    //Y可做辅助塔座
    if(n==1){
        move(X,1,Z);//编号1的圆盘从X移动到Z
        PrintHanoi(X,Y,Z,ORDER);//输出当前汉诺塔结构
    }
    else{
        Hanoi(X,Z,Y,n-1);
        move(X,n,Z);//以Y为辅助塔座，将X编号为n的移到Z上
        PrintHanoi(X,Y,Z,ORDER);//输出汉诺塔
        Hanoi(Y,X,Z,n-1);
    }
}

void move(Towerfoot *X,int id,Towerfoot *Z){
    //将编号为id的圆盘从塔座X移到塔座Z
    int i;
    if(FALSE==Find(X,id)){
        printf("塔座X上没有编号为%d的圆盘.\n",id);
        return;
    }
    if(X->disk[0]!=id){
        printf("编号为%d的圆盘不是塔座X的最上方，无法移动.\n",id);
        return;
    }
    for(i=0;i<X->count-1;i++){//移动塔座X上的圆盘
        X->disk[i]=X->disk[i+1];
    }
    for(i=Z->count-1;i>=0;i--){//移动塔座Z的上圆盘
        Z->disk[i+1]=Z->disk[i];
    }
    Z->disk[0]=id;
    X->count--;
    Z->count++;
    step++; //每移动一次，步数加1
}

Status Find(const Towerfoot *X,int id){
    //检验编号为id的圆盘是否在塔座X上,是返回TRUE;否则返回FALSE
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
    //监测Towerfoot是否排放正确
    int i=0;
    for(i=0;i<X->count-1;i++){
        if((X->disk[i]<0)||(X->disk[i]>X->disk[i+1]))
            return FALSE;
    }
    return TRUE;
}

void PrintHanoi(const Towerfoot *X,const Towerfoot *Y,const Towerfoot *Z,int n){
    //打印汉诺塔三个塔座X，Y，Z上的圆盘
    int i,j;//循环变量
    char disc='#',space=' ';
    printf("\nstep %d:\n",step);
    Adjust(&X,&Y,&Z);   //根据塔座名称调整汉诺塔指针
    for(i=0;i<n;i++){
        for(j=0;j<3*n+2;j++){
            if((n-X->count<=i)&&(X->disk[i-(n-X->count)]>j)){//X塔座
                printf("%c",disc);
            }else
            if((n-Y->count<=i)&&(j-n>0)&&(Y->disk[i-(n-Y->count)]>=j-n)){//Y塔座
                printf("%c",disc);
            }else
            if((n-Z->count<=i)&&(j-2*n-1>0)&&(Z->disk[i-(n-Z->count)]>=j-2*n-1)){//Z塔座
                printf("%c",disc);
            }else{
                printf("%c",space);
            }
        }
        printf("\n");
    }
    for(j=0;j<4*(n+2)+2;j++){//输出塔座名称
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
    //输出当个汉诺塔塔座上的圆盘序号
    int i;
    printf("%c:",X->name);
    for(i=0;i<X->count;i++){
        printf("%d ",X->disk[i]);
    }
    printf("\n");
}

void Adjust(const Towerfoot **X,const Towerfoot **Y,const Towerfoot **Z){
    //根据塔座名称，调整塔座指针
    //根据塔座名称，调整塔座指针
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
