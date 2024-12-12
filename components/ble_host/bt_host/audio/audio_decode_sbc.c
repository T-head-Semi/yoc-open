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

#include <aos/aos.h>
#include <misc/byteorder.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>
#include <bluetooth/audio_decode.h>
#include <bluetooth/a2dp-codec.h>
#include <oi_codec_sbc.h>

#define BT_DBG_ENABLED  IS_ENABLED(CONFIG_BT_DEBUG_A2DP)
#define LOG_MODULE_NAME bt_a2dp_decode
#include "common/log.h"

static OI_CODEC_SBC_DECODER_CONTEXT decoder_context;
static OI_UINT32 context_data[CODEC_DATA_WORDS(2, SBC_CODEC_MIN_FILTER_BUFFERS)];

static int audio_decode_init(void)
{
    BT_DBG("");

    OI_CODEC_SBC_DecoderReset(&decoder_context, context_data, sizeof(context_data), 2,
                              2, 0, 0);

    return 0;
}

static int audio_decode_decode(void **in_data, u32_t *in_size, void *out_data,
                               u32_t *out_size)
{
    OI_STATUS status;

    status = OI_CODEC_SBC_DecodeFrame(&decoder_context, (const OI_BYTE **)in_data,
                                      in_size, out_data, out_size);
    if (!OI_SUCCESS(status)) {
        BT_ERR("%s: Decoding failure: %d", __func__, status);
        return -1;
    }

    return 0;
}

static bt_a2dp_audio_decode_t audio_decode = {
    .codec_type = BT_A2DP_SBC,
    .init       = audio_decode_init,
    .decode     = audio_decode_decode,
};

bt_a2dp_audio_decode_t *bt_a2dp_audio_decode_sbc_get_interface(void)
{
    return &audio_decode;
}
