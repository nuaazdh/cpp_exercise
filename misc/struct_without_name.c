//没有变量名的变量
//作者：nuaazdh
//时间：2011年12月2日

#include<stdio.h>

typedef struct st1{//结构体1
    char a; //成员a
    char b; //成员b
}st1;

typedef struct st2{//结构体2
    st1;    //注意这里没有声明变量名
    int s;
}st2,*st2p;

void main()
{
    st2 s2;//结构体2 的变量
    st2p p;//结构体2 的指针
    char *tmp;//char *指针
    printf("sizeof(st1)=%d\n",sizeof(st1));//输出2
    printf("sizeof(st2)=%d\n",sizeof(st2));//输出8，说明st2中含有st1的空间
    s2.a='C';//可以对st2中的成员a赋值
    s2.b='S';
    p=(st2p)malloc(sizeof(st2));//为p申请空间
    p->a='D';//通过指针给st2的成员a赋值
    p->b='N';
    tmp=(char *)p;//通过char *型指针访问结构体2空间
    printf("%c\n",*tmp);//输出 D
    printf("%c\n",s2.a);//输出 C
    printf("%c\n",s2.b);//输出 S
    printf("%c\n",p->a);//输出 D
    printf("%c\n",p->b);//输出 N
}
/*
本例可以看出，在st2中声明 st1后，st1的成员便原封不动地拷贝到了
st2中，这样省去了通过 "st2变量名.st1变量名.st1成员名"来对st2中
st1变量名成员的访问的麻烦。可见 C语言 代码是多么自由啊。
*/
