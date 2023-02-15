#include "adc.h"
#include "mylib.h"
void adc_Init(void)
{
    SDADC_InitStructure ADC_initStruct;
	PORT_Init(PORTC, PIN2, PORTC_PIN2_SDADC_CH3P, 0);	//ADC1 ADC1.CH3P
	PORT_Init(PORTC, PIN4, PORTC_PIN4_SDADC_CH1P, 0);// ADC2   ADC1.CH1P
	PORT_Init(PORTD, PIN0, PORTD_PIN0_SDADC_CH4P, 0);//ADC3    ADC1.CH4P
	
	ADC_initStruct.clk_src = SDADC_CLKSRC_HRC_DIV8;//�ڲ���ƵRC����8��Ƶ
	ADC_initStruct.channels = SDADC_CH4;
	ADC_initStruct.out_cali=1; //ADC���У׼���ת�����
	ADC_initStruct.refp_sel=0;
	ADC_initStruct.trig_src = ADC_TRIGSRC_SW;//�����������ADC->START.GOд1����ת��
	ADC_initStruct.Continue = 0;					//������ģʽ��������ģʽ ת����ɺ�STARTλ�Զ����ֹͣת��
	ADC_initStruct.EOC_IEn = 0;	
	ADC_initStruct.OVF_IEn = 0;
    ADC_initStruct.HFULL_IEn = 0;
	ADC_initStruct.FULL_IEn = 0;
				//����ADC
	SDADC_Init(SDADC, &ADC_initStruct);
				//ʹ��ADC
	SDADC_Config_Set(SDADC,SDADC_CFG_A, SDADC_CFG_GAIN_1, 1, 1);
	SDADC_Config_Cali(SDADC,SDADC_CFG_A,SDADC_CALI_COM_GND, 0);
	SDADC_Config_Sel(SDADC, SDADC_CFG_A, SDADC_CH4);
	SDADC_Open(SDADC);								

}
//void adc_Init(void){
//	ADC_InitStructure ADC_initStruct;

//	PORT_Init(PORTC, PIN2, PORTC_PIN2_SDADC_CH3P, 0);	//ADC1 ADC1.CH3P
//	PORT_Init(PORTC, PIN4, PORTC_PIN4_SDADC_CH1P, 0);// ADC2   ADC1.CH1P
//	PORT_Init(PORTD, PIN0, PORTD_PIN0_SDADC_CH4P, 0);//ADC3    ADC1.CH4P
//	ADC_initStruct.clk_src = ADC_CLKSRC_HRC_DIV4;
//	ADC_initStruct.channels = ADC_CH3;
//	ADC_initStruct.samplAvg = ADC_AVG_SAMPLE1;
//	ADC_initStruct.trig_src = ADC_TRIGSRC_SW;
//	ADC_initStruct.Continue = 0;					//������ģʽ��������ģʽ
//	ADC_initStruct.EOC_IEn = 0;	
//	ADC_initStruct.OVF_IEn = 0;
//	ADC_Init(ADC, &ADC_initStruct);					//����ADC
//	
//	ADC_Open(ADC);									//ʹ��ADC
//	
//}
int16_t adc_read(void){
	int16_t res;
	double temp,T,t;

	    uint32_t  chn;
		SDADC_Start(SDADC);
		while((SDADC->STAT & SDADC_STAT_EOC_Msk) == 0);
		SDADC->STAT = 1 << SDADC_STAT_EOC_Pos;
		
		res = SDADC_Read(SDADC, &chn);
		temp=(float)(res+32768)*(3.3/65536);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
		t = temp/20;
		t = t / 0.000584;                    //����ɵ���  ��ѹ���Ե���
		T=(2.558*t)-256.02f;    
		printf("%f\r\n", T);
		
			//����ʱ�Ǳ���ģ����̺���ܵ���SDADC����
	return  T;
}
//int16_t adc_read(void){
//	 int16_t res;
//		ADC_Start(ADC);
//		while((ADC->CH[7].STAT & ADC_STAT_EOC_Msk) == 0);
//		ADC->CH[7].STAT = (1 << ADC_STAT_EOC_Pos);
//		
//		printf("%4d,", ADC_Read(ADC, ADC_CH3));
//	return res;
//}
int16_t Get_Adc_Average(int times){

uint32_t temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=adc_read();
//		delay_ms(5);
	}
	return temp_val/times;

}

