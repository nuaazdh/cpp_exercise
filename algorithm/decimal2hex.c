//十进制与其他进制（十以内）数的转化
//作者：nuaazdh
//时间：2011年11月30日
//递归和非递归实现
#include <stdio.h>

#define BASE 2 //进制的基，二进制为2
void Scale(int d,int base);

int main()
{
    int decimal;//存储十进制数
    int n=1;//记录BASE制位数
    int t=2;//
    int *binary;//存储转化后的BASE制数组
    int j=0;//循环变量
    int temp;//临时变量
    printf("请输入一个十进制数:");
    scanf("%d",&decimal);//read the input number
    while(decimal/t!=0)
    {
        n++;
        t=t*BASE;
    }
    printf("该十进制数可以被%d位%d进制表示.\n",n,BASE);

    binary=(int *)malloc(sizeof(int)*n);
    j=0;
    temp=decimal;
    for(j=n-1;j>=0;j--)
    {
        binary[j]=temp%BASE;
        temp=temp/BASE;
    }
    printf("%d对应的%d进制数为：",decimal,BASE);
    for(j=0;j<n;j++)
    {
        printf("%d",binary[j]);
        if((j+1)%4==0) printf(" ");//每四位输出一个空格
    }
    //递归实现
    printf("\n递归实现结果：");
    Scale(decimal,BASE);
    return 0;
}

//将十进制数d转化为base进制输出
void Scale(int d,int base)
{
    if(d/base!=0)//不能用除尽
    {
        Scale(d/base,base);
        printf("%d",d%base);
    }
    else
    {
        printf("%d",d%base);
    }
}
