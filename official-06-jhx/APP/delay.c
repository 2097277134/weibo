#include "SWM181.h"
#include "mylib.h"

uint8_t Flag_Systick = 0;
void IRQ5_Handler(void)
{
	TIMR_INTClr(TIMR0);  //清除中断标志位
	Flag_Systick = 1;
	MCU_t_screen();               //传输一次温度数据	
}

void delay_ms(uint16_t ms)
{
	TIMR_Start(TIMR0);  //启动定时器，从初始值开始计时/计数
  while(ms)
  {
	  while(Flag_Systick)
	  {
		  ms--;
		  Flag_Systick = 0;
	  }
  }
	TIMR_Stop(TIMR0);
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
