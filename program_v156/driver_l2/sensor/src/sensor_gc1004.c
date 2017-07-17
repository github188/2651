#include "drv_l1_i2c.h"
#include "drv_l2_sensor.h"
#include "drv_l1_cdsp.h"
#include "gp_aeawb.h"
//#include "cdsp_cfg.h"

#include "sensor_gc1004_iqj.h"

//=== This is for code configuration DON'T REMOVE or MODIFY it ===//
#if (USE_SENSOR_NAME == SENSOR_GC1004)
//================================================================//
//Set Gain
#if 0//GC1004_GC_AE
#define ANALOG_GAIN_1 64 		// 1.00x
#define ANALOG_GAIN_2 90 		// 1.4x
#define ANALOG_GAIN_3 118 		// 1.8x
#define ANALOG_GAIN_4 163 		// 2.56x
#define ANALOG_GAIN_5 218 		// 3.40x
#define ANALOG_GAIN_6 304 		// 4.7x
#define ANALOG_GAIN_7 438 		// 6.84x
#define ANALOG_GAIN_8 602 		// 9.4x
#define ANALOG_GAIN_9 851 		// 13.2x
#endif


static sensor_exposure_t gc1004_seInfo;
static sensor_calibration_t gc1004_cdsp_calibration;
static INT32U gc1004_analog_gain = 0x100;
static int *p_expTime_table;
//static int sensor_max_ev_idx;
static gpCdspWBGain_t gc1004_wbgain;
/**************************************************************************
 *                         SENSEOR FUNCTION                          *
 **************************************************************************/

gpCdspWBGain_t *gc1004_awb_r_b_gain_boundary(void)
{

    int i;
    int max_r_gain, max_b_gain, min_r_gain, min_b_gain;

    max_r_gain = max_b_gain = 0;
    min_r_gain = min_b_gain = 255;

    for(i = 10 ; i < 55 ; i++)
    {
        if(max_r_gain < g_GC1004_r_b_gain[i][0]) max_r_gain = g_GC1004_r_b_gain[i][0];
        if(max_b_gain < g_GC1004_r_b_gain[i][1]) max_b_gain = g_GC1004_r_b_gain[i][1];
        if(min_r_gain > g_GC1004_r_b_gain[i][0]) min_r_gain = g_GC1004_r_b_gain[i][0];
        if(min_b_gain > g_GC1004_r_b_gain[i][1]) min_b_gain = g_GC1004_r_b_gain[i][1];
    }

    gc1004_wbgain.max_rgain = max_r_gain;
    gc1004_wbgain.max_bgain = max_b_gain;
    gc1004_wbgain.min_rgain = min_r_gain;
    gc1004_wbgain.min_bgain = min_b_gain;

    return &gc1004_wbgain;
}


sensor_exposure_t *gc1004_get_senInfo(void)
{
    return &gc1004_seInfo;
}

void gc1004_sensor_calibration_str(void)
{
    //sensor_calibration_t gc1004_cdsp_calibration;
    gc1004_cdsp_calibration.r_b_gain = g_GC1004_r_b_gain;
    /*
    gc1004_cdsp_calibration.gamma = g_GC1004_gamma_045_table_5;
    gc1004_cdsp_calibration.color_matrix = g_GC1004_color_matrix4gamma045_7;
    gc1004_cdsp_calibration.awb_thr = g_GC1004_awb_thr_2;
    */
}

sensor_calibration_t *gc1004_get_calibration(void)
{
    return &gc1004_cdsp_calibration;
}

void gc1004_sensor_calibration(void)
{
    //OB
    gp_Cdsp_SetBadPixOb((INT16U *)g_GC1004_badpix_ob_table);
    //Lenscmp
    hwIsp_luc_MaxTan8_Slop_CLP((INT16U *)g_GC1004_MaxTan8 , (INT16U *)g_GC1004_Slope4 , (INT16U *)g_GC1004_CLPoint);
    hwIsp_RadusF0((INT16U *)g_GC1004_Radius_File_0);
    hwIsp_RadusF1((INT16U *)g_GC1004_Radius_File_1);
    //Gamma
    hwCdsp_InitGamma((INT32U *)g_GC1004_gamma_045_table);
    //Color Correction
    hwCdsp_SetColorMatrix_Str((INT16S *)g_GC1004_color_matrix4gamma045);
    //AWB
    gp_Cdsp_SetAWBYUV((INT16S *)g_GC1004_awb_thr);
}

