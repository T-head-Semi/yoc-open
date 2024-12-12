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

#ifndef __RESAMPLE_CLS_H__
#define __RESAMPLE_CLS_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

typedef struct resample       resx_t;
typedef struct resx_ops       resx_ops_t;

struct resample {
    aos_mutex_t               lock;

    uint32_t                  irate;
    uint32_t                  orate;
    uint8_t                   bits;      ///< 16bit now only
    uint8_t                   channels;   ///< mono or stereo

    void                      *priv;
    const struct resx_ops     *ops;
};

struct resx_ops {
    const char                *name;

    int      (*init)          (resx_t *r);
    /**
     * @brief  convert nb_samples from src to dst sample format
     * @param  [in] r
     * @param  [in] out
     * @param  [in] nb_osamples : amount of space available for output in samples per channels
     * @param  [in] in
     * @param  [in] nb_isamples : number of input samples available in one channels
     * @return number of samples output per channels, -1 on error
     */
    int      (*convert)       (resx_t *r, void **out, size_t nb_osamples, const void **in, size_t nb_isamples);
    int      (*uninit)        (resx_t *r);
};

__END_DECLS__

#endif /* __RESAMPLE_CLS_H__ */

