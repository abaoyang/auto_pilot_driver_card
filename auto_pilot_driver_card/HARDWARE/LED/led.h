/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * ����    ��VeryAI Team
 * ��汾  ��ST3.5.0
 * ʵ��ƽ̨��VeryAI STM32������
 * ����    ��LED��������  
 *
 * ��̳    ��http://www.veryai.com
 * �Ա�    ��http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

extern u8 led1_toggle;
extern u8 led2_toggle;
extern u8 led3_toggle;
extern u8 led4_toggle;
extern u8 led5_toggle;
extern u8 led6_toggle;

#define LED0 PCout(3)
#define LED1 PDout(12)

#define LED0_BOARD PCout(2)
#define LED1_BOARD PCout(3)

#define LED1_CTL PDout(6)
#define LED2_CTL PDout(4)
#define LED3_CTL PAout(12)
#define LED4_CTL PDout(5)
#define LED5_CTL PDout(3)
#define LED6_CTL PAout(11)

void LED_Init(void);//��ʼ��
void LED_BOARD_Init(void);//��ʼ��������·��LED
	 				    
#endif
