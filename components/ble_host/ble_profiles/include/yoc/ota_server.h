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

#ifndef _TAG_BLE_OTA_
#define _TAG_BLE_OTA_

#include <stdint.h>

typedef enum {
    OTA_ST_IDLE = 0,
    OTA_ST_START,
    OTA_ST_REQUEST,
    OTA_ST_DL,
    OTA_ST_FLASH,
    OTA_ST_STOP,
    OTA_ST_COMPLETE,
} ota_state_en;

typedef void (*ota_event_callback_t)(ota_state_en ota_state);

int ble_prf_ota_servrer_init(ota_event_callback_t cb);

void ble_prf_ota_service_process();

/// deprecated fucntion ble_ota_init, use ble_prf_ota_servrer_init instead
static inline __bt_deprecated int ble_ota_init(ota_event_callback_t cb)
{
    return ble_prf_ota_servrer_init(cb);
}

/// deprecated fucntion ble_ota_init, use ble_prf_ota_servrer_init instead
static inline __bt_deprecated void ble_ota_process()
{
    return ble_prf_ota_service_process();
}

#endif /* _TAG_BLE_OTA_ */
