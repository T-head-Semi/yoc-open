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
#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_

#include <stdint.h>
#include <uservice/uservice.h>
#include <yoc/netmgr_service.h>
#include <uservice/eventid.h>

extern netmgr_hdl_t app_netmgr_hdl;

void board_cli_init();
void board_yoc_init(void);
void app_network_init(void);
void app_wifi_init(void);
void app_exception_init(void);
void app_exception_event(uint32_t event_id);


/* user define event */
#define EVENT_NTP_RETRY_TIMER       (EVENT_USER + 1)
#define EVENT_NET_CHECK_TIMER       (EVENT_USER + 2)
#define EVENT_NET_NTP_SUCCESS       (EVENT_USER + 3)
#endif