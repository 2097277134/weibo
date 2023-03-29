#ifndef __SEND_H__
#define __SEND_H__
#include "SWM181.h"
#include "mylib.h"

extern u8 SENDE_0[8];
extern u8 SENDE_100[8];
extern u8 SENDE_200[8];
/*数字量控制*/
//void uart_1T2(void);  //屏幕到单片机显示函数 	
//void uart_2T1(void);  //屏幕到单片机显示函数



void uart_1(void);
//void uart_2(void);

void MCU_t_screen(void);  //向电容屏发送数据
//void MCU_r_screen(void);  //接收电容屏数据

void select(void);  //选取功率函数

void send_100(void);  //固定功率300W字符串
void send_0(void);  //固定功率0W字符串
void send_200(void);  //固定功率0W字符串

#endif //__SEND_H__
