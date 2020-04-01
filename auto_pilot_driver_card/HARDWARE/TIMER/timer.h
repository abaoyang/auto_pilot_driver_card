/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * 作者    ：VeryAI Team
 * 库版本  ：ST3.5.0
 * 实验平台：VeryAI STM32开发板
 * 描述    ：定时器驱动代码  
 *
 * 论坛    ：http://www.veryai.com
 * 淘宝    ：http://veryaishop.taobao.com
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
