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
int ADCflag[2]={0,100};			//ADC��־λ
int sendflag[2]={0,200};		//���������ͱ�־λ
int upflag=0;		//t1ʱ����жϱ�־λ1000ms
int t2flag=0;		//t2ʱ����жϱ�־λ1000ms
//IRQ5_Handler
void IRQ4_Handler(void){   //ÿ1ms����һ���ж�
  TIMR_INTClr(TIMR1);      //���TIMR1�жϱ�־λ

	taskflag[0]++;           
	ADCflag[0]++;            
	sendflag[0]++;           
	upinitflag++;            //up��ʼ���жϱ�־λ
	upflag++;                //up�жϱ�־λ
	t2flag++;                //
}
void task(void)
{
	
		
		
		if(ADCflag[0]>=ADCflag[1]){
		ADCflag[0]=0;
		TEMP=adc_read();
//		TEMP_2=meas_6();	
		}
	
//		//����ѭ��
//		for(int i=1;i<=256;i++)
//		{
//			TEMP=meas_5();					 //����ʵʱ����
//		}
//		
//		for(int i=1;i<=256;i++)
//		{
//			TEMP_2=meas_6();        //����ʵʱ����
//		}
//		
//		MCU_t_screen();  //�򴮿�������
		
		//��ʼʱÿһ�����Դ����0Wָ��һ��
		if(flag_0w&&flag_200ms>=5)  
		{
			send_0();  //�̶�����150W����
			flag_200ms=0;
		}
		
		//ÿ��һ���趨ʱ���һ
		if(flag_up_s&&flag_200ms>=5)
		{
			remain_time-=1;
			flag_200ms=0;
			if(remain_time==0) 
			{
				flag_up_s=0;
//				sys_reset();
			}
		}
		
		if(TEMP==SETTEMP-4)
		{
			ratio=1;  //ռ�ձ�
			T1=1;  //PID��������ʱ��ʱ����(��)
		}
		
		//���±���������>90;����>50
//		if(TEMP>90 || TEMP_2>50)
//		{
//			BEEP=1;
//		}
//		else
//			BEEP=0;
		
		flag_200ms++;	
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

