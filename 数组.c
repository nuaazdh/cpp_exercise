#include<stdio.h>
void main()
{
    int x,y,i,j,k;
    int x1,y1;
    int a[2][2];

    //元素全部清零
     for(i=0;i<2;i++)
      for(j=0;j<2;j++)
        a[i][j]=0;

      x=0;y=1;
      a[0][1]=1;
    for(k=2;k<10;k++)
    {
     x1=x-1;y1=y-1;
     if(y1<0) y1=1;
     if(x1<0) x1=1;//最大下标为1
     if(a[x1][y1]!=0)
     {
      x1=x;y1=y;
     }
     a[x1][y1]=k;

      printf("%3d\n",a[x1][y1]);

     x=x1;y=y1;
    }
    return 0;
}
