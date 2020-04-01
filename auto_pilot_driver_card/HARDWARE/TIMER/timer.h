/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * ����    ��VeryAI Team
 * ��汾  ��ST3.5.0
 * ʵ��ƽ̨��VeryAI STM32������
 * ����    ����ʱ����������  
 *
 * ��̳    ��http://www.veryai.com
 * �Ա�    ��http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "stm32f10x_tim.h"

#define GUA_TIMER3_PWM_STATUS_ON                0      
#define GUA_TIMER3_PWM_STATUS_OFF               1 

void TIM4_Int_Init(u16 arr,u16 psc);

void TIM3_PWM_Init(u16 arr,u16 psc);

void TIM6_Int_Init(u16 arr,u16 psc);

void GUA_Timer3_PWM_Status(u8 nGUA_Timer3_PWM_Status);    
void GUA_Timer3_PWM_SetDutyCycle(u8 GUA_TIMER3_PWM_PERIOD,u8 nGUA_Timer3_PWM_DutyCycle);
#endif
