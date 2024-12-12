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
#if defined(CONFIG_SAL) || defined(CONFIG_TCPIP)
#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/ethernet.h>
#include <string.h>

static aos_status_t _devfs_eth_ioctl(devfs_file_t *file, int cmd, uintptr_t arg)
{
    int ret;
    rvm_dev_t *dev = devfs_file2dev(file);

    if (!dev) {
        return -EINVAL;
    }

    ret = 0;
    switch (cmd) {
    case ETH_IOC_RESET:
    {
        if (rvm_hal_eth_reset(dev)) {
            return -EIO;
        }
        break;
    }
    case ETH_IOC_START:
    {
        if (rvm_hal_eth_start(dev)) {
            return -EIO;
        }
        break;
    }
    case ETH_IOC_STOP:
    {
        if (rvm_hal_eth_stop(dev)) {
            return -EIO;
        }
        break;
    }
    case ETH_IOC_MAC_CONTROL:
    {
        if (!(const void *)arg) {
            ret = -EFAULT;
            break;
        }
        eth_config_t config;
        memcpy(&config, (void *)arg, sizeof(eth_config_t));
        if (rvm_hal_eth_mac_control(dev, &config)) {
            return -EIO;
        }
        break;
    }
    case ETH_IOC_SET_PACKET_FILTER:
    {
        if (!(const void *)arg) {
            ret = -EFAULT;
            break;
        }
        int type;
        memcpy(&type, (void *)arg, sizeof(int));
        if (rvm_hal_eth_set_packet_filter(dev, type)) {
            return -EIO;
        }
        break;
    }
    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

static const devfs_file_ops_t devfs_eth_ops = {
    .ioctl      = _devfs_eth_ioctl,
    .poll       = NULL,
    .mmap       = NULL,
    .read       = NULL,
    .write      = NULL,
    .lseek      = NULL,
};

static devfs_ops_node_t eth_ops_node = {
    .name = "eth",
    .ops = (devfs_file_ops_t *)&devfs_eth_ops,
};

void eth_devfs_init(void)
{
    devices_add_devfs_ops_node(&eth_ops_node);
}
VFS_DEV_DRIVER_ENTRY(eth_devfs_init);

#endif
#endif

