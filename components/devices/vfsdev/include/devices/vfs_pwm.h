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

#ifndef _DEVICE_VFS_PWM_H_
#define _DEVICE_VFS_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_device.h>

#define PWM_IOC_CONFIG                  (DEV_PWM_IOCTL_CMD_BASE + 1)
#define PWM_IOC_CONFIG_GET              (DEV_PWM_IOCTL_CMD_BASE + 2)
#define PWM_IOC_START                   (DEV_PWM_IOCTL_CMD_BASE + 3)
#define PWM_IOC_STOP                    (DEV_PWM_IOCTL_CMD_BASE + 4)

typedef struct {
    rvm_hal_pwm_config_t config;
    uint8_t channel;
} rvm_pwm_dev_msg_t;
#endif

#ifdef __cplusplus
}
#endif

#endif
