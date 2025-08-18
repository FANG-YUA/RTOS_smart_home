#ifndef _BUSINESS_H_
#define _BUSINESS_H_

#include "cmsis_os.h"
#include "mmc.h"
typedef struct
	{
		int temprature;
		int bright;
		int reserved[4];
	}busi_sample_stru;

typedef struct
	{
		int fan_status;
		int light_status;
		int reserved[4];
	}busi_switch_stru;

extern mmc_ctrl_stru busi_sample_mmc_ctrl;//通信结构体
extern mmc_ctrl_stru busi_switch_mmc_ctrl; 
	
extern busi_sample_stru busi_sample_values;//共享内存首地址
extern busi_switch_stru busi_switch_values;

#define BUSI_TEMPRATURE_DOWN_THRESHHOLD  (20)
#define BUSI_TEMPRATURE_UP_THRESHHOLD  (30)	
	
#define BUSI_BIGHT_DOWN_THRESHHOLD  (2)
#define BUSI_BIGHT_UP_THRESHHOLD  (5)	
	
#endif
