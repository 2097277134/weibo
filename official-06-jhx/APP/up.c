#include "SWM181.h"
#include "mylib.h"
#include "IO.h"

//////////////////////////////////////////////////
//设置升温函数，管理磁控管功率
///////////////////////////////////////////////////

extern double TEMP;						//储存实际实时温度
extern int flag_up_s;      //升温计时开始标志位

extern int SETTIME;

extern struct PID pid;

/*设置值：运行功率、运行时长、周期、占空比*/



int SETTIME;  //设置升温时间为CapacitiveScreen.time-2min

int upinitflag=0;					//UPinit初始化中断标志
int upintnubflag=0;				//UPinit初始化持续时间





void up_init(void)
{
	if(upinitflag>=1000&&upintnubflag<=6){  //初始化6s时间
		upinitflag=0;
		send_100();  //固定功率150W左右开启
		upintnubflag++;
		pid.voltage=0;//磁控管初始化之后需要执行一次
		CapacitiveScreen.time--;
	}
}

void up(void)
{
	
	up_init();	//磁控管预热6s
	if(upintnubflag>6){
	flag_up_s=1;
   
	select();  //固定功率字符串
		if(upflag>1000)
		{
			upflag=0;
				select();  //固定功率字符串
				uart_1();
			CapacitiveScreen.time--;
	}
				//初始化6秒标志位
	
	
}
	
}

