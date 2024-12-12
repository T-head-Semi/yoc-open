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

#ifndef __AO_IOCTL_H__
#define __AO_IOCTL_H__

#include "av/aef/eq_cls.h"

__BEGIN_DECLS__

enum {
    AO_CMD_UNKNOWN,
    AO_CMD_EQ_ENABLE,        ///< equalizer enable, may be not support for some hardware.
    AO_CMD_EQ_SET_PARAM,     ///< equalizer param config, may be not support for some hardware.
    AO_CMD_VOL_SET,          ///< soft vol
    AO_CMD_ATEMPO_SET_SPEED, ///< atempo play speed set
};

/* equalizer typedef below */
//AO_CMD_EQ_SET_PARAM
typedef struct {
    uint8_t                   segid;
    eqfp_t                    param;
} oeq_setpa_t;

//AO_CMD_EQ_SET_ENABLE
typedef struct {
    uint8_t                   enable;
} oeq_seten_t;

//AO_CMD_VOL_SET
typedef struct {
    uint8_t                   vol_index;      ///< soft vol scale index (0~255)
} ovol_set_t;

//AO_CMD_ATEMPO_SET_SPEED
/* float speed; */

__END_DECLS__

#endif /* __AO_IOCTL_H__ */

