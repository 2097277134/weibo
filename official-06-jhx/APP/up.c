#include "SWM181.h"
#include "mylib.h"
#include "IO.h"

//////////////////////////////////////////////////
//�������º���������ſعܹ���
///////////////////////////////////////////////////

extern double TEMP;						//����ʵ��ʵʱ�¶�
extern int flag_up_s;      //���¼�ʱ��ʼ��־λ

//extern int flag_200ms;
extern int SETTIME;
extern int remain_time;

extern struct PID pid;

/*����ֵ�����й��ʡ�����ʱ�������ڡ�ռ�ձ�*/

int time=600;  //������ʱ����(��)
int SETTEMP=45;  //�����¶�
int SETTIME=3*60;  //��������ʱ��Ϊ3����
int remain_time;   //ʣ��ʱ��
int upinitflag=0;					//UPinit��ʼ���жϱ�־
int upintnubflag=0;				//UPinit��ʼ������ʱ��





void up_init(void)
{
	if(upinitflag>=1000&&upintnubflag<=6){  //��ʼ��6sʱ��
		upinitflag=0;
		send_100();  //�̶�����150W���ҿ���
		upintnubflag++;
		pid.voltage=0;//�ſعܳ�ʼ��֮����Ҫִ��һ��
	}
}

void up(void)
{
	
	up_init();	//�ſع�Ԥ��6s
	if(upintnubflag>6){
	flag_up_s=1;
	flag_200ms=0;   
	remain_time=SETTIME;
		if(upflag>1000)
		{
			upflag=0;
				select();  //�̶������ַ���
				uart_1();
	}
	if(CapacitiveScreen.MicrowaveSwitch==0x00||CapacitiveScreen.time==0x00){
	upintnubflag=0;					//��ʼ��6���־λ
	
	}
}
}

