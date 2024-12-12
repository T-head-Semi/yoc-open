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

#ifndef AOS_VFS_CONFIG_H
#define AOS_VFS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
#define VFS_FALSE    0u
#define VFS_TRUE     1u

#ifndef VFS_CONFIG_DEVICE_NODES
#define VFS_DEVICE_NODES 50
#else
#define VFS_DEVICE_NODES VFS_CONFIG_DEVICE_NODES
#endif

#ifndef VFS_CONFIG_FD_OFFSET
#define VFS_FD_OFFSET 48
#else
#define VFS_FD_OFFSET VFS_CONFIG_FD_OFFSET
#endif

#ifndef VFS_CONFIG_PATH_MAX
#define VFS_PATH_MAX 256
#else
#define VFS_PATH_MAX VFS_CONFIG_PATH_MAX
#endif

#ifndef VFS_CONFIG_MAX_FILE_NUM
#define VFS_MAX_FILE_NUM (VFS_DEVICE_NODES * 2)
#else
#define VFS_MAX_FILE_NUM VFS_CONFIG_MAX_FILE_NUM
#endif

#ifndef VFS_CONFIG_STAT_INCLUDE_SIZE
#define VFS_STAT_INCLUDE_SIZE 1
#else
#define VFS_STAT_INCLUDE_SIZE VFS_CONFIG_STAT_INCLUDE_SIZE
#endif

#ifndef VFS_CONFIG_CURRENT_DIRECTORY_ENABLE
#define CURRENT_WORKING_DIRECTORY_ENABLE 1
#else
#define CURRENT_WORKING_DIRECTORY_ENABLE VFS_CONFIG_CURRENT_DIRECTORY_ENABLE
#endif

#ifdef __cplusplus
}
#endif

#endif

