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
#ifndef DEVICE_STL8723_BT_H
#define DEVICE_STL8723_BT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rtl8723ds_bt_config_t {
    int uart_id;
    int bt_dis_pin;
} rtl8723ds_bt_config;

/**
 * @brief  register bluetooth driver of rtl8723 
 * @param  [in] config
 * @return  
 */
extern void bt_rtl8723ds_register(rtl8723ds_bt_config* config);


#ifdef __cplusplus
}
#endif

#endif
