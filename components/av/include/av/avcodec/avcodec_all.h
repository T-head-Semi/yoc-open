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

#ifndef __AVCODEC_ALL_H__
#define __AVCODEC_ALL_H__

#include "av/avutil/av_config.h"
#include "av/avcodec/ad.h"
#include "av/avcodec/avcodec.h"

__BEGIN_DECLS__

#define REGISTER_DECODER(X, x)                                          \
    {                                                                   \
        extern int ad_register_##x();                                   \
        if (CONFIG_DECODER_##X)                                         \
            ad_register_##x();                                          \
    }

/**
 * @brief  regist ad for pcm
 * @return 0/-1
 */
int ad_register_pcm();

/**
 * @brief  regist ad for ipc
 * @return 0/-1
 */
int ad_register_ipc();

/**
 * @brief  regist ad for pvmp3
 * @return 0/-1
 */
int ad_register_pvmp3();

/**
 * @brief  regist ad for adpcm_ms
 * @return 0/-1
 */
int ad_register_adpcm_ms();

/**
 * @brief  regist ad for flac
 * @return 0/-1
 */
int ad_register_flac();

/**
 * @brief  regist ad for amrnb
 * @return 0/-1
 */
int ad_register_amrnb();

/**
 * @brief  regist ad for amrwb
 * @return 0/-1
 */
int ad_register_amrwb();

/**
 * @brief  regist ad for opus
 * @return 0/-1
 */
int ad_register_opus();

/**
 * @brief  regist ad for speex
 * @return 0/-1
 */
int ad_register_speex();

/**
 * @brief  regist ad for alaw
 * @return 0/-1
 */
int ad_register_alaw();

/**
 * @brief  regist ad for mulaw
 * @return 0/-1
 */
int ad_register_mulaw();

/**
 * @brief  regist all decoder
 * attention: can rewrite this function by caller
 * @return 0/-1
 */
int ad_register_all();

__END_DECLS__

#endif /* __AVCODEC_ALL_H__ */

