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

#ifndef DEVICE_VFS_IIC_PAI_H
#define DEVICE_VFS_IIC_PAI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_device.h>

#define IIC_IOC_GET_DEFAULT_CONFIG      (DEV_IIC_IOCTL_CMD_BASE + 1)
#define IIC_IOC_SET_CONFIG              (DEV_IIC_IOCTL_CMD_BASE + 2)
#define IIC_IOC_DMA_ENABLE              (DEV_IIC_IOCTL_CMD_BASE + 3)
#define IIC_IOC_MASTER_SEND             (DEV_IIC_IOCTL_CMD_BASE + 4)
#define IIC_IOC_MASTER_RECV             (DEV_IIC_IOCTL_CMD_BASE + 5)
#define IIC_IOC_SLAVE_SEND              (DEV_IIC_IOCTL_CMD_BASE + 6)
#define IIC_IOC_SLAVE_RECV              (DEV_IIC_IOCTL_CMD_BASE + 7)
#define IIC_IOC_MEM_WRITE               (DEV_IIC_IOCTL_CMD_BASE + 8)
#define IIC_IOC_MEM_READ                (DEV_IIC_IOCTL_CMD_BASE + 9)
#define IIC_IOC_TIMEOUT                 (DEV_IIC_IOCTL_CMD_BASE + 10)

typedef struct {
    uint16_t dev_addr;
    void *data;
    uint32_t size;
    uint32_t timeout;
    uint16_t mem_addr;
    uint16_t mem_addr_size;
} rvm_iic_dev_msg_t;
#endif

#ifdef __cplusplus
}
#endif

#endif
