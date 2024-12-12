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

#ifndef _DEVICE_VFS_GPIOPIN_H_
#define _DEVICE_VFS_GPIOPIN_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_device.h>

#define GPIOPIN_IOC_SET_DIRECTION               (DEV_GPIOPIN_IOCTL_CMD_BASE + 1)
#define GPIOPIN_IOC_SET_MODE                    (DEV_GPIOPIN_IOCTL_CMD_BASE + 2)
#define GPIOPIN_IOC_ATTACH_CALLBACK             (DEV_GPIOPIN_IOCTL_CMD_BASE + 3)
#define GPIOPIN_IOC_SET_IRQ_MODE                (DEV_GPIOPIN_IOCTL_CMD_BASE + 4)
#define GPIOPIN_IOC_SET_IRQ_ENABLE              (DEV_GPIOPIN_IOCTL_CMD_BASE + 5)
#define GPIOPIN_IOC_SET_DEBOUNCE                (DEV_GPIOPIN_IOCTL_CMD_BASE + 6)
#define GPIOPIN_IOC_WRITE                       (DEV_GPIOPIN_IOCTL_CMD_BASE + 7)
#define GPIOPIN_IOC_READ                        (DEV_GPIOPIN_IOCTL_CMD_BASE + 8)
#define GPIOPIN_IOC_OUTPUT_TOGGLE               (DEV_GPIOPIN_IOCTL_CMD_BASE + 9)

typedef struct {
    rvm_hal_gpio_pin_callback callback;
    rvm_hal_gpio_pin_data_t *value;
    void *arg;
} rvm_gpiopin_dev_msg_t;
#endif

#ifdef __cplusplus
}
#endif

#endif
