
/* Includes ------------------------------------------------------------------*/
#include "buzz.h"   

/*
 * ��������BUZZ_Init
 * ����  ����ʼ��PE13Ϊ�����.��ʹ������ڵ�ʱ��,BUZZ IO��ʼ��
 * ����  ����
 * ���  ����
 */	    
void BUZZ_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//ʹ��PE�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;								//�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				     		//�����趨������ʼ��PE.13
	GPIO_ResetBits(GPIOE,GPIO_Pin_13);														//PE.13�����	  
}

