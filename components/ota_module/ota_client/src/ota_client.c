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

#include "ota_module.h"
#include "ais_ota/ais_ota_client.h"
#include "mesh_ota/mesh_ota_client.h"
#include "ulog/ulog.h"

#define TAG "OTA_CLIENT"

int ota_client_init()
{
    int     ret                  = 0;
    uint8_t protocol_choose_flag = 0;
#if defined(CONFIG_OTA_CLIENT_PROCTOCOL_AIS) && CONFIG_OTA_CLIENT_PROCTOCOL_AIS > 0
    ret = ais_ota_client_init();
    if (ret) {
        LOGE(TAG, "Ais ota client init failed %d", ret);
        return ret;
    }
    protocol_choose_flag = 1;
#endif
#if defined(CONFIG_OTA_CLIENT_PROCTOCOL_MESH) && CONFIG_OTA_CLIENT_PROCTOCOL_MESH > 0
    ret = mesh_ota_client_init();
    if (ret) {
        LOGE(TAG, "Mesh ota client init failed %d", ret);
        return ret;
    }
    protocol_choose_flag = 1;
#endif
    if (!protocol_choose_flag) {
        LOGE(TAG, "No ota proctocol choosed for ota client", ret);
        return -1;
    }
    return 0;
}
