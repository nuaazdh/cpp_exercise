//利用系统55ms中断计时
//作者：nuaazdh
//时间：2011年11月30日

#include <stdio.h>
#include <dos.h>
#include <bios.h>
#include <ctype.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

unsigned long count=0;//每55ms中断，count+1
int hour=0,minute=0,second=0,millisecond=0;//时间
struct time t;

void interrupt get();
void interrupt (*old)();

void interrupt get()
{
	count+=1;
}

//根据count值，获得时间
Clock()
{
	millisecond=(count*55)%1000;
	second=(count*55/1000)%60;
	minute=(count*55/60000%60)%60;
	hour=(count*55/3600000%24)%24;
}

//显示时间和中断发生次数
PrintClock()
{
	clrscr();
	printf("\n\n\n\n");
	      printf("\n\n\t\tThe beginning time: %02d:%02d:%02d\n",t.ti_hour,t.ti_min,t.ti_sec);
	printf("\n\n\t\tThe current time is\n\n");
	printf("\n\t\t%-3d: %-3d: %-3d: %-4d\n\n\n\n\n",hour,minute,second);
	printf("\t\tPress esc to exit!");
}

//获取用户按键，监测到Esc退出
End()
{
	long key;

	while(bioskey(1)!=0)
	{
		key=bioskey(0);
		key=key&0x00FF;
		if(key==27)
		{
			setvect(0x1C,old);
			exit(0);
		}
	}
}

void main()
{
	clrscr();//清屏
	old=getvect(0x1C);//获取中断向量
	setvect(0x1C,get);//设置中断向量
	gettime(&t);//获取时间
	while(1)
	{
		Clock();
		PrintClock();//显示时间
		sleep(1);
		End();
	}

}
