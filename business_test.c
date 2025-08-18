#include "business_test.h"
#include "cmsis_os.h"
#include "elog.h"
#include "business.h"
#include "common.h"
#include "shell.h"
#define LOG_TAG  "BUSI_TEST"

TaskHandle_t mast_handle;
void mock_sample_task_entry(void *p)
{
	log_d("mock sample task is running");
	while(1)
	{
		log_d("wait for sample_sem_req");
		xSemaphoreTake(busi_sample_mmc_ctrl.sem_req,portMAX_DELAY);
		busi_sample_values.temprature=25;
		busi_sample_values.bright=2;
		busi_sample_values.reserved[0]=1;
		busi_sample_values.reserved[1]=2;
		busi_sample_values.reserved[2]=3;
		busi_sample_values.reserved[3]=4;
		xSemaphoreGive(busi_sample_mmc_ctrl.sem_ack);
		log_d("release sample_sem_ack");
		
	}

}

void mock_switch_task_entry(void *p)
{
	log_d("mock switch task is running");
	while(1)
	{
		log_d("wait for switch_sem_req");
		xSemaphoreTake(busi_switch_mmc_ctrl.sem_req,portMAX_DELAY);
		busi_switch_values.fan_status=FAN_CTRL_ON_STATUS;
		busi_switch_values.light_status=LIGHT_CTRL_ON_STATUS;
		busi_switch_values.reserved[0]=1;
		busi_switch_values.reserved[1]=2;
		busi_switch_values.reserved[2]=3;
		busi_switch_values.reserved[3]=4;
		xSemaphoreGive(busi_switch_mmc_ctrl.sem_ack);
		log_d("release switch_sem_ack");
		
	}
}
void smst(int argc,char **argv)
{
	log_d("start mock task ");
	xTaskCreate(mock_sample_task_entry,"mock_sample_task",128,(void *)0,7,&mast_handle);
	xTaskCreate(mock_switch_task_entry,"mock_switch_task",128,(void *)0,7,&mast_handle);
}
ZNS_CMD_EXPORT(smst,strt mock sample task)
