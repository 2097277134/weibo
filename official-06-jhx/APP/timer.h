#ifndef __TIMER_H__
#define __TIMER_H__
#include "SWM181.h"

//void delay_us(int us);
//void delay_ms(int ms);
//void delay_s(int s);

extern int flag_0w;       //允许发送0w标志位
extern int flag_up_s;
void task(void);
extern int taskflag;
extern int sendflag[2];
#endif //__TIMER_H__