int gc1004_get_night_ev_idx(void)
{
    return gc1004_seInfo.night_ev_idx;
}

int gc1004_get_max_ev_idx(void)
{
    return gc1004_seInfo.max_ev_idx;
}

/**************************************************************************
 *             F U N C T I O N    I M P L E M E N T A T I O N S           *
 **************************************************************************/
#if 0//GC1004_GC_AE
static void gc1004_cvt_analog_gain(INT32U analog_gain)
{
    INT32U iReg, temp;
    //INT32U coarse_gain, fine_gain;

    gc1004_analog_gain = analog_gain;

    iReg = analog_gain >> 2;

    sccb_write(GC1004_SLAVE_ID, 0xb1, 0x01);

    if(iReg < 0x40)
    {
        iReg = 0x40;
        sccb_write(GC1004_SLAVE_ID, 0xb1, 0x01);
        sccb_write(GC1004_SLAVE_ID, 0xb2, 0x00);
    }
    else if((ANALOG_GAIN_1 <= iReg) && (iReg < ANALOG_GAIN_2))
    {
        //analog gain
        temp = iReg;
        //sccb_write(GC1004_SLAVE_ID, 0xb1, temp>>6);
        sccb_write(GC1004_SLAVE_ID, 0xb2, (temp << 2) & 0xfc);

        sccb_write(GC1004_SLAVE_ID, 0xb6, 0x00);//
        //DBG_PRINT("GC1004 analogic gain 1x , GC1004 add pregain = %d\r\n",temp);
        //DBG_PRINT("a:1x,p:%d\r\n",(temp<<2)&0xfc);
    }
    else if((ANALOG_GAIN_2 <= iReg) && (iReg < ANALOG_GAIN_3))
    {
        temp = 64 * iReg / ANALOG_GAIN_2;
        //sccb_write(GC1004_SLAVE_ID, 0xb1, temp>>6);
        sccb_write(GC1004_SLAVE_ID, 0xb2, (temp << 2) & 0xfc);

        sccb_write(GC1004_SLAVE_ID, 0xb6, 0x01);//
        //DBG_PRINT("a:1.4x,p:%d\r\n",(temp<<2)&0xfc);
        //DBG_PRINT("GC1004 analogic gain 1.4x , GC1004 add pregain = %d\r\n",temp);
    }
    else if((ANALOG_GAIN_3 <= iReg) && (iReg < ANALOG_GAIN_4))
    {
        temp = 64 * iReg / ANALOG_GAIN_3;
        //sccb_write(GC1004_SLAVE_ID, 0xb1, temp>>6);
        sccb_write(GC1004_SLAVE_ID, 0xb2, (temp << 2) & 0xfc);

        sccb_write(GC1004_SLAVE_ID, 0xb6, 0x02);//
        //DBG_PRINT("a:1.8x,p:%d\r\n",(temp<<2)&0xfc);
        //DBG_PRINT("GC1004 analogic gain 1.8x , GC1004 add pregain = %d\r\n",temp);
    }
    else if((ANALOG_GAIN_4 <= iReg) && (iReg < ANALOG_GAIN_5))
    {
        temp = 64 * iReg / ANALOG_GAIN_4;
        //sccb_write(GC1004_SLAVE_ID, 0xb1, temp>>6);
        sccb_write(GC1004_SLAVE_ID, 0xb2, (temp << 2) & 0xfc);

        sccb_write(GC1004_SLAVE_ID, 0xb6, 0x03);
        //DBG_PRINT("a:2.56x,p:%d\r\n",(temp<<2)&0xfc);
        //DBG_PRINT("GC1004 analogic gain 2.56x , GC1004 add pregain = %d\r\n",temp);
    }
    else if((ANALOG_GAIN_5 <= iReg) && (iReg < ANALOG_GAIN_6))
    {
        temp = 64 * iReg / ANALOG_GAIN_5;
        //sccb_write(GC1004_SLAVE_ID, 0xb1, temp>>6);
        sccb_write(GC1004_SLAVE_ID, 0xb2, (temp << 2) & 0xfc);

        sccb_write(GC1004_SLAVE_ID, 0xb6, 0x04);
        //DBG_PRINT("a:3.4x,p:%d\r\n",(temp<<2)&0xfc);
        //DBG_PRINT("GC1004 analogic gain 3.4x , GC1004 add pregain = %d\r\n",temp);
    }
    else if((ANALOG_GAIN_6 <= iReg) && (iReg < ANALOG_GAIN_7))
    {
        temp = 64 * iReg / ANALOG_GAIN_6;
        //sccb_write(GC1004_SLAVE_ID, 0xb1, temp>>6);
        sccb_write(GC1004_SLAVE_ID, 0xb2, (temp << 2) & 0xfc);

        sccb_write(GC1004_SLAVE_ID, 0xb6, 0x05);
        //DBG_PRINT("a:4.7x,p:%d\r\n",(temp<<2)&0xfc);
        //DBG_PRINT("GC1004 analogic gain 4.7x , GC1004 add pregain = %d\r\n",temp);
    }
    else if((ANALOG_GAIN_7 <= iReg) && (iReg < ANALOG_GAIN_8))
    {
        temp = 64 * iReg / ANALOG_GAIN_7;
        //sccb_write(GC1004_SLAVE_ID, 0xb1, temp>>6);
        sccb_write(GC1004_SLAVE_ID, 0xb2, (temp << 2) & 0xfc);

        sccb_write(GC1004_SLAVE_ID, 0xb6, 0x06);//
        //DBG_PRINT("a:6.84x,p:%d\r\n",(temp<<2)&0xfc);
        //DBG_PRINT("GC1004 analogic gain 6.84x, GC1004 add pregain = %d\r\n",temp);
    }
    else if((ANALOG_GAIN_8 <= iReg) && (iReg < ANALOG_GAIN_9))
    {
        temp = 64 * iReg / ANALOG_GAIN_8;
        //sccb_write(GC1004_SLAVE_ID, 0xb1, temp>>6);
        sccb_write(GC1004_SLAVE_ID, 0xb2, (temp << 2) & 0xfc);

        sccb_write(GC1004_SLAVE_ID, 0xb6, 0x07);
        //DBG_PRINT("a:9.4x,p:%d\r\n",(temp<<2)&0xfc);
        //DBG_PRINT("GC1004 analogic gain 9.4x,GC1004 add pregain = %d\r\n",temp);
    }
    else //if((ANALOG_GAIN_9<= iReg)&&(iReg < ANALOG_GAIN_10))
    {
        temp = 64 * iReg / ANALOG_GAIN_9;
        //sccb_write(GC1004_SLAVE_ID, 0xb1, temp>>6);
        sccb_write(GC1004_SLAVE_ID, 0xb2, (temp << 2) & 0xfc);

        sccb_write(GC1004_SLAVE_ID, 0xb6, 0x08);
        //DBG_PRINT("GC1004 analogic gain 13.2x ,GC1004 add pregain = %d\r\n",temp);
    }
}
#else

