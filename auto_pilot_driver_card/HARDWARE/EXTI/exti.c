
/* Includes ------------------------------------------------------------------*/
#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
 
 u8 turn_to_auto = 0;
 u8 turn_to_manual = 0;
/*
 * 函数名：EXTIX_Init
 * 描述  ：外部中断0初始化
 * 输入  ：无
 * 输出  ：无
 */	  
void EXTIX_Init(void)
{
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

    //KEY_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);							//使能复用功能时钟

		//GPIOB.5 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;	//IN_KEY1
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 																//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;						//使能按键KEY1,KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;						//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;									//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  														//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}


/*
 * 函数名：EXTI15_10_IRQHandler
 * 描述  ：外部中断15-10服务程序
 * 输入  ：无
 * 输出  ：无
 */	
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(EXTI_GetITStatus(EXTI_Line5)==SET)//是5线的中断
	{
		if(IN_KEY1 == 0)	 //按键IN_KEY切换到自动模式
		{				 
			turn_to_auto = 1;
			//LED1_BOARD = !LED1_BOARD;
		}	
		if(IN_KEY1 == 1)
		{
			turn_to_manual = 1;
			//LED1_BOARD = !LED1_BOARD;
		}
		EXTI_ClearITPendingBit(EXTI_Line5);  //清除LINE6上的中断标志位
  } 
  
}
