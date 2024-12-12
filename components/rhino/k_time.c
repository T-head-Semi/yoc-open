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

#include "k_api.h"

void krhino_tick_proc(void)
{
    if (g_sys_stat != RHINO_STOPPED) {
#if (RHINO_CONFIG_USER_HOOK > 0)
        krhino_tick_hook();
#endif

        tick_list_update(1);

#if (RHINO_CONFIG_SCHED_RR > 0)
        time_slice_update();
#endif
    }
}

tick_t krhino_sys_tick_get(void)
{
    CPSR_ALLOC();
    tick_t tick_tmp;

    RHINO_CPU_INTRPT_DISABLE();
    tick_tmp = g_tick_count;
    RHINO_CPU_INTRPT_ENABLE();

    return tick_tmp;
}

sys_time_t krhino_sys_time_get(void)
{
    return (sys_time_t)(krhino_sys_tick_get() * 1000 / RHINO_CONFIG_TICKS_PER_SECOND);
}

tick_t krhino_ms_to_ticks(sys_time_t ms)
{
    uint16_t padding;
    tick_t   ticks;

    padding = 1000 / RHINO_CONFIG_TICKS_PER_SECOND;
    padding = (padding > 0) ? (padding - 1) : 0;

    ticks   = ((ms + padding) * RHINO_CONFIG_TICKS_PER_SECOND) / 1000;

    return ticks;
}

sys_time_t krhino_ticks_to_ms(tick_t ticks)
{
    uint32_t   padding;
    sys_time_t time;

    padding = RHINO_CONFIG_TICKS_PER_SECOND / 1000;
    padding = (padding > 0) ? (padding - 1) : 0;

    time    = ((ticks + padding) * 1000) / RHINO_CONFIG_TICKS_PER_SECOND;

    return time;
}

