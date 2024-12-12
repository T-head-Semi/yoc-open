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

#include <stdio.h>
#include <stdlib.h>
#include <drv/timer.h>
#include "soc.h"

static csi_timer_t g_tick_timer;
static volatile uint32_t g_csi_tick = 0U;

static void tick_event_cb(csi_timer_t *timer_handle, void *arg)
{
    g_csi_tick++;
}

int example_timer(uint8_t idx)
{
    csi_error_t ret;

    g_csi_tick = 0U;
    ret = csi_timer_init(&g_tick_timer, idx);

    if (ret == CSI_OK) {
        ret = csi_timer_attach_callback(&g_tick_timer, tick_event_cb, NULL);

        if (ret == CSI_OK) {
            ret = csi_timer_start(&g_tick_timer, 1000000);
        }
    }

    if (ret != CSI_OK)
        goto error;

    mdelay(1000 * 2);
    if (!g_csi_tick)
        goto error;
    else
        g_csi_tick = 0;

    csi_timer_stop(&g_tick_timer);
    mdelay(1000 * 2);
    if (g_csi_tick)
        goto error;
    csi_timer_uninit(&g_tick_timer);

    printf("bare_drv_timer success\n");
    return 0;

error:
    printf("bare_drv_timer failed\n");
    return -1;
}


