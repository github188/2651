
#include "ap_peripheral_handling.h"
#include "ap_state_config.h"
#include "ap_state_handling.h"

//#include "drv_l1_system.h"
#include "driver_l1.h"
#include "drv_l1_cdsp.h"


#define LED_STATUS_FLASH		1
#define LED_STATUS_BLINK		2

#define CRAZY_KEY_TEST			0		// Send key events faster than human finger can do
#define LED_ON					1
#define LED_OFF 				0

//static INT8U led_status;	//0: nothing  1: flash	2: blink
//static INT8U led_cnt;
static INT32U	led_mode;
static INT8U	g_led_count;
static INT8U	g_led_r_state; //0 = OFF;	1=ON;	2=Flicker
static INT8U	g_led_g_state;
static INT8U	g_led_flicker_state; //0=I?E!OEAE!M	1=??IaEAE!M
static INT8U	led_red_flag;
static INT8U	led_green_flag;
extern INT8S	video_record_sts;

static INT16U	adp_cnt;
INT8U			adp_status;
static INT16U	adp_out_cnt;
static INT16U	usbd_cnt;

#if USB_PHY_SUSPEND 			== 1
static INT16U	phy_cnt = 0;

#endif


#if TV_DET_ENABLE
INT8U			tv_plug_in_flag;
INT8U			tv_debounce_cnt = 0;

static INT8U	tv = !TV_DET_ACTIVE;

#endif

///static INT8U backlight_tmr = 0;
#if C_SCREEN_SAVER				== CUSTOM_ON
INT8U			auto_off_force_disable = 0;
void ap_peripheral_auto_off_force_disable_set(INT8U);

#endif

static INT8U	led_flash_timerid;
static INT16U	config_cnt;

//----------------------------
typedef struct 
{
INT8U			byRealVal;
INT8U			byCalVal;
} AD_MAP_t;


//----------------------------
extern void avi_adc_gsensor_data_register(void * *msgq_id, INT32U * msg_id);


#define C_BATTERY_STABLE_THRESHOLD 4  // Defines threshold number that AD value is deemed stable


#if USE_ADKEY_NO
static INT8U	ad_detect_timerid;
static INT16U	ad_value;
static KEYSTATUS ad_key_map[USE_ADKEY_NO + 1];


INT16U			adc_key_value;

//static INT8U	ad_value_cnt ;
INT32U			key_pressed_cnt;
INT8U			fast_key_exec_flag;
INT8U			normal_key_exec_flag;
INT8U			long_key_exec_flag;

#endif

static INT32U	key_active_cnt;

///static INT8U lcd_bl_sts;
static INT8U	power_off_timerid;
static INT8U	usbd_detect_io_timerid;
static KEYSTATUS key_map[USE_IOKEY_NO];
static INT8U	key_detect_timerid;
static INT8U	up_firmware_flag = 0;
static INT8U	flash_flag = 0;

INT8U			adp_status;

///static INT8U battery_low_flag = 0;
INT8U			usbd_exit;
INT8U			s_usbd_pin;

//extern INT8U MODE_KEY_flag;
//	prototypes
void ap_peripheral_key_init(void);
void ap_peripheral_rec_key_exe(INT16U * tick_cnt_ptr);

//void ap_peripheral_function_key_exe(INT16U *tick_cnt_ptr);
//void ap_peripheral_next_key_exe(INT16U *tick_cnt_ptr);
//void ap_peripheral_prev_key_exe(INT16U *tick_cnt_ptr);
//void ap_peripheral_ok_key_exe(INT16U *tick_cnt_ptr);
//void ap_peripheral_sos_key_exe(INT16U *tick_cnt_ptr);
void ap_peripheral_usbd_plug_out_exe(INT16U *tick_cnt_ptr);
void ap_peripheral_pw_key_exe(INT16U * tick_cnt_ptr);
void ap_peripheral_vedio_key_exe(INT16U * tick_cnt_ptr);


//void ap_peripheral_menu_key_exe(INT16U *tick_cnt_ptr);
#if KEY_FUNTION_TYPE			== SAMPLE2
void ap_peripheral_capture_key_exe(INT16U * tick_cnt_ptr);

#endif

void ap_peripheral_null_key_exe(INT16U * tick_cnt_ptr);

#if USE_ADKEY_NO
void ap_peripheral_ad_detect_init(INT8U adc_channel, void(*bat_detect_isr) (INT16U data));
void ap_peripheral_ad_check_isr(INT16U value);

