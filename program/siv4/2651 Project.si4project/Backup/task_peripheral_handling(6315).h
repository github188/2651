#include "application.h"

#define PERIPHERAL_TASK_QUEUE_MAX			256///160///50///192
#define PERIPHERAL_TASK_QUEUE_MAX_MSG_LEN	10


#define PERI_TIME_INTERVAL_AD_DETECT	1         //4//		//128 = 1s //lx
#define Long_Single_width               64	  //500ms
#define Short_Single_width              12	  //100ms
#define LongSingle_width_200	        26     //203ms

//DV: 47-203  电量1格; 203-406 拍照; 406-648 录像;  648-898 电量3格; 898-1101 失控
//DC: 47-203  电量2格; 203-453 拍照; 453-703 低电;  703-898 电量格4;
#define DV_LongSingle_width_400         52     //406ms
#define DV_LongSingle_width_650         83     //648ms
#define DV_LongSingle_width_900         115    //898ms
#define DV_LongSingle_width_1100        141    //1101ms

#define DC_LongSingle_width_450         58     //453ms
#define DC_LongSingle_width_700         90     //703ms
#define DC_LongSingle_width_900         115     //898ms

//#define PERI_TIME_INTERVAL_KEY_DETECT	16		//128 = 1s

#define PERI_COFING_STORE_INTERVAL      5*128/PERI_TIME_INTERVAL_AD_DETECT //5s

#define PERI_TIME_LED_FLASH_ON			64/PERI_TIME_INTERVAL_AD_DETECT	// 0.5s
#define PERI_TIME_LED_BLINK_ON			64/PERI_TIME_INTERVAL_AD_DETECT	// 0.5s
#define PERI_TIME_LED_BLINK_OFF			64/PERI_TIME_INTERVAL_AD_DETECT	// 0.5s

#define PERI_TIME_BACKLIGHT_DELAY		16	//128 = 1s

#define PERI_ADP_OUT_PWR_OFF_TIME       15*128/PERI_TIME_INTERVAL_AD_DETECT //15s	//wwj modify from 15sec to 5sec
#define PERI_USB_PHY_SUSPEND_TIME       4*128/PERI_TIME_INTERVAL_AD_DETECT

extern MSG_Q_ID PeripheralTaskQ;
extern void ap_peripheral_time_set(void);

extern void ap_peripheral_init(void);
extern void task_peripheral_handling_entry(void *para);
extern void ap_peripheral_key_judge(void);
extern void ap_peripheral_adaptor_out_judge(void);
extern void ap_peripheral_key_register(INT8U type);
extern void ap_peripheral_gsensor_data_register(void );
extern void ap_peripheral_motion_detect_judge(void);
extern void ap_peripheral_motion_detect_start(void);
extern void ap_peripheral_motion_detect_stop(void);
#if C_SCREEN_SAVER == CUSTOM_ON
extern void ap_peripheral_lcd_backlight_set(INT8U type);
#endif
//extern void ap_peripheral_night_mode_set(INT8U type);

extern void ap_TFT_backlight_tmr_check(void);
extern void ap_peripheral_tv_detect(void);
extern void ap_peripheral_read_gsensor(void);

extern void ap_peripheral_ad_key_judge(void);
extern INT8U usbd_exit;
extern INT8U screen_saver_enable;
extern void ap_peripheral_config_store(void);


extern void ap_peripheral_hdmi_detect(void);

extern void task_peripheral_handling_init(void);

