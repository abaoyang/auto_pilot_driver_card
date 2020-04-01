/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * ����    ��VeryAI Team
 * ��汾  ��ST3.5.0
 * ʵ��ƽ̨��VeryAI STM32������
 * ����    ������ʵ�����  
 *
 * ��̳    ��http://www.veryai.com
 * �Ա�    ��http://veryaishop.taobao.com
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
 * ��������main
 * ����  ��������,ʵ���˼򵥻��ع��ܡ�ʵ����̣�ʹ�ô������SSCOM3.3 ���ú��˷������У������ڷ�������������Ҫ���͵����֣�Ȼ�󵥻�����,
					 STM32�ᷢ���ոս��յ��Ĵ������ݣ�SSCOM3.3���յ�STM32���͵Ĵ������ݣ�����ʾ�ڴ����ϡ�
 * ����  ����
 * ���  ����
 */
 
//#define CELL_TEST
#define USE_DIGIPOT
u8 op_mode = 1; 					//0�����Զ���ʻģʽ��1�����˹�ģʽ����KEY0�����л�����������Ĭ���ֶ�ģʽ
u8 payload_seq = 0; 		//�����к�
u8 payload_cmd1 = 0;		//����������1
u8 payload_cmd2 = 0;		//����������2
u8 payload_cmd3 = 0;		//����������3

u32 bound = 115200; 		//���ڲ�����
u16 tim3_arr = 0;			//timer3Ԥװ��ֵ
// u16 tim3_psc = 7199;		//timer3��Ƶϵ��
// u16 tim4_arr = 699;			//timer4Ԥװ��ֵ
// u16 tim4_psc = 7199;		//timer4��Ƶϵ��
// u16 tim6_arr = 10000;			//timer4Ԥװ��ֵ
// u16 tim6_psc = 7199;		//timer4��Ƶϵ��


u8 payload_feedback1 = 0;  		//���ڷ���������1
u8 payload_feedback2 = 0;			//���ڷ���������2
u8 payload_feedback3 = 0;			//���ڷ���������3
u8 tx_parity = 0;							//���ڷ���XORУ��
 
