/*
Function: A small phonebook
Author: nuaazdh
Date:11-1,2011
*/
#include <stdio.h>

#define NAMELEN 16
#define PHONELEN 11
#define EMAILLEN 28
#define BUFFERSIZE 100

#define YES 1
#define NO  0

/*关系类型*/
typedef enum Relation
{
	FAMILY,FRIEND,CALSSMEATE,TEACHER,OTHER
};

/*节点结构体*/
typedef struct{
	/*pointer struct*/
	char *name;
	char *phonenum;
	char *email;
	/*array struct
	char name[NAMELEN];
	char phonenum[PHONELEN];
	char email[EMAILLEN];*/
	enum Relation relation;
	struct RecordNode *next;
}RecordNode;

/*函数原型*/
void ShowWelcome();
void ShowBye();
struct RecordNode *Create();
struct RecordNode *CreateNew();
char SelectOperation();
struct RecordNode * Insert(struct RecordNode *head,struct RecordNode *newnode);
void ShowAll(struct RecordNode *head);
void ShowNode(struct RecordNode *node);
struct RecordNode *Delete(struct RecordNode *head);
void Save(struct RecordNode *head);
char *CatNode(struct RecordNode *node);
int strlen(char *src);
int AllNum(char *src);
int IsNum(const char c);
int IsChar(const char c);
struct RecordNode* ReadNode(char *file);

/*主函数*/
int main()
{
	ShowWelcome();
	struct RecordNode *head=Create();
	char op=SelectOperation();
	while(1)
	{
		if('a'==op){
			struct RecordNode *newnode = CreateNew();
			head=Insert(head,newnode);
		}
		else if('d'==op){
			head=Delete(head);
		}
		else if('s'==op){
			ShowAll(head);
		}
		else if('v'==op){
			Save(head);
		}
		else if('q'==op){
			break;
		}
		else{
			;
		}
		printf(">>");/*print */
		scanf("%s",&op);/*only get the first letter*/
		op=tolower(op);
		//op=getch();
	}
	ShowBye();
	return 1;
}

/*创建一个新节点，返回指针*/
struct RecordNode *CreateNew()
{
	struct RecordNode *node=(struct RecordNode *)malloc(sizeof(struct RecordNode));
	node->name=(char *)malloc(sizeof(char)*19);
	node->phonenum=(char*)malloc(sizeof(char)*12);
	node->email=(char *)malloc(sizeof(char)*41);
	printf("Please input the name(less than 16 characters):");
	scanf("%s",node->name);
	printf("Please input the phone number(11 numbers):");
	scanf("%s",node->phonenum);
	while(NO==AllNum(node->phonenum))
	{
		printf("Sorry,invalid phone number.Please input again or 'q' to escape:");
		scanf("%s",node->phonenum);
		if('q'==*node->phonenum)
			return NULL;
	}
	printf("Please input the emain address(less than 40 characters):");
	scanf("%s",node->email);
	node->next=NULL;
	return node;
}

/*获取用户选择*/
char SelectOperation()
{
	char input;
	printf("Please input your opeartion(first letter is valid):\n");
	printf("a: Add a new account\n");
	printf("d: Delete a account\n");
	printf("s: Show all records\n");
	printf("v: Save all records\n");
	printf("q: Quit\n");
	printf("others: Do nothing.\n");
	printf(">>");
	scanf("%s",&input);
	//input=getchar();
	input=tolower(input);/*transfer to lower case*/
	return input;
}

/*插入一个节点，并返回头节点*/
struct RecordNode *Insert(struct RecordNode *head,struct RecordNode *newnode)
{

	if(newnode==NULL)
		return head;/*return directly*/
	if(head==NULL){
		head=newnode;
		head->next=NULL;
	}else{
		struct RecordNode *p=head;
		while(p->next!=NULL)
			p=p->next;
		p->next=newnode;
		newnode->next=NULL;
	}/*if*/
	return head;
}

