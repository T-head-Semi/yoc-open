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

#ifndef __EQ_TYPEDEF_H__
#define __EQ_TYPEDEF_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

enum eqf_type {
    EQF_TYPE_UNKNOWN,
    EQF_TYPE_PEAK,
    EQF_TYPE_NOTCH,
    EQF_TYPE_LP1,
    EQF_TYPE_HP1,
    EQF_TYPE_LP2,
    EQF_TYPE_HP2,
    EQF_TYPE_BP2,
    EQF_TYPE_MAX,
};

/* eq filter-param per segment*/
typedef struct {
    uint8_t                   enable;
    enum eqf_type             type;
    float                     gain;     ///< -24~18
    float                     q;        ///< 0.1~50
    uint32_t                  rate;
} eqfp_t;

__END_DECLS__

#endif /* __EQ_TYPEDEF_H__ */

