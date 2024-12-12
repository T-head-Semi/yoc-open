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

#ifndef DEVICE_ESP8266_H
#define DEVICE_ESP8266_H

#include <stdint.h>
#include <uservice/uservice.h>
#include <yoc/at_port.h>

#ifdef __cplusplus
extern "C" {
#endif

/* xxx_pin= 0 indicate the pin is not use */
typedef struct {
    int             reset_pin;
    int             cs_pin;
    int             wakeup_pin;
    int             int_pin;
    int             channel_id;
    int             baud;
    int             buffer_size;
    // at_channel_t   *channel;
} w800_wifi_param_t;

/**
 * This function will init atparser for w800
 * @param[in]   task         userver_tast
 * @param[in]   idx          uart_port
 * @param[in]   baud         uart_baud
 * @param[in]   buf_size     uart_rb_size
 * @param[in]   flow_control uart_flowcontrol
 * @return      Zero on success, -1 on failed
 */
int w800_module_init(utask_t *task, w800_wifi_param_t *param);

extern void wifi_w800_register(utask_t *task, w800_wifi_param_t *param);

#ifdef __cplusplus
}
#endif

#endif