static INT32U BF2116_Analog_Gain_Table[][2] =
{
    {0x10, 100 * 1      },
    {0x11, 100 * 1.013  },
    {0x12, 100 * 1.105  },
    {0x13, 100 * 1.157  },
    {0x14, 100 * 1.214  },
    {0x15, 100 * 1.302  },
    {0x16, 100 * 1.332  },
    {0x17, 100 * 1.388  },
    {0x18, 100 * 1.449  },
    {0x19, 100 * 1.524  },
    {0x1a, 100 * 1.581  },
    {0x1b, 100 * 1.642  },
    {0x1c, 100 * 1.705  },
    {0x1d, 100 * 1.777  },
    {0x1e, 100 * 1.81   },
    {0x1f, 100 * 1.886  },
    {0x20, 100 * 1.941  },
    {0x21, 100 * 2.049  },
    {0x22, 100 * 2.178  },
    {0x23, 100 * 2.258  },
    {0x24, 100 * 2.392  },
    {0x25, 100 * 2.51   },
    {0x26, 100 * 2.603  },
    {0x27, 100 * 2.714  },
    {0x28, 100 * 2.853  },
    {0x29, 100 * 2.99   },
    {0x2a, 100 * 3.091  },
    {0x2b, 100 * 3.208  },
    {0x2c, 100 * 3.329  },
    {0x2d, 100 * 3.46   },
    {0x2e, 100 * 3.551  },
    {0x2f, 100 * 3.65   },
    {0x30, 100 * 3.669  },
    {0x31, 100 * 3.899  },
    {0x32, 100 * 4.103  },
    {0x33, 100 * 4.281  },
    {0x34, 100 * 4.535  },
    {0x35, 100 * 4.703  },
    {0x36, 100 * 4.906  },
    {0x37, 100 * 5.117  },
    {0x38, 100 * 5.403  },
    {0x39, 100 * 5.581  },
    {0x3a, 100 * 5.835  },
    {0x3b, 100 * 5.997  },
    {0x3c, 100 * 6.269  },
    {0x3d, 100 * 6.429  },
    {0x3e, 100 * 6.625  },
    {0x3f, 100 * 6.863  },
    {0x40, 100 * 7.11   },
    {0x41, 100 * 7.5    },
    {0x42, 100 * 7.902  },
    {0x43, 100 * 8.257  },
    {0x44, 100 * 8.744  },
    {0x45, 100 * 9.078  },
    {0x46, 100 * 9.573  },
    {0x47, 100 * 9.921  },
    {0x48, 100 * 10.5   },
    {0x49, 100 * 10.806 },
    {0x4a, 100 * 11.197 },
    {0x4b, 100 * 11.491 },
    {0x4c, 100 * 12.065 },
    {0x4d, 100 * 12.33  },
    {0x4e, 100 * 12.806 },
    {0x4f, 100 * 13.137 },
    {0x50, 100 * 13.19  },
    {0x51, 100 * 13.907 },
    {0x52, 100 * 14.692 },
    {0x53, 100 * 15.388 },
    {0x54, 100 * 16.28  },
    {0x55, 100 * 16.953 },
    {0x56, 100 * 17.769 },
    {0x57, 100 * 18.434 },
    {0x58, 100 * 19.519 },
    {0x59, 100 * 20.075 },
    {0x5a, 100 * 20.987 },
    {0x5b, 100 * 21.558 },
    {0x5c, 100 * 22.589 },
    {0x5d, 100 * 23.11  },
    {0x5e, 100 * 23.926 },
    {0x5f, 100 * 24.432 },
};

