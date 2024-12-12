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

#ifndef DEVICE_VFS_BATTERY_H
#define DEVICE_VFS_BATTERY_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_device.h>

#define BATTERY_IOC_FETCH               (DEV_BATTERY_IOCTL_CMD_BASE + 1)
#define BATTERY_IOC_GETVALUE            (DEV_BATTERY_IOCTL_CMD_BASE + 2)
#define BATTERY_IOC_EVENT_CB            (DEV_BATTERY_IOCTL_CMD_BASE + 3)

typedef struct {
    rvm_hal_battery_attr_t attr;
    void *value;
    size_t size;
} rvm_battery_dev_msg_t;
#endif

#ifdef __cplusplus
}
#endif

#endif
