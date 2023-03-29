#ifndef __PID_H
#define __PID_H
#include "SWM181.h"

extern double TEMP;						//储存到小数一位的实际实时温度

extern int SETTIME;       //设置时间

extern int stage1;
extern int stage2;
extern int stage3;
extern struct PID pid;

struct PID{
	signed int Set;				//设定值
	float Actual;			//实际值
	float err;				//当前误差
	float err_last;		//上一次误差
	
	float Kp,Ki,Kd,Kout;
	float voltage;			//计算值
	float integral;		//误差积分值
	
	/*增量式pid偏差*/
	float err_02, err_03;
};

void PID_Init(void);  //PID初始化
int PID_realize(void);  //PID控制算法

#endif

