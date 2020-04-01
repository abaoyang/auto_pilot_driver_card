
/* Includes ------------------------------------------------------------------*/
#include "ssr.h"   

u8 beep_toggle = 0;
/*
 * 函数名：LED_Init
 * 描述  ：初始化PC3和PD6为输出口.并使能这两个口的时钟,LED IO初始化
 * 输入  ：无
 * 输出  ：无
 */	    
void SSR_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE, ENABLE);//使能PA,PC,PE端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//根据设定参数初始化PA.2
	GPIO_SetBits(GPIOA,GPIO_Pin_2);														//PA.2输出高 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//根据设定参数初始化PA.3
	GPIO_SetBits(GPIOA,GPIO_Pin_3);													//PA.3输出高 	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//根据设定参数初始化PA.5
	GPIO_SetBits(GPIOA,GPIO_Pin_5);														//PA.5输出高 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//根据设定参数初始化PA.6
	GPIO_SetBits(GPIOA,GPIO_Pin_6);													//PA.6输出高 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				     		//根据设定参数初始化PC.13
	GPIO_SetBits(GPIOC,GPIO_Pin_13);														//PC.13输出高 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				     		//根据设定参数初始化PC.14
	GPIO_SetBits(GPIOC,GPIO_Pin_14);													//PC.14输出高 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				     		//根据设定参数初始化PE.5
	GPIO_SetBits(GPIOE,GPIO_Pin_5);														//PE.5输出高 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				     		//根据设定参数初始化PE.6
	GPIO_SetBits(GPIOE,GPIO_Pin_6);													//PE.6输出高 
}

