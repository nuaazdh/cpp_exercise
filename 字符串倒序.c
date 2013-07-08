#include <stdio.h>

#define BUFFERSIZE 100

int strlen(const char *src);
char *convert(const char *src,char *dst);

void main()
{
    char s[BUFFERSIZE],*dst;
    printf("Pleas input a string(less than 100 characters):");
    scanf("%s",s);
    printf("before:%s\n",s);
    dst=(char *)malloc(strlen(s)+1);
    dst=convert(s,dst);
    printf("after:%s\n",dst);

}

int strlen(const char *src)
{
    int i=0;
    char *p=src;
    while(*(p++)!='\0') i++;
    return i;
}

char *convert(const char *src,char *dst)
{
    int i=0,j;
    char *p=src;
    while(*(p++)!='\0') i++;
    p--;
    for(j=0;j<=i;j++)
    {
        dst[j]=*(--p);
    }
    dst[j]='\0';
    return dst;
}
