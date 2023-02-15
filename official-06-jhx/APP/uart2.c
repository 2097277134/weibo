#include "SWM181.h"
#include "mylib.h"




CapacitiveScreenData CapacitiveScreen;


uint8_t Rxd_End = 0;

char UART_RXBuffer[UART_RX_LEN] = {0};

uint32_t UART_RXIndex=0;
void uart2_init(void)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTB, PIN4, FUNMUX_UART2_RXD, 1);	//GPIOB.4����ΪUART2��������
	PORT_Init(PORTB, PIN5, FUNMUX_UART2_TXD, 0);	//GPIOB.5����ΪUART2�������
 	
 	UART_initStruct.Baudrate = 115200;
	UART_initStruct.DataBits = UART_DATA_8BIT;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOP_1BIT;
	UART_initStruct.RXThreshold = 7;
	UART_initStruct.RXThresholdIEn = 1;
	UART_initStruct.TXThreshold = 3;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;		//5���ַ�ʱ����δ���յ��µ������򴥷���ʱ�ж�
	UART_initStruct.TimeoutIEn = 1;
	UART_Init(UART2, &UART_initStruct);
	
	IRQ_Connect(IRQ0_15_UART2, IRQ0_IRQ, 1);
	
	UART_Open(UART2);
}

uint32_t UART2_GetChars(char *data)
{
	uint32_t len = 0;
	
	if(UART2_RX_STA != 0)
	{
		NVIC_DisableIRQ(IRQ2_IRQ);		//��UART_RXBuffer��ȡ���ݹ�����Ҫ�ر��жϣ���ֹ��д����
		memcpy(data, UART2_RX_BUF, UART_REC_LEN);  //��UART2_RXBuffer����UART_RX_LEN�ֽڵ�data
		len = UART2_RX_STA&0x3FFF;
		UART2_RX_STA = 0;
		NVIC_EnableIRQ(IRQ2_IRQ);   //��ȡ��ɿ��ж�
	}
	return len;
}

u8 UART2_RX_BUF[UART_REC_LEN] = {0};
u16 UART2_RX_STA=0;       //����״̬���
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u8 flag2=0;
//char buffer_2[UART_REC_LEN] = {0};   //UART_RX_LEN=128

void IRQ0_Handler(void)   //�����ж�
{
uint32_t chr;
	
	//�����FIFO���жϣ���ȡ���ݵ�ʱ��ȡ�꣬ʼ����FIFO������һ����Ŀ���Ǵ�����ʱ�ж�
	if(UART_INTRXThresholdStat(UART2))
	{
		while((UART2->FIFO & UART_FIFO_RXLVL_Msk) > 1)
		{
			if(UART_ReadByte(UART2, &chr) == 0)
			{
				if(UART_RXIndex < UART_RX_LEN)
				{
					UART_RXBuffer[UART_RXIndex] = chr;
					
					UART_RXIndex++;
				}
			}
		}
	}
	
	//����ǳ�ʱ�жϲ����ˣ���һ�������Ѿ���������
	else if(UART_INTTimeoutStat(UART2))
	{
		while(UART_IsRXFIFOEmpty(UART2) == 0)
		{
			if(UART_ReadByte(UART2, &chr) == 0)
			{
				if(UART_RXIndex < UART_RX_LEN)
				{
					UART_RXBuffer[UART_RXIndex] = chr;
					
					UART_RXIndex++;
				}
			}
		}
		Rxd_End = 1;
		
//		//�����21���ֽڣ���ô�������Ľ���
//		if(UART_RXIndex == 21)
//		{
//			Rxd_End = 1;
//		}
//		//�����5���ֽڣ���ôӦ�����Լ����͵�����
//		else if(UART_RXIndex == 5)
//		{
//			UART_RXIndex = 0;
//		}
//		//�����26���ֽڣ���ôӦ�����Լ��������ݸ��豸��������ճ����
//		else if(UART_RXIndex == 26)
//		{
//			Rxd_End = 1;
//		}		
//		//�쳣���������ָ��
//		else
//		{
//			UART_RXIndex = 0;
//		}
	}
	printf("%s",UART_RXBuffer);
}

void Data_Deal(void)
{
	uint16_t i = 0;
	
	//���Rxd_End == 1 ���Ѿ�����������һ��������
	if(Rxd_End == 1)
	{
		//�����9���ֽڣ���������
		if((UART_RXIndex == 9)&&(UART_RXBuffer[0]==0x5A)&&(UART_RXBuffer[1]==0xA5))   //���ô��ڽ��ܱ�־λ��ֹ������ʱ�ı����
		{
			//������Ĵ������
			if(UART_RXBuffer[5]==0x00){		//���ʽ�����x10
			CapacitiveScreen.power=UART_RXBuffer[8]*10;
			}
			if (UART_RXBuffer[5]==0x01){  //ʱ�������x10
			CapacitiveScreen.time=UART_RXBuffer[8]*10;
			}
			if (UART_RXBuffer[5]==0x03){		//�¶�=40+4x
			CapacitiveScreen.temperature=UART_RXBuffer[8]*4+40;
			}
			if (UART_RXBuffer[5]==0x06){		//΢������		UART_RXBuffer[8]==0x00�� UART_RXBuffer[8]==0x01��
				CapacitiveScreen.MicrowaveSwitch=UART_RXBuffer[8];
				}
			if (UART_RXBuffer[5]==0x07){		//ˮ�ÿ���		UART_RXBuffer[8]==0x00�� UART_RXBuffer��8]==0x01��
			CapacitiveScreen.WaterPumpSwitch=UART_RXBuffer[8];
			}
		
	
			//�ط����豸
			//Data_Send();
		}
		//������Լ�������ճ����
		else if(UART_RXIndex == 26)
		{
			//������ת��һ��
			for(i = 0; i < 21; i++)
			{
				UART_RXBuffer[i] = UART_RXBuffer[i + 5];
			}
			
			//������Ĵ������
			
			
			//�ط����豸
			//Data_Send();
		}
		
		//���������׼����һ�ν���
		UART_RXIndex = 0;
		Rxd_End = 0;
		
	}
}
