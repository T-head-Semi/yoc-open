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

#ifndef _DEVICE_VFS_RTC_H_
#define _DEVICE_VFS_RTC_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_device.h>

#define RTC_IOC_SET_TIME                    (DEV_RTC_IOCTL_CMD_BASE + 1)
#define RTC_IOC_GET_TIME                    (DEV_RTC_IOCTL_CMD_BASE + 2)
#define RTC_IOC_GET_ALARM_REMAINING_TIME    (DEV_RTC_IOCTL_CMD_BASE + 3)
#define RTC_IOC_SET_ALARM                   (DEV_RTC_IOCTL_CMD_BASE + 4)
#define RTC_IOC_CANCEL_ALARM                (DEV_RTC_IOCTL_CMD_BASE + 5)

typedef struct {
    struct tm *time;
    rvm_hal_rtc_callback callback;
    void *arg;
} rvm_rtc_dev_msg_t;
#endif

#ifdef __cplusplus
}
#endif

#endif
