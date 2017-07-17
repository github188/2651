#include "stdio.h"
#include "string.h"
#include "drv_l1_uart.h"
#include "drv_l1_gsensor.h"
#include "avi_audio_record.h"
#include "ap_state_config.h"

#define FLOAT float

#define C_AVI_AUDIO_RECORD_STACK_SIZE	512
#define C_AVI_AUD_ACCEPT_MAX			(AVI_ENCODE_PCM_BUFFER_NO+8)

/* static function */
AVIPACKER_FRAME_INFO audio_frame[AVI_ENCODE_PCM_BUFFER_NO] = {0};

/*os task stack */
static INT32U	AviAudioRecordStack[C_AVI_AUDIO_RECORD_STACK_SIZE];

/* os task queue */
static OS_EVENT *avi_aud_q;
static OS_EVENT *avi_aud_ack_m;
static void *avi_aud_q_stack[C_AVI_AUD_ACCEPT_MAX];

extern INT8U gsensor_data[2][32];

Gsensor_Data gs_data = {0};

INT32U	gWriteAudioAddr = 0;
INT8U   write_audio_idx = 0;
INT32U  ready_addr, next_addr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void avi_adc_gsensor_data_register(void **msgq_id, INT32U *msg_id)
{
    *msgq_id = (void *)avi_aud_q;
    *msg_id = AVI_G_SENSOR_INFO_HANDLE;
}

INT32S avi_adc_record_task_create(INT8U pori)
{
    INT8U  err;
    INT32S nRet;

    avi_aud_q = OSQCreate(avi_aud_q_stack, C_AVI_AUD_ACCEPT_MAX);
    if(!avi_aud_q) RETURN(STATUS_FAIL);

    avi_aud_ack_m = OSMboxCreate(NULL);
    if(!avi_aud_ack_m) RETURN(STATUS_FAIL);

    err = OSTaskCreate(avi_audio_record_entry, NULL, (void *)&AviAudioRecordStack[C_AVI_AUDIO_RECORD_STACK_SIZE - 1], pori);
    if(err != OS_NO_ERR) RETURN(STATUS_FAIL);

    nRet = STATUS_OK;
Return:
    return nRet;
}

INT32S avi_adc_record_task_del(void)
{
    INT8U  err;
    INT32U nRet, msg;

    nRet = STATUS_OK;
    POST_MESSAGE(avi_aud_q, AVI_AUDIO_RECORD_EXIT, avi_aud_ack_m, 5000, msg, err);
Return:
    OSQFlush(avi_aud_q);
    OSQDel(avi_aud_q, OS_DEL_ALWAYS, &err);
    OSMboxDel(avi_aud_ack_m, OS_DEL_ALWAYS, &err);
    return nRet;
}

INT32S avi_audio_record_start(void)
{
    INT8U  err;
    INT32S nRet, msg;

    nRet = STATUS_OK;
    POST_MESSAGE(avi_aud_q, AVI_AUDIO_RECORD_START, avi_aud_ack_m, 5000, msg, err);
Return:
    return nRet;
}

INT32S avi_audio_record_restart(void)
{
    INT8U  err;
    INT32S nRet, msg;

    nRet = STATUS_OK;
    POST_MESSAGE(avi_aud_q, AVI_AUDIO_RECORD_RESTART, avi_aud_ack_m, 5000, msg, err);
Return:
    return nRet;
}

INT32S avi_audio_record_stop(void)
{
    INT8U  err;
    INT32S nRet, msg;

    nRet = STATUS_OK;
    POST_MESSAGE(avi_aud_q, AVI_AUDIO_RECORD_STOPING, avi_aud_ack_m, 5000, msg, err);
Return:
    if(nRet < 0)
    {
        avi_audio_memory_free();
    }
    return nRet;
}

