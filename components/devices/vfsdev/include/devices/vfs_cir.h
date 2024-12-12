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

#ifndef _DEVICE_VFS_CIR_H_
#define _DEVICE_VFS_CIR_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_device.h>

#define CIR_IOC_SET_CONFIG                    (DEV_CIR_IOCTL_CMD_BASE + 1)
#define CIR_IOC_GET_CONFIG                    (DEV_CIR_IOCTL_CMD_BASE + 2)
#define CIR_IOC_SEND_SCANCODE                 (DEV_CIR_IOCTL_CMD_BASE + 3)
#define CIR_IOC_RECV_START                    (DEV_CIR_IOCTL_CMD_BASE + 4)
#define CIR_IOC_SET_RX_EVENT                  (DEV_CIR_IOCTL_CMD_BASE + 5)
#define CIR_IOC_GET_RECV_SCANCODE             (DEV_CIR_IOCTL_CMD_BASE + 6)

typedef struct 
{
    void *arg;
    rvm_hal_cir_rx_callback callback;
} rvm_cir_dev_rx_event_msg_t;

#endif
#ifdef __cplusplus
}
#endif

#endif
