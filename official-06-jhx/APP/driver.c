#include "driver.h"

void DRIVER_Init(){
	GPIO_Init(GPIOA,PIN7,1, 0, 0, 0);    //ʹ�ܽ�
	GPIO_Init(GPIOA,PIN6,1, 0, 0, 0);    //����ת
	GPIO_Init(GPIOA,PIN5,1, 0, 0, 0);		 //����
	EN_OFF;
	F_OFF;
	HZ_OFF;
}




