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

#ifndef __ATEMPO_CLS_H__
#define __ATEMPO_CLS_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

typedef struct atempo_ops     atempo_ops_t;

typedef struct {
    uint32_t                  rate;           ///< use rate now
    float                     speed;          ///< suggest: 0.5 ~ 2.0;

    void                      *priv;
    const struct atempo_ops   *ops;
    aos_mutex_t               lock;
} atempo_t;

struct atempo_ops {
    const char                *name;

    int      (*init)          (atempo_t *atempo);
    int      (*write)         (atempo_t *atempo, const int16_t *in, size_t isamples);
    int      (*read)          (atempo_t *atempo, int16_t *out, size_t osamples);
    int      (*set_speed)     (atempo_t *atempo, float speed);
    int      (*flush)         (atempo_t *atempo);
    int      (*uninit)        (atempo_t *atempo);
};

__END_DECLS__

#endif /* __ATEMPO_CLS_H__ */

