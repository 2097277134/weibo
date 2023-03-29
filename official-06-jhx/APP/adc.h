#ifndef __ADC_H
#define __ADC_H
#include "SWM181.h"
#include "mylib.h"

void adc_Init(void);
extern double Temp;
extern double TEMP_2;					//´¢´æ¸ËÎÂÊµÊ±ÎÂ¶È
extern double Temp_2;
int16_t adc_read(void);
int16_t Get_Adc_Average(uint16_t len);
#endif
