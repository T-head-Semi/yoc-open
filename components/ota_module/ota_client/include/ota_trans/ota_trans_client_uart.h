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

#include "ais_ota/ais_ota_client.h"

int ais_ota_trans_uart_init(ota_server_event_cb cb);
int ais_ota_trans_uart_prepare(slist_t *dev_list);
int ais_ota_trans_uart_disconnect();
int ais_ota_trans_uart_send(uint8_t *data, uint8_t len, uint8_t ack);
int ais_ota_trans_uart_reset();
int ais_ota_trans_uart_unregister();

#endif
