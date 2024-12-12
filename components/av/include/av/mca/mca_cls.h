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

#ifndef __MCA_CLS_H__
#define __MCA_CLS_H__

#include "av/avutil/common.h"
#include "av/mca/csky_mca.h"

__BEGIN_DECLS__

typedef struct mcax                         mcax_t;
typedef struct mcax_ops                     mcax_ops_t;

struct mcax {
    int32_t                                 type;

    void                                    *priv;
    const struct mcax_ops                   *ops;
    aos_mutex_t                             lock;
};

struct mcax_ops {
    const char                              *name;

    int      (*init)                        (mcax_t *mca, int32_t type);
    int      (*iir_fxp32_coeff32_config)    (mcax_t *mca, const fxp32_t *coeff);
    int      (*iir_fxp32)                   (mcax_t *mca, const fxp32_t *input, size_t input_size,
            fxp32_t yn1, fxp32_t yn2, fxp32_t *output);
    int      (*uninit)                      (mcax_t *mca);
};

__END_DECLS__

#endif /* __MCA_CLS_H__ */

