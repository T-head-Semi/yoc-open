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

#ifndef _DEVICE_VFS_SPI_H_
#define _DEVICE_VFS_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_device.h>

#define SPI_IOC_GET_DEFAULT_CONFIG      (DEV_SPI_IOCTL_CMD_BASE + 1)
#define SPI_IOC_CONFIG                  (DEV_SPI_IOCTL_CMD_BASE + 2)
#define SPI_IOC_CONFIG_GET              (DEV_SPI_IOCTL_CMD_BASE + 3)
#define SPI_IOC_SEND                    (DEV_SPI_IOCTL_CMD_BASE + 4)
#define SPI_IOC_RECV                    (DEV_SPI_IOCTL_CMD_BASE + 5)
#define SPI_IOC_SEND_RECV               (DEV_SPI_IOCTL_CMD_BASE + 6)
#define SPI_IOC_SEND_THEN_RECV          (DEV_SPI_IOCTL_CMD_BASE + 7)
#define SPI_IOC_SEND_THEN_SEND          (DEV_SPI_IOCTL_CMD_BASE + 8)
#define SPI_IOC_TIMEOUT                 (DEV_SPI_IOCTL_CMD_BASE + 9)

typedef struct {
    uint8_t *tx_data;
    uint8_t *rx_data;
    uint8_t *tx1_data;
    size_t size;
    size_t tx_size;
    size_t tx1_size;
    size_t rx_size;
    uint32_t timeout;
} rvm_spi_dev_msg_t;
#endif

#ifdef __cplusplus
}
#endif

#endif
