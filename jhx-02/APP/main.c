#include "SWM181.h"
#include "mylib.h"
#include <string.h>

//uint8_t SEND_BUF1[8]={0x5A,0xA5,0x05,0x82,0x10,0x08,0x10,0x11};


int main(void)
{
	
	SystemInit();  
	TIMR_Init(TIMR0, TIMR_MODE_TIMER, SystemCoreClock/10, 1); //每0.001秒钟触发一次中断
  IRQ_Connect(IRQ0_15_TIMR0, IRQ5_IRQ, 2);  //定时器0中断链接到IRQ5中断线，低优先级
	TIMR_Start(TIMR0);    //定时器1开始工作
	uart1_init();  //串口1初始化，微波电源通信
	uart2_init();  //串口2初始化 用于和电容屏通信
  IO_Init();     //IO初始化，开红灯
	DRIVER_Init();  //电机驱动初始化
  adc_Init();    //测温adc初始化
	PID_Init();    //升温PID
	
	TIMR_Init(TIMR1,TIMR_MODE_TIMER,SystemCoreClock/1000,1);
	IRQ_Connect(IRQ0_15_TIMR1, IRQ4_IRQ, 1);  //定时器1中断链接到IRQ5中断线，高优先级
	TIMR_Start(TIMR1);    //定时器1开始工作

	while(1)
	{
		task();     //此处为一直运行的程序
		if(flag1)  //收到微波电源的消息
		{
			flag1=0;
			judge1();  //电源故障报警
		}
		
		if(CapacitiveScreen.MicrowaveSwitch==0x01&&CapacitiveScreen.time!=0)  //收到电容屏消融按钮按下&运行总时长不为0
		{	
			LEDR_OFF;    //灭红灯
			LEDG_ON;     //开绿灯
			up();        //进入消融程序
		}
		else
		{	
			if(CapacitiveScreen.MicrowaveSwitch==0x00||CapacitiveScreen.time==0x00)  //电容屏不开启或者剩余时间为0
					upintnubflag=0;	   //UPinit初始化持续时间，为了防止中途按下微波关闭按钮然后再开启时没有微波初始化过程
			stage1=1;
			stage2=1;
			stage3=1;
			if(taskflag>=500){  //未收到电容屏设置的时间，则0.5s发送一次功率0w设置
				taskflag=0;
				send_0();  //发送固定功率0W字符串
		}
	}
}
}


