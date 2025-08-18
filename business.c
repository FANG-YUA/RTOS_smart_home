#include "cmsis_os.h"
#define LOG_TAG  "BUSI_MODULE"
#include "elog.h"
#include "business.h"
#include "mmc.h"
#include "common.h"


//
busi_sample_stru busi_sample_values;//共享内存首地址
busi_switch_stru busi_switch_values;

mmc_ctrl_stru busi_sample_mmc_ctrl;//通信结构体
mmc_ctrl_stru busi_switch_mmc_ctrl; 

void busi_process_task_entry(void *p)
{
	log_d("busi_process_task...");
	mmc_ctrl_init(&busi_sample_mmc_ctrl,&busi_sample_values,sizeof(busi_sample_values), "busi_sample_values");
	mmc_ctrl_init(&busi_switch_mmc_ctrl,&busi_switch_values,sizeof(busi_switch_values), "busi_switch_values");
	while(1)
	{

		if(mmc_ctrl_require(&busi_sample_mmc_ctrl,MMC_DELAY_TIME)==pdPASS)
			{
				log_d("sample_req SUC!!");
				log_i("temprature:%d, bright:%d, rsvd0:%d,rsvd1:%d,rsvd2:%d,rsvd3:%d",\
																busi_sample_values.temprature, \
																busi_sample_values.bright, \
																busi_sample_values.reserved[0], \
																busi_sample_values.reserved[1], \
																busi_sample_values.reserved[2], \
																busi_sample_values.reserved[3]  \
					);
				if(busi_sample_values.temprature<BUSI_TEMPRATURE_DOWN_THRESHHOLD)
				{
					log_w("temprature LOW!!");
					busi_switch_values.fan_status=FAN_CTRL_OFF_STATUS;
					
				}
				if(busi_sample_values.temprature>BUSI_TEMPRATURE_UP_THRESHHOLD)
				{
					log_w("temprature HIGH!!");
					busi_switch_values.fan_status=FAN_CTRL_ON_STATUS;
				}
				if(busi_sample_values.bright<BUSI_BIGHT_DOWN_THRESHHOLD)
				{
					log_w("bright LOW!!");
					busi_switch_values.light_status=LIGHT_CTRL_ON_STATUS;
				}
				if(busi_sample_values.bright>BUSI_BIGHT_UP_THRESHHOLD)
				{
					log_w("bright HIGH!!");
					busi_switch_values.light_status=LIGHT_CTRL_OFF_STATUS;
				}
				
				if(mmc_ctrl_require(&busi_switch_mmc_ctrl,MMC_DELAY_TIME)==pdPASS)
				{
					log_d("switch_req SUC!!");
					log_i("fan_status:%d, light_status:%d, rsvd0:%d,rsvd1:%d,rsvd2:%d,rsvd3:%d",\
															busi_switch_values.fan_status, \
															busi_switch_values.light_status, \
															busi_switch_values.reserved[0], \
															busi_switch_values.reserved[1], \
															busi_switch_values.reserved[2], \
															busi_switch_values.reserved[3]  \
					);
				}
				else log_e("switch_req Fall!!");
			}
			else
			{
				log_i("busi_ack_Fall!!");
			}

	}	
}
