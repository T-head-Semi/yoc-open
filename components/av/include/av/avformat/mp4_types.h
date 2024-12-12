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

#ifndef __MP4_TYPES_H__
#define __MP4_TYPES_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

#define ATOMID(a, b, c, d)     ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))
#define ATOM_FTYP_SIZE_MAX     (32)

#define MP4_ES_DESCR_TAG                    (0x03)
#define MP4_DEC_CONFIG_DESCR_TAG            (0x04)
#define MP4_DEC_SPECIFIC_DESCR_TAG          (0x05)

typedef struct {
    uint32_t type;
    int64_t  size;
} mp4_atom_t;

typedef struct {
    int32_t count;
    int32_t duration;
} mp4_stts_t;

typedef struct {
    int32_t first;
    int32_t count;
    int32_t id;
} mp4_stsc_t;

__END_DECLS__

#endif /* __MP4_TYPES_H__ */

