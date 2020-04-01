/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * 作者    ：VeryAI Team
 * 库版本  ：ST3.5.0
 * 实验平台：VeryAI STM32开发板
 * 描述    ：IIC驱动代码  
 *
 * 论坛    ：http://www.veryai.com
 * 淘宝    ：http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "myiic.h"
#include "delay.h"

/*
 * 函数名：IIC_Init
 * 描述  ：初始化IIC   
 * 输入  ：无
 * 输出  ：无
 */
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = SCL_PIN|SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,SCL_PIN|SDA_PIN); 	//PB6,PB7 输出高
	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = SCL_PIN|SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,SCL_PIN|SDA_PIN); 	//PB6,PB7 输出高
}

/*
 * 函数名：IIC_Start
 * 描述  ：产生IIC起始信号
 * 输入  ：无
 * 输出  ：无
 */
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}

/*
 * 函数名：IIC_Stop
 * 描述  ：产生IIC停止信号
 * 输入  ：无
 * 输出  ：无
 */
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}

/*
 * 函数名：IIC_Wait_Ack
 * 描述  ：等待应答信号到来
 * 输入  ：无
 * 输出  ：返回值：1，接收应答失败，0，接收应答成功
 */
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
}

/*
 * 函数名：IIC_Ack
 * 描述  ：产生ACK应答
 * 输入  ：无
 * 输出  ：无
 */
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}

/*
 * 函数名：IIC_NAck
 * 描述  ：不产生ACK应答
 * 输入  ：无
 * 输出  ：无
 */	    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}

/*
 * 函数名：IIC_Send_Byte
 * 描述  ：IIC发送一个字节
 * 输入  ：发送的字节
 * 输出  ：无
 */		  
void IIC_Send_Byte(u8 txd)
{                        
	u8 t;   
	SDA_OUT(); 	    
  IIC_SCL=0;//拉低时钟开始数据传输
  for(t=0;t<8;t++)
  {              
		if((txd&0x80)>>7)
		IIC_SDA=1;
		else
		IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
  }	 
}

/*
 * 函数名：IIC_Read_Byte
 * 描述  ：读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
 * 输入  ：ack=1，0
 * 输出  ：ACK，nACK 
 */	  
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
  for(i=0;i<8;i++ )
	{
		IIC_SCL=0; 
    delay_us(2);
		IIC_SCL=1;
    receive<<=1;
    if(READ_SDA)receive++;   
		delay_us(1); 
  }					 
  if (!ack)
  IIC_NAck();//发送nACK
  else
  IIC_Ack(); //发送ACK   
  return receive;
}
