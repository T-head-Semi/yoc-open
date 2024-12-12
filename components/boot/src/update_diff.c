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
#if (CONFIG_NO_OTA_UPGRADE == 0) && (CONFIG_OTA_NO_DIFF == 0)
#include "update_diff.h"
#include "csky_patch.h"
#include "update_log.h"

int diff_init_config(uint32_t bs_ram_size, uint32_t img_flash_sector, uint32_t misc_flash_sector,
                     uint32_t bs_flash_end_addr)
{
    int ret;
    static int g_diff_init = 0;
    UPD_LOGD("diff init config start.");
    if (g_diff_init == 1) {
        // init already
        UPD_LOGD("diff already init.");
        return 0;
    }
    ret = pat_config(bs_ram_size, img_flash_sector, misc_flash_sector, bs_flash_end_addr);
    g_diff_init = 1;
    UPD_LOGD("diff init config over.");
    return ret;
}

int diff_updata_img(uint32_t old_img_addr, uint32_t old_img_len, uint32_t partion_size,
                    uint32_t diff_img_addr, uint32_t diff_img_len)
{
    return pat_process((uint32_t *)old_img_addr, old_img_len, partion_size,
                       (uint32_t *)diff_img_addr, diff_img_len);
}
#endif