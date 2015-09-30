#include <stdio.h>
#include <stdlib.h>

void main()
{
    FILE *fp;
    FILE *resultfp;
    char buffer[100];
    fp=fopen("main.hex","r");
    resultfp=fopen("main.txt","w");
    if(resultfp==NULL||fp==NULL){//打开文件失败
        printf("Open file error.\n");
        exit(0);
    }
    while(fscanf(fp,"%s",buffer)!=EOF){//读取文件所有内容
        printf("%s\n",buffer);//控制台显示
        fprintf(resultfp,"%s\n",buffer);//写入文件
    }
    fclose(fp);
    fclose(resultfp);
}
