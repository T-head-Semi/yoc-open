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

#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

/*
 *"wiz_config.h" file is used for CDK system configuration.
 *Makefile compilation needs to keep the file empty.
 */
//#include "wiz_config.h"

/* Allow LOGD function to output log information */
#ifndef CONFIG_DEBUG
#define CONFIG_DEBUG 1
#endif

/* You can add user configuration items here. */

//#define CONFIG_WIFI_SSID "o"
//#define CONFIG_WIFI_PSK "12345678"

#define WLAN_ENABLE_PIN PA16
#define WLAN_POWER_PIN  0xFFFFFFFF

#define CONFIG_WIFI_SSID     "OS-TEST"
#define CONFIG_WIFI_PSK      "TEST1234"
#define CONFIG_MANTB_VERSION 4

#define CONSOLE_IDX 0

#endif
