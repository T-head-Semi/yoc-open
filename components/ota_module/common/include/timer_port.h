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
#ifndef _TIMER_PORT_H_
#define _TIMER_PORT_H_
#include "aos/kernel.h"

typedef union
{
    aos_timer_t aos_timer;
} timer_s;

typedef struct {
    timer_s timer;
} ota_timer_t;

typedef void (*ota_timer_handler_t)(void *timer, void *args);

int  ota_timer_init(ota_timer_t *timer, ota_timer_handler_t handle, void *args);
int  ota_timer_start(ota_timer_t *timer, uint32_t timeout);
int  ota_timer_stop(ota_timer_t *timer);
void ota_timer_free(ota_timer_t *timer);

#endif
