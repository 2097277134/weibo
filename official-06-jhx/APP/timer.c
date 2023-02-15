#include "mylib.h"
#include "measure.h"
int flag_200ms=0;    //一秒标志位
int flag_0w=1;       //允许发送0w标志位
extern int flag_up_s;//升温计时
extern double TEMP;						//储存旁温实时温度
extern double TEMP_2;					//储存杆温实时温度
extern int flag_up_s;         //升温计时
extern int SETTIME;           //设定时间
extern int remain_time;

double TEMP_2=0;
int flag_up_s=0;
int taskflag[2]={0,100};      //task标志位
int ADCflag[2]={0,100};			//ADC标志位
int sendflag[2]={0,200};		//电容屏发送标志位
int upflag=0;		//t1时间段中断标志位1000ms
int t2flag=0;		//t2时间段中断标志位1000ms
//IRQ5_Handler
void IRQ4_Handler(void){   //每1ms开启一次中断
  TIMR_INTClr(TIMR1);      //清除TIMR1中断标志位

	taskflag[0]++;           
	ADCflag[0]++;            
	sendflag[0]++;           
	upinitflag++;            //up初始化中断标志位
	upflag++;                //up中断标志位
	t2flag++;                //
}
void task(void)
{
	
		
		
		if(ADCflag[0]>=ADCflag[1]){
		ADCflag[0]=0;
		TEMP=adc_read();
//		TEMP_2=meas_6();	
		}
	
//		//测温循环
//		for(int i=1;i<=256;i++)
//		{
//			TEMP=meas_5();					 //旁温实时测温
//		}
//		
//		for(int i=1;i<=256;i++)
//		{
//			TEMP_2=meas_6();        //杆温实时测温
//		}
//		
//		MCU_t_screen();  //向串口三发送
		
		//初始时每一秒向电源发送0W指令一次
		if(flag_0w&&flag_200ms>=5)  
		{
			send_0();  //固定功率150W左右
			flag_200ms=0;
		}
		
		//每隔一秒设定时间减一
		if(flag_up_s&&flag_200ms>=5)
		{
			remain_time-=1;
			flag_200ms=0;
			if(remain_time==0) 
			{
				flag_up_s=0;
//				sys_reset();
			}
		}
		
		if(TEMP==SETTEMP-4)
		{
			ratio=1;  //占空比
			T1=1;  //PID调节周期时长时长数(秒)
		}
		
		//超温报警，旁温>90;杆温>50
//		if(TEMP>90 || TEMP_2>50)
//		{
//			BEEP=1;
//		}
//		else
//			BEEP=0;
		
		flag_200ms++;	
	}


//void delay_us(int us)
//{
//  int i;
//  int j = 10*us;
//    for(i = 0;i<j;i++);
//}
//void delay_ms(int ms)
//{
//  int i,k;
//  for(k = ms; k  >  0; k--)
//  {
//    for(i = 0;i < 4000; i++);
//  }
//}
//void delay_s(int s)
//{
//  int i;
//  for(i = 0;i<s;i++)
//  {
//    delay_ms(1000);
//  }
//}

