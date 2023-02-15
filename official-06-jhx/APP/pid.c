#include "SWM181.h"
#include "pid.h"

struct PID pid;

//extern double TEMP;						//���浽С��һλ��ʵ��ʵʱ�¶�
extern int SETTEMP;				//���浽С��һλ��ʵ�������¶�
extern int SETTIME;       //����ʱ��
extern int remain_time;   //ʣ��ʱ��

void PID_Init(void)					//PID��ʼ��
{
	pid.Set=SETTEMP;  //�����¶�
	pid.Actual=TEMP;  //ʵ���¶�
	pid.err=0;        //���
	pid.err_last=0;   //��һ�����                                                                                                                                                                                            

	/*����ʽPID������ʼ��*/
	pid.err_02=0;        //���
	pid.err_03=0;        //���
	
	pid.Kp=0;						
	pid.Ki=0;						
	pid.Kd=0;					
//	pid.Kout=5;					//ƫ��ֵ
	pid.voltage=0;				//���������ѹ
	pid.integral=0;     	//�ۼ�ƫ�ƫ�����
	
}

////PID�㷨λ��ʽ 
//float PID_realize(void)
//{
//	float t;
//	
//	pid.Set      = SETTEMP;				//�趨ֵ 40
//	pid.Actual   = TEMP;					//ʵ��ֵ 20
//	pid.err      = pid.Set - pid.Actual;	//֮��
//	

//	pid.integral = pid.integral + pid.err;

//	pid.voltage = pid.Kp*pid.err								//�趨ֵ��ʵ�ʵ�ƫ��
//				+ pid.Ki*pid.integral									//��ʷ�ۼ�ƫ��
//				+ pid.Kd*(pid.err-pid.err_last)				//����ƫ�����ϴ�ƫ��Ƚ�
//				+ pid.Kout;														//���ռ���ֵ
//	
//	pid.err_last = pid.err;
//	
//	t=pid.voltage;
//	
//	LCD_ShowString(30,110,80,24,24,"davol:");  // ��ʾռ�ձȣ�С����
//	LCD_ShowxNum(30+80,110,pid.voltage,4,24,0);
//	LCD_ShowString(30+80+12*4,110,1,1,24,".");
//	LCD_ShowxNum(30+80+12*5,110,pid.voltage*1000,3,24,0x80);	
//	
////	LCD_ShowNum(10,215,pid.voltage,4,24);
//	LCD_ShowxNum(30,215,pid.Set,4,24,0);
//	LCD_ShowxNum(30,250,pid.Actual,4,24,0);
//	
//	if(pid.integral>2000)		pid.integral=2000;			//�����޷�
//	else if(pid.integral<-2000)	pid.integral=-2000;
//	
////	if(t>400)		t=400;       //����޷�-������ֵΪ3.2V
////	else if(t<209)	t=209;

//	if(t>250)		t=250;       //����޷�-������ֵΪ3.2V
//	else if(t<209)	t=209;

//	return t*10;
//}

//PID�㷨����ʽ 
int PID_realize(void)
{
	static int flag_T=1;
	int t;
	static double TEMP1=0;
	static double TEMP2=0;
	if(flag_T)
	{
		TEMP1=TEMP+(SETTEMP-TEMP)*0.6;   //һ�׶��¶�Ŀ��ֵ
		TEMP2=TEMP+(SETTEMP-TEMP)*0.8;   //���׶��¶�Ŀ��ֵ
		flag_T=0;
	}

	if(remain_time>=0.5*SETTIME)    //ǰ���ʱ�䵽һ�׶��¶�ֵ
	{
		pid.Kp=25;						
		pid.Ki=0.8;						
		pid.Kd=1;			
		pid.Set = TEMP1;				//һ�׶��¶�Ŀ��ֵ
	}
	
	if(0.5*SETTIME>remain_time && remain_time>=0.2*SETTIME)   //0.5~0.8����ʱ�䵽����׶�Ŀ��ֵ
	{
		pid.Kp=17;						
		pid.Ki=0.5;						
		pid.Kd=0.5;			
		pid.Set = TEMP2;				//���׶��¶�Ŀ��ֵ
	}
	
	if(0.2*SETTIME>remain_time)    //��� 0.8~����ʱ�� ����������¶�
	{
		pid.Kp=23;						
		pid.Ki=1;						
		pid.Kd=0.1;	
		pid.Set = SETTEMP;				//����¶�ֵ
	}
	
	
	pid.Actual   = TEMP;					//ʵ��ֵ 
	pid.err      = pid.Set - pid.Actual;	//֮��
	
	pid.voltage += pid.Kp*(pid.err-	pid.err_02)							//�趨ֵ��ʵ�ʵ�ƫ��
				+ pid.Ki*pid.err																	//��ʷ�ۼ�ƫ��
				+ pid.Kd*(pid.err-2*pid.err_02 + pid.err_03);			//����ƫ�����ϴ�ƫ��Ƚ�;

	pid.err_03 = pid.err_02;
	pid.err_02 = pid.err;
	
	if(pid.voltage>290)		pid.voltage=290;       //����޷�
	else if(pid.voltage<130)	pid.voltage=130;
	
	t=pid.voltage;

	return t;
}


