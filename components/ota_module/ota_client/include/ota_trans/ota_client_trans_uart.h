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
#ifndef _GATEWAY_OTA_UART_H
#define _GATEWAY_OTA_UART_H

#include "aos/list.h"

typedef void (*ota_client_event_cb)(uint8_t event, const void *event_data, uint8_t len);
typedef void (*ota_event_cb)(int event, uint8_t *data, int len);

void ota_event_input_cb(int event, uint8_t *event_data, int len);
int  ota_client_trans_uart_init(ota_client_event_cb cb);
int  ota_client_trans_uart_prepare(slist_t *dev_list);
int  ota_client_trans_uart_disconnect();
int  ota_client_trans_uart_send(uint8_t msg_id, uint8_t cmd, uint8_t *p_msg, uint16_t len, uint8_t ack);
int  ota_client_trans_uart_reset();
int  ota_client_trans_uart_unregister();

#endif