static void gc1004_cvt_analog_gain(INT32U analog_gain)
{
    INT32U index = 0;
    INT32U t_a, t_b;

    while (1)
    {
        t_a = BF2116_Analog_Gain_Table[index][0];
        t_b = BF2116_Analog_Gain_Table[index][1];

        if (analog_gain > t_b)
        {
            if (index >= (80 - 1)) break;
            else index += 1;
        }
        else break;
    }
#if 1
    sccb_write(GC1004_SLAVE_ID_test, 0xFE , 0x01 ); //page_01
    sccb_write(GC1004_SLAVE_ID_test, 0x6a , t_a );
#else
    sccb_write(GC1004_SLAVE_ID, 0xb1, 0x01);
    sccb_write(GC1004_SLAVE_ID, 0xb2, 0x00);
    sccb_write(GC1004_SLAVE_ID, 0xb6, 0x06);
#endif

}


#endif

int gc1004_set_exposure_time(sensor_exposure_t *si)
{
    //int ret=0;
    //unsigned short tmp;
    //int analog_gain;
    //unsigned char cvt_digital_gain;
    //int digital_gain;
    int lsb_time, msb_time;
    int idx;

    // From agoritham calc new data update to gc1004_seInfo.
    gc1004_seInfo.sensor_ev_idx += si->ae_ev_idx;
    if(gc1004_seInfo.sensor_ev_idx >= gc1004_seInfo.max_ev_idx) gc1004_seInfo.sensor_ev_idx = gc1004_seInfo.max_ev_idx;
    if(gc1004_seInfo.sensor_ev_idx < 0) gc1004_seInfo.sensor_ev_idx = 0;

    idx = gc1004_seInfo.sensor_ev_idx * 3;
    gc1004_seInfo.time = p_expTime_table[idx];
    gc1004_seInfo.analog_gain = p_expTime_table[idx + 1];
    gc1004_seInfo.digital_gain = p_expTime_table[idx + 2];

    gc1004_seInfo.userISO = si->userISO;

    //DBG_PRINT("T %d, ag %d, ev %d.\r\n", gc1004_seInfo.time, gc1004_seInfo.analog_gain, gc1004_seInfo.sensor_ev_idx );
    //DBG_PRINT("Time = %d, a gain = %d, d gain = %d, ev idx = %d [%d]\r\n", gc1004_seInfo.time, gc1004_seInfo.analog_gain, gc1004_seInfo.digital_gain, gc1004_seInfo.sensor_ev_idx, si->ae_ev_idx );
    //digital_gain = ((si->digital_gain >> 2) & 0xFF);	//0x40:1x, 0xff:4x
    // set exposure time

    lsb_time = (gc1004_seInfo.time & 0xFF);
    msb_time = ((gc1004_seInfo.time >> 8 ) & 0xFF);

#if 1
    sccb_write(GC1004_SLAVE_ID_test, 0xFE , 0x01 ); //page_01
    sccb_write(GC1004_SLAVE_ID_test, 0x6c , lsb_time );
    sccb_write(GC1004_SLAVE_ID_test, 0x6b , msb_time );
#else
    sccb_write(GC1004_SLAVE_ID, 0x04 , 0x34 );
    sccb_write(GC1004_SLAVE_ID, 0x03 , 0x02 );
#endif

    return 0;
}

