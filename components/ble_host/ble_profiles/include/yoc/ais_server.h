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

#ifndef __AIS_SERVER_H
#define __AIS_SERVER_H
#include "yoc/ble_ais.h"

typedef enum {
    AIS_SERVER_GATT_EVENT_CONN,
    AIS_SERVER_GATT_EVENT_DISCONN,
    AIS_SERVER_GATT_EVENT_MTU_EXCHANGE,
    AIS_SERVER_GATT_EVENT_DISCOVER_SUCCEED,
    AIS_SERVER_GATT_EVENT_NOTIFY,
    AIS_SERVER_GATT_EVENT_WRITE,
} ais_server_event_en;

int  ble_prf_ais_server_init(ais_cb cb);
void ble_prf_ais_server_indicate(uint8_t msg_id, uint8_t cmd, uint8_t *p_msg, uint16_t len);
void ble_prf_ais_server_notify(uint8_t msg_id, uint8_t cmd, uint8_t *p_msg, uint16_t len);
int  ble_prf_ais_server_disconnect();

/// deprecated fucntion ble_ais_server_init, use ble_prf_ais_server_init instead
static inline __bt_deprecated int ble_ais_server_init(ais_cb cb)
{
    return ble_prf_ais_server_init(cb);
}
/// deprecated fucntion ble_ais_server_indicate, use ble_prf_ais_server_indicate instead
static inline __bt_deprecated void ble_ais_server_indicate(uint8_t msg_id, uint8_t cmd, uint8_t *p_msg, uint16_t len)
{
    return ble_prf_ais_server_indicate(msg_id, cmd, p_msg, len);
}

/// deprecated fucntion ble_ais_server_notify, use ble_prf_ais_server_notify instead
static inline __bt_deprecated void ble_ais_server_notify(uint8_t msg_id, uint8_t cmd, uint8_t *p_msg, uint16_t len)
{
    return ble_prf_ais_server_notify(msg_id, cmd, p_msg, len);
}

/// deprecated fucntion ble_ais_server_disconnect, use ble_prf_ais_server_disconnect instead
static inline __bt_deprecated int ble_ais_server_disconnect()
{
    return ble_prf_ais_server_disconnect();
}

#endif
