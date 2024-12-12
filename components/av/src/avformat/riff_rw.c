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

#include "av/avutil/byte_rw.h"
#include "av/avutil/misc.h"
#include "av/avformat/riff_rw.h"

static const avcodec_tag_t g_codec_tags_wav[] = {
    { AVCODEC_ID_RAWAUDIO, WAV_FORMAT_PCM          },
    { AVCODEC_ID_ADPCM_MS, WAV_FORMAT_ADPCM_MS     },
    { AVCODEC_ID_RAWAUDIO, WAV_FORMAT_FLOAT        },
    { AVCODEC_ID_WMAV1, WAV_FORMAT_WMAV1        },
    { AVCODEC_ID_WMAV2, WAV_FORMAT_WMAV2        },
    { AVCODEC_ID_UNKNOWN, 0                       },
};

/**
 * @brief  get codec id by tag val
 * @param  [in] tag
 * @return
 */
avcodec_id_t wav_get_codec_id(uint32_t tag)
{
    return get_codec_id(g_codec_tags_wav, tag);
}


