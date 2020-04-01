/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * ����    ��VeryAI Team
 * ��汾  ��ST3.5.0
 * ʵ��ƽ̨��VeryAI STM32������
 * ����    ���������Ź�����  
 *
 * ��̳    ��http://www.veryai.com
 * �Ա�    ��http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "wdg.h"
#include "stm32f10x_iwdg.h"

/*
 * ��������IWDG_Init
 * ����  ����ʼ���������Ź�
 * ����  ��prer:��Ƶ��:0~7(ֻ�е�3λ��Ч!),��Ƶ����=4*2^prer.�����ֵֻ����256!
					 rlr:��װ�ؼĴ���ֵ:��11λ��Ч.ʱ�����(���):Tout=((4*2^prer)*rlr)/40 (ms).
 * ���  ����
 */
void IWDG_Init(u8 prer,u16 rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����	
	IWDG_SetPrescaler(prer);  //����IWDGԤ��Ƶֵ:����IWDGԤ��ƵֵΪ64
	IWDG_SetReload(rlr);  		//����IWDG��װ��ֵ
	IWDG_ReloadCounter();  		//����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
	IWDG_Enable();  					//ʹ��IWDG
}

/*
 * ��������IWDG_Feed
 * ����  ��ι�������Ź�
 * ����  ����
 * ���  ����
 */
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();			//reload										   
}
