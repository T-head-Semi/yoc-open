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

#ifndef _BT_HRS_H_
#define _BT_HRS_H_

typedef struct _hrs_t {
    uint16_t conn_handle;
    uint16_t hrs_svc_handle;
    int16_t  mea_ccc;
    uint8_t  hrs_mea_flag;
    uint8_t  hrs_mea_level;
    slist_t  next;
} hrs_t;

typedef hrs_t *hrs_handle_t;

hrs_handle_t ble_prf_hrs_init(hrs_t *hrs);
int          ble_prf_hrs_measure_level_update(hrs_handle_t handle, uint8_t *data, uint8_t length);

/// deprecated fucntion hrs_init, use ble_prf_hrs_init instead
static inline __bt_deprecated hrs_handle_t hrs_init(hrs_t *hrs)
{
    return ble_prf_hrs_init(hrs);
}

/// deprecated fucntion hrs_measure_level_update, use ble_prf_hrs_measure_level_update instead
static inline __bt_deprecated int hrs_measure_level_update(hrs_handle_t handle, uint8_t *data, uint8_t length)
{
    return ble_prf_hrs_measure_level_update(handle, data, length);
}

#endif
