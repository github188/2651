#include "ap_peripheral_handling.h"
#include "ap_state_config.h"
#include "ap_state_handling.h"
//#include "drv_l1_system.h"
#include "driver_l1.h"
#include "drv_l1_cdsp.h"


#define LED_STATUS_FLASH	1
#define LED_STATUS_BLINK	2

#define CRAZY_KEY_TEST		0		// Send key events faster than human finger can do
#define LED_ON              1
#define LED_OFF             0

//static INT8U led_status;	//0: nothing  1: flash	2: blink
//static INT8U led_cnt;

static INT32U   led_mode;
static INT8U 	g_led_count;
static INT8U 	g_led_r_state;	//0 = OFF;	1=ON;	2=Flicker
static INT8U	g_led_g_state;
static INT8U	g_led_flicker_state;	//0=I?E!OEAE!M	1=??IaEAE!M
static INT8U    led_red_flag;
static INT8U    led_green_flag;
extern INT8S video_record_sts;
#if TV_DET_ENABLE
INT8U tv_plug_in_flag;
INT8U tv_debounce_cnt = 0;

static	INT8U tv = !TV_DET_ACTIVE;
#endif
///static INT8U backlight_tmr = 0;

#if C_SCREEN_SAVER == CUSTOM_ON
	INT8U auto_off_force_disable = 0;
	void ap_peripheral_auto_off_force_disable_set(INT8U);
#endif

static INT8U led_flash_timerid;
static INT16U config_cnt;

//----------------------------
    typedef struct {
        INT8U byRealVal ;
        INT8U byCalVal;
    } AD_MAP_t;


//----------------------------
	extern void avi_adc_gsensor_data_register(void **msgq_id, INT32U *msg_id);
	

	#define C_BATTERY_STABLE_THRESHOLD		4  // Defines threshold number that AD value is deemed stable


#if USE_ADKEY_NO
	static INT8U ad_detect_timerid;
	static INT16U ad_value;
	static KEYSTATUS ad_key_map[USE_ADKEY_NO+1];
	

	INT16U adc_key_value;

    //static INT8U  ad_value_cnt ;
	INT32U key_pressed_cnt;
	INT8U fast_key_exec_flag;
	INT8U normal_key_exec_flag;
	INT8U long_key_exec_flag;
#endif

static INT32U key_active_cnt;
///static INT8U lcd_bl_sts;
static INT8U power_off_timerid;
static INT8U usbd_detect_io_timerid;
static KEYSTATUS key_map[USE_IOKEY_NO];
static INT8U key_detect_timerid;
static INT8U up_firmware_flag=0;
static INT8U flash_flag=0;

 INT8U  adp_status;
///static INT8U battery_low_flag = 0;
INT8U  usbd_exit;
INT8U s_usbd_pin;
//extern INT8U MODE_KEY_flag;
//	prototypes
void ap_peripheral_key_init(void);
void ap_peripheral_rec_key_exe(INT16U *tick_cnt_ptr);
//void ap_peripheral_function_key_exe(INT16U *tick_cnt_ptr);
//void ap_peripheral_next_key_exe(INT16U *tick_cnt_ptr);
//void ap_peripheral_prev_key_exe(INT16U *tick_cnt_ptr);
//void ap_peripheral_ok_key_exe(INT16U *tick_cnt_ptr);
//void ap_peripheral_sos_key_exe(INT16U *tick_cnt_ptr);
//void ap_peripheral_usbd_plug_out_exe(INT16U *tick_cnt_ptr);
void ap_peripheral_pw_key_exe(INT16U *tick_cnt_ptr);
//void ap_peripheral_menu_key_exe(INT16U *tick_cnt_ptr);
#if KEY_FUNTION_TYPE == SAMPLE2
void ap_peripheral_capture_key_exe(INT16U *tick_cnt_ptr);
#endif
void ap_peripheral_null_key_exe(INT16U *tick_cnt_ptr);
#if USE_ADKEY_NO
	void ap_peripheral_ad_detect_init(INT8U adc_channel, void (*bat_detect_isr)(INT16U data));
	void ap_peripheral_ad_check_isr(INT16U value);
#endif	



void ap_peripheral_init(void)
{


	power_off_timerid = usbd_detect_io_timerid = led_flash_timerid = 0xFF;
	key_detect_timerid = 0xFF;  	
  	LED_pin_init();
	ap_peripheral_key_init();

#if USE_ADKEY_NO
	ad_detect_timerid = 0xFF;
	ap_peripheral_ad_detect_init(AD_KEY_DETECT_PIN, ap_peripheral_ad_check_isr);
#else
	adc_init();
#endif
	config_cnt = 0;
	//MODE_KEY_flag = 2;
}






