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
#include "led.h"   

u8 led1_toggle=0;
u8 led2_toggle=0;
u8 led3_toggle=0;
u8 led4_toggle=0;
u8 led5_toggle=0;
u8 led6_toggle=0;


/*
 * ��������LED_Init
 * ����  ����ʼ��PC3��PD6Ϊ�����.��ʹ���������ڵ�ʱ��,LED IO��ʼ��
 * ����  ����
 * ���  ����
 */	    
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);//ʹ��PC,PD�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PC.3
	GPIO_SetBits(GPIOC,GPIO_Pin_3);														//PC.3����� 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PD.12
	GPIO_SetBits(GPIOD,GPIO_Pin_12);													//PD.12����� 	  
}

void LED_BOARD_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);//ʹ��PC,PA,PD�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PC.2
	GPIO_SetBits(GPIOC,GPIO_Pin_2);														//PC.2����� 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PC.3
	GPIO_SetBits(GPIOC,GPIO_Pin_3);														//PC.3����� 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PA.11
	GPIO_SetBits(GPIOA,GPIO_Pin_11);														//PA.11����� 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PA.12
	GPIO_SetBits(GPIOA,GPIO_Pin_12);														//PA.12����� 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PD.3
	GPIO_SetBits(GPIOD,GPIO_Pin_3);														//PD.3�����

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PD.4
	GPIO_SetBits(GPIOD,GPIO_Pin_4);														//PD.4����� 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PD.5
	GPIO_SetBits(GPIOD,GPIO_Pin_5);														//PD.5����� 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PD.6
	GPIO_SetBits(GPIOD,GPIO_Pin_6);														//PD.6����� 
}
