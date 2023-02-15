#ifndef __DRIVER_H__
#define __DRIVER_H__
#include "SWM181.h"
#include "mylib.h"

void DRIVER_Init(void);

//EN 
#define EN_ON GPIO_SetBit(GPIOA, PIN7);	   //PA7步进电机使能
#define EN_OFF GPIO_ClrBit(GPIOA, PIN7);	 //PA7清零
//+-
#define F_OFF GPIO_SetBit(GPIOA, PIN6);	   //电机相关
#define F_ON GPIO_ClrBit(GPIOA, PIN6);	   //
//HZ
#define HZ_OFF GPIO_SetBit(GPIOA, PIN5);	
#define HZ_ON GPIO_ClrBit(GPIOA, PIN5);	


#endif
