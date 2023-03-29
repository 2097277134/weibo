#include "mylib.h"
#include "measure.h"

int flag_0w=1;       //������0w��־λ
extern int flag_up_s;//���¼�ʱ
extern double TEMP;						//��������ʵʱ�¶�
extern double TEMP_2;					//�������ʵʱ�¶�
extern int flag_up_s;         //���¼�ʱ
extern int SETTIME;           //�趨ʱ��

int flag_up_s=0;
int taskflag=0;      //task��־λ
int upflag=0;		//t1ʱ����жϱ�־λ1000ms
uint8_t SEND_Microwave_OFF[8]={0x5A,0xA5,0x05,0x82,0x10,0x06,0x00,0x00}; //�����������΢���ر�
//IRQ4_Handler
void IRQ4_Handler(void){   //ÿ1ms����һ���ж�
  TIMR_INTClr(TIMR1);      //���TIMR1�жϱ�־λ
	taskflag++;           
	upinitflag++;            //upinit��ʼ���жϱ�־λ
	upflag++;                //up�жϱ�־λ
}
void task(void)    //����д�볤�����е���Ҫ����
{
	//ˮ�ÿ������¶ȷ���
	if(CapacitiveScreen.WaterPumpSwitch==0x01){
		uint16_t hz,cyc;
		DirverEnable;    //������ʹ��
		hz=TEMP_2;
		if(TEMP_2>600){  //�������޷�
		hz=600;
		}
		//�����ʼΪ600HZ��50%ռ�ձ�
		cyc=6000000/hz;   //cycΪ�趨������ֵ������¶������Ⱦͽ�6000000��С�����ڿɼӹ�ʽ��������ת�ٺͽ������ʹ�ϵ��
		PWM_SetCycle(PWM1,PWM_CH_B,cyc);     //6M/10000=600
	}
	else{
		DirverDisable;
	  CapacitiveScreen.MicrowaveSwitch=0x00;
	}
	
	//���±���������>90;����>50����ƺͷ���������
	if(TEMP>90 || TEMP_2>50)
	{
		LEDR_ON;
		bee_on;
		send_0();
	}
	else{
		LEDR_OFF;
		bee_off;
	}
}


//void delay_us(int us)
//{
//  int i;
//  int j = 10*us;
//    for(i = 0;i<j;i++);
//}
//void delay_ms(int ms)
//{
//  int i,k;
//  for(k = ms; k  >  0; k--)
//  {
//    for(i = 0;i < 4000; i++);
//  }
//}
//void delay_s(int s)
//{
//  int i;
//  for(i = 0;i<s;i++)
//  {
//    delay_ms(1000);
//  }
//}

