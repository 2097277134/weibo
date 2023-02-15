#include "SWM181.h"
#include "mylib.h"
#include "IO.h"

//////////////////////////////////////////////////
//�������º���������ſعܹ����Լ�ͨ��
///////////////////////////////////////////////////

extern double TEMP;						//����ʵ��ʵʱ�¶�
extern double ratio;
extern int flag_up_s;      //���¼�ʱ��ʼ��־λ

//extern int flag_200ms;
extern int SETTIME;
extern int remain_time;

extern struct PID pid;

/*����ֵ�����й��ʡ�����ʱ�������ڡ�ռ�ձ�*/
double ratio=0.6;  //ռ�ձ�
int time=600;  //������ʱ����(��)
int T1=20;  //PID��������ʱ��ʱ����(��)
int SETTEMP=45;  //�����¶�
int SETTIME=3*60;  //��������ʱ��Ϊ3����
int remain_time;   //ʣ��ʱ��
int upinitflag=0;					//UP��ʼ���жϱ�־
int upintnubflag=0;
/*�������ֵ*/
/*����ʱ��T*T1+alone��*/
int T=0;  //��������������
int alone=0;  //m�뵥������
float t1;  //�ߵ�ƽʱ��
float t2;  //�͵�ƽʱ��

void up_init(void)
{
	if(upinitflag==1000&&upintnubflag<=6){
		send_100();  //�̶�����150W���ҿ���
		upintnubflag++;
	}
	else{
	
	select();  //ʹ���һ��Ϊ0
	}
 	
}

void up(void)
{
	
	up_init();	//�ſع�Ԥ��6s
	if(upintnubflag>6){
	alone=time%T1;  //ȡʣ��ʱ��
	flag_up_s=1;
	flag_200ms=0;   
	remain_time=SETTIME;
	
//	select();  ////ʹ������Ϊ0
	/*��������T����*/
T=time/T1;  //ȡ�������ڸ���
		if(T!=0){
		pid.voltage=0;
		t1=T1*ratio;  //�ߵ�ƽʱ��ת��Ϊms
		t2=T1*(1-ratio);  //�͵�ƽʱ��ת��Ϊms
		if(upflag>1000)
		{
			upflag=0;
				select();  //�̶������ַ���
				uart_1();
		T-=1;
	}
	

	if(T==0)
	{
		if(alone!=0)
		{
			alone=(time%T1)*1000;  //ת��Ϊ����
			select();  //�̶�����W�ַ���

			delay_ms(alone);
			send_0();  //�̶�����0W�ַ���
		}
		else
		{
			send_0();  //�̶�����0W�ַ���
		}
	}
}
}
}
