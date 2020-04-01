
/* Includes ------------------------------------------------------------------*/
#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
 
 u8 turn_to_auto = 0;
 u8 turn_to_manual = 0;
/*
 * ��������EXTIX_Init
 * ����  ���ⲿ�ж�0��ʼ��
 * ����  ����
 * ���  ����
 */	  
void EXTIX_Init(void)
{
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

    //KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);							//ʹ�ܸ��ù���ʱ��

		//GPIOB.5 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;	//IN_KEY1
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 																//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;						//ʹ�ܰ���KEY1,KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;						//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;									//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  														//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}


/*
 * ��������EXTI15_10_IRQHandler
 * ����  ���ⲿ�ж�15-10�������
 * ����  ����
 * ���  ����
 */	
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);//����
	if(EXTI_GetITStatus(EXTI_Line5)==SET)//��5�ߵ��ж�
	{
		if(IN_KEY1 == 0)	 //����IN_KEY�л����Զ�ģʽ
		{				 
			turn_to_auto = 1;
			//LED1_BOARD = !LED1_BOARD;
		}	
		if(IN_KEY1 == 1)
		{
			turn_to_manual = 1;
			//LED1_BOARD = !LED1_BOARD;
		}
		EXTI_ClearITPendingBit(EXTI_Line5);  //���LINE6�ϵ��жϱ�־λ
  } 
  
}
