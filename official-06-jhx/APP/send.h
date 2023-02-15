#ifndef __SEND_H__
#define __SEND_H__
#include "SWM181.h"
#include "mylib.h"

extern u8 SENDE_0[8];
extern u8 SENDE_100[8];
extern u8 SENDE_200[8];
/*����������*/
//void uart_1T2(void);  //��Ļ����Ƭ����ʾ���� 	
//void uart_2T1(void);  //��Ļ����Ƭ����ʾ����



void uart_1(void);
//void uart_2(void);

void MCU_t_screen(void);  //���������������
//void MCU_r_screen(void);  //���յ���������

void select(void);  //ѡȡ���ʺ���

void send_100(void);  //�̶�����300W�ַ���
void send_0(void);  //�̶�����0W�ַ���
void send_200(void);  //�̶�����0W�ַ���

#endif //__SEND_H__
