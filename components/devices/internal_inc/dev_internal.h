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

#ifndef _DEVICE_INTERNAL_H_
#define _DEVICE_INTERNAL_H_

#include <stdint.h>
#include <devices/driver.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief       get device object by device name and id
  \param[in]   name     device name
  \param[in]   id       device index
  \return      null on error, device object pointer on success
*/
rvm_dev_t *device_open_id(const char *name, int id);

/**
  \brief       lock device to prevent to access
  \param[in]   dev      device driver object
  \return      none
*/
int device_lock(rvm_dev_t *dev);

/**
  \brief       unlock device to allow to access
  \param[in]   dev      device driver object
  \return      none
*/
int device_unlock(rvm_dev_t *dev);

/**
  \brief       valid a device 's name
  \param[in]   dev      device driver object
  \param[in]   name     device name
  \return      =0 success other is error
*/
int device_valid(rvm_dev_t *dev, const char *name);


/**
  \brief       device is busy
  \return      1 is on busy, 0 is in idle
*/
int device_is_busy(void);


#ifdef __cplusplus
}
#endif

#endif