/*根据编号删除某个节点*/
struct RecordNode *Delete(struct RecordNode *head)
{
	if(head==NULL){
		printf("Sorry,there is no record.\n");
		return NULL;
	}
	else
		printf("Please input the No. your want to delete(from 1):");
	int d;
	scanf("%d",&d);
	struct RecordNode *p=head;
	if(d==1){
		head=head->next;
		/*删除首节点*/
		free(p);
	}else{/*删除非首节点*/
		int i=1;
		while(i!=d&&p!=NULL){
			i++;p=p->next;
		}/*while*/
		if(p==NULL){/*删除节点不存在*/
			printf("Sorry,the node is not exist.\n");
			return head;
		}else{
			struct RecordNode *pre=head;
			while(pre->next!=p)
				pre=pre->next;
			pre->next=p->next;
			free(p);
			}
		}/*else*/
		printf("Delete succeed!\n");
		if(head==NULL)
			printf("There is on record now\n");

	return head;
}

/*循环显示所有节点*/
void ShowAll(struct RecordNode *head)
{
	if(head==NULL){
		printf("Sorry,there is no record now.\n");
		return;
	}
	printf("Name\t\t");
	printf("Phone Number\t");
	printf("Email\n");
	struct RecordNode *p=head;
	while(p!=NULL)
	{
		ShowNode(p);
		p=p->next;
	}
	printf("\n");
}

/*显示一个节点*/
void ShowNode(struct RecordNode *node)
{
	if(node==NULL)
	  return;
	printf("%s\t",node->name);
	printf("%s\t",node->phonenum);
	printf("%s\n",node->email);
}

/*显示欢迎*/
void ShowWelcome()
{
	int i=0;
	for(i=0;i<40;i++)
		printf("*");
	printf("\nWelcome to PhoneBook\n");
	printf("by luerfeng, version:1.0\n");
	for(i=0;i<40;i++)
		printf("*");
	printf("\n");
}

/*显示再见*/
void ShowBye()
{
	int i=0;
	for(i=0;i<40;i++)
		printf("*");
	printf("\nThank you for ues,GoodBye !\n");
	printf("by nuaazdh, version:1.0\n");
	for(i=0;i<40;i++)
		printf("*");
	printf("\n");
}

/*建立从文件中建立链表*/
struct RecordNode *Create()
{
	char *file = "Phone.txt";
	char option;
	int fd;
	if(access(file,F_OK)==-1)/*file does not exist*/
	{
		printf("Phone.txt does not exsit,do you want to create?[y/n]:");
		option=getchar();
		option=tolower(option);/*transfer to lower case*/
		if('y'==option)
		{
			fd=open(file,O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);
			if(fd==-1)
				printf("\nSorry,create file failed.\n\n");
			else
				printf("\nCreate file succeed.\n\n");
			close(fd);
		}
		return NULL;
	}
	else/*Create link-table from file*/
		return ReadNode(file);
}

/*保存所有记录*/
void Save(struct RecordNode *head)
{
	int fd;/*file describtion*/
	struct RecordNode *ptr=head;
	if(head==NULL)
	{
		printf("Sorry,there is no record now.\n");
		return;
	}
	fd=open("Phone.txt",O_TRUNC|O_CREAT|O_RDWR,00666);
	if(fd==-1)
	{
		perror("Sorry,Create or open file failed");
		return;
	}
	int count=0;
	char *cptr;
	int cntw;
	while(ptr!=NULL)
	{
		cptr=CatNode(ptr);
		count=strlen(cptr);
		/*printf("Record info:%s\n",cptr);*/
		if(cptr==NULL)
			continue;
		while((cntw=write(fd,cptr,count))!=0)
		{
			if(cntw==-1)
			{
				printf("Sorry,save failed.\n");
				perror("Error Message:");
				break;
			}
			else if(cntw==count)
				break;
			else if(cntw>0)
			{
				cptr+=cntw;
				count-=cntw;
			}
		}
		ptr=ptr->next;
	}
	close(fd);
}

