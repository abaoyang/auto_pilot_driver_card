

/* Includes ------------------------------------------------------------------*/
#ifndef __SSR_H
#define __SSR_H	 
#include "sys.h"

extern u8 beep_toggle;

#define SSR_L_CTL PAout(2)
#define SSR_W_CTL PAout(3)
#define SSR_SS_CTL PAout(5)
#define SSR_H_CTL PAout(6)

#define SSR_BACK2_CTL PCout(13)
#define SSR_BACK1_CTL PCout(14)
#define SSR_BACK3_CTL PEout(6)
#define SSR_BEEP_CTL PEout(5)


void SSR_Init(void);		//初始化工作电路板SSR端口
	 				    
#endif
