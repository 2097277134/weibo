#ifndef __UART_H__
#define __UART_H__
#include "SWM181.h"
#include "mylib.h"

#define UART_REC_LEN	 128

extern u8  UART1_RX_BUF[UART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  UART2_RX_BUF[UART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
//extern u8  USART3_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�

extern u16 UART1_RX_STA;         		//����״̬���	
extern u16 UART2_RX_STA;
//extern u16 USART3_RX_STA;

extern u8 flag1;         		//����״̬���	
extern u8 flag2;         		//����״̬���	
//extern u8 flag3;         		//����״̬���	

uint32_t UART1_GetChars(char *data);    //��ȡ�����ַ���
uint32_t UART2_GetChars(char *data);    //��ȡ�����ַ���
uint32_t UART3_GetChars(char *data);    //��ȡ�����ַ���

void uart1_init(void);   //���ڳ�ʼ��
void uart2_init(void);   //���ڳ�ʼ��
int fputc(int ch, FILE *f);
#endif //__UART_H__
