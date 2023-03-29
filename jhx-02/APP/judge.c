#include "SWM181.h"
#include "mylib.h"

u8 Res3_1;  //取第4位命令位，01;02为正常，其他则报警
u8 Res4_1;  //取第5位命令位，设置功率数据高8位
u8 Res5_1;  //取第6位命令位，设置功率数据低8位

u8 Res2_2;  //命令数据 01水泵，02消融
u8 Res3_2;  //功率数据，取第四位命令位，功率数据 0-255 W
u8 Res4_2;  //时间数据，取第五位命令位，时间数据 0-20分钟
u8 Res5_2;  //温度数据，取第六位命令位，温度数据 0-100度

void extract(void)
{
//	Res3_2 =UART2_RX_BUF[3];  //取第四位命令位，功率数据 0-255 W
	Res4_2 =UART2_RX_BUF[4];  //取第五位命令位，时间数据 0-20分钟
	Res5_2 =UART2_RX_BUF[5];  //取第六位命令位，温度数据 0-100度
	
}

//UART1连接微波电源
void judge1(void)
{

	Res3_1 =UART1_RX_BUF[3]; //提取第四位数字，不为0,1则报警
	
	switch(Res3_1)
	{
//		case 0x01:  //设置功率
//		uart_1T3();  //将微波电源返回给串口一的数据转发给电容屏
	}
}

//UART2连接电容屏
void judge2(void)
{
	
  Res2_2=UART2_RX_BUF[2];  //取第三位命令位（01 or 02）01开水泵；02开微波
	
	switch(Res2_2)
	{
		case 0x01:
			//水泵开启。电机转速随着温度的改变而改变
		break;
		case 0x02:    //开始消融
			extract();  //提取相关参数，传输给PID控制程序
			//uart_2T1(); //串口2向串口1传输消息
		break;		
	}
}


