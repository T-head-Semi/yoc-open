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

#ifndef __VOL_SCALE_H__
#define __VOL_SCALE_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

#define FACTOR_N               (256)

/**
 * @brief  init factor of the vol scale, divided into FACTOR_N(256) equal parts. once only
 * @param  [in] mindb
 * @param  [in] maxdb
 * @return
 */
void vol_scale_init(int mindb, int maxdb);

/**
 * @brief  vol scale
 * @param  [in] in
 * @param  [in] nb_samples
 * @param  [in] out
 * @param  [in] scale index : 0~255
 * @return 0/-1
 */
int vol_scale(const int16_t *in, size_t nb_samples, int16_t *out, uint8_t scale_index);

__END_DECLS__

#endif /* __VOL_SCALE_H__ */

