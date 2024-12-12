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

#ifndef _DEVICE_WDT_H_
#define _DEVICE_WDT_H_

#include <stdio.h>
#include <stdlib.h>
#include <devices/device.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*rvm_hal_wdt_callback)(rvm_dev_t *dev, void *arg);

#define rvm_hal_wdt_open(name)        rvm_hal_device_open(name)
#define rvm_hal_wdt_close(dev)        rvm_hal_device_close(dev)

/**
  \brief       Set the WDT value
  \param[in]   dev    Pointer to device object.
  \param[in]   ms     The timeout value(ms)
  \return      0 on success, else on fail.
*/
int rvm_hal_wdt_set_timeout(rvm_dev_t *dev, uint32_t ms);

/**
  \brief       Start the WDT
  \param[in]   dev    Pointer to device object.
  \return      0 on success, else on fail.
*/
int rvm_hal_wdt_start(rvm_dev_t *dev);

/**
  \brief       Stop the WDT
  \param[in]   dev    Pointer to device object.
  \return      0 on success, else on fail.
*/
int rvm_hal_wdt_stop(rvm_dev_t *dev);

/**
  \brief       Feed the WDT
  \param[in]   dev    Pointer to device object.
  \return      0 on success, else on fail.
*/
int rvm_hal_wdt_feed(rvm_dev_t *dev);

/**
  \brief       Get the remaining time to timeout
  \param[in]   dev    Pointer to device object.
  \return      The remaining time of WDT(ms)
*/
uint32_t rvm_hal_wdt_get_remaining_time(rvm_dev_t *dev);

/**
  \brief       Attach the callback handler to WDT
  \param[in]   dev    Pointer to device object.
  \param[in]   callback    Callback function
  \param[in]   arg         Callback's param
  \return      0 on success, else on fail.
*/
int rvm_hal_wdt_attach_callback(rvm_dev_t *dev, rvm_hal_wdt_callback callback, void *arg);

/**
  \brief       Detach the callback handler
  \param[in]   dev    Pointer to device object.
  \return      0 on success, else on fail.
*/
int rvm_hal_wdt_detach_callback(rvm_dev_t *dev);


#if defined(AOS_COMP_DEVFS) && AOS_COMP_DEVFS
#include <devices/vfs_wdt.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
