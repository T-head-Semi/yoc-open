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

#ifndef __PCM_CONVERT_H__
#define __PCM_CONVERT_H__

#include "av/avutil/common.h"
#include "av/avutil/sf.h"

__BEGIN_DECLS__

/**
 * @brief  s8_ch1_to_s16_ch2
 * @param  [in] dst
 * @param  [in] src
 * @param  [in] nb_samples : number of input samples available in one channel
 * @return
 */
void s8_ch1_to_s16_ch2(void *dst, const void *src, size_t nb_samples);

/**
 * @brief  s8_ch1_to_s16_ch1
 * @param  [in] dst
 * @param  [in] src
 * @param  [in] nb_samples : number of input samples available in one channel
 * @return
 */
void s8_ch1_to_s16_ch1(void *dst, const void *src, size_t nb_samples);

/**
 * @brief  u8_ch1_to_s16_ch2
 * @param  [in] dst
 * @param  [in] src
 * @param  [in] nb_samples : number of input samples available in one channel
 * @return
 */
void u8_ch1_to_s16_ch2(void *dst, const void *src, size_t nb_samples);

/**
 * @brief  s8_ch2_to_s16_ch2
 * @param  [in] dst
 * @param  [in] src
 * @param  [in] nb_samples : number of input samples available in one channel
 * @return
 */
void s8_ch2_to_s16_ch2(void *dst, const void *src, size_t nb_samples);

/**
 * @brief  s8_ch2_to_s16_ch1
 * @param  [in] dst
 * @param  [in] src
 * @param  [in] nb_samples : number of input samples available in one channel
 * @return
 */
void s8_ch2_to_s16_ch1(void *dst, const void *src, size_t nb_samples);

/**
 * @brief  u8_ch2_to_s16_ch2
 * @param  [in] dst
 * @param  [in] src
 * @param  [in] nb_samples : number of input samples available in one channel
 * @return
 */
void u8_ch2_to_s16_ch2(void *dst, const void *src, size_t nb_samples);

/**
 * @brief  s16_ch1_to_s16_ch2
 * @param  [in] dst
 * @param  [in] src
 * @param  [in] nb_samples : number of input samples available in one channel
 * @return
 */
void s16_ch1_to_s16_ch2(void *dst, const void *src, size_t nb_samples);

/**
 * @brief  s16_ch2_to_s16_ch1
 * @param  [in] dst
 * @param  [in] src
 * @param  [in] nb_samples : number of input samples available in one channel
 * @return
 */
void s16_ch2_to_s16_ch1(void *dst, const void *src, size_t nb_samples);

/**
 * @brief  u16_le_to_s16_le
 * @param  [in] dst
 * @param  [in] src
 * @param  [in] size : space(src) / sizeof(int16_t)
 * @return
 */
void u16_le_to_s16_le(void *dst, const void *src, size_t size);

/**
 * @brief  u16_be_to_s16_le
 * @param  [in] dst
 * @param  [in] src
 * @param  [in] size : space(src) / sizeof(int16_t)
 * @return
 */
void u16_be_to_s16_le(void *dst, const void *src, size_t size);

__END_DECLS__

#endif /* __PCM_CONVERT_H__ */