int main(void)
{	
	u16 adc_result;
	float temp;
	delay_init();	    	 			//��ʱ������ʼ��	  
	NVIC_Configuration(); 	 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(bound);	 				//���ڳ�ʼ��Ϊ9600
 	LED_BOARD_Init();					//��ʼ��������·��LED�˿�
	IN_KEY_Init();						//��ʼ��������·�尴��
	//EXTIX_Init();							//��ʼ���ⲿ�ж�
	SSR_Init();								//��ʼ��������·��SSR�˿�	
	TIM3_PWM_Init(19999,71);	//��������PWM�ź�
	TIM_SetCompare3(TIM3,18499);	//��ʼ��ʹ���������λ������1.5ms�ߵ�ƽ��50hz�ź�
	Adc_Battery_Init();
	Adc_Angle_Init();
	Dac1_Init();
	BUZZ_Init();
	TIM4_Int_Init(699,7199);
	MAX5395_Init();
	MAX5395_Write_CMD(RST_CMD);
	TIM6_Int_Init(10000,7199);//10Khz����Ƶ��,1�����ж�			            
	                                     
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
		if (receive_one_payload == 1)				//ȷ���յ�һ������
		{
			receive_one_payload = 0;					//���ڼ�����������
			payload_seq = USART_RX_BUF[1];		//�����
			payload_cmd1 = USART_RX_BUF[2];		//���ػ����ָʾ�ٶ�
			payload_cmd2 = USART_RX_BUF[3];		//���ػ����ת������
			payload_cmd3 = USART_RX_BUF[4];		//���ػ�������Ⱥ͵�
			
// 				printf("\r\n received payload_seq is %x \r\n",payload_seq);
// 				printf("received payload_cmd1 is %x \r\n",payload_cmd1);
// 				printf("received payload_cmd2 is %x \r\n",payload_cmd2);
// 				printf("received payload_cmd3 is %x \r\n",payload_cmd3);
			//�����յ������ݡ�
			if(op_mode == 0)		 //��������Զ���ʻģʽ������ݴ����յ������ݿ��ƶ�������ȣ��ƣ����ֵ�λ����
			{					
#ifdef	USE_DIGIPOT	
				if(((payload_cmd1&0x80)>>7)==1 &&  (payload_cmd1&0x7f)<=100)		//�����ٶ�ֵΪ����������Ƴ�����
				{
					SSR_BACK1_CTL = 1;
					SSR_BACK2_CTL = 1;
					SSR_BACK3_CTL	= 1;
					MAX5395_Write_WIPER_Reg(payload_cmd1&0x7f);
				}
				if(((payload_cmd1&0x80)>>7)==0 &&  (payload_cmd1&0x7f)<=100)		//�����ٶ�ֵΪ����������Ƴ�ǰ��
				{
					SSR_BACK1_CTL = 0;
					SSR_BACK2_CTL = 0;
					SSR_BACK3_CTL	= 0;
					MAX5395_Write_WIPER_Reg(payload_cmd1&0x7f);
				}			
				
#else
				DAC_SetChannel1Data(DAC_Align_12b_R, payload_cmd1); 	//�ٶ�д��DAC�������ʵ�֣��˴�ֻ�����߼���
#endif	
				if(((payload_cmd2&0x80)>>7)==1 &&  (payload_cmd2&0x7f)<=100)						//������ת��Ϊ��ֵ
				{
					tim3_arr = 18499+(payload_cmd2&0x7f)*10; 								//18499������λ��������1.5ms��payload_cmd2Ϊ-100ʱ��tim3_arrΪ19499������0.5ms
					TIM_SetCompare3(TIM3,tim3_arr);	
				}
				if(((payload_cmd2&0x80)>>7) ==0 &&  (payload_cmd2&0x7f)<=100)						//������ת��Ϊ��ֵ
				{
					tim3_arr = 18499 - (payload_cmd2&0x7f)*10; 						//18499������λ��������1.5ms��payload_cmd2Ϊ+100ʱ��tim3_arrΪ17499������2.5ms
					TIM_SetCompare3(TIM3,tim3_arr);	
				}   			
				
//				TIM_SetCompare3(TIM3,19000);			//��ת������д��PMW CCR�������������ʵ�֣��˴�ֻ�����߼���
				if((payload_cmd3&0x40)>>6) beep_toggle = 1;	//������
				else beep_toggle = 0;												//������
				if((payload_cmd3&0x20)>>5) led6_toggle = 1;	//LED��˸
				else led6_toggle = 0;												//LEDֹͣ��˸
				if((payload_cmd3&0x10)>>4) led5_toggle = 1;	//LED��˸
				else led5_toggle = 0;												//LEDֹͣ��˸
				if((payload_cmd3&0x08)>>3) led4_toggle = 1;	//LED��˸
				else led4_toggle = 0;												//LEDֹͣ��˸
				if((payload_cmd3&0x04)>>2) led3_toggle = 1;	//LED��˸
				else led3_toggle = 0;												//LEDֹͣ��˸
				if((payload_cmd3&0x02)>>1) led2_toggle = 1;	//LED��˸
				else led2_toggle = 0;												//LEDֹͣ��˸
				if(payload_cmd3&0x01) led1_toggle = 1;	//LED��˸
				else led1_toggle = 0;												//LEDֹͣ��˸
			}
			//׼����������
			if((IN_KEY1==0)) 
			{
				payload_feedback1 = payload_feedback1 | 0x01;		//����1����Ϊ�͵�ƽʱ��ģʽ�л����Զ�ģʽ�����ذ��������£���λ��1
				op_mode = 0;																		//������һ�����£�����ģʽ��Ϊ�ֶ�ģʽ���˴���ʵ�־����л�
//					in_key1_pressed = 0;														//ȡ���Ѿ����µļ�¼
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
			temp = (float)adc_result*(3.3/4096);		//���ת��ΪVֵ
			
			if(temp<=2.1)	payload_feedback2 = 0;
			if(temp>=2.94)	payload_feedback2 = 100;
			if(temp>2.1 && temp<2.94)	payload_feedback2 =(u8)(100/((1+(2.94-temp)/(temp-2.1))));		//2.94 = 4.2*7/10;  2.1=3*7/10���ⲿ��ط�ѹ����ADC����ߺ���͵�ѹֵ
				
			
			payload_feedback3 = 50;		//ˮλ���ݣ���ʱ���̶���ֵ50
			tx_parity = TX_FRAME_HEADER^payload_seq^payload_feedback1^payload_feedback2^payload_feedback3;
			
//�������ݵ����ػ�				
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
		

		if((IN_KEY1 ==0)&&(turn_to_auto==1))			//���ֶ��л����Զ�ģʽ
		{
			op_mode = 0;
//				in_key1_pressed = 0;
			SSR_L_CTL = 0;
			SSR_H_CTL = 0;
			delay_ms(50);
			SSR_W_CTL = 0;
			turn_to_auto=0;
		}
		else if((IN_KEY1 ==1)&&(turn_to_manual==1)) 									//���Զ��л����ֶ�ģʽ					
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
