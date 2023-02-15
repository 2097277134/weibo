#ifndef __UP_H
#define __UP_H
#include "SWM181.h"
#include "mylib.h"

extern int power;
extern int time;
extern int T1;
extern int SETTEMP;    //设定时间
extern int T;  //运行整数周期数
extern int upinitflag;
extern int upflag;	//t1时间段中断标志位1000ms
extern int t2flag;  //t2时间段中断标志位1000ms
void up_init(void);  //判断控制信号的控制对象
void up(void);  //判断控制信号的控制对象

#endif
