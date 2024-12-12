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
#include <aos/aos.h>
#include "timer_port.h"
#include "ulog/ulog.h"

#define TAG "OTA_TIMER"

int ota_timer_init(ota_timer_t *timer, ota_timer_handler_t handle, void *args)
{
    int ret = 0;
    ret     = aos_timer_new_ext(&timer->timer.aos_timer, handle, args, 1000, 0, 0);
    if (ret) {
        LOGE(TAG, "Aos timer create failed %d", ret);
    }
    return ret;
}

int ota_timer_start(ota_timer_t *timer, uint32_t timeout)
{
    int ret = 0;
    ret     = aos_timer_change_once(&timer->timer.aos_timer, timeout);
    if (ret) {
        LOGE(TAG, "Aos timer change failed %d", ret);
        return ret;
    }

    return aos_timer_start(&timer->timer.aos_timer);
}

int ota_timer_stop(ota_timer_t *timer)
{
    int ret = 0;
    ret     = aos_timer_stop(&timer->timer.aos_timer);
    if (ret) {
        LOGE(TAG, "Aos timer stop failed %d", ret);
    }
    return ret;
}

void ota_timer_free(ota_timer_t *timer)
{
    aos_timer_stop(&timer->timer.aos_timer);
    aos_timer_free(&timer->timer.aos_timer);
}
