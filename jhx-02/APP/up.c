#include "SWM181.h"
#include "mylib.h"
#include "IO.h"

//////////////////////////////////////////////////
//�������º���������ſعܹ���
///////////////////////////////////////////////////

extern double TEMP;						//����ʵ��ʵʱ�¶�
extern int flag_up_s;      //���¼�ʱ��ʼ��־λ

extern int SETTIME;

extern struct PID pid;

/*����ֵ�����й��ʡ�����ʱ�������ڡ�ռ�ձ�*/



int SETTIME;  //��������ʱ��ΪCapacitiveScreen.time-2min

int upinitflag=0;					//UPinit��ʼ���жϱ�־
int upintnubflag=0;				//UPinit��ʼ������ʱ��





void up_init(void)
{
	if(upinitflag>=1000&&upintnubflag<=6){  //��ʼ��6sʱ��
		upinitflag=0;
		send_100();  //�̶�����150W���ҿ���
		upintnubflag++;
		pid.voltage=0;//�ſعܳ�ʼ��֮����Ҫִ��һ��
		CapacitiveScreen.time--;
	}
}

void up(void)
{
	
	up_init();	//�ſع�Ԥ��6s
	if(upintnubflag>6){
	flag_up_s=1;
   
	select();  //�̶������ַ���
		if(upflag>1000)
		{
			upflag=0;
				select();  //�̶������ַ���
				uart_1();
			CapacitiveScreen.time--;
	}
				//��ʼ��6���־λ
	
	
}
	
}