void LED_pin_init(void)
{
	INT32U type;
	//led init as ouput pull-low
  	gpio_init_io(LED1, GPIO_OUTPUT);
  	gpio_set_port_attribute(LED1, ATTRIBUTE_HIGH);
  	gpio_write_io(LED1, DATA_LOW);
  	
  	gpio_init_io(LED2, GPIO_OUTPUT);
  	gpio_set_port_attribute(LED2, ATTRIBUTE_HIGH);
  	gpio_write_io(LED2, DATA_LOW);
  	led_red_flag=LED_OFF;
	led_green_flag=LED_OFF;
	type = LED_INIT;
	msgQSend(PeripheralTaskQ, MSG_PERIPHERAL_TASK_LED_SET, &type, sizeof(INT32U), MSG_PRI_NORMAL);
  	sys_registe_timer_isr(LED_blanking_isr);	//timer base c to start adc convert
}
extern INT8U card_space_less_flag;

void set_led_mode(LED_MODE_ENUM mode)
{
	INT8U i;
	static INT8U prev_mode=0xaa;
	
	led_mode = mode;
	g_led_g_state = 0;	//3oE??!Aoi�FFFFFFFGgAAA
	g_led_r_state = 0;
	g_led_flicker_state = 0;
	//A?C�FFFFFFFX!No!P!LECEYA?D!OUEeOA�FFFFFFGgA!Ni�FFFFFFGgIEYA?oo�FFFFFFFG?�FFFFFFGgA2?OU!Mo3oEIoIIiO|
	//if(card_space_less_flag)
		//return;
	
	switch((INT32U)mode)
		{
			case LED_INIT:
            	led_red_on();
				led_green_off();			
				DBG_PRINT("led_type = LED_INIT\r\n");
			break;
			case LED_UPDATE_PROGRAM:
		    	led_red_off();
				g_led_g_state=1;
				DBG_PRINT("led_type = LED_UPDATE_PROGRAM\r\n");
			break;
			case LED_UPDATE_FINISH:
				led_red_off();
				led_green_on();
				DBG_PRINT("led_type = LED_UPDATE_FINISH\r\n");
				break;
			case LED_UPDATE_FAIL:
				sys_release_timer_isr(LED_blanking_isr);
				for(i=0;i<2;i++)
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
			
			    break;
			case LED_RECORD:
	   	   	    led_green_off();
				g_led_r_state = 2;
				g_led_flicker_state = 0;
				DBG_PRINT("led_type = LED_RECORD\r\n");
			    break;

			case LED_SDC_FULL:
				sys_release_timer_isr(LED_blanking_isr);
			   	led_green_off();
			   	OSTimeDly(15);
				DBG_PRINT("led_type = LED_SDC_FULL\r\n");
			 	sys_registe_timer_isr(LED_blanking_isr);

			case LED_WAITING_RECORD:
		   	    led_red_off();
			    led_green_on();			
			    DBG_PRINT("led_type = LED_WAITING_RECORD\r\n");
			    break;
		    case LED_AUDIO_RECORD:
		
               
			    break;
		    case LED_WAITING_AUDIO_RECORD:		
               
			    break;
		    case LED_CAPTURE:
			    led_green_off();
			    led_red_on();
			    DBG_PRINT("led_type = LED_CAPTURE\r\n");
		        break;			
		    case LED_CARD_DETE_SUC:
			   if(storage_sd_upgrade_file_flag_get() == 2)
			    break;
			    sys_release_timer_isr(LED_blanking_isr);
				for(i=0;i<3;i++)
				{
			     led_all_off();
				 led_red_on();
				 OSTimeDly(30);
				 led_all_off();
				 led_green_on();
				 OSTimeDly(30);
				}
			  sys_registe_timer_isr(LED_blanking_isr);
			   DBG_PRINT("led_type = LED_CARD_DETE_SUC\r\n");
			  break;
		    case LED_CAPTURE_FAIL:
               for(i=0;i<2;i++)
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

			    break;
		   case LED_NO_SDC:
			    if((prev_mode != mode))
				{
			      if((led_green_flag != LED_ON)&&(!card_space_less_flag))
			 	   {
				     sys_release_timer_isr(LED_blanking_isr);
		             led_all_off();
		             led_green_on();
		             OSTimeDly(10);
		  	         sys_registe_timer_isr(LED_blanking_isr);
			 	   }
			    led_all_off();
				}
			    DBG_PRINT("led_type = LED_NO_SDC\r\n");
			    break;
	

		   case LED_TELL_CARD:
			    sys_release_timer_isr(LED_blanking_isr);
			    led_red_on();
			    OSTimeDly(15);
				led_red_off();
				DBG_PRINT("led_type = LED_TELL_CARD\r\n");
			    sys_registe_timer_isr(LED_blanking_isr);
			break;
		   case LED_CARD_NO_SPACE:
			       //led_all_off();
			       if(storage_sd_upgrade_file_flag_get() == 2)
				   break;
			       g_led_g_state = 3;	//3IDo?oE!O?a!MuDAIe!OI�FFFFFFFG?A?!Mo�FFFFFFGgAI?E!OEAE!M
			       g_led_r_state = 3;
				   DBG_PRINT("led_type = LED_CARD_NO_SPACE\r\n");
				   break;      
	
			
	}
	
	prev_mode=mode;
}

