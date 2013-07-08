#include<stdio.h>

int main()
{
    char str[4][80];
    int j,i,sum[26]={0},count;
    printf("请输入四行大写字母：\n");
    for(i=0;i<4;i++)
      gets(str[i]);
    for(i=0;i<4;i++)
      for(j=0;str[i][j]!='\0';j++)
      sum[str[i][j]-'A']++;
    count=0;//出现最多的字母次数
    for(i=0;i<26;i++)
      if(sum[i]>=count)
        count=sum[i];
    //printf("count=%d\n",count);
    printf("统计结果：\n");
    for(j=count-1;j>=0;j--)
    {
        for(i=0;i<26;i++)
        {
            if(sum[i]<=j)
                printf("  ");
            else
                printf("* ");
        }
        printf("\n");//一行输出完毕，回车
    }

    for(i=0;i<26;i++)
        printf("%c ",i+'A');
    printf("\n");
      return 0;
}
