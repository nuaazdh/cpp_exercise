/**
N皇后问题，回溯法求解
采用严蔚敏《数据结构》的算法，判断棋盘是否有效的算法效率有待改进
作者：nuaazdh
时间：2012年6月3日
*/
#include <stdio.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

#define SCALE   8   // 问题的阶数，8为八皇后问题

typedef int Status; // 函数返回状态值
typedef int BOOL;	// boolean值
typedef char ElemType;// 存储数据类型

typedef struct TreeNode{
	struct TreeNode *child;   //字数
	ElemType solution[SCALE][SCALE];
	struct TreeNode *brother;
}TreeNode,* Tree;

char chessboard[SCALE][SCALE];	// 全局变量，棋盘，放置棋子为' '，否则为'#'

int count=0;	// 全局变量，记录可能结果个数

void Trial(int i);
	// 进入本函数时，在SCALE×SCALE棋盘前的i-1行已放置了互不攻击的i-1个棋子
	// 现从第i行起继续为后续棋子选择合适的位置
	// 当i>n时，秋的一个合法布局，输出之
Status PlaceChess(int i,int j);
	// 在第i行，第j列放置一个棋子
Status RemoveChess(int i,int j);
	// 移走第i行，第j列的棋子
void PrintBoard();
	// 输出当前棋盘的布局
BOOL IsValidLayout();
	// 检验当前棋盘是否为合法布局

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
	// 进入本函数时，在SCALE×SCALE棋盘前的i-1行已放置了互不攻击的i-1个棋子
	// 现从第i行起继续为后续棋子选择合适的位置
	// 当i>n时，秋的一个合法布局，输出之
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
	// 在第i行，第j列放置一个棋子
	if(i>=SCALE || j>=SCALE)
		return FALSE;
	if(chessboard[i][j]==' ')
		return FALSE;
	else
		chessboard[i][j]=' ';
	return TRUE;
}

Status RemoveChess(int i,int j){
	// 移走第i行，第j列的棋子
	if(i>=SCALE || j>=SCALE)
		return FALSE;
	if(chessboard[i][j]=='#')
		return FALSE;
	else
		chessboard[i][j]='#';
	return TRUE;

}

void PrintBoard(){
	// 输出当前棋盘的布局
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
	// 检验当前棋盘是否为合法布局
	int i,j,k,sum;
	// 检验行是否合法
	for (i=0;i<SCALE;i++){//列号
		sum=0;
		for (j=0;j<SCALE;j++){//检测列
			if(chessboard[j][i]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
		sum=0;
		for (j=0;j<SCALE;j++){//检测行
			if(chessboard[i][j]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
		sum=0;
		for(k=i,j=0;k<SCALE;j++,k++){//右上三角对角线
			if(chessboard[j][k]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
		sum=0;
		for(j=i,k=0;j<SCALE;j++,k++){//右下三角对角线
			if(chessboard[j][k]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
		sum=0;
		for(j=0,k=i;k>=0;j++,k--){//左上三角对角线
			if(chessboard[j][k]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
		sum=0;
		for(j=SCALE-1,k=i;k<SCALE;j--,k++){//左下三角对角线
			if(chessboard[j][k]==' '){
				sum++;
			}
			if(sum>1)	return FALSE;
		}
	}
	return TRUE;
}
