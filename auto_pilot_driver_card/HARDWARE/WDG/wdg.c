/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * 作者    ：VeryAI Team
 * 库版本  ：ST3.5.0
 * 实验平台：VeryAI STM32开发板
 * 描述    ：独立看门狗代码  
 *
 * 论坛    ：http://www.veryai.com
 * 淘宝    ：http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "wdg.h"
#include "stm32f10x_iwdg.h"

/*
 * 函数名：IWDG_Init
 * 描述  ：初始化独立看门狗
 * 输入  ：prer:分频数:0~7(只有低3位有效!),分频因子=4*2^prer.但最大值只能是256!
					 rlr:重装载寄存器值:低11位有效.时间计算(大概):Tout=((4*2^prer)*rlr)/40 (ms).
 * 输出  ：无
 */
void IWDG_Init(u8 prer,u16 rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //使能对寄存器IWDG_PR和IWDG_RLR的写操作	
	IWDG_SetPrescaler(prer);  //设置IWDG预分频值:设置IWDG预分频值为64
	IWDG_SetReload(rlr);  		//设置IWDG重装载值
	IWDG_ReloadCounter();  		//按照IWDG重装载寄存器的值重装载IWDG计数器
	IWDG_Enable();  					//使能IWDG
}

/*
 * 函数名：IWDG_Feed
 * 描述  ：喂独立看门狗
 * 输入  ：无
 * 输出  ：无
 */
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();			//reload										   
}
