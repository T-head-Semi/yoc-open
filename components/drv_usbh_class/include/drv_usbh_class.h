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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Register ec200a 4G module rndis driver
 * @return      void
 */
void drv_ec200a_rndis_register();


/**
 * Register ec200a 4G module usb serial AT command driver
 * @return      void
 */
void drv_ec200a_serial_register(uint8_t idx);


/**
 * Register usb msc driver
 * @return      void
 */
void rvm_usb_msc_drv_register(int idx);

#ifdef __cplusplus
}
#endif