void led_red_on(void)
{
  if(led_red_flag != LED_ON)
    {
	  gpio_write_io(LED2, DATA_HIGH);
	  led_red_flag=LED_ON;
    }
}

void led_green_on(void)
{
    if(led_green_flag != LED_ON)
    {
	  gpio_write_io(LED1, DATA_HIGH);
	  led_green_flag=LED_ON;
    }
}
void led_all_off(void)
{   if(led_green_flag != LED_OFF)
    {
	   gpio_write_io(LED1, DATA_LOW);
	   led_green_flag=LED_OFF;
    }
    if(led_red_flag != LED_OFF)
    {
	   gpio_write_io(LED2, DATA_LOW);
	   led_red_flag=LED_OFF;
    }
}
void led_green_off(void)
{
	if(led_green_flag != LED_OFF)
	{
	  gpio_write_io(LED1, DATA_LOW);
	  led_green_flag=LED_OFF;
	}
}

void led_red_off(void)
{
	if(led_red_flag != LED_OFF)
	{
	 gpio_write_io(LED2, DATA_LOW);
	 led_red_flag=LED_OFF;
	}
}
extern INT8U video_stop_flag;

void LED_blanking_isr(void)
{	
  // INT8U type=NULL;
	//if(card_space_less_flag)
	//	return;

	if(g_led_count++ == 105){
		g_led_count = 0;
	}
	if( video_stop_flag)
		return;
	if(g_led_g_state ==1)
   	{
   	     if(g_led_count % 10 ==0)
   	     	{
   	     	 if(up_firmware_flag == 1)
   	     	 	{
   	     	 	 led_green_off();
				 up_firmware_flag=0;
   	     	 	}
			 else
			 	{
			 	 led_green_on();
				 up_firmware_flag=1;
			 	}
   	     	}
   	}
    else if(g_led_g_state == 2)
		{
		 if(g_led_count/53 == g_led_flicker_state)
		 	led_green_on();
		 else
		 	led_green_off();
		}
	else if(g_led_g_state == 3)
		{
		
		 	if(g_led_count % 27 ==0)
		 		{
		 		 if(flash_flag == 0)
		 		 	{
				 	led_green_on();
					flash_flag=1;
		 		 	}
				 else
				 	{
				 	led_green_off();
					 flash_flag=0;
				 	}
				 	
		 		}
		}
  

    if(g_led_r_state == 2)
     	{
     	 if(g_led_count < 53)
			led_red_on();
		 else
		 	led_red_off();		
     	}
	else if(g_led_r_state == 3)
		{
		 if(g_led_count % 27 ==0)
		 		{
		 		 if(flash_flag == 0)				 	
				    led_red_on();
				 else
				 	led_red_off();
				
				 	
		 		}
		}



}






#if USE_ADKEY_NO
void ap_peripheral_ad_detect_init(INT8U adc_channel, void (*ad_detect_isr)(INT16U data))
{
	#if C_BATTERY_DETECT == CUSTOM_ON
   	battery_value_sum=0;
	bat_ck_cnt=0;
	#endif
//	ad_value_cnt = 0;
	
	adc_init();
	adc_vref_enable_set(TRUE);
	adc_conv_time_sel(1);
	adc_manual_ch_set(adc_channel);
	adc_manual_callback_set(ad_detect_isr);
	if (ad_detect_timerid == 0xFF) {
		ad_detect_timerid = AD_DETECT_TIMER_ID;
		sys_set_timer((void*)msgQSend, (void*) PeripheralTaskQ, MSG_PERIPHERAL_TASK_AD_DETECT_CHECK, ad_detect_timerid, PERI_TIME_INTERVAL_AD_DETECT);
	}
}

