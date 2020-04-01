/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * 作者    ：VeryAI Team
 * 库版本  ：ST3.5.0
 * 实验平台：VeryAI STM32开发板
 * 描述    ：串口实验代码  
 *
 * 论坛    ：http://www.veryai.com
 * 淘宝    ：http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "ssr.h"
#include "adc.h"
#include "buzz.h"
#include "dac.h"
#include "max5395.h"
#include "exti.h"

/*
 * 函数名：main
 * 描述  ：主函数,实现了简单环回功能。实验过程：使用串口软件SSCOM3.3 设置好了发送新行，我们在发送区输入你想要发送的文字，然后单击发送,
					 STM32会发出刚刚接收到的串口数据，SSCOM3.3接收到STM32发送的串口数据，并显示在窗口上。
 * 输入  ：无
 * 输出  ：无
 */
 
//#define CELL_TEST
#define USE_DIGIPOT
u8 op_mode = 1; 					//0代表自动驾驶模式，1代表人工模式，由KEY0输入切换，开机启动默认手动模式
u8 payload_seq = 0; 		//包序列号
u8 payload_cmd1 = 0;		//接收命令字1
u8 payload_cmd2 = 0;		//接收命令字2
u8 payload_cmd3 = 0;		//接收命令字3

u32 bound = 115200; 		//串口波特率
u16 tim3_arr = 0;			//timer3预装载值
// u16 tim3_psc = 7199;		//timer3分频系数
// u16 tim4_arr = 699;			//timer4预装载值
// u16 tim4_psc = 7199;		//timer4分频系数
// u16 tim6_arr = 10000;			//timer4预装载值
// u16 tim6_psc = 7199;		//timer4分频系数


u8 payload_feedback1 = 0;  		//串口返回命令字1
u8 payload_feedback2 = 0;			//串口返回命令字2
u8 payload_feedback3 = 0;			//串口返回命令字3
u8 tx_parity = 0;							//串口返回XOR校验
 
