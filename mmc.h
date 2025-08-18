#ifndef _MMC_H_
#define _MMC_H_

#include "cmsis_os.h"

typedef struct
	{
		SemaphoreHandle_t sem_req;
		SemaphoreHandle_t sem_ack;
		void *p_shared_mem;//首地址
		int shared_mem_nbyte;
		
	}mmc_ctrl_stru;
#define MMC_DELAY_TIME (10)

extern void mmc_ctrl_init(mmc_ctrl_stru *p_mmc_ctrl,void *p_sm, int sm_l,char *sm_name);//初始化
	
extern int mmc_ctrl_require(mmc_ctrl_stru *p_mmc_ctrl,int waittime);//通信
#endif
