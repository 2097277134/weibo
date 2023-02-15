#include "SWM181.h"
#include "mylib.h"

u8 SENDH_BUF[3]={0xA5,0X5A,0X01};  //数据头数组
u8 SENDE_BUF[2]={0x55,0XAA};  //数据尾数组

u8 SEND_TTSH_BUF[4]={0x5A,0xA5,0x05,0x82};  //向屏幕发送写温度的数据头（温度到屏幕数据头）
u8 SEND_Sidet_address[2]= {0x10,0x08};
u8 SEND_Rod_address[2]= {0x10,0x09};
u8 SEND_microwave_address[2]= {0x10,0x06};
u8 SEND_TSE_BUF[2]={0x0D,0x0A};  //向屏幕发送的数据尾

u8 SENDE_0[8]={0xA5,0X5A,0X01,0X01,0x00,0x00,0x55,0XAA};  //0W数组
u8 SENDE_100[8]={0xA5,0X5A,0X01,0X01,0x00,0x82,0x55,0XAA};  //130W数组
u8 SENDE_200[8]={0xA5,0X5A,0X01,0X01,0x00,0xf0,0x55,0XAA};  //250W数组

u8 SEND_set[1]={0x01};  
u8 SEND_stp[1]={0x02}; 

u8 t,m,len;
u8 low_p[1]={1},hjght_p[1]={1};



/*发送底层*/
void USART_SendData(UART_TypeDef * UARTx, uint8_t Buf[])
{
	uint16_t i = 0;
  
	__disable_irq();    //关闭IRQ中断
  
	for(i = 0; i < 8; i++)
	{
		UART_WriteByte(UARTx, Buf[i]);
		while(UART_IsTXBusy(UARTx));     //判断是否在发送数据
	}
  
  __enable_irq();     //开启IRQ中断
}

/*设置模拟量控制变量*/
u16 dacval;


void select(void)
{
	dacval=PID_realize();
	low_p[0]=dacval&0xff;
	hjght_p[0]=dacval>>8;
}

void send_0(void)
{
	USART_SendData(UART2,SENDE_0);
}

void send_100(void)
{
	USART_SendData(UART2,SENDE_100);
}

void send_200(void)
{
	USART_SendData(UART2,SENDE_200);
}

//MCU向电容屏(串口2)发送温度数据
void MCU_t_screen(void)
{
	extern double TEMP;						//储存实际实时温度
	
	u8 hjght_t[1],low_t[1];
	
	int TEMP_10=TEMP*10;
	
	hjght_t[0] = TEMP_10>>8;
	low_t[0]=TEMP_10&0xff;
	
	//发送前缀一个0x2B
	USART_SendData(UART2,SEND_TTSH_BUF);
	USART_SendData(UART2,SEND_Rod_address);
	USART_SendData(UART2,hjght_t);
	USART_SendData(UART2,low_t);
	USART_SendData(UART2,SEND_TTSH_BUF);
	USART_SendData(UART2,SEND_Sidet_address);
	USART_SendData(UART2,hjght_t);
	USART_SendData(UART2,low_t);
}



void uart_1()  //MCU向串口一发送温度数据
{
	//发送前缀三个0x5A,0XA5,0X07
		USART_SendData(UART2,SENDH_BUF);
	//发送功能位01设置 or 02查询
		USART_SendData(UART2,SEND_set);
	//发送发送数据高八位
		USART_SendData(UART2,hjght_p);
	//发送发送数据低八位
         USART_SendData(UART2,low_p);      //向串口1发送功率数据
	//发送数据尾
		USART_SendData(UART2, SENDE_BUF);         //向串口1发送数据
}





