/*
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @LastEditors: xjw
 * @file name: app_temperature.c
 * @Description: temperature test init process
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-4-29 15:22:03
 * @LastEditTime: 2021-04-29 15:35:04
 */
/* Includes ------------------------------------------------------------------*/
#include "tuya_iot_wifi_api.h"
#include "tuya_hal_thread.h"
#include "tuya_hal_system.h"
#include "uni_thread.h"
/* Private includes ----------------------------------------------------------*/
#include "b3950.h"
#include "app_temperature.h"

/* Private variables ---------------------------------------------------------*/
DP_VALUE_T temper_s = {
    .dp_id = DP_TEMPER,
    .value = 0,
};

/* Private function prototypes -----------------------------------------------*/
STATIC VOID sensor_data_report_thread(PVOID_T pArg);
/* Private functions ---------------------------------------------------------*/
/*b3590 test init*/
/**
 * @Function: app_b3950_init
 * @Description: temperature acquisition application function
 * @Input: APP_MODE：Application mode
 * @Output: none
 * @Return: op_ret   execution result
 * @Others: 
 */
OPERATE_RET app_b3950_init(IN APP_MODE mode)
{
    OPERATE_RET op_ret = OPRT_OK;

    if(APP_NORMAL == mode) {
        b3950_init();

        tuya_hal_thread_create(NULL, "thread_data_report", 512*4, TRD_PRIO_5, sensor_data_report_thread, NULL);
    }else {
        //not factory test mode
    }

    return op_ret;
}
/**
 * @Function: sensor_data_report_thread
 * @Description: temperature data report thread function
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
STATIC VOID sensor_data_report_thread(PVOID_T pArg)
{   
    while(1) {
        temper_s.value = cur_temper_get();
        PR_DEBUG("temper_value:%d",temper_s.value);
        app_report_all_dp_status();
        /*delay 10s */
        tuya_hal_system_sleep(10*1000);
    }
}

/**
 * @Function: app_report_all_dp_status
 * @Description: app dp data report function
 * @Input: none 
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID app_report_all_dp_status(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    INT_T dp_cnt = 0;
    dp_cnt = 1;

    TY_OBJ_DP_S *dp_arr = (TY_OBJ_DP_S *)Malloc(dp_cnt*SIZEOF(TY_OBJ_DP_S));
    if(NULL == dp_arr) {
        PR_ERR("malloc failed");
        return;
    }

    memset(dp_arr, 0, dp_cnt*SIZEOF(TY_OBJ_DP_S));

    dp_arr[0].dpid = temper_s.dp_id;
    dp_arr[0].type = PROP_VALUE;
    dp_arr[0].time_stamp = 0;
    dp_arr[0].value.dp_value = temper_s.value;

    op_ret = dev_report_dp_json_async(NULL,dp_arr,dp_cnt);
    Free(dp_arr);
    if(OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_json_async relay_config data error,err_num",op_ret);
    }

    PR_DEBUG("dp_query report_all_dp_data");
    return;
}

/**
 * @Function: deal_dp_proc
 * @Description: dp data deal function
 * @Input: TY_OBJ_DP_S 
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID deal_dp_proc(IN CONST TY_OBJ_DP_S *root)
{
    UCHAR_T dpid;

    dpid = root->dpid;
    PR_DEBUG("dpid:%d",dpid);
    
    switch (dpid) {
    
    case 0:

        break;
    default:
        break;
    }

    app_report_all_dp_status();

    return;

}