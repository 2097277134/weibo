#include "mylib.h"
#include "measure.h"
int flag_200ms=0;    //һ���־λ
int flag_0w=1;       //������0w��־λ
extern int flag_up_s;//���¼�ʱ
extern double TEMP;						//��������ʵʱ�¶�
extern double TEMP_2;					//�������ʵʱ�¶�
extern int flag_up_s;         //���¼�ʱ
extern int SETTIME;           //�趨ʱ��
extern int remain_time;

double TEMP_2=0;
int flag_up_s=0;
int taskflag[2]={0,100};      //task��־λ
int upflag=0;		//t1ʱ����жϱ�־λ1000ms
uint8_t SEND_Microwave_OFF[8]={0x5A,0xA5,0x05,0x82,0x10,0x06,0x00,0x00}; //�����������΢���ر�
//IRQ4_Handler
void IRQ4_Handler(void){   //ÿ1ms����һ���ж�
  TIMR_INTClr(TIMR1);      //���TIMR1�жϱ�־λ
	taskflag[0]++;           
	upinitflag++;            //upinit��ʼ���жϱ�־λ
	upflag++;                //up�жϱ�־λ

}
void task(void)    //����д�볤�����е���Ҫ����
{
		 
		if(CapacitiveScreen.WaterPumpSwitch==0x01){
			DirverEnable
		DRIVER_Start();
		}
		else{
		DRIVER_Stop();
		CapacitiveScreen.MicrowaveSwitch=0x00;
		USART_SendData(UART2,SEND_Microwave_OFF,8);
		
		
		}
		TEMP=Get_Adc_Average(2);
		MCU_t_screen();               //����һ���¶�����		
		//���±���������>90;����>50
		if(TEMP>90 || TEMP_2>50)
		{
			bee_on;
		}
		else
			bee_off;
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

