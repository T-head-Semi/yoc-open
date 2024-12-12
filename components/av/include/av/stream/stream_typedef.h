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

#ifndef __STREAM_TYPEDEF_H__
#define __STREAM_TYPEDEF_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

enum stream_mode {
    STREAM_CREATE  = (1<<0),
    STREAM_READ    = (1<<1),
    STREAM_WRITE   = (1<<2),
};

typedef enum stream_type {
    STREAM_TYPE_UNKNOWN,
    STREAM_TYPE_FILE,
    STREAM_TYPE_HTTP,
    STREAM_TYPE_MEM,
    STREAM_TYPE_FIFO,
    STREAM_TYPE_CRYPTO,
    STREAM_TYPE_HLS,
} stream_type_t;

__END_DECLS__

#endif /* __STREAM_TYPEDEF_H__ */

