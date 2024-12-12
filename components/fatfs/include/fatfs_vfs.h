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

#ifndef __FATFS_VFS_H__
#define __FATFS_VFS_H__

#include <aos/aos.h>
#include <aos/kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_SD_FATFS_MOUNTPOINT
#define SD_FATFS_MOUNTPOINT CONFIG_SD_FATFS_MOUNTPOINT
#else
#define SD_FATFS_MOUNTPOINT "/mnt/sd"
#endif

#ifdef CONFIG_FATFS_PARTITION_NAME
#define FATFS_PARTITION_NAME CONFIG_FATFS_PARTITION_NAME
#else
#define FATFS_PARTITION_NAME "fatfs"
#endif

/**
 * @brief  register file system of fat
 * @return 0 on success
 */
int vfs_fatfs_register(void);
int vfs_fatfs_unregister(void);

#ifdef __cplusplus
}
#endif

#endif /* __FATFS_VFS_H__ */

