#include "SWM181.h"
#include "MYLIB.h"


void IO_Init(void)
{
	//LED
	GPIO_Init(GPIOA, PIN15, 1, 0, 0, 0);          //bee��A15��Ϊ������������������ڲ���������·���ϵ�����Ҫ����
	GPIO_Init(GPIOA, PIN14, 1, 0, 0, 0);          //LED1
	GPIO_Init(GPIOA, PIN13, 1, 0, 0, 0);          //LED2
	GPIO_Init(GPIOC, PIN3, 1, 0, 0, 0);          //LED_B
	GPIO_Init(GPIOB, PIN9, 1, 0, 0, 0);          //LED_R
	GPIO_Init(GPIOC, PIN5, 1, 0, 0, 0);          //LED_G
	LEDB_OFF;
	LEDR_ON;  //��ʼ�׶ο����
	LEDG_OFF;

	LED1_ON;
	LED2_ON;
	bee_off;

}
