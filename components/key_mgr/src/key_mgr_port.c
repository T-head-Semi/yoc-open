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

#include "key_mgr_port.h"
#include <sec_crypto_sha.h>
#include <yoc/partition_device.h>

int get_data_from_addr(unsigned long addr, uint8_t *data, size_t data_len, partition_info_t *part_info)
{
#ifdef CONFIG_NON_ADDRESS_FLASH
    void *handle = partition_device_find(&part_info->storage_info);
    return partition_device_read(handle, addr - part_info->base_addr, data, data_len);
#else
    memcpy(data, (uint8_t *)addr, data_len);
#endif /* CONFIG_NON_ADDRESS_FLASH */

    return 0;
}