void ap_peripheral_ad_check_isr(INT16U value)
{
	ad_value = value;
}

INT16U adc_key_release_calibration(INT16U value)
{
	return value;
}

void ap_peripheral_clr_screen_saver_timer(void)
{
	key_active_cnt = 0;
}


#endif


static INT8U RegKey_First_Flag = 0;

void ap_peripheral_key_init(void)
{
	INT32U i;

	gp_memset((INT8S *) &key_map, NULL, sizeof(KEYSTATUS));
	ap_peripheral_key_register(GENERAL_KEY);
		if (RegKey_First_Flag == 0)
	{//output 500 ms high level when power on
		RegKey_First_Flag = 1;
		if (key_map[0].key_io)
		{
			gpio_init_io(key_map[0].key_io, GPIO_INPUT);
			gpio_set_port_attribute(key_map[0].key_io, ATTRIBUTE_HIGH);
			gpio_write_io(key_map[0].key_io, DATA_LOW);
			OSTimeDly(10);
			gpio_write_io(key_map[0].key_io, DATA_HIGH);
			OSTimeDly(50);
			gpio_write_io(key_map[0].key_io, DATA_LOW);
			OSTimeDly(20);
		}
	}
	for (i=0 ; i<USE_IOKEY_NO ; i++) {
		if (key_map[i].key_io) {
	  		key_map[i].key_cnt = 0;
			gpio_init_io(key_map[i].key_io, GPIO_INPUT);
			gpio_set_port_attribute(key_map[i].key_io, ATTRIBUTE_LOW);
	  		gpio_write_io(key_map[i].key_io, (key_map[i].key_active)^1);

		

		 
	  	}
  	}
}

extern void Time_card_storage(TIME_T *intime);
void ap_peripheral_time_set(void)
{
#if 1
    TIME_T  READ_TIME;
	
	DBG_PRINT("TIME_SET1\r\n");
	ap_state_config_timefile_get(&READ_TIME);
	Time_card_storage(&READ_TIME);
	
#if USING_EXT_RTC == CUSTOM_ON
	ap_state_handling_calendar_init();
#else

    ap_state_handing_intime_init(READ_TIME);

#endif
#endif

}
void ap_peripheral_key_register(INT8U type)
{
	
	INT32U i;
		
	if (type == GENERAL_KEY) 
		{
			 key_map[0].key_io = VIDEO_KEY;
			 key_map[0].key_function = (KEYFUNC) ap_peripheral_pw_key_exe;
			 key_map[0].key_active=0;//1;
			 key_map[0].long_flag=0;
			 //key_map[1].key_io = CAPTURE_KEY;
			// key_map[1].key_function = (KEYFUNC) ap_peripheral_capture_key_exe;
			// key_map[1].key_active=1;//1;
			// key_map[1].long_flag=0;
			 ad_key_map[0].key_io = FUNCTION_KEY;
			 ad_key_map[0].key_function = (KEYFUNC) ap_peripheral_null_key_exe;
		}
	else if (type == USBD_DETECT) 
		{
        #if USE_IOKEY_NO
			for (i=0 ; i<USE_IOKEY_NO ; i++) {
				if(key_map[i].key_io != CAPTURE_KEY)
					key_map[i].key_io = NULL;
			}
        #endif
        #if USE_ADKEY_NO		
			for (i=0 ; i<USE_ADKEY_NO ; i++) {
				ad_key_map[i].key_function = ap_peripheral_null_key_exe;
			}
        #endif
		} 
	else if (type == DISABLE_KEY)
		{
        #if USE_IOKEY_NO
			for (i=0 ; i<USE_IOKEY_NO ; i++) {
				key_map[i].key_io = NULL;
			}
        #endif
        #if USE_ADKEY_NO		
			for (i=0 ; i<USE_ADKEY_NO ; i++) {
				ad_key_map[i].key_function = ap_peripheral_null_key_exe;
			}
        #endif
		}
	else if (type == BETTERY_LOW_STATUS_KEY)
		{
			key_map[0].key_io = PW_KEY;
			key_map[0].key_function = (KEYFUNC) ap_peripheral_pw_key_exe;
        #if USE_ADKEY_NO		
			for (i=0 ; i<USE_ADKEY_NO ; i++) {
				ad_key_map[i].key_function = ap_peripheral_null_key_exe;
			}
        #endif
		}
	
}


