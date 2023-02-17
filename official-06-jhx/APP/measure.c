#include "measure.h"
#include "adc.h"
int16_t Buf_ADC_1[256];  //ADC��������
//int16_t Buf_ADC_2[512];
double View_temp,View_adc,View_adc4,View_temp4,View_T;

int Point_Adc = 0;
int Range_Set = 128;
double TEMP=0;

//����һ���¶Ȳɼ�ֵ�������������ݳ��ȣ������ռ�����ƽ��ֵ
int16_t MidSumClucum(int16_t Buf[], uint16_t len)  
{
		int32_t Sum;  
    int16_t Assist_buf[256];  //��������
    int16_t Assist = 0, i, j;
		//�ռ�����ת�Ƶ�������
    for(i = 0; i < len; i++)
    {
        Assist_buf[i] = Buf[i];  //��Buf[i]�е�����ת�Ƶ�Assist_buf[i]��
    }
		//�ռ�����������
    for(i = 0; i < len; i++)
    {
        for(j = i; j < len; j++)
        {
            if(Assist_buf[i] < Assist_buf[j])
            {
                Assist = Assist_buf[i];  //Assist�Ž�С��ֵ
                Assist_buf[i] = Assist_buf[j];  //Assist_buf[i]�Žϴ���ֵ
                Assist_buf[j] = Assist;  //Assist_buf[j]�Ž�С��ֵ
            }
        }
    }

    Sum = 0;
		
		//����Assist_buf[i]�м����ֵ��
    for(i = len / 4; i < len / 4 * 3; i++)
    {
        Sum = Sum + Assist_buf[i];
    }

    return Sum / (len / 2);  //����ƽ��ֵ
}


double meas_5()
{
	int adcx;
	
	int32_t A;  //������ʾ
  double temp,T,t;
	
	adcx=Get_Adc_Average(2);//��ȡͨ����2��ƽ��ת��ֵ

	Buf_ADC_1[Point_Adc] = adcx;  //ת��ֵ���η�������
	Point_Adc++;   
	if(Point_Adc >= Range_Set)  //�ռ����㹻����֮��
	{
		Point_Adc = 0;     
		adcx = MidSumClucum(Buf_ADC_1,Range_Set);  //����ȡ�м䲿��ƽ��ֵ
		View_adc = adcx;

		temp=(float)adcx*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
		t = temp/20;                          //���ԷŴ���
		t = t / 0.000584;                    //����ɵ���  ��ѹ���Ե���
		T=(2.558*t)-256.02f;                //�����¶ȱ任
		
		View_T = T;			                    //�õ������¶�ֵ
		A=T;                                //ȡAΪT����������
		T-=A;                               //ȡTΪС������
		T*=100000;                          //��Ϊ������ʾ
		View_temp = temp;     
	}		
	return View_T;
}

double meas_6()
{
	int adcx;
	
	int32_t A;  //������ʾ
  double temp,T,t;
	
	adcx=Get_Adc_Average(2);//��ȡͨ����2��ƽ��ת��ֵ

	Buf_ADC_1[Point_Adc] = adcx;  //ת��ֵ���η�������
	Point_Adc++;   
	if(Point_Adc >= Range_Set)  //�ռ����㹻����֮��
	{
		Point_Adc = 0;     
		adcx = MidSumClucum(Buf_ADC_1,Range_Set);  //����ȡ�м䲿��ƽ��ֵ
		View_adc = adcx;
		temp=(float)adcx*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
		t = temp/20;
		t = t / 0.000592;                    //����ɵ���  ��ѹ���Ե���
		T=(2.558*t)-256.02f;                //�����¶ȱ任
		View_T = T;			                    //�õ������¶�ֵ
		A=T;                                //ȡAΪT����������
		T-=A;                               //ȡTΪС������
		T*=100000;                          //��Ϊ������ʾ
		View_temp = temp;     
	}		
	return View_T;
}


