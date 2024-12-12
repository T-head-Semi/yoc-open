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

#ifndef BZ_AIS_H
#define BZ_AIS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_UUID_AIS_SERVICE     0xFEB3

typedef struct {
    uint16_t mtu;
} ble_ais_init_t;

typedef struct ble_gatts_char_handles_s {
    uint16_t chrc_handle;
    uint16_t value_handle;
    uint16_t user_desc_handle;
    uint16_t cccd_handle;
    uint16_t sccd_handle;
} ble_gatts_char_handles_t;

typedef struct ble_ais_s {
    uint16_t service_handle;
    ble_gatts_char_handles_t rc_handles;  // Handles related to Read Characteristics
    ble_gatts_char_handles_t wc_handles;  // Handles related to Write Characteristics
    ble_gatts_char_handles_t ic_handles;  // Handles related to Indicate Characteristics
    ble_gatts_char_handles_t wwnrc_handles;  // Handles related to Write WithNoRsp Characteristics
    ble_gatts_char_handles_t nc_handles;  // Handles related to Notify Characteristics
    uint16_t conn_handle;  // Handle of the current connection
    bool is_indication_enabled;
    bool is_notification_enabled;
    void *p_context;
    uint16_t max_pkt_size;
} ble_ais_t;

uint32_t ble_ais_init(const ble_ais_init_t * p_ais_init);
uint32_t ble_ais_send_notification(uint8_t * p_data, uint16_t length);
uint32_t ble_ais_send_indication(uint8_t * p_data, uint16_t length);


#ifdef __cplusplus
}
#endif

#endif // BZ_AIS_H
