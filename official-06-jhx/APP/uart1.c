#include "SWM181.h"
#include "mylib.h"

/****************************************************************************************************************************************** 
* 函数名称: fputc()
* 功能说明: printf()使用此函数完成实际的串口打印动作
* 输    入: int ch		要打印的字符
*			FILE *f		文件句柄
* 输    出: 无
* 注意事项: 无
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
	
	PORT_Init(PORTB, PIN6, FUNMUX_UART1_RXD, 1);	//GPIOB.6配置为UART1输入引脚
	PORT_Init(PORTB, PIN7, FUNMUX_UART1_TXD, 0);	//GPIOB.7配置为UART1输出引脚
 	
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
u16 UART1_RX_STA=0;       //接收状态标记

uint32_t UART1_GetChars(char *data)
{
	uint32_t len = 0;
	
	if(UART1_RX_STA != 0)
	{
		NVIC_DisableIRQ(IRQ1_IRQ);		//从UART_RXBuffer读取数据过程中要关闭中断，防止读写混乱
		memcpy(data, UART1_RX_BUF, UART_REC_LEN);  //从UART1_RXBuffer复制UART_RX_LEN字节到data
		len = UART1_RX_STA&0x3FFF;
		UART1_RX_STA = 0;
		NVIC_EnableIRQ(IRQ1_IRQ);   //读取完成开中断
	}	
	return len;
}

//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u8 flag1=0;
char buffer[UART_REC_LEN] = {0};   //UART_RX_LEN=128
void IRQ1_Handler(void)
{
	
	uint32_t chr;   //用来接收数据
	u16 len;   //用来发送数据
	u16 i;

	if(UART_INTRXThresholdStat(UART1) || UART_INTTimeoutStat(UART1))  //FIFO数据到达或者触发超时中断
	{
		if(UART_ReadByte(UART1, &chr) == 0)    //从UART1接收一字节数据到&chr且数据没有错误
		{
			if((UART1_RX_STA&0x8000)==0)//接收未完成
			{
				if(UART1_RX_STA&0x4000)//接收到了0x55
				{
					if(chr!=0xAA || UART_INTTimeoutStat(UART1))UART1_RX_STA=0;//接收错误或者触发超时中断,重新开始
					else 
					{
						UART1_RX_STA|=0x8000;  //接收完成了 
						flag1=1;
						if((len = UART1_GetChars(buffer)) != 0)
						{
							for(i = 0; i < len; i++)
							{
								UART_WriteByte(UART1, buffer[i]);
								while(UART_IsTXBusy(UART1));     //判断是否在发送数据
							}
						}
					}
				}
				else //还没收到0X55
				{	
					if(chr==0x055)UART1_RX_STA|=0x4000;
					else
					{
						UART1_RX_BUF[UART1_RX_STA&0X3FFF]=chr ;
						UART1_RX_STA++;
						if(UART1_RX_STA>(UART_REC_LEN-1))UART1_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}
		}
	}
}



