#ifndef __ADC_H
#define __ADC_H
#include "SWM181.h"
#include "mylib.h"

void adc_Init(void);

int16_t adc_read(void);
int16_t Get_Adc_Average(int timer);
#endif
