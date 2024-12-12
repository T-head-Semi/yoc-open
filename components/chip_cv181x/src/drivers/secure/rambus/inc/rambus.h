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

#ifndef INC_RAMBUS_H
#define INC_RAMBUS_H

// Driver Framework Basic Defs API
#include "basic_defs.h"

// Driver Framework Device API
#include "device_types.h"
#include <drv/common.h>
#include "rambus_errcode.h"
#include "rambus_log.h"
#include "dmares_types.h"
#include "device_rw.h"

uint32_t rb_get_random_byte(uint8_t *buf, uint32_t count);

/* 0 if NONE */
void rb_perf_init(uint32_t data_len_in_bits, uint32_t type);
void rb_perf_start();
void rb_perf_end();
void rb_perf_get(char *ncase);

#define RB_PERF_START_POINT()                                                  \
        do {                                                                   \
                rb_perf_start();                                               \
        } while (0)

#define RB_PERF_END_POINT()                                                    \
        do {                                                                   \
                rb_perf_end();                                                 \
        } while (0)

#endif