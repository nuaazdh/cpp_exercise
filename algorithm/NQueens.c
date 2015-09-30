/**
N�ʺ����⣬���ݷ����
������ε�������ݽṹ�����㷨���ж������Ƿ���Ч���㷨Ч���д��Ľ�
���ߣ�nuaazdh
ʱ�䣺2012��6��3��
*/
#include <stdio.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

#define SCALE   8   // ����Ľ�����8Ϊ�˻ʺ�����

typedef int Status; // ��������״ֵ̬
typedef int BOOL;	// booleanֵ
typedef char ElemType;// �洢��������

typedef struct TreeNode{
	struct TreeNode *child;   //����
	ElemType solution[SCALE][SCALE];
	struct TreeNode *brother;
}TreeNode,* Tree;

char chessboard[SCALE][SCALE];	// ȫ�ֱ��������̣���������Ϊ' '������Ϊ'#'

int count=0;	// ȫ�ֱ�������¼���ܽ������

void Trial(int i);
	// ���뱾����ʱ����SCALE��SCALE����ǰ��i-1���ѷ����˻���������i-1������
	// �ִӵ�i�������Ϊ��������ѡ����ʵ�λ��
	// ��i>nʱ�����һ���Ϸ����֣����֮
Status PlaceChess(int i,int j);
	// �ڵ�i�У���j�з���һ������
Status RemoveChess(int i,int j);
	// ���ߵ�i�У���j�е�����
void PrintBoard();
	// �����ǰ���̵Ĳ���
BOOL IsValidLayout();
	// ���鵱ǰ�����Ƿ�Ϊ�Ϸ�����

int main(){
	int i,j;
	for(i=0;i<SCALE;i++){
		for(j=0;j<SCALE;j++)
			chessboard[i][j]='#';
	}
	Trial(0);
	printf("Total number of valid layout is %d.\n\n",count);
	return 0;
}

void Trial(int i){
	// ���뱾����ʱ����SCALE��SCALE����ǰ��i-1���ѷ����˻���������i-1������
	// �ִӵ�i�������Ϊ��������ѡ����ʵ�λ��
	// ��i>nʱ�����һ���Ϸ����֣����֮
	int j;
	if(i>=SCALE){
		printf("No. %d\n",count);
		PrintBoard();
		count++;
	}
	else for(j=0;j<SCALE;j++){
		PlaceChess(i,j);
		if(TRUE==IsValidLayout())
			Trial(i+1);
		RemoveChess(i,j);
	}
}

Status PlaceChess(int i,int j){
	// �ڵ�i�У���j�з���һ������
	if(i>=SCALE || j>=SCALE)
		return FALSE;
	if(chessboard[i][j]==' ')
		return FALSE;
	else
		chessboard[i][j]=' ';
	return TRUE;
}

Status RemoveChess(int i,int j){
	// ���ߵ�i�У���j�е�����
	if(i>=SCALE || j>=SCALE)
		return FALSE;
	if(chessboard[i][j]=='#')
		return FALSE;
	else
		chessboard[i][j]='#';
	return TRUE;

}

void PrintBoard(){
	// �����ǰ���̵Ĳ���
	int i,j;
	for(i=0;i<SCALE;i++){
		for(j=0;j<SCALE;j++){
			printf("%c",chessboard[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

BOOL IsValidLayout(){
	// ���鵱ǰ�����Ƿ�Ϊ�Ϸ�����
	int i,j,k,sum;
	// �������Ƿ�Ϸ�
	for (i=0;i<SCALE;i++){//�к�
		sum=0;
		for (j=0;j<SCALE;j++){//�����
			if(chessboard[j][i]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
		sum=0;
		for (j=0;j<SCALE;j++){//�����
			if(chessboard[i][j]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
		sum=0;
		for(k=i,j=0;k<SCALE;j++,k++){//�������ǶԽ���
			if(chessboard[j][k]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
		sum=0;
		for(j=i,k=0;j<SCALE;j++,k++){//�������ǶԽ���
			if(chessboard[j][k]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
		sum=0;
		for(j=0,k=i;k>=0;j++,k--){//�������ǶԽ���
			if(chessboard[j][k]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
		sum=0;
		for(j=SCALE-1,k=i;k<SCALE;j--,k++){//�������ǶԽ���
			if(chessboard[j][k]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
	}
	return TRUE;
}
