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

#ifndef _DEVICE_VFS_I2S_H_
#define _DEVICE_VFS_I2S_H_

#ifdef __cplusplus
extern "C" {
#endif
#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_device.h>

#define I2S_IOC_SET_CONFIG                    (DEV_I2S_IOCTL_CMD_BASE + 1)
#define I2S_IOC_GET_CONFIG                    (DEV_I2S_IOCTL_CMD_BASE + 2)
#define I2S_IOC_PAUSE                         (DEV_I2S_IOCTL_CMD_BASE + 3)
#define I2S_IOC_RESUME                        (DEV_I2S_IOCTL_CMD_BASE + 4)
#define I2S_IOC_STOP                          (DEV_I2S_IOCTL_CMD_BASE + 5)
#define I2S_IOC_TIMEOUT                       (DEV_I2S_IOCTL_CMD_BASE + 6)

#endif
#ifdef __cplusplus
}
#endif

#endif
