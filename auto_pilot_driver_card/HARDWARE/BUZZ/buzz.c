
/* Includes ------------------------------------------------------------------*/
#include "buzz.h"   

/*
 * 函数名：BUZZ_Init
 * 描述  ：初始化PE13为输出口.并使能这个口的时钟,BUZZ IO初始化
 * 输入  ：无
 * 输出  ：无
 */	    
void BUZZ_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//使能PE端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				     		//根据设定参数初始化PE.13
	GPIO_ResetBits(GPIOE,GPIO_Pin_13);														//PE.13输出低	  
}

