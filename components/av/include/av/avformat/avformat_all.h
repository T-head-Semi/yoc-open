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

#ifndef __AVFORMAT_ALL_H__
#define __AVFORMAT_ALL_H__

#include "av/avutil/common.h"
#include "av/avutil/av_config.h"

__BEGIN_DECLS__

#define REGISTER_DEMUXER(X, x)                                          \
    {                                                                   \
        extern int demux_register_##x();                                \
        if (CONFIG_DEMUXER_##X)                                         \
            demux_register_##x();                                       \
    }

/**
 * @brief  regist demux for wav
 * @return 0/-1
 */
int demux_register_wav();

/**
 * @brief  regist demux for mp3
 * @return 0/-1
 */
int demux_register_mp3();

/**
 * @brief  regist demux for mp4
 * @return 0/-1
 */
int demux_register_mp4();

/**
 * @brief  regist demux for rawaudio
 * @return 0/-1
 */
int demux_register_rawaudio();

/**
 * @brief  regist demux for adts
 * @return 0/-1
 */
int demux_register_adts();

/**
 * @brief  regist demux for flac
 * @return 0/-1
 */
int demux_register_flac();

/**
 * @brief  regist demux for asf
 * @return 0/-1
 */
int demux_register_asf();

/**
 * @brief  regist demux for amr
 * @return 0/-1
 */
int demux_register_amr();

/**
 * @brief  regist demux for ts
 * @return 0/-1
 */
int demux_register_ts();

/**
 * @brief  regist demux for ogg
 * @return 0/-1
 */
int demux_register_ogg();

/**
 * @brief  regist all demuxer
 * attention: can rewrite this function by caller
 * @return 0/-1
 */
int demux_register_all();

__END_DECLS__

#endif /* __AVFORMAT_ALL_H__ */

