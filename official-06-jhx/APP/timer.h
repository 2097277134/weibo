#ifndef __TIMER_H__
#define __TIMER_H__
#include "SWM181.h"

//void delay_us(int us);
//void delay_ms(int ms);
//void delay_s(int s);
extern int flag_200ms;    //һ���־λ
extern int flag_0w;       //������0w��־λ
extern int flag_up_s;
void task(void);
extern int taskflag[2];
extern int sendflag[2];
#endif //__TIMER_H__
