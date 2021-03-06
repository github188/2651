#ifndef __DRV_SENSOR_OV9712_H__
#define __DRV_SENSOR_OV9712_H__

/****************************************************************************/
#include "project.h"
#include "drv_l2_sensor.h"
#include "cdsp_cfg_iqj.h"

/****************************************************************************/
extern void sensor_ov9712_init(INT32U format, INT32U width, INT32U height);

/****************************************************************************/

#define OV9712_MAX_EXPOSURE_TIME			(1250)//50hz, (216*3)//60hz
#define OV9712_MIN_EXPOSURE_TIME			(8)
#define OV9712_MAX_ANALOG_GAIN				(8*256)//(MAX_ANALOG_GAIN*256) //(3*256)	//4x
#define OV9712_MIN_ANALOG_GAIN				(1*256)
#define OV9712_MAX_DIGITAL_GAIN				(2*256)//0x3=4x
#define OV9712_MIN_DIGITAL_GAIN 			(1*256)//0:1x

#define OV9712_ID	0x60

#define OV9712_FPS_30	0
#define OV9712_FPS_25	1
#define OV9712_FPS_20	2
#define CDSP_DOWN_FRAME						OV9712_FPS_25

//50Hz
#if (CDSP_DOWN_FRAME == OV9712_FPS_30)
#define OV9712_50HZ_EXP_TIME_TOTAL			212
#define	OV9712_50HZ_INIT_EV_IDX				140//61
#define OV9712_50HZ_NIGHT_EV_IDX			153//81
#define OV9712_50HZ_DAY_EV_IDX				100//51
#define OV9712_50HZ_MAX_EXP_IDX				(OV9712_50HZ_EXP_TIME_TOTAL-22)  // <= OV9712_50HZ_EXP_TIME_TOTAL
#elif (CDSP_DOWN_FRAME == OV9712_FPS_25)
#define OV9712_50HZ_EXP_TIME_TOTAL			221
#define	OV9712_50HZ_INIT_EV_IDX				140//61
#define OV9712_50HZ_NIGHT_EV_IDX			153//81
#define OV9712_50HZ_DAY_EV_IDX				100//51
#define OV9712_50HZ_MAX_EXP_IDX				(OV9712_50HZ_EXP_TIME_TOTAL-24)  // <= OV9712_50HZ_EXP_TIME_TOTAL
#elif (CDSP_DOWN_FRAME == OV9712_FPS_20)
#define OV9712_50HZ_EXP_TIME_TOTAL			231
#define	OV9712_50HZ_INIT_EV_IDX				140//61
#define OV9712_50HZ_NIGHT_EV_IDX			153//81
#define OV9712_50HZ_DAY_EV_IDX				100//51
#define OV9712_50HZ_MAX_EXP_IDX				(OV9712_50HZ_EXP_TIME_TOTAL-28)  // <= OV9712_50HZ_EXP_TIME_TOTAL
#endif

//60Hz
#if (CDSP_DOWN_FRAME == OV9712_FPS_30)
#define OV9712_60HZ_EXP_TIME_TOTAL			217
#define	OV9712_60HZ_INIT_EV_IDX				140
#define OV9712_60HZ_NIGHT_EV_IDX			153
#define OV9712_60HZ_DAY_EV_IDX				51
#define OV9712_60HZ_MAX_EXP_IDX				(OV9712_60HZ_EXP_TIME_TOTAL-25)  // <= OV9712_60HZ_EXP_TIME_TOTAL
#elif (CDSP_DOWN_FRAME == OV9712_FPS_25)
#define OV9712_60HZ_EXP_TIME_TOTAL			224
#define	OV9712_60HZ_INIT_EV_IDX				140
#define OV9712_60HZ_NIGHT_EV_IDX			153
#define OV9712_60HZ_DAY_EV_IDX				51
#define OV9712_60HZ_MAX_EXP_IDX				(OV9712_60HZ_EXP_TIME_TOTAL-29) //(OV9712_60HZ_EXP_TIME_TOTAL-22)  // <= OV9712_60HZ_EXP_TIME_TOTAL
#elif (CDSP_DOWN_FRAME == OV9712_FPS_20)
#define OV9712_60HZ_EXP_TIME_TOTAL			230
#define	OV9712_60HZ_INIT_EV_IDX				140
#define OV9712_60HZ_NIGHT_EV_IDX			153
#define OV9712_60HZ_DAY_EV_IDX				51
#define OV9712_60HZ_MAX_EXP_IDX				(OV9712_60HZ_EXP_TIME_TOTAL-12) //(OV9712_60HZ_EXP_TIME_TOTAL-22)  // <= OV9712_60HZ_EXP_TIME_TOTAL
#endif

#define COLOR_BAR_EN 0

#define OV9712_MIN_D_GAIN					1

#define OV9712_MIN_A_GAIN					1.5


/****************************************************************************/
#if (USE_SENSOR_NAME == SENSOR_OV9712)
void sensor_OV9712_init(INT32U WIDTH, INT32U HEIGHT);
extern void gp_Cdsp_SetAWBYUV(const INT16S *AwbTable);
extern void gp_Cdsp_SetBadPixOb(const INT16U *OBTable);
void OV9712_set_exposure_gain(void);

/**************************************************************************
 *                         G L O B A L    D A T A  For CDSP using                          *
 **************************************************************************/
