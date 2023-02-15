#include "SWM181.h"
#include "mylib.h"
#include <string.h>



uint8_t SEND_BUF1[8]={0x5A,0xA5,0x05,0x82,0x10,0x08,0x10,0x11};


int main(void)
{
	
	SystemInit();
	TIMR_Init(TIMR0, TIMR_MODE_TIMER, SystemCoreClock/1000, 1); //ÿ0.001���Ӵ���һ���ж�
  IRQ_Connect(IRQ0_15_TIMR0, IRQ5_IRQ, 3);  //��ʱ��0�ж����ӵ�IRQ5�ж��ߣ������ȼ�
	uart1_init();  //����1��ʼ��
	uart2_init();  //����2��ʼ�� ���ں͵�Դͨ��
  IO_Init();     //IO��ʼ��
	DRIVER_Init();  //���������ʼ��
  adc_Init();    //����adc��ʼ��
	PID_Init();    //����PID
	
	TIMR_Init(TIMR1,TIMR_MODE_TIMER,SystemCoreClock/1000,1);
	IRQ_Connect(IRQ0_15_TIMR1, IRQ4_IRQ, 2);  //��ʱ��1�ж����ӵ�IRQ5�ж��ߣ������ȼ�
	TIMR_Start(TIMR1);    //��ʱ��1��ʼ����

	while(1)
	{
		if(taskflag[0]==taskflag[1]){   //taskflag[2]={0,100}����ʱ100ms
		taskflag[0]=0;
		task();
		}	

		Data_Deal();							//���������ݴ�����Ҫһֱ���в�Ҫ���ж�
		if(flag1)  //�յ�΢����Դ����Ϣ
		{
			flag1=0;
			judge1();
		}
		
		if(CapacitiveScreen.MicrowaveSwitch==0x01&&time!=0)  //�յ�����������Ϣ&������ʱ����Ϊ0
		{
			up();             //�������ڳ���
		}
		else
		{	
			if(upflag%500==0)  //δ�յ����������õ�ʱ�䣬��0.5s����һ�ι���0w����
				send_0();  //���͹̶�����0W�ַ���
		}
	}
}






