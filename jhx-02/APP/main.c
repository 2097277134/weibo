#include "SWM181.h"
#include "mylib.h"
#include <string.h>

//uint8_t SEND_BUF1[8]={0x5A,0xA5,0x05,0x82,0x10,0x08,0x10,0x11};


int main(void)
{
	
	SystemInit();  
	TIMR_Init(TIMR0, TIMR_MODE_TIMER, SystemCoreClock/10, 1); //ÿ0.001���Ӵ���һ���ж�
  IRQ_Connect(IRQ0_15_TIMR0, IRQ5_IRQ, 2);  //��ʱ��0�ж����ӵ�IRQ5�ж��ߣ������ȼ�
	TIMR_Start(TIMR0);    //��ʱ��1��ʼ����
	uart1_init();  //����1��ʼ����΢����Դͨ��
	uart2_init();  //����2��ʼ�� ���ں͵�����ͨ��
  IO_Init();     //IO��ʼ���������
	DRIVER_Init();  //���������ʼ��
  adc_Init();    //����adc��ʼ��
	PID_Init();    //����PID
	
	TIMR_Init(TIMR1,TIMR_MODE_TIMER,SystemCoreClock/1000,1);
	IRQ_Connect(IRQ0_15_TIMR1, IRQ4_IRQ, 1);  //��ʱ��1�ж����ӵ�IRQ5�ж��ߣ������ȼ�
	TIMR_Start(TIMR1);    //��ʱ��1��ʼ����

	while(1)
	{
		task();     //�˴�Ϊһֱ���еĳ���
		if(flag1)  //�յ�΢����Դ����Ϣ
		{
			flag1=0;
			judge1();  //��Դ���ϱ���
		}
		
		if(CapacitiveScreen.MicrowaveSwitch==0x01&&CapacitiveScreen.time!=0)  //�յ����������ڰ�ť����&������ʱ����Ϊ0
		{	
			LEDR_OFF;    //����
			LEDG_ON;     //���̵�
			up();        //�������ڳ���
		}
		else
		{	
			if(CapacitiveScreen.MicrowaveSwitch==0x00||CapacitiveScreen.time==0x00)  //����������������ʣ��ʱ��Ϊ0
					upintnubflag=0;	   //UPinit��ʼ������ʱ�䣬Ϊ�˷�ֹ��;����΢���رհ�ťȻ���ٿ���ʱû��΢����ʼ������
			stage1=1;
			stage2=1;
			stage3=1;
			if(taskflag>=500){  //δ�յ����������õ�ʱ�䣬��0.5s����һ�ι���0w����
				taskflag=0;
				send_0();  //���͹̶�����0W�ַ���
		}
	}
}
}


