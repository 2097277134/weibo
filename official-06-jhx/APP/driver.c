#include "driver.h"

void DRIVER_Init(){
	GPIO_Init(GPIOA,PIN7,1, 0, 0, 0);    //使能脚
	GPIO_Init(GPIOA,PIN6,1, 0, 0, 0);    //正反转
	GPIO_Init(GPIOA,PIN5,1, 0, 0, 0);		 //脉冲
	EN_OFF;
	F_OFF;
	HZ_OFF;
}




