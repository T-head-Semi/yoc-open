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
#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/battery.h>
#include <string.h>

static aos_status_t _devfs_battery_ioctl(devfs_file_t *file, int cmd, uintptr_t arg)
{
    int ret;
    rvm_dev_t *dev = devfs_file2dev(file);

    if (!dev) {
        return -EINVAL;
    }

    ret = 0;
    switch (cmd) {
    case BATTERY_IOC_FETCH:
    {
        if (!(const void *)arg) {
            ret = -EFAULT;
            break;
        }

        rvm_hal_battery_attr_t attr;
        memcpy(&attr, (const void *)arg, sizeof(rvm_hal_battery_attr_t));
        if (rvm_hal_battery_fetch(dev, attr)) {
            ret = -EIO;
            break;
        }
        break;
    }
    case BATTERY_IOC_GETVALUE:
    {
        if (!(const void *)arg) {
            ret = -EFAULT;
            break;
        }

        rvm_battery_dev_msg_t msg;
        memcpy(&msg, (const void *)arg, sizeof(rvm_battery_dev_msg_t));
        if (rvm_hal_battery_getvalue(dev, msg.attr, msg.value, msg.size)) {
            ret = -EIO;
            break;
        }
        break;
    }
    case BATTERY_IOC_EVENT_CB:
    {
        if (!(const void *)arg) {
            ret = -EFAULT;
            break;
        }

        rvm_hal_battery_event_t event;
        memcpy(&event, (const void *)arg, sizeof(rvm_hal_battery_event_t));
        if (rvm_hal_battery_event_cb(event)) {
            ret = -EIO;
            break;
        }
        break;
    }
    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

static const devfs_file_ops_t devfs_battery_ops = {
    .ioctl      = _devfs_battery_ioctl,
    .poll       = NULL,
    .mmap       = NULL,
    .read       = NULL,
    .write      = NULL,
    .lseek      = NULL,
};

static devfs_ops_node_t battery_ops_node = {
    .name = "battery",
    .ops = (devfs_file_ops_t *)&devfs_battery_ops,
};

void battery_devfs_init(void)
{
    devices_add_devfs_ops_node(&battery_ops_node);
}
VFS_DEV_DRIVER_ENTRY(battery_devfs_init);

#endif
