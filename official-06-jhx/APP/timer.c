#include "mylib.h"
#include "measure.h"

int flag_0w=1;       //允许发送0w标志位
extern int flag_up_s;//升温计时
extern double TEMP;						//储存旁温实时温度
extern double TEMP_2;					//储存杆温实时温度
extern int flag_up_s;         //升温计时
extern int SETTIME;           //设定时间



int flag_up_s=0;
int taskflag=0;      //task标志位
int upflag=0;		//t1时间段中断标志位1000ms
uint8_t SEND_Microwave_OFF[8]={0x5A,0xA5,0x05,0x82,0x10,0x06,0x00,0x00}; //向电容屏发送微波关闭
//IRQ4_Handler
void IRQ4_Handler(void){   //每1ms开启一次中断
  TIMR_INTClr(TIMR1);      //清除TIMR1中断标志位
	taskflag++;           
	upinitflag++;            //upinit初始化中断标志位
	upflag++;                //up中断标志位
}
void task(void)    //建议写入长期运行的主要程序
{
		 
		if(CapacitiveScreen.WaterPumpSwitch==0x01){
			uint16_t hz,cyc;
			DirverEnable;
			hz=TEMP_2;
			if(TEMP_2>600){
			
			hz=600;
			}
			
			cyc=6000000/hz;
			PWM_SetCycle(PWM1,PWM_CH_B,cyc);     //6M/10000=600

			
		}
		else{
			DirverDisable;
		CapacitiveScreen.MicrowaveSwitch=0x00;
		}
		//超温报警，旁温>90;杆温>50
		if(TEMP>90 || TEMP_2>50)
		{
			LEDR_ON;
			bee_on;
		}
		else{
			LEDR_OFF;
			bee_off;
		}
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

