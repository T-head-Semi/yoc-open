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

#ifndef __AEF_ICORE_H__
#define __AEF_ICORE_H__

#include "av/aef/aef_cls.h"

__BEGIN_DECLS__

typedef struct aef_icore aef_icore_t;

/**
 * @brief  init inter-core audio effecter
 * @return 0/-1
 */
int aef_icore_init();

/**
 * @brief  alloc a inter-core audio effecter
 * @param  [in] rate      : audio freq
 * @param  [in] conf
 * @param  [in] conf_size
 * @param  [in] nsamples_max : max frame len
 * @return NULL on error
 */
aef_icore_t* aef_icore_new(uint32_t rate, uint8_t *conf, size_t conf_size, size_t nsamples_max);

/**
 * @brief  process samples
 * @param  [in] hdl
 * @param  [in] in
 * @param  [in] out
 * @param  [in] nb_samples : samples per channel
 * @return 0/-1
 */
int aef_icore_process(aef_icore_t *hdl, const int16_t *in, int16_t *out, size_t nb_samples);

/**
 * @brief  free the inter-core audio effecter
 * @param  [in] hdl
 * @return 0/-1
 */
int aef_icore_free(aef_icore_t *hdl);

__END_DECLS__

#endif /* __AEF_ICORE_H__ */