#endif



void ap_peripheral_init(void)
{
	power_off_timerid	= usbd_detect_io_timerid = led_flash_timerid = 0xFF;
	key_detect_timerid	= 0xFF;

	LED_pin_init();
	ap_peripheral_key_init();

#if USE_ADKEY_NO
	ad_detect_timerid	= 0xFF;
	ap_peripheral_ad_detect_init(AD_KEY_DETECT_PIN, ap_peripheral_ad_check_isr);

#else

	adc_init();
#endif

	config_cnt			= 0;

	//MODE_KEY_flag = 2;
}






void LED_pin_init(void)
{
	INT32U			type;

	//led init as ouput pull-low
	gpio_init_io(LED1, GPIO_OUTPUT);
	gpio_set_port_attribute(LED1, ATTRIBUTE_HIGH);
	gpio_write_io(LED1, LED1_ACTIVE ^ 1);

	gpio_init_io(LED2, GPIO_OUTPUT);
	gpio_set_port_attribute(LED2, ATTRIBUTE_HIGH);
	gpio_write_io(LED2, LED2_ACTIVE ^ 1);
	led_red_flag		= LED_OFF;
	led_green_flag		= LED_OFF;
	
	type				= LED_INIT;
	msgQSend(PeripheralTaskQ, MSG_PERIPHERAL_TASK_LED_SET, &type, sizeof(INT32U), MSG_PRI_NORMAL);
	
	sys_registe_timer_isr(LED_blanking_isr);		//timer base c to start adc convert
}


extern INT8U	card_space_less_flag;
extern volatile INT8U pic_down_flag;
static INT8U	tf_card_state_led = 0;
static INT8U	usb_led_flag = 0;