extern INT8U ap_state_config_auto_off_get(void);

INT8U long_pw_key_pressed = 0;
#if CRAZY_KEY_TEST == 1
INT8U crazy_key_enable=0;
INT32U crazy_key_cnt=0;
#endif
void ap_peripheral_key_judge(void)
{
	INT32U i, key_press = 0;
	INT16U key_down=0;

      for (i=0 ; i<USE_IOKEY_NO ; i++) 
        {
	       if(key_map[i].key_io) 
		      {

		       if(key_map[i].key_active)
                 key_down = gpio_read_io(key_map[i].key_io);
               else
				 key_down=  !gpio_read_io(key_map[i].key_io);	
			   if(key_down)
		         {
         
				  if(!key_map[i].long_flag)
					{
					    key_map[i].key_cnt += 1;
						#if SUPPORT_LONGKEY == CUSTOM_ON
					    if (key_map[i].key_cnt >= Long_Single_width)
							{
							  key_map[i].long_flag = 1;
						      key_map[i].key_function(&(key_map[i].key_cnt));
					        }
						#endif
				    } 
				  else 
					{
					key_map[i].key_cnt = 0;
				    }
				  if (key_map[i].key_cnt == 65535)
					{
					key_map[i].key_cnt = 0;
				    }
			    } 
			   else 
			    {			 
			     // long_pw_key_pressed=0;
			     if(key_map[i].long_flag)
			     	{
			     	 key_map[i].long_flag=0;
					 key_map[i].key_cnt=0;
			     	}
				  if(key_map[i].key_cnt >= Short_Single_width) //Short_Single_width
					{
					
					 key_map[i].key_function(&(key_map[i].key_cnt));
					 key_press = 1;
				    }
				 key_map[i].key_cnt = 0;
				
			   }
		}
	}

}



void ap_peripheral_adaptor_out_judge(void)
{
	
}



#if KEY_FUNTION_TYPE == SAMPLE2
extern volatile  INT8U pic_down_flag;
extern volatile  INT8U video_down_flag;
void ap_peripheral_capture_key_exe(INT16U *tick_cnt_ptr)
{
	INT32U led_type;
	if (!s_usbd_pin)
		{
	 	if(ap_state_handling_storage_id_get() == NO_STORAGE)
			{
			 
			  led_type = LED_TELL_CARD;
		      msgQSend(PeripheralTaskQ, MSG_PERIPHERAL_TASK_LED_SET, &led_type, sizeof(INT32U), MSG_PRI_NORMAL);
			}
		 else
	 	    {
			if((!pic_down_flag)&&(!card_space_less_flag)&&(!video_down_flag))
            {
	           DBG_PRINT("[CAPTUER_ACTIVE...]\r\n");
			   if(*tick_cnt_ptr >15)
	            msgQSend(ApQ, MSG_APQ_VIDEO_RECORD_ACTIVE, NULL, NULL, MSG_PRI_NORMAL);
			   else
			   	msgQSend(ApQ, MSG_APQ_CAPTUER_ACTIVE, NULL, NULL, MSG_PRI_NORMAL);
			}
	 	    }
	     
        } 

	*tick_cnt_ptr = 0;
}
#endif



void ap_peripheral_pw_key_exe(INT16U *tick_cnt_ptr)
{
	INT32U led_type;
	if (!s_usbd_pin) 
	{
	  if(ap_state_handling_storage_id_get() == NO_STORAGE)
			{
			 
			  led_type = LED_TELL_CARD;
		      msgQSend(PeripheralTaskQ, MSG_PERIPHERAL_TASK_LED_SET, &led_type, sizeof(INT32U), MSG_PRI_NORMAL);
			}
	  else
	  	    {
			if((!pic_down_flag)&&(!card_space_less_flag)&&(!video_down_flag))
             {
	          DBG_PRINT("[VIDEO_RECORD_...]\r\n");
	          if(*tick_cnt_ptr >15)
	            msgQSend(ApQ, MSG_APQ_VIDEO_RECORD_ACTIVE, NULL, NULL, MSG_PRI_NORMAL);
			   else
			   	{
			   	msgQSend(ApQ, MSG_APQ_CAPTUER_ACTIVE, NULL, NULL, MSG_PRI_NORMAL);
			   	}
			  }
	  	    }
	     
	}

	*tick_cnt_ptr = 0;
}


void ap_peripheral_null_key_exe(INT16U *tick_cnt_ptr)
{
	
}



