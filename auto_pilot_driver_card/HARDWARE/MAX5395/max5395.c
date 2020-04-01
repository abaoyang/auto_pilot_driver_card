

/* Includes ------------------------------------------------------------------*/
#include "max5395.h" 
#include "delay.h"

/*
 * 函数名：MAX5395_Init
 * 描述  ：初始化IIC接口
 * 输入  ：无
 * 输出  ：无
 */
void MAX5395_Init(void)
{
	IIC_Init();
}


void MAX5395_Write_CMD(u8 CMD)
{
	IIC_Start();
	IIC_Send_Byte(WRITE_SLAVE_ADRESS);
	IIC_Wait_Ack();
	IIC_Send_Byte(CMD);
	IIC_Wait_Ack();
	IIC_Send_Byte(0);
	IIC_Wait_Ack();
	IIC_Stop();	
}

void MAX5395_Write_WIPER_Reg(u8 data)
{
	IIC_Start();
	IIC_Send_Byte(WRITE_SLAVE_ADRESS);
	IIC_Wait_Ack();
	IIC_Send_Byte(WIPER_CMD);
	IIC_Wait_Ack();
	IIC_Send_Byte(data);
	IIC_Wait_Ack();
	IIC_Stop();	
}

u8 MAX5395_Read_WIPER_Reg(void)
{
	u8 temp=0;
	IIC_Start();
	IIC_Send_Byte(WRITE_SLAVE_ADRESS);
	IIC_Wait_Ack();
	IIC_Send_Byte(WIPER_REG);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(READ_SLAVE_ADRESS);
	IIC_Wait_Ack();
	temp = IIC_Read_Byte(0);
	IIC_Stop();
	return temp;
}

u8 MAX5395_Read_CONFIG_Reg(void)
{
	u8 temp=0;
	IIC_Start();
	IIC_Send_Byte(WRITE_SLAVE_ADRESS);
	IIC_Wait_Ack();
	IIC_Send_Byte(CONFIG_REG);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(READ_SLAVE_ADRESS);
	IIC_Wait_Ack();
	temp = IIC_Read_Byte(0);
	IIC_Stop();
	return temp;
}