void set_led_mode(LED_MODE_ENUM mode)
{
	INT8U			i;
	static INT8U	prev_mode = 0xaa;

	led_mode			= mode;
	g_led_g_state		= 0;						//3oE??!Aoi￠FFFFFFGgAAA
	g_led_r_state		= 0;
	g_led_flicker_state = 0;

	//A?C￠FFFFFFX!No!P!LECEYA?D!OUEeOA￠FFFFFGgA!Ni￠FFFFFGgIEYA?oo￠FFFFFFG?￠FFFFFGgA2?OU!Mo3oEIoIIiO|
	//if(card_space_less_flag)
	//return;
	tf_card_state_led	= 0;

	switch ((INT32U)
	mode)
	{
		case LED_INIT:
			led_red_off();
			led_green_on();
			DBG_PRINT("led_type = LED_INIT\r\n");
			break;

		case LED_UPDATE_PROGRAM:
			led_red_off();
			g_led_g_state = 1;
			DBG_PRINT("led_type = LED_UPDATE_PROGRAM\r\n");
			break;

		case LED_UPDATE_FINISH:
			led_red_off();
			led_green_on();
			DBG_PRINT("led_type = LED_UPDATE_FINISH\r\n");
			break;

		case LED_UPDATE_FAIL:
			sys_release_timer_isr(LED_blanking_isr);

			for (i = 0; i < 2; i++)
			{
				led_all_off();
				OSTimeDly(15);
				led_green_on();
				OSTimeDly(15);
				led_all_off();
			}

			DBG_PRINT("led_type = LED_UPDATE_FAIL\r\n");
			sys_registe_timer_isr(LED_blanking_isr);
			break;

		case LED_USB_CONNECT:
			if (prev_mode != mode)
			{
				g_led_count 		= 0;
			}

			led_red_off();
			g_led_g_state = 2; //
			g_led_flicker_state = 0;
			usb_led_flag = 1;
			DBG_PRINT("led_type = LED_USB_CONNECT\r\n");
			break;

		case LED_RECORD:
			led_green_off();
			g_led_r_state = 2;
			g_led_flicker_state = 0;
			DBG_PRINT("led_type = LED_RECORD\r\n");
			break;

		case LED_SDC_FULL:
			if (sys_pwr_key1_read() == 0)
			{
				led_all_off();
				led_green_on();
				g_led_r_state		= 2;
				g_led_g_state		= 0;
				g_led_flicker_state = 0;
				tf_card_state_led	= 1;
				DBG_PRINT("led_type = LED_SDC_FULL\r\n");
			}

			break;

		case LED_WAITING_RECORD:
			led_red_off();
			led_green_on();
			DBG_PRINT("led_type = LED_WAITING_RECORD\r\n");
			break;

		case LED_AUDIO_RECORD:
			g_led_r_state = 2;
			g_led_flicker_state = 0;
			led_green_off();
			DBG_PRINT("led_type = LED_AUDIO_RECORD\r\n");
			break;

		case LED_WAITING_AUDIO_RECORD:
			led_red_off();
			led_green_on();
			DBG_PRINT("led_type = LED_WAITING_AUDIO_RECORD\r\n");
			break;

		case LED_CAPTURE:
			sys_release_timer_isr(LED_blanking_isr);
			led_green_off();

			while (pic_down_flag)
			{
				OSTimeDly(1);
				led_red_on();
			}

			led_all_off();
			led_green_on();
			sys_registe_timer_isr(LED_blanking_isr);
			DBG_PRINT("led_type = LED_CAPTURE\r\n");
			break;

		case LED_CARD_DETE_SUC:
			if (sys_pwr_key1_read() != 0)
				break;

			if (storage_sd_upgrade_file_flag_get() == 2)
				break;

			sys_release_timer_isr(LED_blanking_isr);
			led_all_off();
			OSTimeDly(15);
			led_green_on();
			tf_card_state_led = 0;
			DBG_PRINT("led_type = LED_TELL_CARD\r\n");
			sys_registe_timer_isr(LED_blanking_isr);
			break;

		case LED_CAPTURE_FAIL:
			for (i = 0; i < 2; i++)
			{
				led_all_off();
				OSTimeDly(50);
				led_red_on();
				OSTimeDly(50);
			}

		case LED_WAITING_CAPTURE:
			led_red_off();
			led_green_on();
			DBG_PRINT("led_type = LED_WAITING_CAPTURE\r\n");
			break;

		case LED_MOTION_DETECTION:
			led_red_on();
			led_green_on();
			DBG_PRINT("led_type = LED_MOTION_DETECTION\r\n");
			break;

		case LED_NO_SDC:
			if ((!card_space_less_flag) && (sys_pwr_key1_read() == 0))
			{
				led_all_off();
				led_green_on();
				g_led_r_state		= 2;
				g_led_g_state		= 0;
				g_led_flicker_state = 0;
				tf_card_state_led	= 1;
				DBG_PRINT("led_type = LED_NO_SDC\r\n");
			}

			break;

		case LED_TELL_CARD:
			//sys_release_timer_isr(LED_blanking_isr);
			//led_red_on();
			//OSTimeDly(15);
			//led_red_off();
			//DBG_PRINT("led_type = LED_TELL_CARD\r\n");
			//sys_registe_timer_isr(LED_blanking_isr);
			break;

		case LED_CARD_NO_SPACE:
			//led_all_off();
			if (storage_sd_upgrade_file_flag_get() == 2)
				break;

			if (sys_pwr_key1_read() == 0)
			{
				led_all_off();
				led_green_on();
				g_led_r_state		= 2;
				g_led_g_state		= 0;
				g_led_flicker_state = 0;
				tf_card_state_led	= 1;
				DBG_PRINT("led_type = LED_CARD_NO_SPACE\r\n");
			}

			break;
	}

	prev_mode			= mode;
}


void led_red_on(void)
{
	if (led_red_flag != LED_ON)
	{
		gpio_write_io(LED2, LED2_ACTIVE ^ 0);
		led_red_flag		= LED_ON;
	}
}


void led_green_on(void)
{
	if (led_green_flag != LED_ON)
	{
		gpio_write_io(LED1, LED1_ACTIVE ^ 0);
		led_green_flag		= LED_ON;
	}
}


void led_all_off(void)
{
	if (led_green_flag != LED_OFF)
	{
		gpio_write_io(LED1, LED1_ACTIVE ^ 1);
		led_green_flag		= LED_OFF;
	}

	if (led_red_flag != LED_OFF)
	{
		gpio_write_io(LED2, LED2_ACTIVE ^ 1);
		led_red_flag		= LED_OFF;
	}
}


void led_green_off(void)
{
	if (led_green_flag != LED_OFF)
	{
		gpio_write_io(LED1, LED1_ACTIVE ^ 1);
		led_green_flag		= LED_OFF;
	}
}


void led_red_off(void)
{
	if (led_red_flag != LED_OFF)
	{
		gpio_write_io(LED2, LED2_ACTIVE ^ 1);
		led_red_flag		= LED_OFF;
	}
}


