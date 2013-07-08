//˳��ջ��Ӧ�ã����ʽ��ֵ
//�����û�����ո�ϵͳ�Զ�ɾ������ֻ�ܽ����������������㣬֧��С����
//�Բ��������Ľ����������������������ȡ��
//���ߣ�nuaazdh
//ʱ�䣺2011��12��8�� 10:49:39
#include <stdio.h>
#include <stdlib.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define BUFFERSIZE 256

typedef int Status; //��������״̬
typedef int opndElem;  //������Ԫ������
typedef struct{//������ջ�ṹ����
    opndElem *base;
    opndElem *top;
    int stacksize;
}OpndStack;

typedef char optrElem;//������Ԫ������
typedef struct{//������ջ�ṹ����
    optrElem *base;
    optrElem *top;
    int stacksize;
}OptrStack;

//==========������ջ=============//
Status InitStack_OPND(OpndStack *S);
    //����һ����ջS
Status GetTop_OPND(OpndStack S,opndElem *e);
    //��ջ��Ϊ�գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�FALSE
Status Push_OPND(OpndStack *S,opndElem e);
    //����Ԫ��eΪ�µ�ջ��Ԫ��
Status Pop_OPND(OpndStack *S,opndElem *e);
    //��ջS��Ϊ�գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK,���򷵻�ERROR

//==========������ջ=============//
Status InitStack_OPTR(OptrStack *S);
    //����һ����ջS
optrElem GetTop_OPTR(OptrStack S);
    //��ջ��Ϊ�գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�FALSE
Status Push_OPTR(OptrStack *S,optrElem e);
    //����Ԫ��eΪ�µ�ջ��Ԫ��
Status Pop_OPTR(OptrStack *S,optrElem *e);
    //��ջS��Ϊ�գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK,���򷵻�ERROR

//============�������================//
void Standard(char *expression);
    //�����ʽ��׼��
opndElem EvalueateExpression(const char *expression);
    //�������ʽ��ֵ
Status Isoperator(char c);
    //�ж�c�Ƿ���һ��������
char Precede(char op1,char op2);
    //�ж�op1��op2���ȼ��ĸߵͣ�����'>','<','='
opndElem operate(opndElem a,optrElem theta,opndElem b);
    //�Բ�����a��b����theta����
const char *getOpnd(const char *c,opndElem *op);
    //�����*c��ʼ�Ĳ����������غ�cΪ������

int main()
{
    opndElem result=0;
    char *expression=(char*)malloc(sizeof(char)*BUFFERSIZE);
    if(expression==NULL){
        printf("Sorry,memory initialize error.\n");
        exit(0);
    }
    printf("Please input an expression(just for integer):\n");
    gets(expression);
    printf("Before standard:%s\n",expression);
    Standard(expression);//��׼��
    printf("Standard expression:%s\n",expression);
    result=EvalueateExpression(expression);
    printf("The result of the expression:%d\n",result);
    return 0;
}