void avi_audio_record_entry(void *parm)
{
    INT32S  nRet, audio_stream, cnt;
    INT32U  msg_id, pcm_cwlen;
    INT32S  adc_pga_gain, adc_pga_gain_target;
    INT8U   err, bStop, audio_flag, i;

#if C_USB_AUDIO == CUSTOM_ON
    ISOTaskMsg audioios;
#endif

    while(1)
    {
        msg_id = (INT32U) OSQPend(avi_aud_q, 0, &err);
        if(err != OS_NO_ERR)
            continue;

        switch(msg_id & 0xFF000000)
        {
        case AVI_AUDIO_DMA_DONE:
            if (msg_id != C_DMA_STATUS_DONE)
            {
                DBG_PRINT("AVI_AUDIO_DMA_DONE Error !!\r\n");
                break;
            }

            pcm_cwlen =  AVI_AUDIO_PCM_SAMPLES;  //////////joseph////////////////////////pAviEncAudPara->pcm_input_size * C_WAVE_ENCODE_TIMES;

            if(bStop)
            {
                OSQPost(avi_aud_q, (void *)AVI_AUDIO_RECORD_STOP);  // check dma is done and stop
            }
            else
            {
                OSSchedLock();
                if(gWriteAudioAddr != 0)
                {
                    gWriteAudioAddr = 0;
                    audio_frame[write_audio_idx].is_used = 0;
                }
                OSSchedUnlock();

                /*
                if(ready_addr == (audio_frame[0].buffer_addrs+8))
                {
                	if(audio_frame[1].is_used != 0)
                	{
                		DBG_PRINT("&");

                		avi_adc_double_buffer_set((INT16U*) 0xF8500000, pcm_cwlen);
                		break;
                	}

                    write_audio_idx = 0;
                    ready_addr = audio_frame[1].buffer_addrs+8;
                    next_addr = audio_frame[0].buffer_addrs+8;
                }
                else if(ready_addr == (audio_frame[1].buffer_addrs+8))
                {
                	if(audio_frame[0].is_used != 0)
                	{
                		DBG_PRINT("&");

                		avi_adc_double_buffer_set((INT16U*) 0xF8500000, pcm_cwlen);
                		break;
                	}

                    write_audio_idx = 1;
                    ready_addr = audio_frame[0].buffer_addrs+8;
                    next_addr = audio_frame[1].buffer_addrs+8;
                } */

                if(ready_addr == (audio_frame[0].buffer_addrs + 8))
                {
                    write_audio_idx = 0;
                }
                else if(ready_addr == (audio_frame[1].buffer_addrs + 8))
                {
                    write_audio_idx = 1;
                }
                else if(ready_addr == (audio_frame[2].buffer_addrs + 8))
                {
                    write_audio_idx = 2;
                }
                else
                {
                    DBG_PRINT("audio buffer error!\r\n");
                    while(1);
                }

                for(i = 0; i < AVI_ENCODE_PCM_BUFFER_NO; i++)
                {
                    if((audio_frame[i].buffer_addrs + 8) == next_addr)
                    {
                        continue;
                    }

                    if(audio_frame[i].is_used == 0)
                    {
                        break;
                    }
                }

                if(i == AVI_ENCODE_PCM_BUFFER_NO)
                {
                    // waiting avi packer, if there is no audio buffer
                    DBG_PRINT("&");

                    avi_adc_double_buffer_set((INT16U *) 0xF8500000, pcm_cwlen);
                    break;
                }

                ready_addr = next_addr;
                next_addr = audio_frame[i].buffer_addrs + 8;

#if C_USB_AUDIO == CUSTOM_ON
                if((avi_encode_get_status()&C_AVI_ENCODE_USB_WEBCAM))
                {
                    avi_adc_double_buffer_set((INT16U *)next_addr, pcm_cwlen); // set dma buffer
                }
                else
#endif
                {
                    avi_adc_double_buffer_set((INT16U *)(next_addr), pcm_cwlen); // set dma buffer
                }
            }

#if C_USB_AUDIO == CUSTOM_ON
            if((avi_encode_get_status()&C_AVI_ENCODE_USB_WEBCAM))
            {
                audioios.FrameSize = USB_AUDIO_PCM_SAMPLES * 2;
                audioios.AddrFrame = pcm_addr;
                OSQPost(USBAudioApQ, (void *)(&audioios));
                break;
            }
#endif

            {
                // Ramp Up/Down
                INT32U REG = R_MIC_READY;

                if (ap_state_config_voice_record_switch_get())
                {
                    // Voice : ON
                    adc_pga_gain -= 8;
                    if (adc_pga_gain <= adc_pga_gain_target)
                    {
                        adc_pga_gain = adc_pga_gain_target;
                    }
                }
                else
                {
                    // Voice: OFF
                    adc_pga_gain += 8;
                    if (adc_pga_gain >= 0x1F)  // mute
                    {
                        adc_pga_gain = 0x1F;
                    }
                }

                if ( (R_MIC_READY & 0x1F) != adc_pga_gain)
                {
                    REG &= (~0x1F);
                    REG |= adc_pga_gain;
                    R_MIC_READY = REG;
                    DBG_PRINT("G:%d\r\n", adc_pga_gain);
                }
            }
#if AUDIO_SFX_HANDLE
            pcm_addr = (INT16U *)video_encode_audio_sfx((INT16U *)pcm_addr, pcm_cwlen << 1);
#endif
            audio_stream = (pcm_cwlen << 1) + 8;

            // when restart, wait pcm frame end
            if(audio_flag == 1)
            {
                audio_flag = 0;
                OSMboxPost(avi_aud_ack_m, (void *)C_ACK_SUCCESS);
            }

            if((avi_encode_get_status()&C_AVI_ENCODE_START) == 0) break;

            nRet = avi_encode_disk_size_is_enough(audio_stream);
            if (nRet == 0)
            {
                avi_enc_storage_full();
                continue;
            }
            else if (nRet == 2)
            {
                msgQSend(ApQ, MSG_APQ_RECORD_SWITCH_FILE, NULL, NULL, MSG_PRI_NORMAL);
            }

            audio_frame[write_audio_idx].is_used = 1;
            gWriteAudioAddr = audio_frame[write_audio_idx].buffer_addrs;
#if !VODEO_MUTE_OPEN
            gp_memset((INT8S *)(audio_frame[write_audio_idx].buffer_addrs + 8), 0, (AVI_AUDIO_PCM_SAMPLES << 1));
#endif
            break;

        case AVI_AUDIO_RECORD_START:
            bStop = audio_flag = 0;

#if C_USB_AUDIO == CUSTOM_ON
            if((avi_encode_get_status()&C_AVI_ENCODE_USB_WEBCAM))
            {
                pcm_cwlen = USB_AUDIO_PCM_SAMPLES;

                nRet = avi_audio_memory_allocate(pcm_cwlen << 1);
                if(nRet < 0)
                {
                    DBG_PRINT("Audio Buffer Alloc Fail\r\n");
                    goto AUDIO_RECORD_START_FAIL;
                }
                DBG_PRINT("audlen=%d\r\n", pcm_cwlen);

                ready_addr = avi_audio_get_next_buffer();
                next_addr = avi_audio_get_next_buffer();

                nRet = avi_adc_double_buffer_put((INT16U *)(ready_addr), pcm_cwlen, avi_aud_q);
                if(nRet < 0) goto AUDIO_RECORD_START_FAIL;
                nRet = avi_adc_double_buffer_set((INT16U *)(next_addr), pcm_cwlen);
                if(nRet < 0) goto AUDIO_RECORD_START_FAIL;
            }
            else
#endif
            {
                pcm_cwlen =  AVI_AUDIO_PCM_SAMPLES;  //////////joseph////////////////////////pAviEncAudPara->pcm_input_size * C_WAVE_ENCODE_TIMES;

                nRet = avi_audio_memory_allocate((pcm_cwlen << 1) + 8);
                if(nRet < 0)
                {
                    DBG_PRINT("Audio Buffer Alloc Fail\r\n");
                    goto AUDIO_RECORD_START_FAIL;
                }
                DBG_PRINT("audlen=%d\r\n", pcm_cwlen);

                for (i = 0; i < AVI_ENCODE_PCM_BUFFER_NO; i++)
                {
                    audio_frame[i].is_used = 0;
                    audio_frame[i].buffer_addrs = avi_audio_get_next_buffer();
                    audio_frame[i].buffer_idx = i;
                    *(INT32S *)(audio_frame[i].buffer_addrs) = (('0' & 0xFF) | (('1' & 0xFF) << 8) | (('w' & 0xFF) << 16) | (('b' & 0xFF) << 24)); // add "01wb"
                    *(INT32S *)(audio_frame[i].buffer_addrs + 4) = (INT32U)(pcm_cwlen << 1);            // add length=0
                }

                ready_addr = audio_frame[0].buffer_addrs + 8;
                next_addr = audio_frame[1].buffer_addrs + 8;

                nRet = avi_adc_double_buffer_put((INT16U *)(ready_addr), pcm_cwlen, avi_aud_q);
                if(nRet < 0) goto AUDIO_RECORD_START_FAIL;
                nRet = avi_adc_double_buffer_set((INT16U *)(next_addr), pcm_cwlen);
                if(nRet < 0) goto AUDIO_RECORD_START_FAIL;
            }

            avi_adc_hw_start(pAviEncAudPara->audio_sample_rate);

            adc_pga_gain_target = (INT32S)(R_MIC_READY & 0x1F);
            if (ap_state_config_voice_record_switch_get())
            {
                // Voice : ON
                adc_pga_gain	= (INT32S)(R_MIC_READY & 0x1F);	// bit[4:0] PGA gain
            }
            else
            {
                // Voice OFF
                adc_pga_gain = (INT32S)(0x1F);
                R_MIC_READY |= (INT32U)(adc_pga_gain);
            }

#if C_USB_AUDIO == CUSTOM_ON
            if((avi_encode_get_status()&C_AVI_ENCODE_USB_WEBCAM))
            {
                OSMboxPost(avi_aud_ack_m, (void *)C_ACK_SUCCESS);
                break;
            }
#endif
            //pAviEncPara->delta_ta = (INT64S)my_pAviEncVidPara->dwRate * pcm_cwlen;
            OSMboxPost(avi_aud_ack_m, (void *)C_ACK_SUCCESS);
            break;

AUDIO_RECORD_START_FAIL:
            avi_adc_hw_stop();
            {
                // 還原音量
                R_MIC_READY &= (~0x1F);
                R_MIC_READY |= adc_pga_gain_target;
            }
            avi_adc_double_buffer_free();
            avi_audio_memory_free();
            DBG_PRINT("AudEncStartFail!!!\r\n");
            OSMboxPost(avi_aud_ack_m, (void *)C_ACK_FAIL);
            break;

        case AVI_AUDIO_RECORD_STOP:

            do
            {
                cnt = 0;
                for (i = 0; i < AVI_ENCODE_PCM_BUFFER_NO; i++)
                {
                    if(audio_frame[i].is_used) cnt++;
                }
                if(cnt != 0)  OSTimeDly(10);
            }
            while(cnt != 0);

            avi_adc_hw_stop();
            {
                // 還原音量
                R_MIC_READY &= (~0x1F);
                R_MIC_READY |= adc_pga_gain_target;
            }

            avi_adc_double_buffer_free();
            avi_audio_memory_free();
            OSMboxPost(avi_aud_ack_m, (void *)C_ACK_SUCCESS);
            break;

        case AVI_AUDIO_RECORD_STOPING:
            bStop = 1;
            break;

        case AVI_AUDIO_RECORD_RESTART:
            DBG_PRINT("AVI_AUDIO_RECORD_RESTART\r\n");
            audio_flag = 1;
            break;

        case AVI_AUDIO_RECORD_EXIT:
            OSQFlush(avi_aud_q);
            OSMboxPost(avi_aud_ack_m, (void *)C_ACK_SUCCESS);
            OSTaskDel(OS_PRIO_SELF);
            break;
        case AVI_G_SENSOR_INFO_HANDLE:
        {
            //int idx = msg_id & 0x1;
            //G_Sensor_gps_data_set((void*)(&gs_data), gsensor_data[idx]);
            //DBG_PRINT("%d, %d, %d\r\n",GPS.gs_data.Axis.Xacc,GPS.gs_data.Axis.Yacc,GPS.gs_data.Axis.Zacc);
        }
        break;
        }
    }
}

