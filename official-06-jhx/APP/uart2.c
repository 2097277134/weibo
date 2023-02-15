#include "SWM181.h"
#include "mylib.h"




CapacitiveScreenData CapacitiveScreen;


uint8_t Rxd_End = 0;

char UART_RXBuffer[UART_RX_LEN] = {0};

uint32_t UART_RXIndex=0;
void uart2_init(void)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTB, PIN4, FUNMUX_UART2_RXD, 1);	//GPIOB.4配置为UART2输入引脚
	PORT_Init(PORTB, PIN5, FUNMUX_UART2_TXD, 0);	//GPIOB.5配置为UART2输出引脚
 	
 	UART_initStruct.Baudrate = 115200;
	UART_initStruct.DataBits = UART_DATA_8BIT;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOP_1BIT;
	UART_initStruct.RXThreshold = 7;
	UART_initStruct.RXThresholdIEn = 1;
	UART_initStruct.TXThreshold = 3;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;		//5个字符时间内未接收到新的数据则触发超时中断
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

void IRQ0_Handler(void)   //空闲中断
{
uint32_t chr;
	
	//如果是FIFO满中断，则取数据的时候不取完，始终在FIFO里面留一个，目的是触发超时中断
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
	
	//如果是超时中断产生了，则一包数据已经接收完了
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
		
//		//如果是21个字节，那么是正常的接收
//		if(UART_RXIndex == 21)
//		{
//			Rxd_End = 1;
//		}
//		//如果是5个字节，那么应该是自己发送的数据
//		else if(UART_RXIndex == 5)
//		{
//			UART_RXIndex = 0;
//		}
//		//如果是26个字节，那么应该是自己发的数据跟设备发的数据粘包了
//		else if(UART_RXIndex == 26)
//		{
//			Rxd_End = 1;
//		}		
//		//异常情况，清零指针
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
	
	//如果Rxd_End == 1 则已经正常接收了一包数据了
	if(Rxd_End == 1)
	{
		//如果是9个字节，正常数据
		if((UART_RXIndex == 9)&&(UART_RXBuffer[0]==0x5A)&&(UART_RXBuffer[1]==0xA5))   //设置串口接受标志位防止在消融时改变参数
		{
			//放入你的处理代码
			if(UART_RXBuffer[5]==0x00){		//功率接受需x10
			CapacitiveScreen.power=UART_RXBuffer[8]*10;
			}
			if (UART_RXBuffer[5]==0x01){  //时间接受需x10
			CapacitiveScreen.time=UART_RXBuffer[8]*10;
			}
			if (UART_RXBuffer[5]==0x03){		//温度=40+4x
			CapacitiveScreen.temperature=UART_RXBuffer[8]*4+40;
			}
			if (UART_RXBuffer[5]==0x06){		//微波开关		UART_RXBuffer[8]==0x00关 UART_RXBuffer[8]==0x01开
				CapacitiveScreen.MicrowaveSwitch=UART_RXBuffer[8];
				}
			if (UART_RXBuffer[5]==0x07){		//水泵开关		UART_RXBuffer[8]==0x00关 UART_RXBuffer【8]==0x01开
			CapacitiveScreen.WaterPumpSwitch=UART_RXBuffer[8];
			}
		
	
			//回发给设备
			//Data_Send();
		}
		//如果是自己的数据粘包了
		else if(UART_RXIndex == 26)
		{
			//把数据转移一下
			for(i = 0; i < 21; i++)
			{
				UART_RXBuffer[i] = UART_RXBuffer[i + 5];
			}
			
			//放入你的处理代码
			
			
			//回发给设备
			//Data_Send();
		}
		
		//清零变量，准备下一次接收
		UART_RXIndex = 0;
		Rxd_End = 0;
		
	}
}
