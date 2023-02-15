#ifndef __PID_H
#define __PID_H
#include "SWM181.h"

extern double TEMP;						//���浽С��һλ��ʵ��ʵʱ�¶�
extern int SETTEMP;				//���浽С��һλ��ʵ�������¶�
extern int SETTIME;       //����ʱ��
extern int remain_time;   //ʣ��ʱ��

extern struct PID pid;

struct PID{
	signed int Set;				//�趨ֵ
	float Actual;			//ʵ��ֵ
	float err;				//��ǰ���
	float err_last;		//��һ�����
	
	float Kp,Ki,Kd,Kout;
	float voltage;			//����ֵ
	float integral;		//������ֵ
	
	/*����ʽpidƫ��*/
	float err_02, err_03;
};

void PID_Init(void);  //PID��ʼ��
int PID_realize(void);  //PID�����㷨

#endif
