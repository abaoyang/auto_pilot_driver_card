 /******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * 作者    ：VeryAI Team
 * 库版本  ：ST3.5.0
 * 实验平台：VeryAI STM32开发板
 * 描述    ：DAC驱动代码  
 *
 * 论坛    ：http://www.veryai.com
 * 淘宝    ：http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	
#include "stm32f10x_dac.h"

void Dac1_Init(void);//回环模式初始化		 	 
void Dac1_Set_Vol(u16 vol);
#endif