/*
static INT32S avi_wave_encode_start(void)
{
	INT32S nRet, size;

	size = wav_enc_get_mem_block_size();
	pAviEncAudPara->work_mem = (INT8U *)gp_malloc(size);
	if(!pAviEncAudPara->work_mem) RETURN(STATUS_FAIL);
	gp_memset((INT8S*)pAviEncAudPara->work_mem, 0, size);
	nRet = wav_enc_Set_Parameter( pAviEncAudPara->work_mem,
								  pAviEncAudPara->channel_no,
								  pAviEncAudPara->audio_sample_rate,
								  pAviEncAudPara->audio_format);
	if(nRet < 0) RETURN(STATUS_FAIL);
	nRet = wav_enc_init(pAviEncAudPara->work_mem);
	if(nRet < 0) RETURN(STATUS_FAIL);
	pAviEncAudPara->pcm_input_size = wav_enc_get_SamplePerFrame(pAviEncAudPara->work_mem);

	switch(pAviEncAudPara->audio_format)
	{
	case WAVE_FORMAT_PCM:
		pAviEncAudPara->pack_size = pAviEncAudPara->pcm_input_size;
		pAviEncAudPara->pack_size *= 2;
		break;

	case WAVE_FORMAT_ALAW:
	case WAVE_FORMAT_MULAW:
	case WAVE_FORMAT_ADPCM:
	case WAVE_FORMAT_IMA_ADPCM:
		pAviEncAudPara->pack_size = wav_enc_get_BytePerPackage(pAviEncAudPara->work_mem);
		break;
	}

	nRet = STATUS_OK;
Return:
	return nRet;
}

static INT32S avi_wave_encode_stop(void)
{
	gp_free((void*)pAviEncAudPara->work_mem);
	pAviEncAudPara->work_mem = 0;
	return STATUS_OK;
}

static INT32S avi_wave_encode_once(INT16S *pcm_input_addr)
{
	INT8U *encode_output_addr;
	INT32S nRet, encode_size, N;

	encode_size = 0;
	N = C_WAVE_ENCODE_TIMES;
	encode_output_addr = (INT8U*)pAviEncAudPara->pack_buffer_addr;
	encode_output_addr += 16;		//added by wwj
	while(N--)
	{
		nRet = wav_enc_run(pAviEncAudPara->work_mem, (short *)pcm_input_addr, encode_output_addr);
		if(nRet < 0)
			return  STATUS_FAIL;

		encode_size += nRet;
		pcm_input_addr += pAviEncAudPara->pcm_input_size;
		encode_output_addr += pAviEncAudPara->pack_size;
	}

	return encode_size;
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////

