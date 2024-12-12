 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amrwb/pvamrwbdecoder.h"
#include "test_data.h"

#define ARRAY_SIZE(arr)        sizeof(arr) / sizeof(arr[0])
#define RAW_PCM_SIZE           (kOutputBufferSize * FRAME_COUNT)

// Constants for AMR-WB.
enum {
    kInputBufferSize = 64,
    kSamplesPerFrame = 320,
    kBitsPerSample = 16,
    kOutputBufferSize = kSamplesPerFrame * kBitsPerSample/8,
    kSampleRate = 16000,
    kChannels = 1,
    kFileHeaderSize = 9,
    kMaxSourceDataUnitSize = 477 * sizeof(int16_t)
};

static  uint32_t kFrameSizes[] = { 17, 23, 32, 36, 40, 46, 50, 58, 60 };
static  uint8_t  pcm_out[RAW_PCM_SIZE];

void* amrwb_test(void)
{
    int i, offset = 0, len;
    const unsigned char *data;
    char *dec_buf;

	memset(pcm_out, 0, RAW_PCM_SIZE);
	g_audio_info.out_data = (char*)pcm_out;
    g_audio_info.out_data_len = 0;
    dec_buf = malloc(kOutputBufferSize);

    // Allocate the decoder memory.
    uint32_t memRequirements = pvDecoder_AmrWbMemRequirements();
    void *decoderBuf = malloc(memRequirements);

    // Allocate input sample buffer.
    int16_t *inputSampleBuf = (int16_t*) malloc(kMaxSourceDataUnitSize);

    // Create AMR-WB decoder instance.
    void *amrHandle;
    int16_t *decoderCookie;
    pvDecoder_AmrWb_Init(&amrHandle, decoderBuf, &decoderCookie);

    for (i = 0; i < ARRAY_SIZE(amr_frames); i++) {
        uint8_t mode;
        len   = amr_frames[i].size;

        data  = amr_audio_data + amr_frames[i].pos;

        mode = ((data[0] >> 3) & 0x0f);
        // AMR-WB file format cannot have mode 10, 11, 12 and 13.
        if (mode >= 10 && mode <= 13) {
            fprintf(stderr, "Encountered illegal frame type %d\n", mode);
            break;
        }

        int16_t *outputBuf = (int16_t *)dec_buf;
        if (mode >= 9) {
            // Produce silence for comfort noise, speech lost and no data.
            memset(outputBuf, 0, kOutputBufferSize);
        } else { /* if (mode < 9) */
            // Read rest of the frame.
            int32_t frameSize = kFrameSizes[mode];
            if (len != (frameSize + 1)) break;

            int16 frameType, frameMode;
            RX_State_wb rx_state;
            frameMode = mode;
            mime_unsorting(
                (uint8_t *)&data[1],
                inputSampleBuf,
                &frameType, &frameMode, 1, &rx_state);

            int16_t numSamplesOutput;
            pvDecoder_AmrWb(
                frameMode, inputSampleBuf,
                outputBuf,
                &numSamplesOutput,
                decoderBuf, frameType, decoderCookie);

            if (numSamplesOutput != kSamplesPerFrame) {
                fprintf(stderr, "Decoder encountered error\n");
                break;
            }

            for (int j = 0; j < kSamplesPerFrame; ++j) {
                outputBuf[j] &= 0xfffC;
            }
        }
        if (offset + kOutputBufferSize < RAW_PCM_SIZE) {
            memcpy(pcm_out + offset, dec_buf, kOutputBufferSize);
            offset += kOutputBufferSize;
         }
    }
    g_audio_info.out_data_len = offset;
    free(inputSampleBuf);
    free(dec_buf);
    free(decoderBuf);

    printf("=====>>>pcm = 0x%p, offset = %d, 0x%x\n", pcm_out, offset, offset);
    
    return &g_audio_info;
}