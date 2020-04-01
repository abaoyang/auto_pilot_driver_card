/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * ����    ��VeryAI Team
 * ��汾  ��ST3.5.0
 * ʵ��ƽ̨��VeryAI STM32������
 * ����    : ������������  
 *
 * ��̳    ��http://www.veryai.com
 * �Ա�    ��http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "stm32f10x_usart.h"
	
#define USART_REC_LEN	10  	//�����������ֽ��� 10
#define EN_USART1_RX 	1			//ʹ�ܣ�1��/��ֹ��0������1����

#define RX_FRAME_HEADER	0x55
#define TX_FRAME_HEADER 0xAA
#define RX_CMD_LENGTH	6
 
	  	
extern u8  USART_RX_BUF[USART_REC_LEN];//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;    //����״̬���
extern u8 receive_one_payload;


//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
#endif