/*将当前节点内容转换为带格式的字符串*/
char *CatNode(struct RecordNode *node)
{
	if(node==NULL)
		return NULL;
	//int count=sizeof(node->name)+sizeof(node->phonenum)+sizeof(node->email);
	char *cptr=(char *)malloc(60);
	char *dst=cptr;
	char *p;
	p=node->name;
	/*printf("%s\n",p);*/
	while(*p!='\0')
	{
		*cptr++=*p++;
	}
	*cptr++='\t';
	p=node->phonenum;
	/*printf("%s\n",p);*/
	while(*p!='\0')
	{
		*cptr++=*p++;
	}
	*cptr++='\t';
	p=node->email;
	/*printf("%s\n",p);*/
	while(*p!='\0')
	{
		*cptr++=*p++;
	}
	*cptr++='\r';
	*cptr++='\n';
	*cptr='\0';
	/*printf("%s\n",cptr);*/
	return dst;/*return the string*/
}

/*计算字符串长度*/
int strlen(char *src)
{
	if(src==NULL)
		return 0;
	int i=0;/*counter*/
	char *p=src;
	while(*p!='\0')
	{
		p++;i++;
	}
	return i;
}

/*检验字符串是否全为数字，1：全数字，0：不是全数字*/
int AllNum(char *src)
{
	char *p=src;
	int flag=YES;
	while(*p!='\0')
	{
		if(NO==IsNum(*p))
		{
			flag=NO;
			break;
		}
		p++;
	}
	return flag;
}

/*检验某个字符是否为数字，YES：是数字，NO：非数字*/
int IsNum(const char c)
{
	if((c>='0')&&(c<='9'))
	{
		return YES;
	}
	else
		return NO;
}

/*判断字符是否为数字或字母，YES：是，NO：否*/
int IsChar(const char c)
{
	if((c<='9'&&c>='0')||(c<='z'&&c>='a')||(c<='Z'&&c>='A'))
		return YES;
	else
		return NO;
}

/*判断字符是否可能出现在邮箱中,YES:可以，NO：不可以*/
int IsEmailChar(const char c)
{
	if(IsChar(c)||('@'==c)||('_'==c)||('.'==c)||('-'==c))
		return YES;
	else
		return NO;
}

/*从文件中读取记录，返回链表头指针*/
struct RecordNode* ReadNode(char *file)
{
	FILE *fp;
	struct RecordNode *head=NULL;
	fp=fopen(file,"r");
	if(fp==NULL)
	{
		printf("Sorry,read file failed.\n");
		return head;
	}
	char buffer[BUFFERSIZE];
	//char *fptr;
	char *p,*q;
	struct RecordNode* newnode;
	while(fgets(buffer,BUFFERSIZE,fp)!=NULL)
	{
		/*apply for a new node*/
		newnode=(struct RecordNode*)malloc(sizeof(struct RecordNode));
		p=buffer;
		if(newnode==NULL)
		{
			printf("Memory apply error.\n");
			break;
		}
		/*get name*/
		newnode->name=(char *)malloc(sizeof(char)*NAMELEN);
		q=newnode->name;
		while(YES==IsChar(*p))
		{
			*q++=*p++;
		}
		*q='\0';
		while(NO==IsChar(*p)) p++;
		/*get phonenum*/
		newnode->phonenum=(char *)malloc(sizeof(char)*PHONELEN);
		q=newnode->phonenum;
		while(YES==IsChar(*p))
		{
			*q++=*p++;
		}
		*q='\0';
		while(NO==IsChar(*p)) p++;
		/*get email*/
		newnode->email=(char *)malloc(sizeof(char)*EMAILLEN);
		q=newnode->email;
		while(YES==IsEmailChar(*p))
		{
			*q++=*p++;
		}
		*q='\0';
		head=Insert(head,newnode);
	}
	fclose(fp);
	return head;
}
