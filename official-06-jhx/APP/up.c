#include "SWM181.h"
#include "mylib.h"
#include "IO.h"

//////////////////////////////////////////////////
//设置升温函数，管理磁控管功率
///////////////////////////////////////////////////

extern double TEMP;						//储存实际实时温度
extern int flag_up_s;      //升温计时开始标志位

//extern int flag_200ms;
extern int SETTIME;
extern int remain_time;

extern struct PID pid;

/*设置值：运行功率、运行时长、周期、占空比*/

int time=600;  //运行总时长数(秒)
int SETTEMP=45;  //设置温度
int SETTIME=3*60;  //设置升温时间为3分钟
int remain_time;   //剩余时间
int upinitflag=0;					//UPinit初始化中断标志
int upintnubflag=0;				//UPinit初始化持续时间





void up_init(void)
{
	if(upinitflag>=1000&&upintnubflag<=6){  //初始化6s时间
		upinitflag=0;
		send_100();  //固定功率150W左右开启
		upintnubflag++;
		pid.voltage=0;//磁控管初始化之后需要执行一次
	}
}

void up(void)
{
	
	up_init();	//磁控管预热6s
	if(upintnubflag>6){
	flag_up_s=1;
	flag_200ms=0;   
	remain_time=SETTIME;
		if(upflag>1000)
		{
			upflag=0;
				select();  //固定功率字符串
				uart_1();
	}
	if(CapacitiveScreen.MicrowaveSwitch==0x00||CapacitiveScreen.time==0x00){
	upintnubflag=0;					//初始化6秒标志位
	
	}
}
}