int main(void)
{	
	u16 adc_result;
	float temp;
	delay_init();	    	 			//延时函数初始化	  
	NVIC_Configuration(); 	 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(bound);	 				//串口初始化为9600
 	LED_BOARD_Init();					//初始化工作电路板LED端口
	IN_KEY_Init();						//初始化工作电路板按键
	//EXTIX_Init();							//初始化外部中断
	SSR_Init();								//初始化工作电路板SSR端口	
	TIM3_PWM_Init(19999,71);	//用来产生PWM信号
	TIM_SetCompare3(TIM3,18499);	//初始化使舵机处于中位，产生1.5ms高电平，50hz信号
	Adc_Battery_Init();
	Adc_Angle_Init();
	Dac1_Init();
	BUZZ_Init();
	TIM4_Int_Init(699,7199);
	MAX5395_Init();
	MAX5395_Write_CMD(RST_CMD);
	TIM6_Int_Init(10000,7199);//10Khz计数频率,1秒钟中断			            
	                                     
	GUA_Timer3_PWM_Status(GUA_TIMER3_PWM_STATUS_ON);  

 	while(1)
	{
#ifdef 	CELL_TEST	
// 		MAX5395_Write_WIPER_Reg(0x55);
// 		temp = MAX5395_Read_WIPER_Reg();
// 		printf("received payload_seq is %x \r\n",temp);
// 		delay_ms(100);
// 			delay_ms(1000);
// 		
// 			temp = Get_Adc_Battery_Average(ADC_Channel_1,10);
// 		  printf("received Get_Adc_Battery_Average is %x \r\n",temp);
// 			printf("received Get_Adc_Battery_Average is %d \r\n",temp);
// 			temp = Get_Adc_Angle_Average(ADC_Channel_0,10);
// 			printf("received Get_Adc_Angle_Average is %x \r\n",temp);
// 			printf("received Get_Adc_Angle_Average is %d \r\n",temp);
// 		  delay_ms(1000);


#else		
		if (receive_one_payload == 1)				//确认收到一包数据
		{
			receive_one_payload = 0;					//串口继续接收数据
			payload_seq = USART_RX_BUF[1];		//包序号
			payload_cmd1 = USART_RX_BUF[2];		//工控机命令，指示速度
			payload_cmd2 = USART_RX_BUF[3];		//工控机命令，转角数据
			payload_cmd3 = USART_RX_BUF[4];		//工控机命令，喇叭和灯
			
// 				printf("\r\n received payload_seq is %x \r\n",payload_seq);
// 				printf("received payload_cmd1 is %x \r\n",payload_cmd1);
// 				printf("received payload_cmd2 is %x \r\n",payload_cmd2);
// 				printf("received payload_cmd3 is %x \r\n",payload_cmd3);
			//处理收到的数据。
			if(op_mode == 0)		 //如果处于自动驾驶模式，则根据串口收到的数据控制舵机，喇叭，灯，数字电位器。
			{					
#ifdef	USE_DIGIPOT	
				if(((payload_cmd1&0x80)>>7)==1 &&  (payload_cmd1&0x7f)<=100)		//输入速度值为负数，则控制车倒行
				{
					SSR_BACK1_CTL = 1;
					SSR_BACK2_CTL = 1;
					SSR_BACK3_CTL	= 1;
					MAX5395_Write_WIPER_Reg(payload_cmd1&0x7f);
				}
				if(((payload_cmd1&0x80)>>7)==0 &&  (payload_cmd1&0x7f)<=100)		//输入速度值为正数，则控制车前行
				{
					SSR_BACK1_CTL = 0;
					SSR_BACK2_CTL = 0;
					SSR_BACK3_CTL	= 0;
					MAX5395_Write_WIPER_Reg(payload_cmd1&0x7f);
				}			
				
#else
				DAC_SetChannel1Data(DAC_Align_12b_R, payload_cmd1); 	//速度写入DAC（需具体实现，此处只代表逻辑）
#endif	
				if(((payload_cmd2&0x80)>>7)==1 &&  (payload_cmd2&0x7f)<=100)						//输入舵机转角为负值
				{
					tim3_arr = 18499+(payload_cmd2&0x7f)*10; 								//18499代表中位数，产生1.5ms，payload_cmd2为-100时，tim3_arr为19499，产生0.5ms
					TIM_SetCompare3(TIM3,tim3_arr);	
				}
				if(((payload_cmd2&0x80)>>7) ==0 &&  (payload_cmd2&0x7f)<=100)						//输入舵机转角为正值
				{
					tim3_arr = 18499 - (payload_cmd2&0x7f)*10; 						//18499代表中位数，产生1.5ms，payload_cmd2为+100时，tim3_arr为17499，产生2.5ms
					TIM_SetCompare3(TIM3,tim3_arr);	
				}   			
				
//				TIM_SetCompare3(TIM3,19000);			//将转角数据写入PMW CCR计算器（需具体实现，此处只代表逻辑）
				if((payload_cmd3&0x40)>>6) beep_toggle = 1;	//响喇叭
				else beep_toggle = 0;												//关喇叭
				if((payload_cmd3&0x20)>>5) led6_toggle = 1;	//LED闪烁
				else led6_toggle = 0;												//LED停止闪烁
				if((payload_cmd3&0x10)>>4) led5_toggle = 1;	//LED闪烁
				else led5_toggle = 0;												//LED停止闪烁
				if((payload_cmd3&0x08)>>3) led4_toggle = 1;	//LED闪烁
				else led4_toggle = 0;												//LED停止闪烁
				if((payload_cmd3&0x04)>>2) led3_toggle = 1;	//LED闪烁
				else led3_toggle = 0;												//LED停止闪烁
				if((payload_cmd3&0x02)>>1) led2_toggle = 1;	//LED闪烁
				else led2_toggle = 0;												//LED停止闪烁
				if(payload_cmd3&0x01) led1_toggle = 1;	//LED闪烁
				else led1_toggle = 0;												//LED停止闪烁
			}
			//准备返回数据
			if((IN_KEY1==0)) 
			{
				payload_feedback1 = payload_feedback1 | 0x01;		//按键1输入为低电平时，模式切换到自动模式，返回按键被按下，即位置1
				op_mode = 0;																		//当按键一被按下，操作模式改为手动模式，此处需实现具体切换
//					in_key1_pressed = 0;														//取消已经按下的记录
			}
			else 
			{
				payload_feedback1 = payload_feedback1&(~0x01);
				op_mode = 1;
			}
			if((in_key2_pressed ==1)&&(IN_KEY2==1)) 
			{
				payload_feedback1 = payload_feedback1 | 0x02;
				
				in_key2_pressed = 0;
			}
			else payload_feedback1 = payload_feedback1&(~0x02);
			
			if((in_key3_pressed ==1)&&(IN_KEY3==1)) 
			{
				payload_feedback1 = payload_feedback1 | 0x04;
				
				in_key3_pressed = 0;
			}
			else payload_feedback1 = payload_feedback1&(~0x04);	
			
			if((in_key4_pressed ==1)&&(IN_KEY4==1)) 
			{
				payload_feedback1 = payload_feedback1 | 0x08;
				
				in_key4_pressed = 0;
			}
			else payload_feedback1 = payload_feedback1&(~0x08);
			
			if((in_key5_pressed ==1)&&(IN_KEY5==1)) 
			{
				payload_feedback1 = payload_feedback1 | 0x10;
				
				in_key5_pressed = 0;
			}
			else payload_feedback1 = payload_feedback1&(~0x10);
			
			if((in_key6_pressed ==1)&&(IN_KEY6==1)) 
			{
				payload_feedback1 = payload_feedback1 | 0x20;
				
				in_key6_pressed = 0;
			}
			else payload_feedback1 = payload_feedback1&(~0x20);
			
			if((in_key7_pressed ==1)&&(IN_KEY7==1)) 
			{
				payload_feedback1 = payload_feedback1 | 0x40;
				
				in_key7_pressed = 0;
			}
			else payload_feedback1 = payload_feedback1&(~0x40);
			
			if((in_key8_pressed ==1)&&(IN_KEY8==1)) 
			{
				payload_feedback1 = payload_feedback1 | 0x80;
				
				in_key8_pressed = 0;
			}
			else payload_feedback1 = payload_feedback1&(~0x80);
			
			adc_result = Get_Adc_Battery_Average(ADC_Channel_1,10);
			temp = (float)adc_result*(3.3/4096);		//结果转化为V值
			
			if(temp<=2.1)	payload_feedback2 = 0;
			if(temp>=2.94)	payload_feedback2 = 100;
			if(temp>2.1 && temp<2.94)	payload_feedback2 =(u8)(100/((1+(2.94-temp)/(temp-2.1))));		//2.94 = 4.2*7/10;  2.1=3*7/10，外部电池分压输入ADC的最高和最低电压值
				
			
			payload_feedback3 = 50;		//水位数据，暂时传固定数值50
			tx_parity = TX_FRAME_HEADER^payload_seq^payload_feedback1^payload_feedback2^payload_feedback3;
			
//反馈数据到工控机				
		USART_SendData(USART1,TX_FRAME_HEADER);
		delay_us(100);	
		USART_SendData(USART1,payload_seq);
		delay_us(100);
		USART_SendData(USART1,payload_feedback1);
		delay_us(100);	
		USART_SendData(USART1,payload_feedback2);
		delay_us(100);
		USART_SendData(USART1,payload_feedback3);
		delay_us(100);
		USART_SendData(USART1,tx_parity);	
		}	
		

		if((IN_KEY1 ==0)&&(turn_to_auto==1))			//由手动切换到自动模式
		{
			op_mode = 0;
//				in_key1_pressed = 0;
			SSR_L_CTL = 0;
			SSR_H_CTL = 0;
			delay_ms(50);
			SSR_W_CTL = 0;
			turn_to_auto=0;
		}
		else if((IN_KEY1 ==1)&&(turn_to_manual==1)) 									//由自动切换到手动模式					
		{
			op_mode=1;
			SSR_L_CTL = 1;
			SSR_H_CTL = 1;
			delay_ms(50);
			SSR_W_CTL = 1;
			turn_to_manual=0;
		}
		
		
#endif			
	}	 
}
