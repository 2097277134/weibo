#include "SWM181.h"
#include "mylib.h"
#include <string.h>

	
int main(void)
{
	
	SystemInit();
//	uart1_init();  //����1��ʼ��
	uart2_init();  //����2��ʼ�� ���ں͵�Դͨ��
  IO_Init();     //IO��ʼ��
	//up_init();
	DRIVER_Init();  //���������ʼ��
  adc_Init();    //����adc��ʼ��
	PID_Init();    //����PID
	TIMR_Init(TIMR0, TIMR_MODE_TIMER, SystemCoreClock/1000, 1); //ÿ0.001���Ӵ���һ���ж�
  IRQ_Connect(IRQ0_15_TIMR0, IRQ5_IRQ, 3);  //��ʱ��0�ж����ӵ�IRQ5�ж��ߣ������ȼ�
	TIMR_Init(TIMR1,TIMR_MODE_TIMER,SystemCoreClock/1000,1);
	IRQ_Connect(IRQ0_15_TIMR1, IRQ4_IRQ, 2);  //��ʱ��1�ж����ӵ�IRQ5�ж��ߣ������ȼ�
	TIMR_Start(TIMR1);    //��ʱ��1��ʼ����
	
	EN_ON;
//	F_ON;
	while(1)
	{
		if(taskflag[0]==taskflag[1]){   //taskflag[2]={0,100}����ʱ100ms
		taskflag[0]=0;
		task();
		}	
		if(sendflag[0]>=sendflag[1]){   //sendflag[2]={0,200}����ʱ200ms
			sendflag[0]=0;
			MCU_t_screen();               //����һ���¶�����
		}

		
		if(flag1)  //�յ�΢����Դ����Ϣ
		{
			flag1=0;
			judge1();
		}
		
		if(flag2&&time!=0)  //�յ�����������Ϣ&������ʱ����Ϊ0
		{
			flag2=0;          //������������ձ�־λ
			judge2();         //���н���õ���Ҫ����Ϣ
			up();             //�������ڳ���
		}
		else
		{	
			if(upflag%500==0)  //δ�յ����������õ�ʱ�䣬��0.5s����һ�ι���0w����
				send_0();  //���͹̶�����0W�ַ���
		}

	for(int i=0;i>=200;i++){
	HZ_OFF;
		F_OFF;
	delay_ms(100);
	HZ_ON;
		F_ON;
	delay_ms(100);
	}
	}
	//111222333
}






