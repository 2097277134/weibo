#ifndef __DRIVER_H__
#define __DRIVER_H__
#include "SWM181.h"
#include "mylib.h"

void DRIVER_Init(void);

//EN 
#define DirverDisable  GPIO_ClrBit(GPIOA, PIN5);	   //PA5步进电机失能
#define DirverEnable GPIO_SetBit(GPIOA, PIN5);	 //PA5步进电机失能
//+-
#define DirverPositiveDirection GPIO_SetBit(GPIOA, PIN4);	   //电机方向+
#define DirverNegativeDirection GPIO_ClrBit(GPIOA, PIN4);	   //-
//HZ
#define HZ_OFF GPIO_SetBit(GPIOA, PIN1);		//脉冲
#define HZ_ON GPIO_ClrBit(GPIOA, PIN1);	

void DRIVER_Start(void);
void DRIVER_Stop(void);
#endif
