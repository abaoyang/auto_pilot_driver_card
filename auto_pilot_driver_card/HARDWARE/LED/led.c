/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * 作者    ：VeryAI Team
 * 库版本  ：ST3.5.0
 * 实验平台：VeryAI STM32开发板
 * 描述    ：LED驱动代码  
 *
 * 论坛    ：http://www.veryai.com
 * 淘宝    ：http://veryaishop.taobao.com
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
 * 函数名：LED_Init
 * 描述  ：初始化PC3和PD6为输出口.并使能这两个口的时钟,LED IO初始化
 * 输入  ：无
 * 输出  ：无
 */	    
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);//使能PC,PD端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				     		//根据设定参数初始化PC.3
	GPIO_SetBits(GPIOC,GPIO_Pin_3);														//PC.3输出高 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.12
	GPIO_SetBits(GPIOD,GPIO_Pin_12);													//PD.12输出高 	  
}

void LED_BOARD_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);//使能PC,PA,PD端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				     		//根据设定参数初始化PC.2
	GPIO_SetBits(GPIOC,GPIO_Pin_2);														//PC.2输出高 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				     		//根据设定参数初始化PC.3
	GPIO_SetBits(GPIOC,GPIO_Pin_3);														//PC.3输出高 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//根据设定参数初始化PA.11
	GPIO_SetBits(GPIOA,GPIO_Pin_11);														//PA.11输出高 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//根据设定参数初始化PA.12
	GPIO_SetBits(GPIOA,GPIO_Pin_12);														//PA.12输出高 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.3
	GPIO_SetBits(GPIOD,GPIO_Pin_3);														//PD.3输出高

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.4
	GPIO_SetBits(GPIOD,GPIO_Pin_4);														//PD.4输出高 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.5
	GPIO_SetBits(GPIOD,GPIO_Pin_5);														//PD.5输出高 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.6
	GPIO_SetBits(GPIOD,GPIO_Pin_6);														//PD.6输出高 
}