void gc1004_BLK_Cal(void)
{

    INT32U u32NCurrent, u32SCurrent;
    INT32U u32Ratio_this, u32Ratio_last;


    u32NCurrent = sccb_read(GC1004_SLAVE_ID, 0x56) | (sccb_read(GC1004_SLAVE_ID, 0xd6) << 8);
    u32SCurrent = sccb_read(GC1004_SLAVE_ID, 0x46) | (sccb_read(GC1004_SLAVE_ID, 0xc6) << 8); //----------add 20141201

    if(u32NCurrent > 0)
    {
        u32Ratio_this = (u32NCurrent * 10 + 11 * u32SCurrent) * 32 / ( 21 * u32NCurrent);	 //k=1.1

        if(u32Ratio_this > 32)	 u32Ratio_this = 32;

        u32Ratio_this = (u32Ratio_last + u32Ratio_this) / 2;	//a + b = 10

        sccb_write(GC1004_SLAVE_ID, 0x66, u32Ratio_this);
    }
    u32Ratio_last = u32Ratio_this;

}

void gc1004_set_exposure_gain(void)
{
    //int digital_gain_tmp;
    /*digital_gain_tmp =  0x60;((gc1004_seInfo.digital_gain  >> 2) & 0xFF);	//0x40:1x, 0xff:4x
    sccb_write(GC1004_SLAVE_ID, 0xb0, digital_gain_tmp);*/
    gc1004_cvt_analog_gain(gc1004_seInfo.analog_gain);
    //DBG_PRINT("G");
}


void gc1004_get_exposure_time(sensor_exposure_t *se)
{
    //int ret=0;
    gp_memcpy((INT8S *)se, (INT8S *)&gc1004_seInfo, sizeof(sensor_exposure_t));

}

void gc1004_set_exp_freq(int freq)
{
    if(freq == 50)
    {
        gc1004_seInfo.sensor_ev_idx = GC1004_50HZ_INIT_EV_IDX;
        gc1004_seInfo.ae_ev_idx = 0;
        gc1004_seInfo.daylight_ev_idx = GC1004_50HZ_DAY_EV_IDX;
        gc1004_seInfo.night_ev_idx = GC1004_50HZ_NIGHT_EV_IDX;

        gc1004_seInfo.max_ev_idx = GC1004_50HZ_MAX_EXP_IDX - 1;
        p_expTime_table = (int *)g_GC1004_exp_time_gain_50Hz;
    }
    else if(freq == 60)
    {
        gc1004_seInfo.sensor_ev_idx = GC1004_60HZ_INIT_EV_IDX;
        gc1004_seInfo.ae_ev_idx = 0;
        gc1004_seInfo.daylight_ev_idx = GC1004_60HZ_DAY_EV_IDX;
        gc1004_seInfo.night_ev_idx = GC1004_60HZ_NIGHT_EV_IDX;
        gc1004_seInfo.max_ev_idx = GC1004_60HZ_MAX_EXP_IDX - 1;
        p_expTime_table = (int *)g_GC1004_exp_time_gain_60Hz;
    }
}

