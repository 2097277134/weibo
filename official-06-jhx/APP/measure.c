#include "measure.h"
#include "adc.h"
int16_t Buf_ADC_1[256];  //ADC缓存数组
//int16_t Buf_ADC_2[512];
double View_temp,View_adc,View_adc4,View_temp4,View_T;

int Point_Adc = 0;
int Range_Set = 128;
double TEMP=0;

//参数一：温度采集值；参数二：数据长度，返回收集数据平均值
int16_t MidSumClucum(int16_t Buf[], uint16_t len)  
{
		int32_t Sum;  
    int16_t Assist_buf[256];  //帮助缓存
    int16_t Assist = 0, i, j;
		//收集数据转移到缓存中
    for(i = 0; i < len; i++)
    {
        Assist_buf[i] = Buf[i];  //将Buf[i]中的数据转移到Assist_buf[i]中
    }
		//收集参数的排序
    for(i = 0; i < len; i++)
    {
        for(j = i; j < len; j++)
        {
            if(Assist_buf[i] < Assist_buf[j])
            {
                Assist = Assist_buf[i];  //Assist放较小数值
                Assist_buf[i] = Assist_buf[j];  //Assist_buf[i]放较大数值
                Assist_buf[j] = Assist;  //Assist_buf[j]放较小数值
            }
        }
    }

    Sum = 0;
		
		//计算Assist_buf[i]中间段数值和
    for(i = len / 4; i < len / 4 * 3; i++)
    {
        Sum = Sum + Assist_buf[i];
    }

    return Sum / (len / 2);  //返回平均值
}


double meas_5()
{
	int adcx;
	
	int32_t A;  //用于显示
  double temp,T,t;
	
	adcx=Get_Adc_Average(2);//获取通道的2次平均转换值

	Buf_ADC_1[Point_Adc] = adcx;  //转换值依次放入数组
	Point_Adc++;   
	if(Point_Adc >= Range_Set)  //收集到足够数据之后
	{
		Point_Adc = 0;     
		adcx = MidSumClucum(Buf_ADC_1,Range_Set);  //排序，取中间部分平均值
		View_adc = adcx;

		temp=(float)adcx*(3.3/4096);          //获取计算后的带小数的实际电压值，比如3.1111
		t = temp/20;                          //除以放大倍数
		t = t / 0.000584;                    //换算成电阻  电压除以电流
		T=(2.558*t)-256.02f;                //电阻温度变换
		
		View_T = T;			                    //得到返回温度值
		A=T;                                //取A为T的整数部分
		T-=A;                               //取T为小数部分
		T*=100000;                          //变为整数显示
		View_temp = temp;     
	}		
	return View_T;
}

double meas_6()
{
	int adcx;
	
	int32_t A;  //用于显示
  double temp,T,t;
	
	adcx=Get_Adc_Average(2);//获取通道的2次平均转换值

	Buf_ADC_1[Point_Adc] = adcx;  //转换值依次放入数组
	Point_Adc++;   
	if(Point_Adc >= Range_Set)  //收集到足够数据之后
	{
		Point_Adc = 0;     
		adcx = MidSumClucum(Buf_ADC_1,Range_Set);  //排序，取中间部分平均值
		View_adc = adcx;
		temp=(float)adcx*(3.3/4096);          //获取计算后的带小数的实际电压值，比如3.1111
		t = temp/20;
		t = t / 0.000592;                    //换算成电阻  电压除以电流
		T=(2.558*t)-256.02f;                //电阻温度变换
		View_T = T;			                    //得到返回温度值
		A=T;                                //取A为T的整数部分
		T-=A;                               //取T为小数部分
		T*=100000;                          //变为整数显示
		View_temp = temp;     
	}		
	return View_T;
}


