/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * 作者    ：VeryAI Team
 * 库版本  ：ST3.5.0
 * 实验平台：VeryAI STM32开发板
 * 描述    : 串口驱动代码  
 *
 * 论坛    ：http://www.veryai.com
 * 淘宝    ：http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "stm32f10x_usart.h"
	
#define USART_REC_LEN	10  	//定义最大接收字节数 10
#define EN_USART1_RX 	1			//使能（1）/禁止（0）串口1接收

#define RX_FRAME_HEADER	0x55
#define TX_FRAME_HEADER 0xAA
#define RX_CMD_LENGTH	6
 
	  	
extern u8  USART_RX_BUF[USART_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;    //接收状态标记
extern u8 receive_one_payload;


//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
#endif