//==========������ջ===========//
Status InitStack_OPND(OpndStack *S){
    //����һ���ղ�����ջS
    S->base=(opndElem *)malloc(STACK_INIT_SIZE*sizeof(opndElem));
    if(!S->base)//����ʧ��
    {
        printf("�����ڴ�ʧ��.\n");
        exit(0);
    }
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

Status GetTop_OPND(OpndStack S,opndElem *e){
    //��������ջ��Ϊ�գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�FALSE
    if(S.top==S.base){
        printf("ջΪ��.\n");
        return FALSE;
    }else{
        *e=*(S.top-1);
        return OK;
    }
}

Status Push_OPND(OpndStack *S,opndElem e){
    //����Ԫ��eΪ�µ�ջ��Ԫ��
    if(S->top-S->base>=S->stacksize){//ջ������׷�Ӵ洢�ռ�
        S->base=(opndElem *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(opndElem));
        if(!S->base)
        {
            printf("��������ռ�ʧ��.\n");
            exit(0);
        }
        S->top=S->base+S->stacksize;//����ջ��ָ��
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}

Status Pop_OPND(OpndStack *S,opndElem *e){
    //��ջS��Ϊ�գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK,���򷵻�ERROR
    if(S->top==S->base){//ջΪ��
        printf("ջΪ��.\n");
        return ERROR;
    }
    *e=*(--S->top);
    return OK;
}

//==========������ջ===========//
Status InitStack_OPTR(OptrStack *S){
    //����һ���ղ�����ջS
    S->base=(optrElem *)malloc(STACK_INIT_SIZE*sizeof(optrElem));
    if(!S->base)//����ʧ��
    {
        printf("�����ڴ�ʧ��.\n");
        exit(0);
    }
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

optrElem GetTop_OPTR(OptrStack S){
    //��������ջ��Ϊ�գ��򷵻�S��ջ��Ԫ�أ�������OK�����򷵻�FALSE
    optrElem e;
    if(S.top==S.base){
        printf("ջΪ��.\n");
    }else{
        e=*(S.top-1);
    }
    return e;
}

Status Push_OPTR(OptrStack *S,optrElem e){
    //����Ԫ��eΪ�µ�ջ��Ԫ��
    if(S->top-S->base>=S->stacksize){//ջ������׷�Ӵ洢�ռ�
        S->base=(optrElem *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(optrElem));
        if(!S->base)
        {
            printf("��������ռ�ʧ��.\n");
            exit(0);
        }
        S->top=S->base+S->stacksize;//����ջ��ָ��
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}

Status Pop_OPTR(OptrStack *S,optrElem *e){
    //��ջS��Ϊ�գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK,���򷵻�ERROR
    if(S->top==S->base){//ջΪ��
        printf("ջΪ��.\n");
        return ERROR;
    }
    *e=*(--S->top);
    return OK;
}

//============�������================//
opndElem EvalueateExpression(const char *expression){
    //��ֻ��������������������ʽ expression ��ֵ
    //OPTR:������ջ��OPND:������ջ
    const char *c=expression;
    OpndStack OPND;
    OptrStack OPTR;
    optrElem x,theta;
    opndElem a,b,num,result;
    InitStack_OPTR(&OPTR);//��ʼ��������ջ
    InitStack_OPND(&OPND);//��ʼ��������ջ
    Push_OPTR(&OPTR,'#');//���Ƚ�ƥ�����'#'��ջ
    while(*c!='#'||GetTop_OPTR(OPTR)!='#'){
        //printf("getchar=%c\n",*c);
        if(*c=='\0')//�����س��˳�
            break;
        if(FALSE==Isoperator(*c)){
            c=getOpnd(c,&num);
            Push_OPND(&OPND,num);
        }
        else
            switch(Precede(GetTop_OPTR(OPTR),*c)){
                case '<':
                    Push_OPTR(&OPTR,*c);
                    c++;
                    break;
                case '=':
                    Pop_OPTR(&OPTR,&x);
                    c++;
                    break;
                case '>':
                    Pop_OPTR(&OPTR,&theta);
                    Pop_OPND(&OPND,&b);
                    Pop_OPND(&OPND,&a);
                    result=operate(a,theta,b);
                    //printf("temp result is:%d\n",result);
                    Push_OPND(&OPND,result);
                    break;
                default:
                    //printf("Precede:%c",Precede(GetTop_OPTR(OPTR),*c));
                    break;
            }//switch
    }//while
    GetTop_OPND(OPND,&result);
    return result;
}

void Standard(char *expression){
    //���ַ������ʽ��׼��Ϊ�������ʽ
    char *p=expression,*q;
    while(*p!='\0'){//�����ַ���
        if(*p==' '){//����ǿո�ɾ��
            while(*p==' '){//ɾ�������ո�
                q=p;
                do{
                    *q=*(q+1);
                    q++;
                }while(*q!='\0');
            }
        }
        p++;
    }
    *p++='#';
    *p='\0';
}

const char *getOpnd(const char *c,opndElem *op){
    //�����*c��ʼ�Ĳ����������غ�cΪ������
    int sum=0,tmp;
    while(FALSE==Isoperator(*c)){//��c���ǲ�����
        tmp=*c-'0';
        sum=sum*10+tmp;
        //printf("tmp=%d\n",tmp);
        c++;
    }
    *op=sum;
    //printf("getOpnd:%d\n",*op);
    return c;
}

Status Isoperator(char c){
    //�ж�c�Ƿ���һ�����������
    switch(c){
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '#':
            return TRUE;
            break;
        default:
            return FALSE;
            break;
    }
}

char Precede(char op1,char op2){
    //�ж�op1��op2���ȼ��ĸߵͣ�����'>','<','='
    switch(op1){
        case '+':
            switch(op2){
                case '*':
                case '/':
                case '(':
                       return '<';
                       break;
                default:
                    return '>';
                    break;
            }
            break;
        case '-':
            switch(op2){
                case '*':
                case '/':
                case '(':
                       return '<';
                       break;
                default:
                    return '>';
                    break;
            }
            break;
        case '*':
            switch(op2){
                case '(':
                       return '<';
                       break;
                default:
                    return '>';
                    break;
            }
            break;
        case '/':
            switch(op2){
                case '(':
                       return '<';
                       break;
                default:
                    return '>';
                    break;
            }
            break;
        case '(':
            switch(op2){
                case ')':
                    return '=';
                    break;
                default:
                    return '<';
                    break;
            }
            break;
        case ')':
            switch(op2){
                default:
                    return '>';
                    break;
            }
            break;
        case '#':
            switch(op2){
                case '#':
                    return '=';
                    break;
                default:
                    return '<';
                    break;
            }
            break;
        default:
            return '<';
            break;
    }
}

opndElem operate(opndElem a,optrElem theta,opndElem b){
    //�Բ�����a��b����theta���㣬������������
    //thetaֻ���������������
    int rs_i;
    switch(theta){
        case '+':
            rs_i=a+b;
            break;
        case '-':
            rs_i=a-b;
            break;
        case '*':
            rs_i=a*b;
            break;
        case '/':
            if(b==0){
                printf("errror:����Ϊ0.");
                exit(0);
            }
            rs_i=a/b;
            break;
        default:
            printf("Is not a operator.\n");
            break;
    }
    printf("%d %c %d = %d\n",a,theta,b,rs_i);
    return rs_i;
}
