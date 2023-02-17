#include "driver.h"

void DRIVER_Init(){

	PWM_InitStructure  PWM_initStruct;
	
	PWM_initStruct.clk_div = PWM_CLKDIV_4;		//F_PWM = 24M/4 = 6M�����з�Ƶ
	PWM_initStruct.mode = PWM_MODE_INDEP;		//A·��B·�������					
	PWM_initStruct.cycleB = 10000;					//6M/10000 = 600Hz��Ƶ��
	PWM_initStruct.hdutyB =  5000;				//5000/10000 = 50%��ռ�ձ�
	PWM_initStruct.deadzoneB = 10;        //���������������Ƴ�ʱ��
	PWM_initStruct.initLevelB = 1;        //��ʼ��ƽ
	PWM_initStruct.HEndAIEn = 0;          //A·�ߵ�ƽ�����ж�ʹ��
	PWM_initStruct.NCycleAIEn = 0;        //A·�����ڿ�ʼ�ж�ʹ��
	PWM_initStruct.HEndBIEn = 0;          //B·�ߵ�ƽ�����ж�ʹ��
	PWM_initStruct.NCycleBIEn = 0;        //B·�����ڿ�ʼ�ж�ʹ��
	
	PWM_Init(PWM1, &PWM_initStruct);
	
	PORT_Init(PORTA, PIN1, FUNMUX_PWM1B_OUT, 0);
	
	GPIO_Init(GPIOA,PIN4,1, 0, 0, 0);    //����ת
	GPIO_Init(GPIOA,PIN5,1, 0, 0, 0);		 //ʹ�ܽ�
	PWM_Start(PWM1, 0, 1);
	
	DirverPositiveDirection;
	DirverDisable;

}

void DRIVER_Start(void){

PWM_Start(PWM1, 0, 1);
	
}
void DRIVER_Stop(void){

PWM_Stop(PWM1,0,1);


}

