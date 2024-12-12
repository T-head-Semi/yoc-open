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

#ifndef __SWRESAMPLE_H__
#define __SWRESAMPLE_H__

#include "av/avutil/avframe.h"

__BEGIN_DECLS__

typedef struct swr_context swr_t;

/**
 * @brief  new a swreampler
 * @param  [in] isf : original sample format
 * @param  [in] osf : destination sample format
 * TODO: (dst only support 16bit/!planar now)
 * @return NULL on error
 */
swr_t *swr_new(sf_t isf, sf_t osf);

/**
 * @brief  get the max out samples number per channel
 * @param  [in] s
 * @param  [in] nb_isamples : number of input samples available in one channel
 * @return -1 on error
 */
int swr_get_osamples_max(swr_t *s, size_t nb_isamples);

/**
 * @brief  convert nb_isamples from src to dst sample format
 * @param  [in] s
 * @param  [in] out
 * @param  [in] nb_osamples : amount of space available for output in samples per channel
 * @param  [in] in
 * @param  [in] nb_isamples : number of input samples available in one channel
 * @return number of samples output per channel, -1 on error
 */
int swr_convert(swr_t *s, void **out, size_t nb_osamples, const void **in, size_t nb_isamples);

/**
 * @brief  convert a audio avframe from src to dst sample format
 * @param  [in] s
 * @param  [in] iframe
 * @param  [in] oframe
 * @return number of samples output per channel, -1 on error
 */
int swr_convert_frame(swr_t *s, const avframe_t *iframe, avframe_t *oframe);

/**
 * @brief  free the swreasampler
 * @param  [in] s
 * @return
 */
void swr_free(swr_t *s);

__END_DECLS__


#endif /* __SWRESAMPLE_H__ */

