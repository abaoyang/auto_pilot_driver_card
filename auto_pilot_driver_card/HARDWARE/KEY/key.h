/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * ����    ��VeryAI Team
 * ��汾  ��ST3.5.0
 * ʵ��ƽ̨��VeryAI STM32������
 * ����    ��KEY��������  
 *
 * ��̳    ��http://www.veryai.com
 * �Ա�    ��http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"	 

#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define KEY1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)
#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) 

#define IN_KEY1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define IN_KEY2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
#define IN_KEY3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
#define IN_KEY4 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)
#define IN_KEY5 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)
#define IN_KEY6 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define IN_KEY7 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define IN_KEY8 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)


#define KEY_DOWN	1
#define KEY_RIGHT	2
#define KEY_UP 		3

extern u8 key_up_pressed;
extern u8 key_down_pressed;
extern u8 key_right_pressed;

extern u8 in_key1_pressed;
extern u8 in_key2_pressed;
extern u8 in_key3_pressed;
extern u8 in_key4_pressed;
extern u8 in_key5_pressed;
extern u8 in_key6_pressed;
extern u8 in_key7_pressed;
extern u8 in_key8_pressed;

void KEY_Init(void);//IO��ʼ��

void IN_KEY_Init(void);//������·�尴����ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��
void key_scan(u8 mode);
void in_key_scan(u8 mode);//������·�尴��ɨ�躯��
#endif
