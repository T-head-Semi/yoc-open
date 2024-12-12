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
#include <stdlib.h>
#include <string.h>
#include <csky_patch.h>
#include <yoc/partition.h>
#include "boot_flash_porting.h"
#include "update_log.h"

/****************************************************************************
 * Functions
 ****************************************************************************/

int diff_bsp_flash_read(uint32_t addroffset, uint8_t *buff, int bytesize)
{
    boot_device_info_t dev_info;
    storage_info_t storage_info = {0, MEM_DEVICE_TYPE_SPI_NOR_FLASH, 0, 0};
    if (boot_device_info_get(&storage_info, &dev_info)) {
        return -1;
    }
    return boot_device_read(&storage_info, addroffset - dev_info.base_addr, buff, bytesize);
}

int diff_bsp_flash_write(uint32_t addroffset, uint8_t *buff, int bytesize)
{
    boot_device_info_t dev_info;
    storage_info_t storage_info = {0, MEM_DEVICE_TYPE_SPI_NOR_FLASH, 0, 0};
    if (boot_device_info_get(&storage_info, &dev_info)) {
        return -1;
    }
    return boot_device_write(&storage_info, addroffset - dev_info.base_addr, buff, bytesize);
}

int diff_bsp_flash_erase(uint32_t addroffset, uint32_t bytesize)
{
    boot_device_info_t dev_info;
    storage_info_t storage_info = {0, MEM_DEVICE_TYPE_SPI_NOR_FLASH, 0, 0};
    if (boot_device_info_get(&storage_info, &dev_info)) {
        return -1;
    }
    // UPD_LOGD("diff, addroffset:0x%x, bytesize:%d", addroffset, bytesize);
    return boot_device_erase(&storage_info, addroffset - dev_info.base_addr, bytesize);
}

void *diff_malloc(uint32_t bytesize)
{
    return malloc(bytesize);
}

void diff_free(void *ptr)
{
    free(ptr);
}
#endif