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

#include "aos/kernel.h"
#include <breeze_hal_os.h>

int os_timer_new(os_timer_t *timer, os_timer_cb_t cb, void *arg, int ms)
{
    return aos_timer_new_ext(timer, cb, arg, ms, 0, 0);
}

int bz_os_timer_start(os_timer_t *timer)
{
    return aos_timer_start(timer);
}

int os_timer_stop(os_timer_t *timer)
{
    return aos_timer_stop(timer);
}

void os_timer_free(os_timer_t *timer)
{
    aos_timer_free(timer);
}

void os_reboot()
{
    aos_reboot();
}

void os_msleep(int ms)
{
    aos_msleep(ms);
}

long long os_now_ms()
{
    return aos_now_ms();
}

int os_kv_set(const char *key, const void *value, int len, int sync)
{
    return aos_kv_set(key, value, len, sync);
}

int os_kv_get(const char *key, void *buffer, int *buffer_len)
{
    return aos_kv_get(key, buffer, buffer_len);
}

int os_kv_del(const char *key)
{
    return aos_kv_del(key);
}

int os_rand(void)
{
    return 0;
}
