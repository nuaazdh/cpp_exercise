//ʮ�������������ƣ�ʮ���ڣ�����ת��
//���ߣ�nuaazdh
//ʱ�䣺2011��11��30��
//�ݹ�ͷǵݹ�ʵ��
#include <stdio.h>

#define BASE 2 //���ƵĻ���������Ϊ2
void Scale(int d,int base);

int main()
{
    int decimal;//�洢ʮ������
    int n=1;//��¼BASE��λ��
    int t=2;//
    int *binary;//�洢ת�����BASE������
    int j=0;//ѭ������
    int temp;//��ʱ����
    printf("������һ��ʮ������:");
    scanf("%d",&decimal);//read the input number
    while(decimal/t!=0)
    {
        n++;
        t=t*BASE;
    }
    printf("��ʮ���������Ա�%dλ%d���Ʊ�ʾ.\n",n,BASE);

    binary=(int *)malloc(sizeof(int)*n);
    j=0;
    temp=decimal;
    for(j=n-1;j>=0;j--)
    {
        binary[j]=temp%BASE;
        temp=temp/BASE;
    }
    printf("%d��Ӧ��%d������Ϊ��",decimal,BASE);
    for(j=0;j<n;j++)
    {
        printf("%d",binary[j]);
        if((j+1)%4==0) printf(" ");//ÿ��λ���һ���ո�
    }
    //�ݹ�ʵ��
    printf("\n�ݹ�ʵ�ֽ����");
    Scale(decimal,BASE);
    return 0;
}

//��ʮ������dת��Ϊbase�������
void Scale(int d,int base)
{
    if(d/base!=0)//�����ó���
    {
        Scale(d/base,base);
        printf("%d",d%base);
    }
    else
    {
        printf("%d",d%base);
    }
}