extern INT8U	video_stop_flag;

static INT8U	no_card_led_cnt = 0;


void LED_blanking_isr(void)
{
	INT8U			type = NULL;
	static INT8U	led_flag = 0;

	//if(card_space_less_flag)
	//	return;
	if (g_led_count++ == 105)
	{
		g_led_count 		= 0;
	}

	if (video_stop_flag)
		return;

	if (g_led_g_state == 1)
	{
		if (g_led_count % 10 == 0)
		{
			if (up_firmware_flag == 1)
			{
				led_green_off();
				up_firmware_flag	= 0;
			}
			else 
			{
				led_green_on();
				up_firmware_flag	= 1;
			}
		}
	}
	else if (g_led_g_state == 2)
	{
		if (usb_led_flag == 1)
		{
			if (g_led_count == 1)
			{
				led_flag			^= 0x01;

				if (led_flag)
					led_green_on();
				else 
					led_green_off();
			}
		}
		else 
		{
			if (g_led_count / 53 == g_led_flicker_state)
				led_green_on();
			else 
				led_green_off();
		}
	}
	else if (g_led_g_state == 3)
	{

		if (g_led_count % 27 == 0)
		{
			if (flash_flag == 0)
			{
				led_green_on();
				flash_flag			= 1;
			}
			else 
			{
				led_green_off();
				flash_flag			= 0;
			}

		}
	}


	if (g_led_r_state == 2)
	{
		if (tf_card_state_led == 1)
		{
			if (++no_card_led_cnt > 16)
			{
				no_card_led_cnt 	= 0;
				led_flag			^= 0x01;

				if (led_flag)
					led_red_on();
				else 
					led_red_off();
			}
		}
		else 
		{
			if (g_led_count < 53)
				led_red_on();
			else 
				led_red_off();
		}
	}
	else if (g_led_r_state == 3)
	{
		if (g_led_count % 27 == 0)
		{
			if (flash_flag == 0)
				led_red_on();
			else 
				led_red_off();


		}
	}



}






#if USE_ADKEY_NO


void ap_peripheral_ad_detect_init(INT8U adc_channel, void(*ad_detect_isr) (INT16U data))
{
#if C_BATTERY_DETECT				== CUSTOM_ON
	battery_value_sum	= 0;
	bat_ck_cnt			= 0;
#endif

	//	ad_value_cnt = 0;
	adc_init();
	adc_vref_enable_set(TRUE);
	adc_conv_time_sel(1);
	adc_manual_ch_set(adc_channel);
	adc_manual_callback_set(ad_detect_isr);

	if (ad_detect_timerid == 0xFF)
	{
		ad_detect_timerid	= AD_DETECT_TIMER_ID;
		sys_set_timer((void *) msgQSend, (void *) PeripheralTaskQ, MSG_PERIPHERAL_TASK_AD_DETECT_CHECK, 
			ad_detect_timerid, PERI_TIME_INTERVAL_AD_DETECT);
	}
}


void ap_peripheral_ad_check_isr(INT16U value)
{
	ad_value			= value;
}


INT16U adc_key_release_calibration(INT16U value)
{
	return value;
}


void ap_peripheral_clr_screen_saver_timer(void)
{
	key_active_cnt		= 0;
}


#endif


static INT8U	RegKey_First_Flag = 0;


void ap_peripheral_key_init(void)
{
	INT32U			i;

	gp_memset((INT8S *) &key_map, NULL, sizeof(KEYSTATUS));
	ap_peripheral_key_register(GENERAL_KEY);

	for (i = 0; i < USE_IOKEY_NO; i++)
	{
		if (key_map[i].key_io)
		{
			key_map[i].key_cnt	= 0;
			gpio_init_io(key_map[i].key_io, GPIO_INPUT);
			gpio_set_port_attribute(key_map[i].key_io, ATTRIBUTE_LOW);
			gpio_write_io(key_map[i].key_io, (key_map[i].key_active) ^ 1);
		}
	}
}


extern void Time_card_storage(TIME_T * intime);


void ap_peripheral_time_set(void)
{
#if 1
	TIME_T			READ_TIME;

	DBG_PRINT("TIME_SET1\r\n");
	ap_state_config_timefile_get(&READ_TIME);
	Time_card_storage(&READ_TIME);

#if USING_EXT_RTC					== CUSTOM_ON
	ap_state_handling_calendar_init();

#else

	ap_state_handing_intime_init(READ_TIME);

#endif

#endif

}


