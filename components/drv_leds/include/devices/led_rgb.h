/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __LED_RGB_H__
#define __LED_RGB_H__

#include <stdint.h>
#include <devices/led.h>
#ifdef __cplusplus
extern "C" {
#endif

void rvm_led_rgb_drv_register(led_pin_config_t *config, int idx);

#ifdef __cplusplus
}
#endif

#endif