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

/******************************************************************************
 * @file     reboot.c
 * @brief    source file for the reboot
 * @version  V1.0
 * @date     7. April 2020
 ******************************************************************************/

#include <soc.h>
#include <drv/wdt.h>

void drv_reboot(void)
{
    csi_wdt_t wdt_handle;
    uint32_t irq_flag = 0U;

    irq_flag = csi_irq_save();

    csi_wdt_init(&wdt_handle, 0U);
    csi_wdt_set_timeout(&wdt_handle, 0U);
    csi_wdt_start(&wdt_handle);

    /* waiting for reboot */
    while (1);


    csi_irq_restore(irq_flag);
}
