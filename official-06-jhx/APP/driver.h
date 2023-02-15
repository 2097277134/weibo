#ifndef __DRIVER_H__
#define __DRIVER_H__
#include "SWM181.h"
#include "mylib.h"

void DRIVER_Init(void);

//EN 
#define DirverDisable  GPIO_ClrBit(GPIOA, PIN5);	   //PA5�������ʧ��
#define DirverEnable GPIO_SetBit(GPIOA, PIN5);	 //PA5�������ʧ��
//+-
#define DirverPositiveDirection GPIO_SetBit(GPIOA, PIN4);	   //�������+
#define DirverNegativeDirection GPIO_ClrBit(GPIOA, PIN4);	   //-
//HZ
#define HZ_OFF GPIO_SetBit(GPIOA, PIN1);		//����
#define HZ_ON GPIO_ClrBit(GPIOA, PIN1);	

void DRIVER_Start(void);
void DRIVER_Stop(void);
#endif
