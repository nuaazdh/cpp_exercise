#include <stdio.h>
#include <stdlib.h>

void main(int argc,char **argv)
{
    float a;
    float b;
    float result;
    char op;
    if(argc<4)
    {
        printf("对不起，参数太少.\n");
        exit(0);
    }
    a=atof(argv[2]);
    b=atof(argv[3]);
    op=argv[1][0];
    switch(op)
    {
        case '+':
            result=a+b;
            break;
        case '-':
            result=a-b;
            break;
        case '*':
            result=a*b;
            break;
        case '/':
            if(b==0)
            {
                printf("除数为0.\n");
                exit(0);
            }
            result=a*1.0/b;
    }
    printf("%g %c %g = %g",a,op,b,result);

}
