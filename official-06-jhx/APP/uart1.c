#include "SWM181.h"
#include "mylib.h"

/****************************************************************************************************************************************** 
* ��������: fputc()
* ����˵��: printf()ʹ�ô˺������ʵ�ʵĴ��ڴ�ӡ����
* ��    ��: int ch		Ҫ��ӡ���ַ�
*			FILE *f		�ļ����
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
int fputc(int ch, FILE *f)
{
	UART_WriteByte(UART1, ch);
	
	while(UART_IsTXBusy(UART2));
 	
	return ch;
}


void uart1_init(void)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTB, PIN6, FUNMUX_UART1_RXD, 1);	//GPIOB.6����ΪUART1��������
	PORT_Init(PORTB, PIN7, FUNMUX_UART1_TXD, 0);	//GPIOB.7����ΪUART1�������
 	
 	UART_initStruct.Baudrate = 9600;
	UART_initStruct.DataBits = UART_DATA_8BIT;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOP_1BIT;
	UART_initStruct.RXThreshold = 3;
	UART_initStruct.RXThresholdIEn = 1;
	UART_initStruct.TXThreshold = 3;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;
	UART_initStruct.TimeoutIEn = 1;
 	UART_Init(UART1, &UART_initStruct);
	
	IRQ_Connect(IRQ0_15_UART1, IRQ1_IRQ, 1);
	
	UART_Open(UART1);
}




u8 UART1_RX_BUF[UART_REC_LEN] = {0};
u16 UART1_RX_STA=0;       //����״̬���

uint32_t UART1_GetChars(char *data)
{
	uint32_t len = 0;
	
	if(UART1_RX_STA != 0)
	{
		NVIC_DisableIRQ(IRQ1_IRQ);		//��UART_RXBuffer��ȡ���ݹ�����Ҫ�ر��жϣ���ֹ��д����
		memcpy(data, UART1_RX_BUF, UART_REC_LEN);  //��UART1_RXBuffer����UART_RX_LEN�ֽڵ�data
		len = UART1_RX_STA&0x3FFF;
		UART1_RX_STA = 0;
		NVIC_EnableIRQ(IRQ1_IRQ);   //��ȡ��ɿ��ж�
	}	
	return len;
}

//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u8 flag1=0;
char buffer[UART_REC_LEN] = {0};   //UART_RX_LEN=128
void IRQ1_Handler(void)
{
	
	uint32_t chr;   //������������
	u16 len;   //������������
	u16 i;

	if(UART_INTRXThresholdStat(UART1) || UART_INTTimeoutStat(UART1))  //FIFO���ݵ�����ߴ�����ʱ�ж�
	{
		if(UART_ReadByte(UART1, &chr) == 0)    //��UART1����һ�ֽ����ݵ�&chr������û�д���
		{
			if((UART1_RX_STA&0x8000)==0)//����δ���
			{
				if(UART1_RX_STA&0x4000)//���յ���0x55
				{
					if(chr!=0xAA || UART_INTTimeoutStat(UART1))UART1_RX_STA=0;//���մ�����ߴ�����ʱ�ж�,���¿�ʼ
					else 
					{
						UART1_RX_STA|=0x8000;  //��������� 
						flag1=1;
						if((len = UART1_GetChars(buffer)) != 0)
						{
							for(i = 0; i < len; i++)
							{
								UART_WriteByte(UART1, buffer[i]);
								while(UART_IsTXBusy(UART1));     //�ж��Ƿ��ڷ�������
							}
						}
					}
				}
				else //��û�յ�0X55
				{	
					if(chr==0x055)UART1_RX_STA|=0x4000;
					else
					{
						UART1_RX_BUF[UART1_RX_STA&0X3FFF]=chr ;
						UART1_RX_STA++;
						if(UART1_RX_STA>(UART_REC_LEN-1))UART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}
		}
	}
}



