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

#ifndef _DEVICE_VFS_CLK_H_
#define _DEVICE_VFS_CLK_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_device.h>

#define CLK_IOC_ENABLE          (DEV_CLK_IOCTL_CMD_BASE + 1)
#define CLK_IOC_DISABLE         (DEV_CLK_IOCTL_CMD_BASE + 2)
#define CLK_IOC_GET_FREQ        (DEV_CLK_IOCTL_CMD_BASE + 3)
#define CLK_IOC_SET_FREQ        (DEV_CLK_IOCTL_CMD_BASE + 4)

typedef struct {
    rvm_hal_clk_id_t clk_id;
    uint32_t idx;
    uint32_t freq;
} rvm_clk_dev_msg_t;
#endif

#ifdef __cplusplus
}
#endif

#endif
