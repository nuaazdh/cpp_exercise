#include<stdio.h>

int main()
{
    char str[4][80];
    int j,i,sum[26]={0},count;
    printf("���������д�д��ĸ��\n");
    for(i=0;i<4;i++)
      gets(str[i]);
    for(i=0;i<4;i++)
      for(j=0;str[i][j]!='\0';j++)
      sum[str[i][j]-'A']++;
    count=0;//����������ĸ����
    for(i=0;i<26;i++)
      if(sum[i]>=count)
        count=sum[i];
    //printf("count=%d\n",count);
    printf("ͳ�ƽ����\n");
    for(j=count-1;j>=0;j--)
    {
        for(i=0;i<26;i++)
        {
            if(sum[i]<=j)
                printf("  ");
            else
                printf("* ");
        }
        printf("\n");//һ�������ϣ��س�
    }

    for(i=0;i<26;i++)
        printf("%c ",i+'A');
    printf("\n");
      return 0;
}
