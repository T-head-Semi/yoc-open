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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dev_internal.h>
#include <devices/impl/i2s_impl.h>

#define I2S_DRIVER(dev)  ((i2s_driver_t*)(dev->drv))
#define I2S_VAILD(dev) do { \
    if (device_valid(dev, "iis") != 0) \
        return -1; \
} while(0)

int rvm_hal_i2s_config(rvm_dev_t *dev, rvm_hal_i2s_config_t *config)
{
    int ret;

    I2S_VAILD(dev);

    device_lock(dev);
    ret = I2S_DRIVER(dev)->config(dev, config);
    device_unlock(dev);

    return ret;
}

int rvm_hal_i2s_config_get(rvm_dev_t *dev, rvm_hal_i2s_config_t *config)
{
    int ret;

    I2S_VAILD(dev);

    device_lock(dev);
    ret = I2S_DRIVER(dev)->config_get(dev, config);
    device_unlock(dev);

    return ret;
}

int rvm_hal_i2s_send(rvm_dev_t *dev, const void *data, size_t size, uint32_t timeout)
{
    int ret;

    I2S_VAILD(dev);

    device_lock(dev);
    ret = I2S_DRIVER(dev)->send(dev, data, size, timeout);
    device_unlock(dev);

    return ret;
}

int rvm_hal_i2s_recv(rvm_dev_t *dev, void *data, size_t size, uint32_t timeout)
{
    int ret;

    I2S_VAILD(dev);

    device_lock(dev);
    ret = I2S_DRIVER(dev)->recv(dev, data, size, timeout);
    device_unlock(dev);

    return ret;
}

int rvm_hal_i2s_pause(rvm_dev_t *dev)
{
    int ret;

    I2S_VAILD(dev);

    device_lock(dev);
    ret = I2S_DRIVER(dev)->pause(dev);
    device_unlock(dev);

    return ret;
}

int rvm_hal_i2s_resume(rvm_dev_t *dev)
{
    int ret;

    I2S_VAILD(dev);

    device_lock(dev);
    ret = I2S_DRIVER(dev)->resume(dev);
    device_unlock(dev);

    return ret;
}

int rvm_hal_i2s_stop(rvm_dev_t *dev)
{
    int ret;

    I2S_VAILD(dev);

    device_lock(dev);
    ret = I2S_DRIVER(dev)->stop(dev);
    device_unlock(dev);

    return ret;
}
