#ifndef __IO_H__
#define __IO_H__

#include "SWM181.h"
#include "mylib.h"

//LED_B
#define LEDB_ON GPIO_SetBit(GPIOC, PIN3);	
#define LEDB_OFF GPIO_ClrBit(GPIOC, PIN3);	
//LED_G
#define LEDG_ON GPIO_SetBit(GPIOC, PIN5);	
#define LEDG_OFF GPIO_ClrBit(GPIOC, PIN5);	
//LED_R
#define LEDR_ON GPIO_SetBit(GPIOB, PIN9);	
#define LEDR_OFF GPIO_ClrBit(GPIOB, PIN9);	
//bee
#define bee_on GPIO_SetBit(GPIOA, PIN15);	
#define bee_off GPIO_ClrBit(GPIOA, PIN15);	
//LED1
#define LED1_OFF GPIO_SetBit(GPIOA, PIN14);	
#define LED1_ON GPIO_ClrBit(GPIOA, PIN14);	
//LED2
#define LED2_OFF GPIO_SetBit(GPIOA, PIN13);	
#define LED2_ON GPIO_ClrBit(GPIOA, PIN13);	
void IO_Init(void);

#endif