void ap_peripheral_key_register(INT8U type)
{

	INT32U			i;

	if (type == GENERAL_KEY)
	{
		key_map[0].key_io	= VIDEO_KEY;
		key_map[0].key_function = (KEYFUNC)ap_peripheral_vedio_key_exe;
		key_map[0].key_active = VIDEO_KEY_ACTIVE;	//1;
		key_map[0].long_flag = 0;
		
		key_map[1].key_io	= CAPTURE_KEY;
		key_map[1].key_function = (KEYFUNC)ap_peripheral_capture_key_exe;
		key_map[1].key_active = CAPTURE_KEY_ACTIVE; //1;
		key_map[1].long_flag = 0;
		
		ad_key_map[0].key_io = FUNCTION_KEY;
		ad_key_map[0].key_function = (KEYFUNC)ap_peripheral_null_key_exe;
	}
	else if (type == USBD_DETECT)
	{
#if USE_IOKEY_NO

		for (i = 0; i < USE_IOKEY_NO; i++)
		{
			if (key_map[i].key_io != CAPTURE_KEY)
				key_map[i].key_io = NULL;
		}

#endif

#if USE_ADKEY_NO

		for (i = 0; i < USE_ADKEY_NO; i++)
		{
			ad_key_map[i].key_function = ap_peripheral_null_key_exe;
		}

#endif
	}
	else if (type == DISABLE_KEY)
	{
#if USE_IOKEY_NO

		for (i = 0; i < USE_IOKEY_NO; i++)
		{
			key_map[i].key_io	= NULL;
		}

#endif

#if USE_ADKEY_NO

		for (i = 0; i < USE_ADKEY_NO; i++)
		{
			ad_key_map[i].key_function = ap_peripheral_null_key_exe;
		}

#endif
	}
	else if (type == BETTERY_LOW_STATUS_KEY)
	{
		key_map[0].key_io	= PW_KEY;
		key_map[0].key_function = (KEYFUNC)
		ap_peripheral_pw_key_exe;

#if USE_ADKEY_NO

		for (i = 0; i < USE_ADKEY_NO; i++)
		{
			ad_key_map[i].key_function = ap_peripheral_null_key_exe;
		}

#endif
	}

}


extern INT8U ap_state_config_auto_off_get(void);

INT8U			long_pw_key_pressed = 0;

#if CRAZY_KEY_TEST				== 1
INT8U			crazy_key_enable = 0;
INT32U			crazy_key_cnt = 0;

#endif


void ap_peripheral_key_judge(void)
{
	INT32U			i, key_press = 0;
	INT16U			key_down = 0;

	for (i = 0; i < USE_IOKEY_NO; i++)
	{
		if (key_map[i].key_io)
		{

			if (key_map[i].key_active)
				key_down = gpio_read_io(key_map[i].key_io);
			else 
				key_down = !gpio_read_io(key_map[i].key_io);

			if (key_down)
			{

				if (!key_map[i].long_flag)
				{
					key_map[i].key_cnt	+= 1;

#if SUPPORT_LONGKEY 								== CUSTOM_ON

					if (key_map[i].key_cnt >= Long_Single_width)
					{
						key_map[i].long_flag = 1;
						key_map[i].key_function(& (key_map[i].key_cnt));
					}

#endif
				}
				else 
				{
					key_map[i].key_cnt	= 0;
				}

				if (key_map[i].key_cnt == 65535)
				{
					key_map[i].key_cnt	= 32 + 10;	//64+10;
				}
			}
			else 
			{
				// long_pw_key_pressed=0;
				if (key_map[i].long_flag)
				{
					key_map[i].long_flag = 0;
				}

				if (key_map[i].key_cnt >= Short_Single_width) //Short_Single_width
				{

					key_map[i].key_function(& (key_map[i].key_cnt));
					key_press			= 1;
				}

				key_map[i].key_cnt	= 0;

			}
		}
	}

}

static int ap_peripheral_power_key_read(int pin)
{
    int 			status;


#if (KEY_TYPE == KEY_TYPE1)||(KEY_TYPE == KEY_TYPE2)||(KEY_TYPE == KEY_TYPE3)||(KEY_TYPE == KEY_TYPE4)||(KEY_TYPE == KEY_TYPE5)
    status				= gpio_read_io(pin);

#else

    switch (pin)
    {
    case PWR_KEY0:
        status = sys_pwr_key0_read();
        break;

    case PWR_KEY1:
        status = sys_pwr_key1_read();
        break;
    }

#endif

    if (status != 0)
        return 1;

    else
        return 0;
}



