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
#include "timer.h"
#include "led.h"	
#include "key.h"
#include "ssr.h"

/*
 * 函数名：TIM4_Int_Init
 * 描述  ：通用定时器4中断初始化，这里时钟选择为APB1的2倍，而APB1为36M
 * 输入  ：arr：自动重装值。
					 psc：时钟预分频数
 * 输出  ：无
 */	 
void TIM4_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	
	//定时器TIM4初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  //使能TIMx					 
}


void TIM4_IRQHandler(void)   //TIM4中断
{
	
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
//		key_scan(0);
		in_key_scan(0);
	}
// 	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
// 	{
// 		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
// 		LED1=!LED1;
// 	}
}




void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	    
  //GPIO_AFIODeInit();
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3 , ENABLE);
	//设置该引脚为复用输出功能,输出TIM3 CH3的PWM脉冲波形	GPIOB.0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM4_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
  //初始化TIM3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	//使能定时器3时钟
	 //TIM_DeInit(TIM3);
	//TIM_InternalClockConfig(TIM3);


	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//TIM_OCStructInit(&TIM_OCInitStructure);
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC1

	GUA_Timer3_PWM_Status(GUA_TIMER3_PWM_STATUS_OFF); 
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
  TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
	//TIM_CtrlPWMOutputs(TIM3, ENABLE);
}


void GUA_Timer3_PWM_Status(u8 nGUA_Timer3_PWM_Status)    
{    
     
  if(nGUA_Timer3_PWM_Status == GUA_TIMER3_PWM_STATUS_ON)    
  {     
        TIM_SetCounter(TIM3, 0);          
        TIM_CCxCmd(TIM3, TIM_Channel_3, TIM_CCx_Enable);          
  }    
   
  else    
  {    
        TIM_CCxCmd(TIM3, TIM_Channel_3, TIM_CCx_Disable);                 
  }    
}    

void GUA_Timer3_PWM_SetDutyCycle(u8 GUA_TIMER3_PWM_PERIOD,u8 nGUA_Timer3_PWM_DutyCycle)    
{    
  TIM_SetCompare3(TIM3, GUA_TIMER3_PWM_PERIOD*nGUA_Timer3_PWM_DutyCycle/100);     
}   

void TIM6_Int_Init(u16 arr,u16 psc)
{	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig( TIM6,TIM_IT_Update|TIM_IT_Trigger,ENABLE);//使能定时器6更新触发中断
 
	TIM_Cmd(TIM6, ENABLE);  //使能TIMx外设
 	
  NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 								 
}

void TIM6_IRQHandler(void)
{ 	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{


		if (led1_toggle == 1)	LED1_CTL = !LED1_CTL;
		if (led2_toggle == 1)	LED2_CTL = !LED2_CTL;
		if (led3_toggle == 1)	LED3_CTL = !LED3_CTL;
		if (led4_toggle == 1)	LED4_CTL = !LED4_CTL;
		if (led5_toggle == 1)	LED5_CTL = !LED5_CTL;
		if (led6_toggle == 1)	LED6_CTL = !LED6_CTL;
		if (beep_toggle == 1)	SSR_BEEP_CTL = !SSR_BEEP_CTL;

//		LED1=!LED1;	
		
//			LED0=!LED0;
	} 
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
				    		  			    	    
}

