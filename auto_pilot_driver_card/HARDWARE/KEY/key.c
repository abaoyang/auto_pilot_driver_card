/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * ����    ��VeryAI Team
 * ��汾  ��ST3.5.0
 * ʵ��ƽ̨��VeryAI STM32������
 * ����    ��KEY��������  
 *
 * ��̳    ��http://www.veryai.com
 * �Ա�    ��http://veryaishop.taobao.com
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
 * ��������KEY_Init
 * ����  ��������ʼ������
 * ����  ����
 * ���  ����
 */	 
void KEY_Init(void) 														//IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//ʹ��PORTA,PORTC,PORTDʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);				//��ʼ��GPIO

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//���ó���������
 	GPIO_Init(GPIOD, &GPIO_InitStructure);				//��ʼ��GPIO
	
	//��ʼ�� WK_UP-->GPIOA.0	��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);				//��ʼ��GPIOA.0
}

/*
 * ��������IN_KEY_Init
 * ����  ��ʵ�ʹ�����·�尴����ʼ������
 * ����  ����
 * ���  ����
 */	 
void IN_KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTB,PORTEʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//���óɸ�������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);				//��ʼ��GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//���óɸ�������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);				//��ʼ��GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//���óɸ�������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);				//��ʼ��GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//���óɸ�������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				//��ʼ��GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//���óɸ�������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				//��ʼ��GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//���óɸ�������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				//��ʼ��GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//���óɸ�������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				//��ʼ��GPIO
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//���óɸ�������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				//��ʼ��GPIO
}


/*
 * ��������KEY_Init
 * ����  ������������
					 0��û���κΰ�������
					 1��KEY0����
					 2��KEY1����
					 3��KEY2���� WK_UP
					 ע��˺�������Ӧ���ȼ�,KEY2>KEY0>KEY1
 * ����  ��mode:0,��֧��������;1,֧��������;
 * ���  �����ذ���ֵ
 */	 
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;														//�������ɿ���־
	if(mode)key_up=1;  														//֧������		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
	{
		delay_ms(10);																//ȥ���� 
		key_up=0;
		if(KEY2==1) return KEY_UP;
		else if(KEY0==0)return KEY_DOWN;
		else if(KEY1==0)return KEY_RIGHT;
	}else if(KEY2==0&&KEY0==1&&KEY1==1)key_up=1; 	// �ް�������
 	return 0;																			
}

void key_scan(u8 mode)
{
	static u8 key_up=1;														//�������ɿ���־
	if(mode)key_up=1;  														//֧������		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
	{
		delay_ms(5);																//ȥ���� 
		key_up=0;
		if(KEY2==1)key_up_pressed = 1;
		else if(KEY0==0)key_down_pressed = 1;
		else if(KEY1==0)key_right_pressed = 1;
	}else if(KEY2==0&&KEY0==1&&KEY1==1)key_up=1; 	// �ް������� 			
}

void in_key_scan(u8 mode)
{
	static u8 key_up=1;														//�������ɿ���־
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
	if(mode)key_up=1;  														//֧������		  
	if(key_up&&(IN_KEY2==0||IN_KEY3==0||IN_KEY4==0||IN_KEY5==0||IN_KEY6==0||IN_KEY7==0||IN_KEY8==0))
	{
		delay_ms(5);																//ȥ���� 
		key_up=0;
//		if(IN_KEY1==0)in_key1_pressed = 1;
	  if(IN_KEY2==0)in_key2_pressed = 1;
		if(IN_KEY3==0)in_key3_pressed = 1;
		if(IN_KEY4==0)in_key4_pressed = 1;
 		if(IN_KEY5==0)in_key5_pressed = 1;
		if(IN_KEY6==0)in_key6_pressed = 1;
		if(IN_KEY7==0)in_key7_pressed = 1;
		if(IN_KEY8==0)in_key8_pressed = 1;

	}else if(IN_KEY2==1&&IN_KEY3==1&&IN_KEY4==1&&IN_KEY5==1&&IN_KEY6==1&&IN_KEY7==1&&IN_KEY8==1)key_up=1; 	// �ް������� 			
}
