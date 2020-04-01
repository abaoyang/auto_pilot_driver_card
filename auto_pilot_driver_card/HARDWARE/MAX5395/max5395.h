

/* Includes ------------------------------------------------------------------*/
#ifndef __MAX5395_H
#define __MAX5395_H
#include "myiic.h"   

#define WRITE_SLAVE_ADRESS	0X50
#define READ_SLAVE_ADRESS	0X51

#define WIPER_REG	0X00
#define CONFIG_REG 0X80

#define WIPER_CMD	0X00
#define SD_CLR_CMD 0X80
#define SD_H_WREG_CMD  0X90
#define SD_H_ZERO_CMD  0X91
#define SD_H_MID_CMD  0X92
#define SD_H_FULL_CMD	 0X93
#define SD_L_WREG_CMD	0X88
#define SD_L_ZERO_CMD	0X89
#define SD_L_MID_CMD	0X8A
#define SD_L_FULL_CMD 0X8B
#define SD_W_CMD		0X84
#define QP_OFF_CMD	0XA0
#define	QP_ON_CMD		0XA1
#define RST_CMD			0XC0

void MAX5395_Write_CMD(u8 CMD);
void MAX5395_Write_WIPER_Reg(u8 data);
u8 MAX5395_Read_WIPER_Reg(void);
u8 MAX5395_Read_CONFIG_Reg(void);

void MAX5395_Init(void); //≥ı ºªØIIC
#endif
















