#ifndef __MEASURE_H
#define __MEASURE_H
#include "SWM181.h"
#include "mylib.h"

extern double TEMP;   //����
extern double TEMP_2;   //����
extern double View_T;
double meas_5(void);  //��������
double meas_6(void);  //��������

int16_t MidSumClucum(int16_t Buf[], uint16_t len);


#endif
