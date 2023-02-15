#include "adc.h"
#include "mylib.h"

#include "math.h" 

extern double Temp;
double Temp=0;
int16_t SDADC_Result[8] = {0};
void adc_Init(void)
{
    SDADC_InitStructure ADC_initStruct;
	PORT_Init(PORTC, PIN2, PORTC_PIN2_SDADC_CH3P, 0);	//ADC1 ADC1.CH3P
	PORT_Init(PORTC, PIN4, PORTC_PIN4_SDADC_CH1P, 0);// ADC2   ADC1.CH1P
	PORT_Init(PORTD, PIN0, PORTD_PIN0_SDADC_CH4P, 0);//ADC3    ADC1.CH4P
	
	ADC_initStruct.clk_src = SDADC_CLKSRC_HRC_DIV8;//�ڲ���ƵRC����8��Ƶ
	ADC_initStruct.channels = SDADC_CH1 | SDADC_CH3 | SDADC_CH4;
	ADC_initStruct.out_cali=SDADC_OUT_CALIED; //ADC���У׼���ת�����
	ADC_initStruct.refp_sel=SDADC_REFP_AVDD;
	ADC_initStruct.trig_src = SDADC_TRIGSRC_TIMR3;
	ADC_initStruct.Continue = 0;					//������ģʽ��������ģʽ ת����ɺ�STARTλ�Զ����ֹͣת��
	ADC_initStruct.EOC_IEn = 1;	
	ADC_initStruct.OVF_IEn = 0;
    ADC_initStruct.HFULL_IEn = 0;
	ADC_initStruct.FULL_IEn = 0;
				//����ADC
	SDADC_Init(SDADC, &ADC_initStruct);
				//ʹ��ADC
	SDADC_Config_Set(SDADC, SDADC_CFG_A, SDADC_CFG_GAIN_2, 1, 1);
	SDADC_Config_Cali(SDADC, SDADC_CFG_A, SDADC_CALI_COM_GND, 1);
	SDADC_Config_Sel(SDADC, SDADC_CFG_A, SDADC_CH1 | SDADC_CH3 | SDADC_CH4);
	
	IRQ_Connect(IRQ0_15_SDADC, IRQ3_IRQ, 0);
	
	SDADC_Open(SDADC);		
	TIMR_Init(TIMR3, TIMR_MODE_TIMER, SystemCoreClock/500, 0);
	TIMR_Start(TIMR3);	

}

//int16_t adc_read(void){
//	int16_t res;
//	double temp,T,t;

//	    uint32_t  chn;
//		SDADC_Start(SDADC);
//		while((SDADC->STAT & SDADC_STAT_EOC_Msk) == 0);
//		SDADC->STAT = 1 << SDADC_STAT_EOC_Pos;
//		
//		res = SDADC_Read(SDADC, &chn);
//		temp=(float)(res+32768)*(3.3/65536);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//		t = temp/20;
//		t = t / 0.000584;                    //����ɵ���  ��ѹ���Ե���
//		T=(2.558*t)-256.02f;    
//		printf("%f\r\n", T);
//		
//			//����ʱ�Ǳ���ģ����̺���ܵ���SDADC����
//	return  T;
//}

void IRQ3_Handler(void)
{
	double temp,t;
	int16_t res;
	uint32_t chn,val;
	
	SDADC_IntEOCClr(SDADC);			//����жϱ�־

	while((SDADC->STAT & SDADC_STAT_FFEM_Msk) == 0)
	{
		val = SDADC_Read(SDADC, &chn) + 0x8000;
		SDADC_Result[chn] = val;
	}
		res=SDADC_Result[4];
		temp=(float)(res)*(3.3/65536);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//		t = temp*20;
//		t = t / 0.000586;                    //����ɵ���  ��ѹ���Ե���
//		Temp=(2.558*t)-256.02f;  
		t = temp/20;
		t = t / 0.000584;                    //����ɵ���  ��ѹ���Ե���
//		Temp=(2.558*t)-256.02f;                //�����¶ȱ任
		Temp=1/(log(t/10000)/3950+1/(273.15+25.0));
	Temp=Temp-273.15;
}

int16_t Get_Adc_Average(int times){

uint32_t temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Temp;
//		delay_ms(5);
	}
	return temp_val/times;

}

