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

#ifndef DEVICE_VFS_UART_PAI_H
#define DEVICE_VFS_UART_PAI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_device.h>

#define UART_IOC_GET_DEFAULT_CONFIG     (DEV_UART_IOCTL_CMD_BASE + 1)
#define UART_IOC_SET_CONFIG             (DEV_UART_IOCTL_CMD_BASE + 2)
#define UART_IOC_GET_CONFIG             (DEV_UART_IOCTL_CMD_BASE + 3)
#define UART_IOC_SET_TYPE               (DEV_UART_IOCTL_CMD_BASE + 4)
#define UART_IOC_SET_BUFFER_SIZE        (DEV_UART_IOCTL_CMD_BASE + 5)
#define UART_IOC_SET_EVENT              (DEV_UART_IOCTL_CMD_BASE + 6)
#define UART_IOC_SEND_POLL              (DEV_UART_IOCTL_CMD_BASE + 7)
#define UART_IOC_RECV_POLL              (DEV_UART_IOCTL_CMD_BASE + 8)
#define UART_IOC_DMA_ENABLE             (DEV_UART_IOCTL_CMD_BASE + 9)

typedef struct {
    uint32_t size;
    void *buffer;
    void (*event)(rvm_dev_t *dev, int event_id, void *priv);
    void *priv;
} rvm_uart_dev_msg_t;
#endif

#ifdef __cplusplus
}
#endif

#endif
