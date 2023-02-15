#include "SWM181.h"
#include "mylib.h"








#define UART_RX_LEN	 128

char UART_RXBuffer[UART_RX_LEN] = {0};
uint32_t UART_RXIndex = 0;
void uart2_init(void)//
{
	UART_InitStructure UART_initStruct;
//	
//	PORT_Init(PORTB, PIN4, FUNMUX_UART2_RXD, 1);	//GPIOB.4配置为UART2输入引脚
//	PORT_Init(PORTB, PIN5, FUNMUX_UART2_TXD, 0);	//GPIOB.5配置为UART2输出引脚
 	PORT_Init(PORTB, PIN6, FUNMUX_UART2_RXD, 1);	//GPIOB.6配置为UART2输入引脚
	PORT_Init(PORTB, PIN7, FUNMUX_UART2_TXD, 0);	//GPIOB.7配置为UART2输出引脚
 	UART_initStruct.Baudrate = 115200;
	UART_initStruct.DataBits = UART_DATA_8BIT;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOP_1BIT;
	UART_initStruct.RXThreshold = 3;
	UART_initStruct.RXThresholdIEn = 1;
	UART_initStruct.TXThreshold = 3;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;
	UART_initStruct.TimeoutIEn = 1;
 	UART_Init(UART2, &UART_initStruct);
	
	IRQ_Connect(IRQ0_15_UART2, IRQ2_IRQ, 2);
	
	UART_Open(UART2);
}

uint32_t UART2_GetChars(char *data)
{
	uint32_t len = 0;
	
	if(UART2_RX_STA != 0)
	{
		NVIC_DisableIRQ(IRQ2_IRQ);		//从UART_RXBuffer读取数据过程中要关闭中断，防止读写混乱
		memcpy(data, UART2_RX_BUF, UART_REC_LEN);  //从UART2_RXBuffer复制UART_RX_LEN字节到data
		len = UART2_RX_STA&0x3FFF;
		UART2_RX_STA = 0;
		NVIC_EnableIRQ(IRQ2_IRQ);   //读取完成开中断
	}
	return len;
}

u8 UART2_RX_BUF[UART_REC_LEN] = {0};
u16 UART2_RX_STA=0;       //接收状态标记
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u8 flag2=0;
//char buffer_2[UART_REC_LEN] = {0};   //UART_RX_LEN=128

void IRQ2_Handler(void)
{
	uint32_t chr;
	
	if(UART_INTRXThresholdStat(UART2) || UART_INTTimeoutStat(UART2))
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
	}
	printf("%s",UART_RXBuffer);
}

