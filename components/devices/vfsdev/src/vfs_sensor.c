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
#include <devices/sensor.h>
#include <string.h>

static aos_status_t _devfs_sensor_ioctl(devfs_file_t *file, int cmd, uintptr_t arg)
{
    int ret;
    rvm_dev_t *dev = devfs_file2dev(file);

    if (!dev) {
        return -EINVAL;
    }

    ret = 0;
    switch (cmd) {
    case SENSOR_IOC_FETCH:
    {
        if (!(void *)arg) {
            ret = -EFAULT;
            break;
        }

        if (rvm_hal_sensor_fetch(dev)) {
            return -EIO;
        }
        break;
    }
    case SENSOR_IOC_GETVALUE:
    {
        if (!(const void *)arg) {
            ret = -EFAULT;
            break;
        }
        rvm_sensor_dev_msg_t msg;
        memcpy(&msg, (void *)arg, sizeof(rvm_sensor_dev_msg_t));
        if (rvm_hal_sensor_getvalue(dev, msg.value, msg.size)) {
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

static const devfs_file_ops_t devfs_sensor_ops = {
    .ioctl      = _devfs_sensor_ioctl,
    .poll       = NULL,
    .mmap       = NULL,
    .read       = NULL,
    .write      = NULL,
    .lseek      = NULL,
};

static devfs_ops_node_t sensor_ops_node = {
    .name = "sensor",
    .ops = (devfs_file_ops_t *)&devfs_sensor_ops,
};

void sensor_devfs_init(void)
{
    devices_add_devfs_ops_node(&sensor_ops_node);
}
VFS_DEV_DRIVER_ENTRY(sensor_devfs_init);

#endif