//û�б������ı���
//���ߣ�nuaazdh
//ʱ�䣺2011��12��2��

#include<stdio.h>

typedef struct st1{//�ṹ��1
    char a; //��Աa
    char b; //��Աb
}st1;

typedef struct st2{//�ṹ��2
    st1;    //ע������û������������
    int s;
}st2,*st2p;

void main()
{
    st2 s2;//�ṹ��2 �ı���
    st2p p;//�ṹ��2 ��ָ��
    char *tmp;//char *ָ��
    printf("sizeof(st1)=%d\n",sizeof(st1));//���2
    printf("sizeof(st2)=%d\n",sizeof(st2));//���8��˵��st2�к���st1�Ŀռ�
    s2.a='C';//���Զ�st2�еĳ�Աa��ֵ
    s2.b='S';
    p=(st2p)malloc(sizeof(st2));//Ϊp����ռ�
    p->a='D';//ͨ��ָ���st2�ĳ�Աa��ֵ
    p->b='N';
    tmp=(char *)p;//ͨ��char *��ָ����ʽṹ��2�ռ�
    printf("%c\n",*tmp);//��� D
    printf("%c\n",s2.a);//��� C
    printf("%c\n",s2.b);//��� S
    printf("%c\n",p->a);//��� D
    printf("%c\n",p->b);//��� N
}
/*
�������Կ�������st2������ st1��st1�ĳ�Ա��ԭ�ⲻ���ؿ�������
st2�У�����ʡȥ��ͨ�� "st2������.st1������.st1��Ա��"����st2��
st1��������Ա�ķ��ʵ��鷳���ɼ� C���� �����Ƕ�ô���ɰ���
*/