void ap_peripheral_adaptor_out_judge(void)
{
	adp_out_cnt++;

	switch (adp_status)
	{
	case 0: //unkown state
		if (ap_peripheral_power_key_read(ADP_OUT_PIN))
		{
			//DBG_PRINT("xx:%d",adp_cnt);
			adp_cnt++;

			if (adp_cnt > 16)
			{
				adp_out_cnt 		= 0;
				adp_cnt 			= 0;
				adp_status			= 1;
				OSQPost(USBTaskQ, (void *) MSG_USBD_INITIAL);

#if C_BATTERY_DETECT								== CUSTOM_ON && USE_ADKEY_NO

				//battery_lvl = 1;
#endif
			}
		}
		else
		{
			adp_cnt 			= 0;
		}

		//	DBG_PRINT("yy:%d\r\n",adp_out_cnt);
		if (adp_out_cnt > 24)
		{
			adp_out_cnt 		= 0;
			adp_status			= 3;

#if C_BATTERY_DETECT							== CUSTOM_ON && USE_ADKEY_NO

			//battery_lvl = 2;
			low_voltage_cnt 	= 0;
#endif
		}

		break;

	case 1: //adaptor in state
		if (!ap_peripheral_power_key_read(ADP_OUT_PIN))
		{
			if (adp_out_cnt > 8)
			{
				adp_status			= 2;

#if C_BATTERY_DETECT								== CUSTOM_ON
				low_voltage_cnt 	= 0;
#endif
				if (screen_saver_enable)
				{
					screen_saver_enable = 0;

#if C_SCREEN_SAVER										== CUSTOM_ON
					ap_state_handling_lcd_backlight_switch(1);
#endif
				}
			}
		}
		else
		{
			adp_out_cnt 		= 0;
		}

		break;

	case 2: //adaptor out state
		if (!ap_peripheral_power_key_read(ADP_OUT_PIN))
		{
			if ((adp_out_cnt > PERI_ADP_OUT_PWR_OFF_TIME))
			{
#if 0
				adp_out_cnt 		= 192;
				ap_peripheral_pw_key_exe(&adp_out_cnt);
#endif
			}

			adp_cnt 			= 0;
		}
		else
		{
			adp_cnt++;

			if (adp_cnt > 3)
			{
				adp_out_cnt 		= 0;
				adp_status			= 1;
				usbd_exit			= 0;
				OSQPost(USBTaskQ, (void *) MSG_USBD_INITIAL);
			}
		}

		break;

	case 3: //adaptor initial out state
		if (ap_peripheral_power_key_read(ADP_OUT_PIN))
		{
			if (adp_out_cnt > 3)
			{
				adp_out_cnt 		= 0;
				adp_status			= 1;
				OSQPost(USBTaskQ, (void *) MSG_USBD_INITIAL);
			}
		}
		else
		{
			adp_out_cnt 		= 0;
		}

		break;

	default:
		break;
	}

	///DBG_PRINT("USB_PIN=%d\r\n",s_usbd_pin);
	if (s_usbd_pin == 1)
	{
		usbd_cnt++;

		if (!ap_peripheral_power_key_read(C_USBDEVICE_PIN))
		{
			if (usbd_cnt > 3)
			{
				ap_peripheral_usbd_plug_out_exe(&usbd_cnt);
			}
		}
		else
		{
			usbd_cnt			= 0;
		}
	}

#if USB_PHY_SUSPEND 				== 1

	if (s_usbd_pin == 0)
	{
		if (ap_peripheral_power_key_read(C_USBDEVICE_PIN))
		{
			if (phy_cnt == PERI_USB_PHY_SUSPEND_TIME)
			{
				// disable USB PHY CLK for saving power
				DBG_PRINT("Turn Off USB PHY clk (TODO)\r\n");
				phy_cnt++;							// 目的是 Turn Off 只做一次
			}
			else if (phy_cnt < PERI_USB_PHY_SUSPEND_TIME)
			{
				phy_cnt++;
			}
		}
		else
		{
			phy_cnt 			= 0;
		}
	}

#endif
}

