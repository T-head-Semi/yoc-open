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

#ifndef __RIFF_RW_H__
#define __RIFF_RW_H__

#include "av/avutil/common.h"
#include "av/avutil/av_typedef.h"

__BEGIN_DECLS__


#define WAV_FORMAT_PCM         (0x0001U)
#define WAV_FORMAT_ADPCM_MS    (0x0002U)
#define WAV_FORMAT_FLOAT       (0x0003U)
#define WAV_FORMAT_ALAW        (0x0006U)
#define WAV_FORMAT_MULAW       (0x0007U)
#define WAV_FORMAT_WMAV1       (0x0160U)
#define WAV_FORMAT_WMAV2       (0x0161U)
#define WAV_FORMAT_EXTENSIBLE  (0xfffeU)

/**
 * @brief  get codec id by tag val
 * @param  [in] tag
 * @return
 */
avcodec_id_t wav_get_codec_id(uint32_t tag);

__END_DECLS__

#endif /* __RIFF_RW_H__ */

