#ifndef __JUDGE_H__
#define __JUDGE_H__
#include "SWM181.h"

extern	u8 Res3_1;  //功率数据
extern	u8 Res4_1;  //时间数据
extern	u8 Res5_1;  //温度数据

extern	u8 Res2_2;  //命令数据
extern	u8 Res3_2;  //功率数据
extern	u8 Res4_2;  //时间数据
extern	u8 Res5_2;  //温度数据

void judge1(void);  //判断电阻屏控制信号的控制对象	
void judge2(void);  //判断微波电源控制信号的控制对象	
void extract(void);  //判断微波电源控制信号的控制对象	

#endif //__JUDGE_H__
