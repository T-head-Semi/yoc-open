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

#ifndef __AEF_CLS_H__
#define __AEF_CLS_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

typedef struct audio_effect   aefx_t;
typedef struct aefx_ops       aefx_ops_t;

struct audio_effect {
    uint32_t                  rate;
    uint8_t                   *conf;
    size_t                    conf_size;
    size_t                    nsamples_max;   ///< the max frame len for input on processing

    void                      *priv;
    const struct aefx_ops     *ops;
    aos_mutex_t               lock;
};

struct aefx_ops {
    const char                *name;

    int      (*init)          (aefx_t *aef);
    int      (*process)       (aefx_t *aef, const int16_t *in, int16_t *out, size_t nb_samples);
    int      (*uninit)        (aefx_t *aef);
};

__END_DECLS__

#endif /* __AEF_CLS_H__ */