static int gc1004_init(void)
{
    gc1004_seInfo.max_time = GC1004_MAX_EXPOSURE_TIME;
    gc1004_seInfo.min_time = GC1004_MIN_EXPOSURE_TIME;

    gc1004_seInfo.max_digital_gain = GC1004_MAX_DIGITAL_GAIN ;
    gc1004_seInfo.min_digital_gain = GC1004_MIN_DIGITAL_GAIN ;

    gc1004_seInfo.max_analog_gain = GC1004_MAX_ANALOG_GAIN;
    gc1004_seInfo.min_analog_gain = GC1004_MIN_ANALOG_GAIN;

    gc1004_seInfo.analog_gain = gc1004_seInfo.min_analog_gain;
    gc1004_seInfo.digital_gain = gc1004_seInfo.min_digital_gain;
    gc1004_seInfo.time = gc1004_seInfo.max_time;// >> 1;
    gc1004_seInfo.userISO = ISO_AUTO;

    gc1004_set_exp_freq(50);

    DBG_PRINT("gc1004_init\r\n");
    return 0;
}

void sensor_gc1004_init(INT32U WIDTH, INT32U HEIGHT)
{
    //i2c_bus_handle_t i2c_handle;
    INT32U i;
    /*
      ?????3]-??им??им
    */
    //i2c_handle.slaveAddr = 0x60;
    //i2c_handle.clkRate = 100;

    gc1004_init();
    gc1004_sensor_calibration_str();

    if(sensor_format == GC1004_RAW)
    {
        if(WIDTH == 1280 && HEIGHT == 720)
        {
            for (i = 0; i < sizeof(GC1004_Para_720P_30) / 2; i++)
            {
                //reg_1byte_data_1byte_write(&i2c_handle,GC1004_Para_720P_30[i][0], GC1004_Para_720P_30[i][1]);
                sccb_write(GC1004_SLAVE_ID_test, GC1004_Para_720P_30[i][0], GC1004_Para_720P_30[i][1]);
            }
        }
        else
        {
            while(1);
        }
    }
    else if(sensor_format == GC1004_MIPI)
    {
        if(WIDTH == 1280 && HEIGHT == 800)
        {
            for (i = 0; i < sizeof(GC1004_MIPI_1280_800_30) / 2; i++)
            {
                //reg_1byte_data_1byte_write(&i2c_handle,GC1004_MIPI_1280_800_30[i][0], GC1004_MIPI_1280_800_30[i][1]);
                sccb_write(GC1004_SLAVE_ID, GC1004_MIPI_1280_800_30[i][0], GC1004_MIPI_1280_800_30[i][1]);
            }
        }
        else if	(WIDTH == 1280 && HEIGHT == 720)
        {
            for (i = 0; i < sizeof(GC1004_MIPI_720P) / 2; i++)
            {
                //reg_1byte_data_1byte_write(&i2c_handle,GC1004_MIPI_720P[i][0], GC1004_MIPI_720P[i][1]);
                sccb_write(GC1004_SLAVE_ID, GC1004_MIPI_720P[i][0], GC1004_MIPI_720P[i][1]);
            }
        }
        else if(WIDTH == 640 && HEIGHT == 480)
        {
            for (i = 0; i < sizeof(GC1004_MIPI_VGA_f60) / 2; i++)
            {
                //reg_1byte_data_1byte_write(&i2c_handle,GC1004_MIPI_VGA_f60[i][0], GC1004_MIPI_VGA_f60[i][1]);
                sccb_write(GC1004_SLAVE_ID, GC1004_MIPI_VGA_f60[i][0], GC1004_MIPI_VGA_f60[i][1]);
            }
        }
        else
        {
            while(1);
        }
    }
}

//=== This is for code configuration DON'T REMOVE or MODIFY it ===//
#endif //(USE_SENSOR_NAME == SENSOR_GC1004)     //
//================================================================//
