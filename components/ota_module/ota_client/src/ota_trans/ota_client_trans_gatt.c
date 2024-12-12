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

#if defined(CONFIG_OTA_CLIENT_TRANS_GATT) && CONFIG_OTA_CLIENT_TRANS_GATT

#include "aos/kernel.h"
#include "errno.h"
#include "ulog/ulog.h"
#include "yoc/ais_server.h"
#include "ota_trans/ota_client_trans.h"
#include "ota_trans/ota_client_trans_gatt.h"

#define TAG "OTA_TRANS_GATT"

static ota_client_event_cb g_cb = NULL;

void ais_event_cb(uint8_t event, const void *event_data, uint32_t len)
{
    uint8_t trans_event = 0;
    switch (event) {
        case AIS_SERVER_GATT_EVENT_CONN: {
            trans_event = OTA_CLIENT_EVENT_CONN;
        } break;
        case AIS_SERVER_GATT_EVENT_DISCONN: {
            trans_event = OTA_CLIENT_EVENT_DISCONN;
        } break;
        case AIS_SERVER_GATT_EVENT_WRITE: {
            trans_event = OTA_CLIENT_EVENT_WRITE;
        } break;
        default:
            return;
    }

    if (g_cb) {
        g_cb(trans_event, event_data, len);
    }
}

int ota_client_trans_gatt_init(void (*cb)(uint8_t, const void *, uint8_t))
{
    int ret = 0;
    ret     = ble_prf_ais_server_init(ais_event_cb);
    if (ret) {
        LOGE(TAG, "ble ais init failed %d", ret);
        return ret;
    }
    g_cb = (ota_client_event_cb)cb;
    return 0;
}

int ota_client_trans_gatt_disconnect()
{
    return ble_prf_ais_server_disconnect();
}

int ota_client_trans_gatt_send(uint8_t msg_id, uint8_t cmd, uint8_t *p_msg, uint16_t len, uint8_t ack)
{
    if (!ack) {
        ble_prf_ais_server_notify(msg_id, cmd, p_msg, len);
    } else {
        ble_prf_ais_server_indicate(msg_id, cmd, p_msg, len);
    }
    return 0;
}

#endif