#if (CDSP_DOWN_FRAME == OV9712_FPS_30)
static const  int g_OV9712_exp_time_gain_50Hz[OV9712_50HZ_EXP_TIME_TOTAL][3] =
{
    // {time, analog gain, digital gain}
    {8,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {8,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {16, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {16, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {18, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {19, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {19, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {20, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {21, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {21, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {22, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {23, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {24, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {25, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {25, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {26, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {27, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {28, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {29, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {30, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {31, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {32, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {33, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {35, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {36, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {37, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {38, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {40, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {41, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {43, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {44, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {46, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {47, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {49, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {51, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {53, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {54, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {56, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {58, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {60, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {63, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {65, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {67, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {69, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {72, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {74, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {77, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {80, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {82, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {85, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {88, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {92, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {95, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {98, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {102, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {105, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {109, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {113, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {117, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {121, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {125, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {129, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {134, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {139, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {144, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {149, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {154, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {159, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {165, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {171, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {177, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {183, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {189, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {196, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {203, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {210, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {218, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {225, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {233, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {241, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(3.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(3.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(3.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(3.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(3.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(3.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(3.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(3.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(4.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(4.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(5.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(5.75 * OV9712_MIN_A_GAIN * 256), (int)(1.02 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(6.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(6.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(6.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(6.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.07 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.11 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.15 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.19 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.23 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.27 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.32 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.37 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.41 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.46 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.52 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.57 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.62 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.68 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.74 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.80 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.87 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.93 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.25 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.50 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(7.75 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(8.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)}
};
#elif (CDSP_DOWN_FRAME == OV9712_FPS_25)
static const  int g_OV9712_exp_time_gain_50Hz[OV9712_50HZ_EXP_TIME_TOTAL][3] =
{
    // {time, analog gain, digital gain}
    {8,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {8,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {16, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {16, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {18, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {19, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {19, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {20, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {21, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {21, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {22, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {23, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {24, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {25, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {25, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {26, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {27, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {28, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {29, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {30, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {31, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {32, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {33, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {35, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {36, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {37, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {38, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {40, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {41, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {43, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {44, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {46, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {47, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {49, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {51, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {53, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {54, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {56, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {58, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {60, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {63, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {65, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {67, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {69, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {72, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {74, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {77, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {80, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {82, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {85, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {88, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {92, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {95, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {98, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {102, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {105, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {109, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {113, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {117, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {121, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {125, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {129, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {134, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {139, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {144, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {149, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {154, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {159, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {165, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {171, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {177, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {183, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {189, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {196, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {203, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {210, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {218, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {225, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {233, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {241, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {800, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {850, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {900, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {950, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(3.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(3.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(3.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(3.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(3.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(3.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(3.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(3.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(4.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(4.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(5.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(5.75 * OV9712_MIN_A_GAIN * 256), (int)(1.02 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(6.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(6.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(6.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(6.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.07 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.11 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.15 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.19 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.23 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.27 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.32 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.37 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.41 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.46 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.52 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.57 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.62 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.68 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.74 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.80 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.87 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.93 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.25 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.50 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(7.75 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(8.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)}
};
#elif (CDSP_DOWN_FRAME == OV9712_FPS_20)
static const  int g_OV9712_exp_time_gain_50Hz[OV9712_50HZ_EXP_TIME_TOTAL][3] =
{
    // {time, analog gain, digital gain}
    {8,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {8,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9,	(int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {16, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {16, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {18, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {19, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {19, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {20, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {21, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {21, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {22, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {23, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {24, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {25, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {25, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {26, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {27, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {28, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {29, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {30, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {31, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {32, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {33, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {35, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {36, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {37, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {38, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {40, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {41, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {43, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {44, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {46, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {47, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {49, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {51, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {53, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {54, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {56, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {58, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {60, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {63, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {65, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {67, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {69, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {72, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {74, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {77, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {80, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {82, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {85, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {88, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {92, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {95, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {98, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {102, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {105, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {109, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {113, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {117, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {121, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {125, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {129, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {134, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {139, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {144, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {149, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {154, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {159, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {165, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {171, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {177, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {183, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {189, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {196, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {203, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {210, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {218, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {225, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {233, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {241, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {250, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {500, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {750, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {800, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {850, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {900, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {950, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1000, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1050, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1100, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1150, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1200, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(3.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(3.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(3.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(3.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(3.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(3.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(3.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(3.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(4.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(4.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(5.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(5.75 * OV9712_MIN_A_GAIN * 256), (int)(1.02 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(6.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(6.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(6.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(6.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.07 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.11 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.15 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.19 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.23 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.27 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.32 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.37 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.41 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.46 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.52 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.57 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.62 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.68 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.74 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.80 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.87 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.93 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.25 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.50 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(7.75 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1250, (int)(8.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)}
};
#endif

#if (CDSP_DOWN_FRAME == OV9712_FPS_30)
static const  int g_OV9712_exp_time_gain_60Hz[OV9712_60HZ_EXP_TIME_TOTAL][3] =
{
    // {time, analog gain, digital gain}
    {8	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {8	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {8	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {16	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {18	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {18	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {19	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {20	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {20	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {21	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {22	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {23	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {23	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {24	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {25	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {26	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {27	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {28	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {29	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {30	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {31	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {32	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {33	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {34	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {36	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {37	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {38	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {39	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {41	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {42	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {44	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {45	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {47	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {49	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {50	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {52	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {54	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {56	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {58	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {60	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {62	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {64	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {66	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {69	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {71	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {74	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {76	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {79	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {82	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {84	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {87	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {91	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {94	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {97	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {100, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {104, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {108, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {111, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {115, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {119, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {124, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {128, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {133, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {137, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {142, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {147, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {152, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {158, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {163, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {169, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {175, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {181, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {187, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {194, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {201, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(3.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(3.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(3.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(3.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(3.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(3.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(3.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(3.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(4.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(4.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(5.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(5.75 * OV9712_MIN_A_GAIN * 256), (int)(1.02 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(6.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(6.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(6.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(6.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.07 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.11 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.15 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.19 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.23 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.27 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.32 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.37 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.41 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.46 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.52 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.57 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.62 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.68 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.74 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.80 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.87 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.93 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.25 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.50 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(7.75 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(8.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)}
    /*
    {8	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {8	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {8	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {9	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {9	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {9	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {10	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {10	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {10	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {11	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {11	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {11	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {12	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {12	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {13	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {13	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {13	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {14	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {14	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {15	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {15	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {16	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {17	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {17	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {18	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {18	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {19	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {20	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {20	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {21	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {22	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {23	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {23	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {24	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {25	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {26	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {27	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {28	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {29	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {30	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {31	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {32	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {33	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {34	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {36	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {37	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {38	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {39	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {41	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {42	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {44	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {45	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {47	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {49	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {50	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {52	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {54	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {56	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {58	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {60	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {62	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {64	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {66	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {69	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {71	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {74	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {76	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {79	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {82	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {84	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {87	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {91	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {94	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {97	,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {100,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {104,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {108,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {111,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {115,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {119,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {124,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {128,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {133,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {137,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {142,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {147,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {152,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {158,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {163,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {169,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {175,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {181,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {187,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {194,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {201,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.04*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.06*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.13*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.13*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.19*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.25*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.25*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.31*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.38*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.44*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.44*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.50*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.56*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.63*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.69*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.75*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.81*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.88*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {208,(int)(1.94*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.00*OV9712_MIN_A_GAIN*256), (int)(1.04*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.06*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.13*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.13*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.19*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.25*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.25*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.31*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.38*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.44*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.44*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.50*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.56*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.63*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.69*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.75*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.81*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.88*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {416,(int)(1.94*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.31*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.38*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.44*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.44*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.50*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.56*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.63*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.69*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.75*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.81*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.88*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(1.94*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.00*OV9712_MIN_A_GAIN*256), (int)(1.04*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.13*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.25*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.25*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.38*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.50*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.50*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.63*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.75*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.88*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(2.88*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(3.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(3.13*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(3.25*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(3.38*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(3.50*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(3.63*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(3.75*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(3.88*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(4.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(4.00*OV9712_MIN_A_GAIN*256), (int)(1.04*OV9712_MIN_D_GAIN*256)},
    {624,(int)(4.25*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(4.25*OV9712_MIN_A_GAIN*256), (int)(1.04*OV9712_MIN_D_GAIN*256)},
    {624,(int)(4.50*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(4.75*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(5.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(5.00*OV9712_MIN_A_GAIN*256), (int)(1.04*OV9712_MIN_D_GAIN*256)},
    {624,(int)(5.25*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(5.50*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(5.50*OV9712_MIN_A_GAIN*256), (int)(1.04*OV9712_MIN_D_GAIN*256)},
    {624,(int)(5.75*OV9712_MIN_A_GAIN*256), (int)(1.02*OV9712_MIN_D_GAIN*256)},
    {624,(int)(6.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(6.25*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(6.50*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(6.75*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.04*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.07*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.11*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.15*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.19*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.23*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.27*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.32*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.37*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.41*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.46*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.52*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.57*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.62*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.68*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.74*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.80*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.87*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(1.93*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.00*OV9712_MIN_A_GAIN*256), (int)(2.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.25*OV9712_MIN_A_GAIN*256), (int)(2.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.50*OV9712_MIN_A_GAIN*256), (int)(2.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(7.75*OV9712_MIN_A_GAIN*256), (int)(2.00*OV9712_MIN_D_GAIN*256)},
    {624,(int)(8.00*OV9712_MIN_A_GAIN*256), (int)(2.00*OV9712_MIN_D_GAIN*256)}
    */
};
#elif (CDSP_DOWN_FRAME == OV9712_FPS_25)
static const  int g_OV9712_exp_time_gain_60Hz[OV9712_60HZ_EXP_TIME_TOTAL][3] =
{
    // {time, analog gain, digital gain}
    {8	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {8	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {8	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {16	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {18	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {18	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {19	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {20	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {20	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {21	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {22	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {23	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {23	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {24	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {25	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {26	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {27	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {28	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {29	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {30	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {31	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {32	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {33	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {34	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {36	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {37	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {38	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {39	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {41	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {42	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {44	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {45	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {47	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {49	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {50	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {52	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {54	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {56	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {58	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {60	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {62	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {64	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {66	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {69	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {71	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {74	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {76	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {79	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {82	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {84	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {87	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {91	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {94	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {97	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {100, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {104, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {108, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {111, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {115, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {119, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {124, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {128, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {133, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {137, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {142, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {147, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {152, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {158, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {163, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {169, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {175, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {181, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {187, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {194, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {201, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(3.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(3.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(3.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(3.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(3.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(3.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(3.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(3.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(4.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(4.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(5.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(5.75 * OV9712_MIN_A_GAIN * 256), (int)(1.02 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(6.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(6.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(6.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(6.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.07 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.11 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.15 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.19 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.23 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.27 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.32 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.37 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.41 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.46 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.52 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.57 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.62 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.68 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.74 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.80 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.87 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.93 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.25 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.50 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(7.75 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(8.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)}
};
#elif (CDSP_DOWN_FRAME == OV9712_FPS_20)
static const  int g_OV9712_exp_time_gain_60Hz[OV9712_60HZ_EXP_TIME_TOTAL][3] =
{
    // {time, analog gain, digital gain}
    {8	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {8	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {8	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {9	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {10	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {11	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {12	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {13	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {14	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {15	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {16	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {17	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {18	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {18	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {19	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {20	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {20	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {21	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {22	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {23	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {23	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {24	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {25	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {26	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {27	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {28	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {29	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {30	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {31	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {32	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {33	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {34	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {36	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {37	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {38	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {39	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {41	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {42	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {44	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {45	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {47	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {49	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {50	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {52	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {54	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {56	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {58	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {60	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {62	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {64	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {66	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {69	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {71	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {74	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {76	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {79	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {82	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {84	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {87	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {91	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {94	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {97	, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {100, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {104, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {108, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {111, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {115, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {119, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {124, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {128, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {133, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {137, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {142, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {147, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {152, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {158, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {163, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {169, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {175, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {181, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {187, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {194, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {201, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {208, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.06 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.19 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {416, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.31 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {624, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.44 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {832, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.56 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1040, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(1.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(1.69 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(1.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(1.81 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(1.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(1.94 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(2.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(3.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(3.13 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(3.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(3.38 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(3.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(3.63 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(3.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(3.88 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(4.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(4.25 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(4.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(4.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(5.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(5.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(5.50 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(5.75 * OV9712_MIN_A_GAIN * 256), (int)(1.02 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(6.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(6.25 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(6.50 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(6.75 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.04 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.07 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.11 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.15 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.19 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.23 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.27 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.32 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.37 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.41 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.46 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.52 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.57 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.62 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.68 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.74 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.80 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.87 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(1.93 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.25 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.50 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(7.75 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)},
    {1248, (int)(8.00 * OV9712_MIN_A_GAIN * 256), (int)(2.00 * OV9712_MIN_D_GAIN * 256)}
};
#endif

/********************************************************************************
** Initial Code**
********************************************************************************/
static const INT8U OV9712_720P_F30_A24[][2] =
{
    {0x12, 0x80},	//Reset
    {0x09, 0x10},

    //---------------------------------------------------------
    //Core Settings
    //---------------------------------------------------------

    {0x1e, 0x07},
    {0x5f, 0x18},
    {0x69, 0x04},
    {0x65, 0x2a},
    {0x68, 0x0a},
    {0x39, 0x28},
    {0x4d, 0x90},
    {0xc1, 0x80},
    {0x0c, 0x30},
    {0x6d, 0x02},
    {0x60, 0x9d},


    //HYSNC Mode Enable
    /*
    {0xcb, 0x32},    //0x32:Hsync enable,0xA2:HREF enable
    {0xc3, 0x21},    //0x21;Starts to calculate the parameters for HYSNC mode
    {0xc2, 0x88},    //pclk gate disable
    */
#if 1
    {0x15, 0x00},	//40:HREF swap to HYSNC
    {0x30, 0x08},    //HYSNC Start Point
    {0x31, 0x20},    //HYSNC Stop Point
    {0x0c, 0x30},    //??[0]:single_frame_output
    {0x6d, 0x02},    //reserved
#endif

    //---------------------------------------------------------
    //DSP
    //---------------------------------------------------------
    {0x96, 0x00},	//0xf1: DSP options enable
    {0xbc, 0x68},	// [7]   reserved
    // [6:5] bd_sel
    // [4]   th_opt
    // [3:0] thresh_hold
    //---------------------------------------------------------
    //Resolution and Format
    //---------------------------------------------------------

    {0x12, 0x00},
    {0x3b, 0x00},	// DSP Downsample
    {0x97, 0x80},	// [7]   smph_mean
    // [6]   reserved
    // [5:4] smph_drop

    //---- Place generated settings here ----//
    /*HightxWeight*/
#if 0
    {0x17, 0x25},	//HSTART:0x25
    {0x18, 0xD0}, //0xCA},//{0x18,0xA2},	//HSize[10:3]	/*0xA2x8=0x510=1296*/0xca
    {0x19, 0x01},	//VSTART_MSBs
    {0x1a, 0xCF}, //{0x1a,0xCA},	//VSize_MSB[9:2] /*0xca0>>2=808*/
    {0x03, 0x0A},	//[3:2]VSize_LSBs,[1:0]VSTART_LSBs
    {0x32, 0x07},	//[5:3]HSize_LSBs[2:0],[2:0]HSTART_LSBs (0x07)
#else
    {0x17, 0x25},    //HSTART,start 0x25 valid frame
    {0x18, 0xa2},    //HSize_MSB /*0xa20>>1=1296*/
    {0x19, 0x02},    //0x0//VSTART_MSBs
    {0x1a, 0xCF},    //VSize_MSB /*0xca0>>2=808*/
    {0x03, 0x02},    //[3:2]VSize_LSBs,[1:0]VSTART_LSBs
    {0x32, 0x07},    //[5:3]HSize_LSBs,[2:0]HSTART_LSBs (0x07)
#endif

    {0x98, 0x00},
    {0x99, 0x28},
    {0x9a, 0x00},
    //DSP Output Size
    {0x57, 0x00},    	//DSP[4:2] output_Hszie_LSBs,[1:0]output_Vsize_LSBs
    {0x58, 0xB6},   	//DSP output_Vsize_MSBs	/*0xc80>>2=800; 0xb40>>2=720*/
    {0x59, 0xA2},   	//DSP output_Hsize_MSBs	/*0xa00>>1=1280*/

    {0x4c, 0x13},
    {0x4b, 0x36},

    {0xbd, 0xA0},
    {0xbe, 0xb4},

    //---------------------------------------------------------
    //Flip
    //---------------------------------------------------------
#if SENSOR_FLIP
    {0x04, 0xC8}, //Mirror & Flip
    {0x19, 0x00},
    {0x03, 0x0b},
#elif 0
    {0x04, 0x88}, //Mirror
    {0x19, 0x01},
    {0x03, 0x0a},
#elif 0//SENSOR_FLIP
    {0x04, 0x48}, //Flip		//VHREF must be adjusted.
    {0x19, 0x00},
    {0x03, 0x0b},
#else
    {0x04, 0x08}, //Normal
    {0x19, 0x01},
    {0x03, 0x0a},
#endif

    //---------------------------------------------------------
    //Frame Rate
    //---------------------------------------------------------
#if 1	//30fps
    {0x3d, 0x3c},	//VTS[7:0]0x507:19fps
    {0x3e, 0x03},	//VTS[15:8]0x407:24fps
#elif 0	//24fps
    {0x3d, 0x08},	//VTS[7:0]0x507:19fps
    {0x3e, 0x04},	//VTS[15:8]0x407:24fps
    //{0x19,0x02},
    //{0x03,0x0b},
#else	//19fps
    {0x3d, 0x07},	//VTS[7:0]0x507:19fps
    {0x3e, 0x05},	//VTS[15:8]0x407:24fps
    //{0x19,0x75},
    //{0x03,0x0a},
#endif
    //---------------------------------------------------------
    //Lens Correction
    //---------------------------------------------------------


    //---- Place lens correction settins here ----//
    // Lens model  	:
    // Module type	:



    //---------------------------------------------------------
    //YAVG
    //---------------------------------------------------------

    //---- Place generated "WIndows Weight" settings here ----//

    {0x4e, 0x55},	//AVERAGE
    {0x4f, 0x55},	//
    {0x50, 0x55},	//
    {0x51, 0x55},	//


    {0x24, 0x55},	//Exposure windows
    {0x25, 0x40},
    {0x26, 0xa1},

    //---------------------------------------------------------
    //Clock
    //---------------------------------------------------------
    {0x5c, 0x52},
    {0x5d, 0x00},
    {0x11, 0x01},
    {0x2a, 0x98},	//HTS[7:0]
    {0x2b, 0x06},	//HTS[15:8]
    {0x2d, 0x00},	//0xA6: 25fps, Vsync dummy,LSB
    {0x2e, 0x00},	//0x1A0: 20fps, Vsync dummy,MSB


    //---------------------------------------------------------
    //General
    //1x~16x is analog gain. 16x~ 64x is digital gain
    //0x00= 00 ~0F 1x ~2x gain 0x00= 10 ~1F 2x ~4x gain
    //0x00= 30 ~3F 4x ~8x gain 0x00= 70 ~7F 8x ~16x gain 0x00= f0 ~FF 16x ~32x gain
    //---------------------------------------------------------

    {0x13, 0xA5},
    {0x14, 0x40},	//0x40:Gain Ceiling 8X

    //---------------------------------------------------------
    //Banding
    //---------------------------------------------------------

    {0x4a, 0x00},
    {0x49, 0xce},
    {0x22, 0x03},


    //off 3A
    {0x13, 0x80}, // manual AEC/AGC
    {0x38, 0x00}, // 0x10:manual AWB, 0x0:ISP control WB
    {0xb6, 0x08},
    {0x96, 0xe1}, //0xe1},
    //
    {0x01, 0x40}, // Unity WB R/G/B Gain
    {0x02, 0x40},
    {0x05, 0x40},
    {0x06, 0x00},
    {0x07, 0x00},
    //

    {0x10, 0x50},		//Exposure_Time_LSB	//0xF9:2700K, 0xD0:6500K
    {0x16, 0x02},		//Exposure_Time_MSB
    {0x00, 0x00},		//AGC Gain CTRL for manual

#if 0 //COLOR_BAR_EN == 1	
    {0x96, 0xf1},
    {0x12, 0x02},    //tune resolution reference vertical or Horizontal timming
    {0x3b, 0x00},    //reserved
    {0x97, 0x08},    //smph_mean+colorbar
#endif

    {0x09, 0x00}
};

#if 0
static INT8U OV9712_720P_F30[][2] =	//1280*720,24MHz,30fps
{
    // CMOS Sensor Initialization Start...
    {0x12, 0x80},	//reset,[7]set to factory default values for all register

    /*Core Setting*/
    {0x1e, 0x07},   //reserved
    {0x5f, 0x18},    //reserved
    {0x69, 0x04},    //reserved
    {0x65, 0x2a},    //reserved
    {0x68, 0x0a},    //reserved
    {0x39, 0x28},    //reserved
    {0x4d, 0x90},    //reserved
    {0xc1, 0x80},	//added

    /*HYSNC Mode Enable*/
    {0xcb, 0x32},    //Hsync mode enable
    {0xc3, 0x21},    //0x29;Starts to calculate the parameters for HYSNC mode
    {0xc2, 0x88},//b1},//84},    //pclk gate disable

#if 1
    {0x15, 0x00},//40},	//HREF swap to HYSNC
    {0x30, 0x08},    //HYSNC Start Point
    {0x31, 0x20},    //HYSNC Stop Point
    {0x0c, 0x30},    //??[0]:single_frame_output
    {0x6d, 0x02},    //reserved
#endif

    /*DSP*/
    {0x96, 0x01}, 	//DSP options enable_0xf1, disable 0  //en_black&white_pixel,isp 0xC1
    //{0xbc, 0x68},    //WB_CTRL
    /* PLL (Pixel CLK)*/				//CLK1=XCLK(MCLK)/r5c[6:5]

#if 1			//pclk=1.7*mclk; 24Mhz->42Mhz->30fps
    {0x5c, 0x59},
    {0x5d, 0x00},
    {0x11, 0x00},
#else 			//pclk=//27MHz->10MHz /*for FPGA*/
    {0x5c, 0x5D},    		//CLK2 = ((mclk/2) *6) => 12/2*6=36
    {0x5d, 0x01},  			//CLK3 = CLK2/(r5d[3:2]+1)=>42/(0+1)=36
    {0x11, 0x01},			//PCLK=sysCLK=CLK3/((r11[5:0]+1)*2)=>36/((1+1)*2)=9
#endif

    /*Mirror & Vertical Flip*/
#if SENSOR_FLIP
    {0x04, 0xC0}, //Mirror & Flip
#elif 0
    {0x04, 0x80}, //Mirror
#elif 0
    {0x04, 0x40}, //Flip		//VHREF must be adjusted.
#else
    {0x04, 0x00}, //Normal
#endif

    /*Resolution and format*/
    {0x3b, 0x00},    //reserved
#if COLOR_BAR_EN == 1
    {0x96, 0xf1},
    {0x12, 0x02},    //tune resolution reference vertical or Horizontal timming
    {0x3b, 0x00},    //reserved
    {0x97, 0x08},    //smph_mean+colorbar
#else
    //{ 0x12, 0x00},
    {0x97, 0x80},    //smph_mean, test pattern
#endif

    /*HightxWeight*/
    {0x17, 0x25},    //HSTART,start 0x25 valid frame
    {0x18, 0xa2},    //HSize_MSB /*0xa20>>1=1296*/
    {0x19, 0x02},    //0x0//VSTART_MSBs
    {0x1a, 0xBB},    //VSize_MSB /*0xca0>>2=808*/
    {0x03, 0x02},    //[3:2]VSize_LSBs,[1:0]VSTART_LSBs
    {0x32, 0x02},//7},    //[5:3]HSize_LSBs,[2:0]HSTART_LSBs (0x07)

    {0x98, 0x00},   	//pre_out_hoff[7:0]		/*sccb_write-(SLAVE_ID,0x98, 0x00)*/
    {0x99, 0x00},   	//pre_out_voff[7:0]		/*sccb_write-(SLAVE_ID,0x99, 0x00)*/
    {0x9a, 0x00},   	//pre_out_voff[9:8],pre_out_hoff[10:8]/*sccb_write-(SLAVE_ID,0x9a, 0x00)*/
    //DSP Output Size
    {0x57, 0x00},    	//DSP[4:2] output_Hszie_LSBs,[1:0]output_Vsize_LSBs
    {0x58, 0xB5},   	//DSP output_Vsize_MSBs	/*0xc80>>2=800; 0xb40>>2=720*/
    {0x59, 0xA0},   	//DSP output_Hsize_MSBs	/*0xa00>>1=1280*/

    {0x4c, 0x13},    //reserved
    {0x4b, 0x36},    //reserved
    {0x3d, 0x3c},    //Red_counter_End_Point_LSBs
    {0x3e, 0x03},    //Red_counter_End_Point_MSBs

#if 1		//Manual Exposure time & Gain
    /*AEC/AGC/Banding function*/
    {0x13, 0x80},	//0x00:manual_en,0x20:AEC Banding,0x08:LAEC_en,0x04:AGC_en,0x01:Exposure_en
    {0x38, 0x00},
    {0xb6, 0x08},
    {0x96, 0x01},

    {0x10, 0xf0},		//Exposure_Time_LSB
    {0x16, 0x03},		//Exposure_Time_MSB
    {0x00, 0x15},		//AGC Gain CTRL for manual

    {0x4a, 0x00},	//Banding step MSBs[1:0]
    {0x49, 0xce},	//Banding step LSBs[1:0]
    {0x22, 0x03},	//Max smooth banding steps
    //{0x09, 0x00},
    {0x0d, 0x01},	//AEC_ctrl,default:0x01,
    {0x0e, 0x48},	//AEC/AGC_based mode,default:0x40,
    {0x14, 0x40},//40},	//AGC-Gainx8(0x40)
    {0x1f, 0x0},		//LAEC[7:0]:less_lan_1_row_of_exposure_time
    {0x3c, 0x0},		//LAEC[15:8]

    {0xc8, 0x00},	//h2v delay[5:3]
    {0xc9, 0x80},

    {0x01, 0x40},
    {0x02, 0x40},
    {0x05, 0x40},
    {0x06, 0x00},
    {0x07, 0x00},
    /*Add Horizomtal TP & Dummy Line*/
    //{0x2a, 0xA0},	//[7:0], enhance Dummy Line
    //{0x2b, 0x07},	//[15:8]
    {0x2d, 0x00},	//[7:0]
    {0x2e, 0x00},	//[15:8]

    /*AEC/AGC operation*/				//Maximum_Exposue_Lines:[(0x1A+0x03[3:2])-2Lines]
    //{0x24, 0x70},    //Luminance Signal High Range for AEC/AGC
    //{0x25, 0x40},    //Luminance Signal Low  Range for AEC/AGC
    //{0x26, 0xa1},    //Fast mode Thresholds,([3:0]*16)>YAVG(0x2f)>([7:4]*16)
#endif

    /*BLC*/
    {0x41, 0x82},
    {0x37, 0x02},

    {0x2f, 0x00},//55},    //Luminance_Average_Value(YAVG)



    {0x09, 0x08},   	//[4]:Chip sleep mode, [3]:Reset sensor timing when mode changes
    {0x55, 0xff},    //0xfc:disable Y0,Y1; 0xff:enable Y0,Y1
    {0x56, 0x1f},    //Enable HREF & enable HSync b[1:0]=Y9,Y8
    {0xca, 0x20} 	//test pattern bit b[2]0:10bit, 1:8bit

};
#endif

static const INT8U OV9712_1280_800_F30[][2] =	//1280*800,24MHz,30fps
{
    // CMOS Sensor Initialization Start...
    {0x12, 0x80},	//reset,[7]set to factory default values for all register

    /*Core Setting*/
    {0x1e, 0x07},   	//reserved
    {0x5f, 0x18},    //reserved
    {0x69, 0x04},    //reserved
    {0x65, 0x2a},    //reserved
    {0x68, 0x0a},    //reserved
    {0x39, 0x28},    //reserved
    {0x4d, 0x90},    //reserved
    {0xc1, 0x80},	//added

    /*HYSNC Mode Enable*/
    {0xcb, 0x32},    //Hsync mode enable
    {0xc3, 0x21},    //0x29;Starts to calculate the parameters for HYSNC mode
    {0xc2, 0x88},//b1},//84},    //pclk gate disable

#if 1
    {0x15, 0x00},//40},	//HREF swap to HYSNC
    {0x30, 0x05},    //HYSNC Start Point
    {0x31, 0x20},    //HYSNC Stop Point
    {0x0c, 0x30},    //??[0]:single_frame_output
    {0x6d, 0x02},    //reserved
#endif

    /*DSP*/
    {0x96, 0x00}, 	//DSP options enable_0xf1, disable 0  //en_black&white_pixel,isp 0xC1
    {0xbc, 0x68},    //WB_CTRL
    /* PLL (Pixel CLK)*/				//CLK1=XCLK(MCLK)/r5c[6:5]
#if 1
#if 0	//pclk=2*mclk
    {0x5c, 0x17},
    {0x5d, 0x84},
    {0x11, 0x00},
#elif 1	//pclk=//27MHz->10MHz /*for FPGA*/
    {0x11, 0x01},			//PCLK=sysCLK=CLK3/((r11[5:0]+1)*2)=>36/((1+1)*2)=9
    {0x5c, 0x5D},    		//CLK2 = ((mclk/2) *6) => 12/2*6=36
    {0x5d, 0x01},  			//CLK3 = CLK2/(r5d[3:2]+1)=>42/(0+1)=36
#elif 0		//pclk=mclk/4  (27MHz->7MHz)	//未確認是否可行						
    {0x11, 0x01},			//PCLK=sysCLK=CLK3/((r11[5:0]+1)*2)=>PCLK=54/((1+1)*2)
    {0x5c, 0x5D},    		//CLK2=CLK1*(32-r5c[4:0]) ,CLK1=(MCLK/r5c[6:5])=>CLK2=((27/2)*(32-28))=54MHz
    {0x5d, 0x01},  			//CLK3=CLK2/(r5d[3:2]+1)=>CLK3=54/(0+1)=54
#else 		//pclk=mclk/2  //未確認是否可行		
    {0x11, 0x01},			//PCLK=sysCLK=CLK3/((r11[5:0]+1)*2)=>PCLK=54/((1+1)*2)
    {0x5c, 0x5E},    		//CLK2=CLK1*(32-r5c[4:0]) ,CLK1=(MCLK/r5c[6:5])=>CLK2=((27/2)*(32-28))=54MHz
    {0x5d, 0xC0},
#endif
#endif

    /*Mirror & Vertical Flip*/
#if 1
    {0x04, 0x00}, //Normal
#elif 0
    {0x04, 0x80}, //Mirror
#elif 0
    {0x04, 0x40}, //Flip		//VHREF must be adjusted.
#else
    {0x04, 0xC0}, //Mirror & Flip
#endif

    /*Resolution and format*/
    {0x3b, 0x00},    //reserved
#if COLOR_BAR_EN == 1
    {0x96, 0xf1},
    {0x12, 0x02},    //tune resolution reference vertical or Horizontal timming
    {0x3b, 0x00},    //reserved
    {0x97, 0x08},    //smph_mean+colorbar
#else
    //{ 0x12, 0x00},
    {0x97, 0x80},    //smph_mean, test pattern
#endif

    /*HightxWeight*/
    {0x17, 0x25},    //HSTART,start 0x25 valid frame
    {0x18, 0xa2},    //HSize_MSB /*0xa20>>1=1296*/
    {0x19, 0x02},    //0x0//VSTART_MSBs
    {0x1a, 0xca},    //VSize_MSB /*0xca0>>2=808*/
    {0x03, 0x02},    //[3:2]VSize_LSBs,[1:0]VSTART_LSBs
    {0x32, 0x00},//7},    //[5:3]HSize_LSBs,[2:0]HSTART_LSBs (0x07)

    {0x98, 0x00},   	//pre_out_hoff[7:0]		/*sccb_write-(SLAVE_ID,0x98, 0x00)*/
    {0x99, 0x00},   	//pre_out_voff[7:0]		/*sccb_write-(SLAVE_ID,0x99, 0x00)*/
    {0x9a, 0x00},   	//pre_out_voff[9:8],pre_out_hoff[10:8]/*sccb_write-(SLAVE_ID,0x9a, 0x00)*/
    {0x57, 0x00},    //DSP[4:2] output_Hszie_LSBs,[1:0]output_Vsize_LSBs
    {0x58, 0xc8},   	//DSP output_Vsize_MSBs	/*0xc80>>2=800; 0xb40>>2=720*/
    {0x59, 0xa0},   	//DSP output_Hsize_MSBs	/*0xa00>>1=1280*/
    {0x4c, 0x13},    //reserved
    {0x4b, 0x36},    //reserved
    {0x3d, 0x3c},    //Red_counter_End_Point_LSBs
    {0x3e, 0x03},    //Red_counter_End_Point_MSBs

#if 1		//Manual Exposure time & Gain
    /*AEC/AGC/Banding function*/
    {0x13, 0x0},	//OFF Fast AEC adj,Banding ,Auto AGC, Auto Exposure

    {0x10, 0xf0},		//Exposure_Time_LSB
    {0x16, 0x01},		//Exposure_Time_MSB
    {0x00, 0x15},		//AGC Gain CTRL for manual

    {0x4a, 0x00},	//Banding step MSBs[1:0]
    {0x49, 0xce},	//Banding step LSBs[1:0]
    {0x22, 0x03},	//Max smooth banding steps
    //{0x09, 0x00},
    {0x0d, 0x01},	//AEC_ctrl,default:0x01,
    {0x0e, 0x40},	//AEC/AGC_based mode,default:0x40,
    {0x14, 0x50},//40},	//AGC-Gainx8(0x40)
    {0x1f, 0x0},		//LAEC[7:0]:less_lan_1_row_of_exposure_time
    {0x3c, 0x0},		//LAEC[15:8]

    /*AEC/AGC operation*/				//Maximum_Exposue_Lines:[(0x1A+0x03[3:2])-2Lines]
    {0x24, 0x70},    //Luminance Signal High Range for AEC/AGC
    {0x25, 0x40},    //Luminance Signal Low  Range for AEC/AGC
    {0x26, 0xa1},    //Fast mode Thresholds,([3:0]*16)>YAVG(0x2f)>([7:4]*16)
#endif

#if 0	//Auto Exporsure & Gain
    /*AEC/AGC/Banding function*/
    {0x13, 0xa5},	//Fast AEC adj,Banding ON,Auto AGC, Auto Exposure
    {0x1f, 0x0},		//LAEC[7:0]:less_lan_1_row_of_exposure_time
    {0x3c, 0x0},		//LAEC[15:8]
    {0x00, 0x80},		//AGC Gain CTRL
    {0x14, 0x40},	//AGC-Gainx8(0x40)

    {0x4a, 0x00},	//Banding step MSBs[1:0]
    {0x49, 0xce},	//Banding step LSBs[1:0]
    {0x22, 0x03},	//Max smooth banding steps
    //{0x09, 0x00},

    {0x10, 0x60},		//Exposure_Time_LSB
    {0x16, 0x02},		//Exposure_Time_MSB
    {0x0d, 0x01},	//AEC_ctrl,default:0x01,
    {0x0e, 0x40},	//AEC/AGC_based mode,default:0x40,

    /*AEC/AGC operation*/				//Maximum_Exposue_Lines:[(0x1A+0x03[3:2])-2Lines]
    {0x24, 0x70},    //Luminance Signal High Range for AEC/AGC
    {0x25, 0x40},    //Luminance Signal Low  Range for AEC/AGC
    {0x26, 0xa1},    //Fast mode Thresholds,([3:0]*16)>YAVG(0x2f)>([7:4]*16)

    /*YAVG_CTRL*/
    {0xc1, 0x80},    //YAVG_CTRL:yacg_win_man en
    {0xbd, 0xa0},   	//yavg_winh	/*sccb_write-(SLAVE_ID,0xbd, 0xa0},*/
    {0xbe, 0xc8},   	//yavg_winv	/*sccb_write-(SLAVE_ID,0xbe, 0xc8},*/
    /*16-Zone_Y_Avarage_Select*/
    {0x4e, 0x55},    //Y Avg Select:zone1~4 = weight x 1
    {0x4f, 0x55},	//Y Avg Select:zone5~8 = weight x 1
    {0x50, 0x55},	//Y Avg Select:zone9~12 = weight x 1
    {0x51, 0x55},	//Y Avg Select:zone13~16 = weight x 1
    {0x2c, 0x60},	//Reserved
    {0x23, 0x10},    //Reserved

    /*Histogram-based*/
    {0x72, 0x60},    //
    {0x73, 0x49},    //
    {0x74, 0xe0},    //
    {0x75, 0xe0},    //
    {0x76, 0xc0},    //
    {0x77, 0xc0},    //
    {0x78, 0xff},    //
    {0x79, 0xff},    //
#endif

    {0x2f, 0x00},//55},    //Luminance_Average_Value(YAVG)

    {0x09, 0x08},   	//[4]:Chip sleep mode, [3]:Reset sensor timing when mode changes
    {0x55, 0xff},    //0xfc:disable Y0,Y1; 0xff:enable Y0,Y1
    {0x56, 0x1f},    //Enable HREF & enable HSync b[1:0]=Y9,Y8
    {0xca, 0x20} 	//test pattern bit b[2]0:10bit, 1:8bit

};

static const INT8U OV9712_VGA_F30[][2] =	//640*400,24MHz, 30fps	//copy from 1280p
{
    {0x12, 0x80},	//reset,[7]set to factory default values for all register
    //sccb_delay (200},

    //{0x09, 0x10},   	//[4]:Chip sleep mode, [3]:Reset sensor timing when mode changes
    /*Core Setting*/
    {0x1e, 0x07},   	//reserved
    {0x5f, 0x18},    //reserved
    {0x69, 0x04},    //reserved
    {0x65, 0x2a},    //reserved
    {0x68, 0x0a},    //reserved
    {0x39, 0x28},    //reserved
    {0x4d, 0x90},    //reserved
    {0xc1, 0x80},	//added

    //sccb_read(SLAVE_ID, 0x65},				//read

    /*DSP*/
    {0x96, 0x01}, 	//DSP options enable_0xf1, disable 0  //en_black&white_pixel,isp 0xC1
    {0xbc, 0x68},    //WB_CTRL

    /*HYSNC Mode Enable*/
    {0xcb, 0x32},    //Hsync mode enable
    {0xc3, 0x21},    //0x29;Starts to calculate the parameters for HYSNC mode
    {0xc2, 0x88},    //pclk gate disable

    {0x15, 0x0},	//HREFswaptoHYSNC(0x40)
    {0x30, 0x05},    //HYSNC Start Point
    {0x31, 0x20},    //HYSNC Stop Point
    {0x0c, 0x30},    //??[0]:single_frame_output
    {0x6d, 0x02},    //reserved

    /*Resolution and format*/
#if 0	//this config disable dsp still can start sensor
    {0x12, 0x80},   //software reset
    {0x3b, 0x0},    //reserved
    {0x97, 0x0},    //smph_mean
#endif

#if 0	//show test pattern colorBar
    //{0x12, 0x80},    //tune resolution reference vertical or Horizontal timming
    {0x3b, 0x0},    //reserved
    {0x97, 0x88},    //smph_mean+colorbar
#endif

#if 1
    {0x96, 0x01},	//dsp must be enable
    {0x12, 0x40},   	//tune_resolution_reference_vertical_orHorizontal_timming(down sample)
    {0x3b, 0x0},    	//reserved
    {0x97, 0x80},   	//smph_mean
#endif

    //{0x3b, 0x0},    	//reserved
    //{0x97, 0x0},	//smph_mean

    /*HightxWeight*/
    {0x17, 0x25},    //HSTART,MSBs 0x25
    {0x18, 0xa2},    //HSize (0xa20>>1=1296) (H640= 0x510>>1)
    {0x19, 0x01},    //0x0//VSTART_MSBs
    {0x1a, 0x78},    //VSize_MSBs  (0x780>>2=480)
    {0x03, 0x02},    //[3:2]VSize_LSBs,[1:0]VSTART_LSBs
    {0x32, 0x07},    //[3:2]HSize_LSBs,[1:0]HSTART_LSBs (0x07)

    {0x98, 0x00},   	//pre_out_hoff[7:0]		/*sccb_write-(SLAVE_ID,0x98, 0x00)*/
    {0x99, 0x00},   	//pre_out_voff[7:0]		/*sccb_write-(SLAVE_ID,0x99, 0x00)*/
    {0x9a, 0x00},   	//pre_out_voff[9:8],pre_out_hoff[10:8]/*sccb_write-(SLAVE_ID,0x9a, 0x00)*/
    {0x57, 0x00},    //DSP[4:2] output_Hszie_LSBs,[1:0]output_Vsize_LSBs
    {0x58, 0x78},   	//DSP output_Vsize_MSBs	/*0x780>>2=480*/ 0xb40=0x2d0=720
    {0x59, 0x50},   	//DSP output_Hsize_MSBs	/*0x500>>1=640*/
    {0x4c, 0x09},    //reserved
    {0x4b, 0x9a},    //reserved
    {0x3d, 0x9e},//3c},    //Red_counter_End_Point_LSBs
    {0x3e, 0x01},//03},    //Red_counter_End_Point_MSBs

    /*YAVG_CTRL*/
    {0xc1, 0x80},    //YAVG_CTRL:yacg_win_man en
    {0xbd, 0xa0},   	//yavg_winh	/*sccb_write-(SLAVE_ID,0xbd, 0xa0},*/
    {0xbe, 0xc8},   	//yavg_winv	/*sccb_write-(SLAVE_ID,0xbe, 0xc8},*/
    {0x4e, 0x55},    //Y Avg Select:zone1~4 = weight x 1
    {0x4f, 0x55},	//Y Avg Select:zone5~8 = weight x 1
    {0x50, 0x55},	//Y Avg Select:zone9~12 = weight x 1
    {0x51, 0x55},	//Y Avg Select:zone13~16 = weight x 1
    {0x2c, 0x60},	//Reserved
    {0x23, 0x10},    //Reserved

    /*AEC/AGC operation*/
    {0x24, 0x55},    //Luminance Signal High Range for AEC/AGC
    {0x25, 0x40},    //Luminance Signal Low  Range for AEC/AGC
    {0x26, 0xa1},    //Thresholds effective

#if 1
    /*AEC/AGC/Banding function*/
    {0x4a, 0x00},	//Banding step MSBs[1:0]
    {0x49, 0xce},	//Banding step LSBs[1:0]
    {0x22, 0x03},	//Max smooth banding steps
    //{0x09, 0x00},
    {0x16, 0x01},
    {0x10, 0x35},
    {0x00, 0x08},	//AGC Gain CTRL
    {0x09, 0x08},   	//[4]:Chip sleep mode, [3]:Reset sensor timing when mode changes
    {0x55, 0xfc},    //disable Y0,Y1
    {0x56, 0x1f},    //Enable HREF & enable HSync
#endif

    /* PLL (Pixel CLK)*/				//CLK1=XCLK(MCLK)/r5c[6:5]
#if 0	//pclk=mclk*2
    {0x5c, 0x17},    //CLK2=CLK1*(32-r5c[4:0])
    {0x5d, 0x84},    	//CLK3  clk2/1
    {0x11, 0x00},		//sysCLK clk3/((reg+1)*2)
#else	//for FPGA pclk=mclk/2
    {0x5c, 0x59},    //CLK2  plck=mclk/4 *7
    {0x5d, 0x00},  	//CLK3=CLK2/(r5d[3:2]+1)
    {0x11, 0x01},	//sysCLK clk3/((reg+1)*2)
#endif									//PCLK=sysCLK=CLK3/((r11[5:0]+1)*2)


    //{0xd6, 0x0c},	//0x00 //system control

    /*H TP Counter End Point*/
    {0x2a, 0x98},	//LSBs
    {0x2b, 0x06},	//MSBs

    /*For night mode*/
    {0x2d, 0x00},	//dummy line_LSBs
    {0x2e, 0x00},	//dummy line_MSBs

    {0x13, 0x00},	//OFF Fast AEC adj,Banding ,Auto AGC, Auto Exposure
    {0x14, 0x10}	//AGC Gain*8(0x40)
};


/**************************************************************************
 *                         G L O B A L    D A T A  For CDSP using                          *
 **************************************************************************/
static const short OV9712_badpix_ob_table[12] =
{
    0, 		// obautoen
    1, 		// obmanuen
    8, 		// maunob

    1, 		// wboffseten
    0,		// wbo_r
    0, 		// wbo_gr
    0, 		// wbo_gb
    0, 		// wbo_b

    1,		//badPixel En
    160,	//bprthr
    160,	//bpgthr
    160		//bpbthr
};

/*
static const unsigned short OV9712_r_b_gain[71][2] =
{
{33, 143}, // 2
{36, 142},
{39, 141},
{42, 140},
{44, 140},
{47, 139},
{49, 138},
{52, 137},
{54, 136},
{56, 135}, // 3
{58, 134},
{60, 132},
{62, 131},
{64, 130},
{66, 129},
{68, 128}, // 3.6
{69, 127},
{71, 126},
{72, 124},
{74, 123}, // 4
{75, 122},
{77, 121},
{78, 119},
{79, 118},
{80, 117},
{81, 115},
{82, 114},
{83, 113},
{84, 111},
{84, 110}, // 5
{85, 108},
{86, 107},
{86, 105},
{87, 104},
{88, 102}, // 5.5
{88, 101},
{88, 99},
{89, 98},
{89, 96},
{90, 95},  // 6
{90, 93},
{90, 91},
{90, 90},
{90, 88},
{91, 86},  // 6.5
{91, 84},
{91, 83},
{91, 81},
{91, 79},
{91, 77},
{91, 76},
{91, 74},
{91, 72},
{91, 70},
{91, 68},
{90, 66},
{90, 64},
{90, 62},
{90, 60},
{90, 58},
{90, 56},
{90, 54},
{89, 52},
{89, 50},
{89, 48},
{89, 46},
{89, 44},
{89, 41},
{89, 39},
{89, 37},
{88, 35}
};


static const unsigned int OV9712_gamma_045_table[] =
{
0x11110a, 0x11110e, 0x111112, 0x011116, 0x04441a, 0x11041e, 0x011121, 0x044425,
0x011128, 0x10442c, 0x04112f, 0x110433, 0x104436, 0x044139, 0x04113c, 0x011040,
0x011043, 0x011046, 0x011049, 0x04104c, 0x04104f, 0x104151, 0x104154, 0x010457,
0x04105a, 0x10415c, 0x04045f, 0x104161, 0x010464, 0x104166, 0x041069, 0x01016b,
0x10406e, 0x040470, 0x010472, 0x004174, 0x104077, 0x101079, 0x04107b, 0x04047d,
0x04047f, 0x040481, 0x040483, 0x040485, 0x101087, 0x101089, 0x00408b, 0x00408d,
0x01018e, 0x040490, 0x001092, 0x004094, 0x040195, 0x100497, 0x004099, 0x04019a,
0x00109c, 0x01009e, 0x10049f, 0x0040a1, 0x1001a2, 0x0040a4, 0x1001a5, 0x0040a7,
0x1004a8, 0x0100aa, 0x0004ab, 0x0100ad, 0x0010ae, 0x0401af, 0x0040b1, 0x0004b2,
0x0400b4, 0x0010b5, 0x1001b6, 0x0100b8, 0x0010b9, 0x1001ba, 0x0100bc, 0x0010bd,
0x1001be, 0x0100c0, 0x0010c1, 0x1001c2, 0x0100c4, 0x0010c5, 0x1001c6, 0x0100c8,
0x0010c9, 0x1001ca, 0x0100cc, 0x0010cd, 0x1001ce, 0x0100d0, 0x0010d1, 0x0400d3,
0x0040d4, 0x1004d5, 0x0100d7, 0x0010d8, 0x0400da, 0x0010db, 0x0401dc, 0x0010de,
0x0401df, 0x0010e1, 0x0401e2, 0x0010e4, 0x0100e6, 0x1004e7, 0x0040e9, 0x0401ea,
0x0010ec, 0x0040ee, 0x0401ef, 0x1010f1, 0x0040f3, 0x0100f5, 0x0401f6, 0x0404f8,
0x1010fa, 0x1010fc, 0x0010fe, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff
};

static const short OV9712_color_matrix4gamma045[9] =
{
	(short) (1.20584525531044860000*64),
	(short) (-0.1508717276180829600*64),
	(short) (-0.0549735276923655550*64),
	(short) (-0.2250626277587189100*64),
	(short) (1.32599878790178850000*64),
	(short) (-0.1009361601430696400*64),
	(short) (-0.0027266614940476691*64),
	(short) (-0.9601597518226134800*64),
	(short) (1.96288641331666120000*64)
};

static const short OV9712_awb_thr[19] =
{
	200, // awbwinthr

	0*64, // sindata
	1*64, // cosdata

	 30, // Ythr0
	 90, // Ythr1
	150, // Ythr2
	200, // Ythr3

	-4, // UL1N1
	 6, // UL1P1
	-4, // VL1N1
	 4, // VL1P1

	 -6, //UL1N2
	  8, //UL1P2
	 -6, //VL1N2
	  6, // VL1P2

	 -9, // UL1N3
	  8, //UL1P3
	 -9, // VL1N3
	  7, //VL1P3
};*/


static const unsigned short OV9712_r_b_gain[71][2] =
{
    {63 , 191},
    {64 , 187},
    {64 , 184},
    {65 , 180},
    {66 , 177},
    {67 , 173},
    {68 , 170},
    {69 , 167},
    {70 , 164},
    {71 , 161},
    {72 , 158},
    {73 , 155},
    {74 , 152},
    {75 , 149},
    {76 , 146},
    {77 , 144},
    {78 , 141},
    {79 , 139},
    {81 , 136},
    {82 , 134},
    {83 , 132},
    {84 , 129},
    {85 , 127},
    {87 , 125},
    {88 , 123},
    {89 , 121},
    {90 , 119},
    {92 , 118},
    {93 , 116},
    {94 , 114},
    {96 , 113},
    {97 , 111},
    {99 , 110},
    {100, 108},
    {101, 107},
    {103, 106},
    {104, 105},
    {106, 104},
    {107, 103},
    {109, 102},
    {110, 101},
    {112, 100},
    {114, 100},
    {115, 99 },
    {117, 98 },
    {118, 98 },
    {120, 98 },
    {122, 97 },
    {124, 97 },
    {125, 97 },
    {127, 97 },
    {129, 97 },
    {130, 97 },
    {132, 97 },
    {134, 97 },
    {136, 97 },
    {138, 97 },
    {140, 98 },
    {141, 98 },
    {143, 99 },
    {145, 99 },
    {147, 100},
    {149, 101},
    {151, 102},
    {153, 103},
    {155, 104},
    {157, 105},
    {159, 106},
    {161, 107},
    {163, 108},
    {165, 110}

};

static const unsigned int OV9712_gamma_045_table[] =
{
    0x111415, 0x111119, 0x04511d, 0x044422, 0x044426, 0x04442a, 0x11102e, 0x111131,
    0x044135, 0x104439, 0x01113c, 0x044440, 0x011143, 0x110447, 0x04414a, 0x04114d,
    0x011051, 0x010454, 0x010457, 0x01045a, 0x01045d, 0x041060, 0x041063, 0x104165,
    0x010468, 0x04106b, 0x10416d, 0x040470, 0x104172, 0x041075, 0x010177, 0x10107a,
    0x04047c, 0x01047e, 0x004180, 0x004083, 0x101085, 0x101087, 0x101089, 0x10108b,
    0x10108d, 0x00408f, 0x004091, 0x010192, 0x040194, 0x100496, 0x004098, 0x01009a,
    0x10049b, 0x00409d, 0x04019e, 0x0010a0, 0x0100a2, 0x1004a3, 0x0100a5, 0x0004a6,
    0x0100a8, 0x0010a9, 0x0400ab, 0x0040ac, 0x1004ad, 0x0100af, 0x0010b0, 0x1001b1,
    0x0400b3, 0x0040b4, 0x0004b5, 0x1000b7, 0x0100b8, 0x0010b9, 0x0004ba, 0x1000bc,
    0x0100bd, 0x0040be, 0x0004bf, 0x1001c0, 0x0400c2, 0x0040c3, 0x0010c4, 0x0001c5,
    0x1000c7, 0x0100c8, 0x0040c9, 0x0004ca, 0x1001cb, 0x0100cd, 0x0040ce, 0x0004cf,
    0x1000d1, 0x0100d2, 0x0010d3, 0x1001d4, 0x0100d6, 0x0010d7, 0x1001d8, 0x0100da,
    0x0004db, 0x0400dd, 0x0010de, 0x0401df, 0x0040e1, 0x0401e2, 0x0010e4, 0x0400e6,
    0x0010e7, 0x0100e9, 0x0401ea, 0x0010ec, 0x0040ee, 0x0401ef, 0x1004f1, 0x1010f3,
    0x0040f5, 0x0040f7, 0x0101f8, 0x0101fa, 0x0101fc, 0x0001fe, 0x0000ff, 0x0000ff,
    0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff
};
static const short OV9712_color_matrix4gamma045[9] =
{
    (short) (1.09593623513238380000 * 64),
    (short) (-0.2603013044668260300 * 64),
    (short) (0.16436506933444223000 * 64),
    (short) (0.15535309409367457000 * 64),
    (short) (0.73387843343490966000 * 64),
    (short) (0.11076847247141582000 * 64),
    (short) (0.19357256156957131000 * 64),
    (short) (-0.4483282158392732900 * 64),
    (short) (1.25475565426970200000 * 64)
};


static const short OV9712_awb_thr[19] =
{
    200, // awbwinthr

    0 * 64, // sindata
    1 * 64, // cosdata

    30, // Ythr0
    90, // Ythr1
    150, // Ythr2
    200, // Ythr3

    -5, // UL1N1
    7, // UL1P1
    -5, // VL1N1
    6, // VL1P1

    -6, //UL1N2
    7, //UL1P2
    -6, //VL1N2
    7, // VL1P2

    -8, // UL1N3
    7, //UL1P3
    -7, // VL1N3
    7, //VL1P3
};

#endif //(USE_SENSOR_NAME == SENSOR_OV9712)
/****************************************************************************/
#endif	// __DRV_SENSOR_OV9712_H__
/****************************************************************************/
