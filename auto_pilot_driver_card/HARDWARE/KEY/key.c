/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * 作者    ：VeryAI Team
 * 库版本  ：ST3.5.0
 * 实验平台：VeryAI STM32开发板
 * 描述    ：KEY驱动代码  
 *
 * 论坛    ：http://www.veryai.com
 * 淘宝    ：http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

u8 key_up_pressed = 0;
u8 key_down_pressed = 0;
u8 key_right_pressed = 0;

u8 in_key1_pressed = 0;
u8 in_key2_pressed = 0;
u8 in_key3_pressed = 0;
u8 in_key4_pressed = 0;
u8 in_key5_pressed = 0;
u8 in_key6_pressed = 0;
u8 in_key7_pressed = 0;
u8 in_key8_pressed = 0;

/*
 * 函数名：KEY_Init
 * 描述  ：按键初始化函数
 * 输入  ：无
 * 输出  ：无
 */	 
void KEY_Init(void) 														//IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//使能PORTA,PORTC,PORTD时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);				//初始化GPIO

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//设置成上拉输入
 	GPIO_Init(GPIOD, &GPIO_InitStructure);				//初始化GPIO
	
	//初始化 WK_UP-->GPIOA.0	下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);				//初始化GPIOA.0
}

/*
 * 函数名：IN_KEY_Init
 * 描述  ：实际工作电路板按键初始化函数
 * 输入  ：无
 * 输出  ：无
 */	 
void IN_KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTB,PORTE时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//设置成浮空输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);				//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//设置成浮空输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);				//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//设置成浮空输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);				//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//设置成浮空输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//设置成浮空输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//设置成浮空输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//设置成浮空输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//设置成浮空输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				//初始化GPIO
}


/*
 * 函数名：KEY_Init
 * 描述  ：按键处理函数
					 0，没有任何按键按下
					 1，KEY0按下
					 2，KEY1按下
					 3，KEY2按下 WK_UP
					 注意此函数有响应优先级,KEY2>KEY0>KEY1
 * 输入  ：mode:0,不支持连续按;1,支持连续按;
 * 输出  ：返回按键值
 */	 
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;														//按键按松开标志
	if(mode)key_up=1;  														//支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
	{
		delay_ms(10);																//去抖动 
		key_up=0;
		if(KEY2==1) return KEY_UP;
		else if(KEY0==0)return KEY_DOWN;
		else if(KEY1==0)return KEY_RIGHT;
	}else if(KEY2==0&&KEY0==1&&KEY1==1)key_up=1; 	// 无按键按下
 	return 0;																			
}

void key_scan(u8 mode)
{
	static u8 key_up=1;														//按键按松开标志
	if(mode)key_up=1;  														//支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
	{
		delay_ms(5);																//去抖动 
		key_up=0;
		if(KEY2==1)key_up_pressed = 1;
		else if(KEY0==0)key_down_pressed = 1;
		else if(KEY1==0)key_right_pressed = 1;
	}else if(KEY2==0&&KEY0==1&&KEY1==1)key_up=1; 	// 无按键按下 			
}

void in_key_scan(u8 mode)
{
	static u8 key_up=1;														//按键按松开标志
// 	if(IN_KEY1 == 0)
// 	{
// 		delay_ms(5);
// 		if(IN_KEY1 == 0)
// 			{
// 				in_key1_pressed=1;
// 			}
// 			else in_key1_pressed=0;
// 	}
// 	else in_key1_pressed=0;
	if(mode)key_up=1;  														//支持连按		  
	if(key_up&&(IN_KEY2==0||IN_KEY3==0||IN_KEY4==0||IN_KEY5==0||IN_KEY6==0||IN_KEY7==0||IN_KEY8==0))
	{
		delay_ms(5);																//去抖动 
		key_up=0;
//		if(IN_KEY1==0)in_key1_pressed = 1;
	  if(IN_KEY2==0)in_key2_pressed = 1;
		if(IN_KEY3==0)in_key3_pressed = 1;
		if(IN_KEY4==0)in_key4_pressed = 1;
 		if(IN_KEY5==0)in_key5_pressed = 1;
		if(IN_KEY6==0)in_key6_pressed = 1;
		if(IN_KEY7==0)in_key7_pressed = 1;
		if(IN_KEY8==0)in_key8_pressed = 1;

	}else if(IN_KEY2==1&&IN_KEY3==1&&IN_KEY4==1&&IN_KEY5==1&&IN_KEY6==1&&IN_KEY7==1&&IN_KEY8==1)key_up=1; 	// 无按键按下 			
}
