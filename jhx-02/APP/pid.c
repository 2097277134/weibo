#include "SWM181.h"
#include "pid.h"
#include "mylib.h"
struct PID pid;

//extern double TEMP;						//储存到小数一位的实际实时温度

int stage1=1;
int stage2=1;
int stage3=1;

void PID_Init(void)					//PID初始化
{
	pid.Set=CapacitiveScreen.temperature;  //设置温度
	pid.Actual=TEMP;  //实际温度
	pid.err=0;        //误差
	pid.err_last=0;   //上一次误差                                                                                                                                                                                            

	/*增量式PID参数初始化*/
	pid.err_02=0;        //误差
	pid.err_03=0;        //误差
	
	pid.Kp=0;						
	pid.Ki=0;						
	pid.Kd=0;					
//	pid.Kout=5;					//偏移值
	pid.voltage=0;				//计算输出电压
	pid.integral=0;     	//累计偏差，偏差积分
	
}

////PID算法位置式 
//float PID_realize(void)
//{
//	float t;
//	
//	pid.Set      = SETTEMP;				//设定值 40
//	pid.Actual   = TEMP;					//实际值 20
//	pid.err      = pid.Set - pid.Actual;	//之差
//	

//	pid.integral = pid.integral + pid.err;

//	pid.voltage = pid.Kp*pid.err								//设定值与实际的偏差
//				+ pid.Ki*pid.integral									//历史累计偏差
//				+ pid.Kd*(pid.err-pid.err_last)				//本次偏差与上次偏差比较
//				+ pid.Kout;														//最终计算值
//	
//	pid.err_last = pid.err;
//	
//	t=pid.voltage;
//	
//	LCD_ShowString(30,110,80,24,24,"davol:");  // 显示占空比（小数）
//	LCD_ShowxNum(30+80,110,pid.voltage,4,24,0);
//	LCD_ShowString(30+80+12*4,110,1,1,24,".");
//	LCD_ShowxNum(30+80+12*5,110,pid.voltage*1000,3,24,0x80);	
//	
////	LCD_ShowNum(10,215,pid.voltage,4,24);
//	LCD_ShowxNum(30,215,pid.Set,4,24,0);
//	LCD_ShowxNum(30,250,pid.Actual,4,24,0);
//	
//	if(pid.integral>2000)		pid.integral=2000;			//积分限幅
//	else if(pid.integral<-2000)	pid.integral=-2000;
//	
////	if(t>400)		t=400;       //输出限幅-输出最大值为3.2V
////	else if(t<209)	t=209;

//	if(t>250)		t=250;       //输出限幅-输出最大值为3.2V
//	else if(t<209)	t=209;

//	return t*10;
//}

//PID算法增量式 
int PID_realize(void)
{
	static int flag_T=1;
	int t;
	static double TEMP1=0;
	static double TEMP2=0;
	if(flag_T)
	{	
		TEMP1=TEMP/10+(CapacitiveScreen.temperature-TEMP/10)*0.6;   //一阶段温度目标值
		TEMP2=TEMP/10+(CapacitiveScreen.temperature-TEMP/10)*0.8;   //二阶段温度目标值
		flag_T=0;
	}

	if(CapacitiveScreen.time-120>=0.5*SETTIME&&stage3)    //前半段时间到一阶段温度值
	{PID_Init();
		stage3=0;
		pid.Kp=70;						
		pid.Ki=0.001;						
		pid.Kd=2;			
		pid.Set = TEMP1;				//一阶段温度目标值
	}
	
	if(0.5*SETTIME>CapacitiveScreen.time-120 && CapacitiveScreen.time-120>=0.2*SETTIME&&stage1)   //0.5~0.8倍总时间到达二阶段目标值
	{
		PID_Init();
		pid.Kp=70;						
		pid.Ki=0.002;						
		pid.Kd=2;			
		stage1=0;
		pid.Set = TEMP2;				//二阶段温度目标值
	}
	
	if(0.2*SETTIME>CapacitiveScreen.time-120&&stage2)    //最后 0.8~最终时间 上升到最后温度
	{
		PID_Init();
		pid.Kp=80;						
		pid.Ki=0.001;						
		pid.Kd=2;	
		stage2=0;
		pid.Set = CapacitiveScreen.temperature;				//最后温度值
	}
	
	
	pid.Actual   = TEMP/10;					//实际值 
	pid.err      = pid.Set - pid.Actual;	//之差
	
	pid.voltage += pid.Kp*(pid.err-	pid.err_02)							//设定值与实际的偏差
				+ pid.Ki*pid.err																	//历史累计偏差
				+ pid.Kd*(pid.err-2*pid.err_02 + pid.err_03);			//本次偏差与上次偏差比较;

	pid.err_03 = pid.err_02;
	pid.err_02 = pid.err;
		t=pid.voltage;
	if(t>220)		t=220;       //输出限幅
	else if(t<100)	t=100;
	


	return t;
}


