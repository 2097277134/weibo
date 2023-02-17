#ifndef __UART_H__
#define __UART_H__
#include "SWM181.h"
#include "mylib.h"

#define UART_REC_LEN	 128

extern u8  UART1_RX_BUF[UART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u8  UART2_RX_BUF[UART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
//extern u8  USART3_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符

extern u16 UART1_RX_STA;         		//接收状态标记	
extern u16 UART2_RX_STA;
//extern u16 USART3_RX_STA;
extern uint32_t UART_RXIndex;
extern uint8_t Rxd_End;
extern u8 flag1;         		//接收状态标记	
extern u8 flag2;         		//接收状态标记	
//extern u8 flag3;         		//接收状态标记	
#define UART_RX_LEN	 128
extern char UART_RXBuffer[UART_RX_LEN];
uint32_t UART1_GetChars(char *data);    //获取接收字符数
uint32_t UART2_GetChars(char *data);    //获取接收字符数
uint32_t UART3_GetChars(char *data);    //获取接收字符数

typedef struct {

	uint8_t  power;			//电容屏功率数据
	
	uint16_t  time;			//电容屏时间数据
	
	uint8_t  temperature;			//电容屏温度数据
	
	uint8_t  MicrowaveSwitch;			//微波开关
	
	uint8_t  WaterPumpSwitch;		//水泵开关
	

} CapacitiveScreenData;  //电容屏数据；

extern CapacitiveScreenData CapacitiveScreen;	//电容屏结构体定义，全局变量

void uart1_init(void);   //串口初始化
void uart2_init(void);   //串口初始化
int fputc(int ch, FILE *f);
void Data_Deal(void);    //数据处理
#endif //__UART_H__
