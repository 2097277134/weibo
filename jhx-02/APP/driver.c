#include "driver.h"

void DRIVER_Init(){

	PWM_InitStructure  PWM_initStruct;
	
	PWM_initStruct.clk_div = PWM_CLKDIV_4;		//F_PWM = 24M/4 = 6M，进行分频
	PWM_initStruct.mode = PWM_MODE_INDEP;		//A路和B路独立输出					
	PWM_initStruct.cycleB = 10000;					//6M/10000 = 600Hz，频率
	PWM_initStruct.hdutyB =  5000;				//5000/10000 = 50%，占空比
	PWM_initStruct.deadzoneB = 10;        //死区，即上升沿推迟时长
	PWM_initStruct.initLevelB = 1;        //初始电平
	PWM_initStruct.HEndAIEn = 0;          //A路高电平结束中断使能
	PWM_initStruct.NCycleAIEn = 0;        //A路新周期开始中断使能
	PWM_initStruct.HEndBIEn = 0;          //B路高电平结束中断使能
	PWM_initStruct.NCycleBIEn = 0;        //B路新周期开始中断使能
	
	PWM_Init(PWM1, &PWM_initStruct);
	
	PORT_Init(PORTA, PIN1, FUNMUX_PWM1B_OUT, 0);
	
	GPIO_Init(GPIOA,PIN4,1, 0, 0, 0);    //正反转
	GPIO_Init(GPIOA,PIN5,1, 0, 0, 0);		 //使能脚
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

