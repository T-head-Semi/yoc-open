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

#ifndef DEVICE_VFS_ADC_H
#define DEVICE_VFS_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_device.h>

#define ADC_IOC_GET_DEFAULT_CONFIG      (DEV_ADC_IOCTL_CMD_BASE + 1)
#define ADC_IOC_SET_CONFIG              (DEV_ADC_IOCTL_CMD_BASE + 2)
#define ADC_IOC_GET_PIN2CHANNEL         (DEV_ADC_IOCTL_CMD_BASE + 3)
#define ADC_IOC_DMA_ENABLE              (DEV_ADC_IOCTL_CMD_BASE + 4)
#define ADC_IOC_GET_VALUE               (DEV_ADC_IOCTL_CMD_BASE + 5)
#define ADC_IOC_GET_MULTIPLE_VALUE      (DEV_ADC_IOCTL_CMD_BASE + 6)

typedef struct {
    uint8_t ch;
    size_t num;
    uint8_t pin;
    uint32_t timeout;
    void *output;
} rvm_adc_dev_msg_t;
#endif

#ifdef __cplusplus
}
#endif

#endif
