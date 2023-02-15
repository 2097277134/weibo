#include "SWM181.h"
#include "mylib.h"
#include "IO.h"

//////////////////////////////////////////////////
//设置升温函数，管理磁控管功率以及通断
///////////////////////////////////////////////////

extern double TEMP;						//储存实际实时温度
extern double ratio;
extern int flag_up_s;      //升温计时开始标志位

//extern int flag_200ms;
extern int SETTIME;
extern int remain_time;

extern struct PID pid;

/*设置值：运行功率、运行时长、周期、占空比*/
double ratio=0.6;  //占空比
int time=600;  //运行总时长数(秒)
int T1=20;  //PID调节周期时长时长数(秒)
int SETTEMP=45;  //设置温度
int SETTIME=3*60;  //设置升温时间为3分钟
int remain_time;   //剩余时间
int upinitflag=0;					//UP初始化中断标志
int upintnubflag=0;
/*程序计算值*/
/*运行时间T*T1+alone秒*/
int T=0;  //运行整数周期数
int alone=0;  //m秒单独运行
float t1;  //高电平时间
float t2;  //低电平时间

void up_init(void)
{
	if(upinitflag==1000&&upintnubflag<=6){
		send_100();  //固定功率150W左右开启
		upintnubflag++;
	}
	else{
	
	select();  //使误差一不为0
	}
 	
}

void up(void)
{
	
	up_init();	//磁控管预热6s
	if(upintnubflag>6){
	alone=time%T1;  //取剩余时间
	flag_up_s=1;
	flag_200ms=0;   
	remain_time=SETTIME;
	
//	select();  ////使误差二不为0
	/*完整周期T运行*/
T=time/T1;  //取完整周期个数
		if(T!=0){
		pid.voltage=0;
		t1=T1*ratio;  //高电平时间转换为ms
		t2=T1*(1-ratio);  //低电平时间转换为ms
		if(upflag>1000)
		{
			upflag=0;
				select();  //固定功率字符串
				uart_1();
		T-=1;
	}
	

	if(T==0)
	{
		if(alone!=0)
		{
			alone=(time%T1)*1000;  //转换为毫秒
			select();  //固定功率W字符串

			delay_ms(alone);
			send_0();  //固定功率0W字符串
		}
		else
		{
			send_0();  //固定功率0W字符串
		}
	}
}
}
}
