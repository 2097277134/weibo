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
int upflag=0;		//t1时间段中断标志位1000ms
uint8_t SEND_Microwave_OFF[8]={0x5A,0xA5,0x05,0x82,0x10,0x06,0x00,0x00}; //向电容屏发送微波关闭
//IRQ4_Handler
void IRQ4_Handler(void){   //每1ms开启一次中断
  TIMR_INTClr(TIMR1);      //清除TIMR1中断标志位
	taskflag[0]++;           
	upinitflag++;            //upinit初始化中断标志位
	upflag++;                //up中断标志位

}
void task(void)    //建议写入长期运行的主要程序
{
		 
		if(CapacitiveScreen.WaterPumpSwitch==0x01){
			DirverEnable
		DRIVER_Start();
		}
		else{
		DRIVER_Stop();
		CapacitiveScreen.MicrowaveSwitch=0x00;
		USART_SendData(UART2,SEND_Microwave_OFF,8);
		
		
		}
		TEMP=Get_Adc_Average(2);
		MCU_t_screen();               //传输一次温度数据		
		//超温报警，旁温>90;杆温>50
		if(TEMP>90 || TEMP_2>50)
		{
			bee_on;
		}
		else
			bee_off;
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

