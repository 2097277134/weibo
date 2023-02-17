#ifndef __MEASURE_H
#define __MEASURE_H
#include "SWM181.h"
#include "mylib.h"

extern double TEMP;   //旁温
extern double TEMP_2;   //杆温
extern double View_T;
double meas_5(void);  //测量函数
double meas_6(void);  //测量函数

int16_t MidSumClucum(int16_t Buf[], uint16_t len);


#endif
