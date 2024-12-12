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

#ifndef __OTA_SERVER_TRANS__
#define __OTA_SERVER_TRANS__

#include "k_types.h"
#include "aos/list.h"

typedef void (*ota_server_event_cb)(uint8_t event, const void *event_data);

int ota_server_trans_init(uint8_t channel, ota_server_event_cb cb);
int ota_server_trans_prepare(uint8_t channel, slist_t *dev_list);
int ota_server_trans_send(uint8_t channel, uint8_t *data, uint8_t len, uint8_t ack);
int ota_server_trans_disconnect(uint8_t channel);
int ota_server_trans_unregister(uint8_t channel);
int ota_server_trans_reset(uint8_t channel);

#endif
