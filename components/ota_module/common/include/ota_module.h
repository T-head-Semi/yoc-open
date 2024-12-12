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
#ifndef __OTA_MODULE_H
#define __OTA_MODULE_H

typedef enum
{
    OTA_CHANNEL_ON_GATT = 0x00,
    OTA_CHANNEL_ON_UART,
    OTA_CHANNEL_ON_HCI_UART,
    OTA_CHANNEL_ON_MESH_EXT_1M,
    OTA_CHANNEL_ON_MESH_EXT_2M,
    OTA_CHANNEL_MAX,
} ota_channel_en;

#ifndef CONFIG_ALLOW_OTA_FOR_HIGH_VERSION
#define CONFIG_ALLOW_OTA_FOR_HIGH_VERSION 1
#endif

#endif
