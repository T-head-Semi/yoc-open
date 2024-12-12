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

#ifndef __PLAYER_IOCTL_H__
#define __PLAYER_IOCTL_H__

#include "av/stream/stream_ioctl.h"
#include "av/output/ao_ioctl.h"

__BEGIN_DECLS__

enum {
    PLAYER_CMD_UNKNOWN,
    PLAYER_CMD_EQ_SET_PARAM,       ///< if support
    PLAYER_CMD_EQ_ENABLE,          ///< if support
    PLAYER_CMD_SET_CACHE_SIZE,     ///< next play valid
    PLAYER_CMD_SET_RESAMPLE_RATE,  ///< next play valid
    PLAYER_CMD_SET_RCVTO,          ///< next play valid
};

/* equalizer typedef below */
//PLAYER_CMD_EQ_SET_PARAM
typedef oeq_setpa_t peq_setpa_t;

//PLAYER_CMD_EQ_SET_ENABLE
typedef oeq_seten_t peq_seten_t;

__END_DECLS__

#endif /* __PLAYER_IOCTL_H__ */

