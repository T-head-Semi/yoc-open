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




#include <string.h>

#include "iotx_system_internal.h"

static iotx_conn_info_t     iotx_conn_info = {0, 0, NULL, NULL, NULL, NULL, NULL};

int iotx_device_info_get(iotx_device_info_t *device_info)
{
    if (device_info == NULL) {
        return -1;
    }
    memset(device_info, 0x0, sizeof(iotx_device_info_t));
    HAL_GetProductKey(device_info->product_key);
    HAL_GetDeviceName(device_info->device_name);
    HAL_GetDeviceSecret(device_info->device_secret);
    HAL_GetDeviceID(device_info->device_id);

    return 0;
}

iotx_conn_info_pt iotx_conn_info_get(void)
{
    return &iotx_conn_info;
}

void iotx_conn_info_release(void)
{
    if (iotx_conn_info.host_name != NULL) {
        LITE_free(iotx_conn_info.host_name);
    }
    if (iotx_conn_info.username != NULL) {
        LITE_free(iotx_conn_info.username);
    }
    if (iotx_conn_info.password != NULL) {
        LITE_free(iotx_conn_info.password);
    }
    if (iotx_conn_info.client_id != NULL) {
        LITE_free(iotx_conn_info.client_id);
    }
    memset(&iotx_conn_info, 0, sizeof(iotx_conn_info));
}

iotx_conn_info_pt iotx_conn_info_reload(void (*cb)(void *), void* client)
{
    iotx_conn_info_release();
    if (iotx_guider_authenticate(&iotx_conn_info, cb, client) < 0  || iotx_conn_info.init == 0) {
        return NULL;
    }
    return &iotx_conn_info;
}

