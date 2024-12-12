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
#ifndef __BOOT_FLASH_H__
#define __BOOT_FLASH_H__

#include <stdint.h>
#include <stddef.h>
#include <yoc/partition_device.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef partition_device_info_t boot_device_info_t;

int boot_device_info_get(storage_info_t *storage_info, boot_device_info_t *info);
int boot_device_read(storage_info_t *storage_info, uint32_t offset, void *data, size_t data_len);
int boot_device_write(storage_info_t *storage_info, uint32_t offset, void *data, size_t data_len);
int boot_device_erase(storage_info_t *storage_info, uint32_t offset, size_t len);

#ifdef __cplusplus
}
#endif
#endif