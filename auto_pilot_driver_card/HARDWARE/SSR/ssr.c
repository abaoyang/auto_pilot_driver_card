
/* Includes ------------------------------------------------------------------*/
#include "ssr.h"   

u8 beep_toggle = 0;
/*
 * ��������LED_Init
 * ����  ����ʼ��PC3��PD6Ϊ�����.��ʹ���������ڵ�ʱ��,LED IO��ʼ��
 * ����  ����
 * ���  ����
 */	    
void SSR_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE, ENABLE);//ʹ��PA,PC,PE�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PA.2
	GPIO_SetBits(GPIOA,GPIO_Pin_2);														//PA.2����� 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PA.3
	GPIO_SetBits(GPIOA,GPIO_Pin_3);													//PA.3����� 	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PA.5
	GPIO_SetBits(GPIOA,GPIO_Pin_5);														//PA.5����� 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PA.6
	GPIO_SetBits(GPIOA,GPIO_Pin_6);													//PA.6����� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PC.13
	GPIO_SetBits(GPIOC,GPIO_Pin_13);														//PC.13����� 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PC.14
	GPIO_SetBits(GPIOC,GPIO_Pin_14);													//PC.14����� 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PE.5
	GPIO_SetBits(GPIOE,GPIO_Pin_5);														//PE.5����� 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PE.6
	GPIO_SetBits(GPIOE,GPIO_Pin_6);													//PE.6����� 
}

