#include "driver.h"

void DRIVER_Init(){
	
	
	
		PWM_InitStructure  PWM_initStruct;
	
	PWM_initStruct.clk_div = PWM_CLKDIV_4;		//F_PWM = 24M/4 = 6M
	
	PWM_initStruct.mode = PWM_MODE_INDEP;		//A路和B路独立输出					
	PWM_initStruct.cycleB = 10000;					//6M/10000 = 600Hz	
	PWM_initStruct.hdutyB =  5000;				//5000/10000 = 50%
	PWM_initStruct.deadzoneB = 10;
	PWM_initStruct.initLevelB = 1;
	PWM_initStruct.HEndAIEn = 0;
	PWM_initStruct.NCycleAIEn = 0;
	PWM_initStruct.HEndBIEn = 0;
	PWM_initStruct.NCycleBIEn = 0;
	
	PWM_Init(PWM1, &PWM_initStruct);
	
	PORT_Init(PORTA, PIN1, FUNMUX_PWM1B_OUT, 0);
	
//	PWM_Start(PWM1, 0, 1);
	
	GPIO_Init(GPIOA,PIN4,1, 0, 0, 0);    //正反转
	GPIO_Init(GPIOA,PIN5,1, 0, 0, 0);		 //使能脚
	
	
	
	DirverPositiveDirection;
	DirverDisable;
}

void DRIVER_Start(void){

PWM_Start(PWM1, 0, 1);
	
}
void DRIVER_Stop(void){

PWM_Stop(PWM1,0,1);


}

