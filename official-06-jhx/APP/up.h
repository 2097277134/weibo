#ifndef __UP_H
#define __UP_H
#include "SWM181.h"
#include "mylib.h"

extern int power;
extern int time;
extern int T1;
extern int SETTEMP;    //�趨ʱ��
extern int T;  //��������������
extern int upinitflag;
extern int upflag;	//t1ʱ����жϱ�־λ1000ms
extern int t2flag;  //t2ʱ����жϱ�־λ1000ms
void up_init(void);  //�жϿ����źŵĿ��ƶ���
void up(void);  //�жϿ����źŵĿ��ƶ���

#endif
