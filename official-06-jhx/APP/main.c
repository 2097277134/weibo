#include "SWM181.h"
#include "mylib.h"
#include <string.h>

	
int main(void)
{
	
	SystemInit();
//	uart1_init();  //串口1初始化
	uart2_init();  //串口2初始化 用于和电源通信
  IO_Init();     //IO初始化
	//up_init();
	DRIVER_Init();  //电机驱动初始化
  adc_Init();    //测温adc初始化
	PID_Init();    //升温PID
	TIMR_Init(TIMR0, TIMR_MODE_TIMER, SystemCoreClock/1000, 1); //每0.001秒钟触发一次中断
  IRQ_Connect(IRQ0_15_TIMR0, IRQ5_IRQ, 3);  //定时器0中断链接到IRQ5中断线，低优先级
	TIMR_Init(TIMR1,TIMR_MODE_TIMER,SystemCoreClock/1000,1);
	IRQ_Connect(IRQ0_15_TIMR1, IRQ4_IRQ, 2);  //定时器1中断链接到IRQ5中断线，高优先级
	TIMR_Start(TIMR1);    //定时器1开始工作
	
	EN_ON;
//	F_ON;
	while(1)
	{
		if(taskflag[0]==taskflag[1]){   //taskflag[2]={0,100}，定时100ms
		taskflag[0]=0;
		task();
		}	
		if(sendflag[0]>=sendflag[1]){   //sendflag[2]={0,200}，定时200ms
			sendflag[0]=0;
			MCU_t_screen();               //传输一次温度数据
		}

		
		if(flag1)  //收到微波电源的消息
		{
			flag1=0;
			judge1();
		}
		
		if(flag2&&time!=0)  //收到电容屏的消息&运行总时长不为0
		{
			flag2=0;          //清除电容屏接收标志位
			judge2();         //进行解包得到需要的消息
			up();             //进入消融程序
		}
		else
		{	
			if(upflag%500==0)  //未收到电容屏设置的时间，则0.5s发送一次功率0w设置
				send_0();  //发送固定功率0W字符串
		}

	for(int i=0;i>=200;i++){
	HZ_OFF;
		F_OFF;
	delay_ms(100);
	HZ_ON;
		F_ON;
	delay_ms(100);
	}
	}
	//111222333
}






