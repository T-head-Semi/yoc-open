/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pvmp3decoder_api.h"
#include "test_data.h"

#define PVMP3DEC_OBUF_SIZE     (4608 * 2)
#define ARRAY_SIZE(arr)        sizeof(arr) / sizeof(arr[0])
#define RAW_PCM_OUTPUT_SIZE    (100 * 1024)
static uint8_t pcm_out[RAW_PCM_OUTPUT_SIZE];

void* pvmp3_test(void)
{
    uint32_t msize;
    ERROR_CODE ecode;
    int rc, i, offset = 0, len;
    tPVMP3DecoderExternal _config, *config = &_config;
    const unsigned char *data;
    void *dbuf = NULL, *obuf = NULL;
    

    memset(config, 0, sizeof(tPVMP3DecoderExternal));
    msize  = pvmp3_decoderMemRequirements();
    dbuf   = malloc(msize);
    obuf   = malloc(PVMP3DEC_OBUF_SIZE);

    pvmp3_InitDecoder(config, dbuf);
    config->crcEnabled    = 0;
    config->equalizerType = flat;
    config->pOutputBuffer = obuf;

    memset(pcm_out, 0, RAW_PCM_OUTPUT_SIZE);
    g_audio_info.out_data =  (char*)pcm_out;
    g_audio_info.out_data_len = 0;

    for (i = 0; i < ARRAY_SIZE(mp3_frames); i++) {
        len   = mp3_frames[i].size;
        data  = mp3_audio_data + mp3_frames[i].pos;

        config->inputBufferMaxLength     = 0;
        config->inputBufferUsedLength    = 0;
        config->pInputBuffer             = (uint8 *)data;
        config->inputBufferCurrentLength = len;
        config->outputFrameSize          = PVMP3DEC_OBUF_SIZE / sizeof(int16_t);

        ecode = pvmp3_framedecoder(config, dbuf);
        if (!((ecode == NO_DECODING_ERROR) &&
              config->outputFrameSize && config->num_channels && config->samplingRate)) {
            printf("ecode = %d, frame size = %d, ch = %d, rate = %d.", ecode,
                   config->outputFrameSize, config->num_channels, config->samplingRate);
            goto quit;
        }

        rc = config->outputFrameSize * 16 / 8;
        /* no memcpy*/
        if (offset + rc < RAW_PCM_OUTPUT_SIZE) {
            memcpy(pcm_out + offset, config->pOutputBuffer, rc);
            offset += rc;
        }
    }
    g_audio_info.out_data_len = offset;
quit:
    printf("=====>>>pcm = 0x%p, offset = %d, 0x%x\n", pcm_out, offset, offset);
    
    free(obuf);
    free(dbuf);
    return &g_audio_info;
}



