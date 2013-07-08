#include <stdio.h>
float add(float i,float j); //加法
float subtract(float i,float j); //减法
float multiply(float i,float j); //乘法
float divide(float i,float j); //除法
float get_float(void); //正确读取一个浮点数
char get_first(void); //得到首字符

int main(void)
{
    float m,n,p;
    char ch;


    printf("Enter the operation of your choice:\n"
    "a. add s. subtract \n"
    "m. multiply d. divide \n"
    "q. quit\n");
    ch=get_first();

    while(ch!='q'){
    printf("Enter first number:");
    m=get_float();
    printf("Enter second number:");
    n=get_float();
    switch(ch){
        case 'a':p=add(m,n);printf("%.2f + %.2f = %.2f\n",m,n,p);break;
        case 's':p=subtract(m,n);printf("%.2f - %.2f = %.2f\n",m,n,p);break;
        case 'm':p=multiply(m,n);printf("%.2f * %.2f = %.2f\n",m,n,p);break;
        case 'd':p=divide(m,n);printf("%.2f / %.2f = %.2f\n",m,n,p);break;
        case 'q':break;
        default:break;
    }
    printf("Enter the operation of your choice:\n"
    "a. add s. subtract \n"
    "m. multiply d. divide \n"
    "q. quit\n");
    ch=get_first();
    }

    printf("Bye!\n");
    return 0;
    }

    float add(float i,float j){
    float k;
    k=i+j;
    return k;
}

float subtract(float i,float j)
{
    float k;
    k=i-j;
    return k;
}

float multiply(float i,float j)
{
    float k;
    k=i*j;
    return k;
}

float divide(float i,float j)
{
    float k;
    if(j==0){
    printf("Enter a number other than 0:");
    j=get_float();
    }
    k=i/j;
    return k;
}

char get_first(void)
{ //这个似乎存在一个小问题
    char ch;
    ch=getchar();
    printf("Your input is:%c\n",ch);

    while(ch!='a'&&ch!='s'&&ch!='m'&&ch!='d'&&ch!='q'){
        flushall();/*清除缓冲区内容*/
        printf("Please enter the right choice 'a','s','m','d',or 'q':");
        ch=getchar();
    }
    flushall();
    return ch;
}

float get_float(void)
{
    float k;
    char ch;

    while(!scanf("%f",&k)){
        printf(" is not an number!\n");
        printf("Please enter an number such as 2.5,-1.78E8,or 3:");
        flushall();
    }
    printf("invalid float:%f\n",k);
    flushall();
    return k;
}
