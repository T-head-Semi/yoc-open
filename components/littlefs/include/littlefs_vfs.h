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

#ifndef __LITTLEFS_VFS_H__
#define __LITTLEFS_VFS_H__

#include <aos/aos.h>
#include <aos/kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LFS_MOUNTPOINT
#define LFS_MOUNTPOINT CONFIG_LFS_MOUNTPOINT
#else
#define LFS_MOUNTPOINT "/"
#endif
#ifdef CONFIG_LFS_BLOCK_SIZE
#define LFS_BLOCK_SIZE CONFIG_LFS_BLOCK_SIZE
#endif
#ifdef CONFIG_LFS_BLOCK_COUNT
#define LFS_BLOCK_COUNT CONFIG_LFS_BLOCK_COUNT
#endif
#ifdef CONFIG_LFS_READ_SIZE
#define LFS_READ_SIZE CONFIG_LFS_READ_SIZE
#endif
#ifdef CONFIG_LFS_PROG_SIZE
#define LFS_PROG_SIZE CONFIG_LFS_PROG_SIZE
#endif
#ifdef CONFIG_LFS_CACHE_SIZE
#define LFS_CACHE_SIZE CONFIG_LFS_CACHE_SIZE
#endif
#ifdef CONFIG_LFS_LOOKAHEAD_SIZE
#define LFS_LOOKAHEAD_SIZE CONFIG_LFS_LOOKAHEAD_SIZE
#endif
#ifdef CONFIG_LFS_BLOCK_CYCLES
#define LFS_BLOCK_CYCLES CONFIG_LFS_BLOCK_CYCLES
#endif

/**
 * @brief  register little file system
 * @param  [in] partition_desc: partion table
 * @return 0 on success
 */
int32_t vfs_lfs_register(char *partition_desc);

/**
 * @brief  register little file system with mount point
 * @param  [in] partition_desc: partion table
 * @param  [in] path: the mount point
 * @return 0 on success
 */
int32_t vfs_lfs_register_with_path(char *partition_desc, const char *path);

/**
 * @brief  unregister little file system
 * @return 0 on success
 */
int32_t vfs_lfs_unregister(void);

/**
 * @brief  unregister little file system with mount point
 * @param  [in] path: the mount point
 * @return 0 on success
 */
int32_t vfs_lfs_unregister_with_path(const char *path);

#ifdef __cplusplus
}
#endif

#endif /* __LITTLEFS_VFS_H__ */

