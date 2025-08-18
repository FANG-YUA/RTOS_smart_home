#include "mmc.h"
#include "elog.h"
#include "string.h"
#define LOG_TAG  "MMC_MODULE"

void mmc_ctrl_init(mmc_ctrl_stru *p_mmc_ctrl,void *p_sm, int sm_l,char *sm_name)//初始化
{
	p_mmc_ctrl->sem_req=xSemaphoreCreateBinary();
	p_mmc_ctrl->sem_ack=xSemaphoreCreateBinary();
	
	p_mmc_ctrl->p_shared_mem=p_sm;
	p_mmc_ctrl->shared_mem_nbyte=sm_l;
	memset(p_mmc_ctrl->p_shared_mem,p_mmc_ctrl->shared_mem_nbyte,0);
	log_d("sem_req&ack created，shared mem \"%d\" initialized",sm_name);

}

int mmc_ctrl_require(mmc_ctrl_stru *p_mmc_ctrl,int waittime)//通信
{
	xSemaphoreGive(p_mmc_ctrl->sem_req);
	log_d("sem_req gived");
	log_d("busi_waitting_ack");
	if (xSemaphoreTake(p_mmc_ctrl->sem_ack,waittime)==pdTRUE)
		{
			log_d("busi_ack_SUC!!");
			elog_hexdump("shared content",16,p_mmc_ctrl->p_shared_mem,p_mmc_ctrl->shared_mem_nbyte); 
			return pdPASS;
		}
	else return pdFAIL;
}