void ap_peripheral_usbd_plug_out_exe(INT16U *tick_cnt_ptr)
{
    msgQSend(ApQ, MSG_APQ_DISCONNECT_TO_PC, NULL, NULL, MSG_PRI_NORMAL);
    *tick_cnt_ptr		= 0;
}



#if KEY_FUNTION_TYPE			== SAMPLE2
extern volatile INT8U pic_down_flag;
extern volatile INT8U video_down_flag;


void ap_peripheral_capture_key_exe(INT16U * tick_cnt_ptr)
{
	INT32U			led_type;

	if (!s_usbd_pin)
	{
		if (ap_state_handling_storage_id_get() == NO_STORAGE)
		{

			led_type			= LED_TELL_CARD;
			msgQSend(PeripheralTaskQ, MSG_PERIPHERAL_TASK_LED_SET, &led_type, sizeof(INT32U), MSG_PRI_NORMAL);
		}
		else 
		{
			if ((!pic_down_flag) && (!card_space_less_flag) && (!video_down_flag))
			{
				DBG_PRINT("[CAPTUER_ACTIVE...]\r\n");

//				if (*tick_cnt_ptr > 15)
//					msgQSend(ApQ, MSG_APQ_VIDEO_RECORD_ACTIVE, NULL, NULL, MSG_PRI_NORMAL);
//				else 
					msgQSend(ApQ, MSG_APQ_CAPTUER_ACTIVE, NULL, NULL, MSG_PRI_NORMAL);
			}
		}

	}

	*tick_cnt_ptr		= 0;
}


#endif

void ap_peripheral_vedio_key_exe(INT16U * tick_cnt_ptr)
{
	INT32U			led_type;

	if (!s_usbd_pin)
	{
		if (ap_state_handling_storage_id_get() == NO_STORAGE)
		{

			led_type			= LED_TELL_CARD;
			msgQSend(PeripheralTaskQ, MSG_PERIPHERAL_TASK_LED_SET, &led_type, sizeof(INT32U), MSG_PRI_NORMAL);
		}

		if ((!pic_down_flag) && (!card_space_less_flag) && (!video_down_flag))
		{
			if (ap_state_handling_storage_id_get() != NO_STORAGE)
			{
#if SUPPORT_LONGKEY 							== CUSTOM_ON

				if (*tick_cnt_ptr >= Long_Single_width)
				{
					DBG_PRINT("[VIDEO_RECORD_...]\r\n");
					msgQSend(ApQ, MSG_APQ_VIDEO_RECORD_ACTIVE, NULL, NULL, MSG_PRI_NORMAL);
				}
				else 
#endif

				{
					DBG_PRINT("[CAPTUER_ACTIVE...]\r\n");
					msgQSend(ApQ, MSG_APQ_VIDEO_RECORD_ACTIVE, NULL, NULL, MSG_PRI_NORMAL);
				}
			}
		}
	}

	*tick_cnt_ptr		= 0;
}


void ap_peripheral_pw_key_exe(INT16U * tick_cnt_ptr)
{
	INT32U			led_type;

	if (!s_usbd_pin)
	{
		if (ap_state_handling_storage_id_get() == NO_STORAGE)
		{

			led_type			= LED_TELL_CARD;
			msgQSend(PeripheralTaskQ, MSG_PERIPHERAL_TASK_LED_SET, &led_type, sizeof(INT32U), MSG_PRI_NORMAL);
		}

		if ((!pic_down_flag) && (!card_space_less_flag) && (!video_down_flag))
		{
			if (ap_state_handling_storage_id_get() != NO_STORAGE)
			{
#if SUPPORT_LONGKEY 							== CUSTOM_ON

				if (*tick_cnt_ptr >= Long_Single_width)
				{
					DBG_PRINT("[VIDEO_RECORD_...]\r\n");
					msgQSend(ApQ, MSG_APQ_VIDEO_RECORD_ACTIVE, NULL, NULL, MSG_PRI_NORMAL);
				}
				else 
#endif

				{
					DBG_PRINT("[CAPTUER_ACTIVE...]\r\n");
					msgQSend(ApQ, MSG_APQ_CAPTUER_ACTIVE, NULL, NULL, MSG_PRI_NORMAL);
				}
			}
		}
	}

	*tick_cnt_ptr		= 0;
}


void ap_peripheral_null_key_exe(INT16U * tick_cnt_ptr)
{

}



