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

#ifndef _IOTX_AUTH_H_
#define _IOTX_AUTH_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdio.h>
#include "iot_import.h"
#include "iot_export.h"
#include "utils_sysinfo.h"
#include "report.h"

/* domain type define */
typedef enum _DOMAIN_TYPE {
    GUIDER_DOMAIN_MQTT,
    GUIDER_DOMAIN_HTTP,
    GUIDER_DOMAIN_DYNAMIC_REGISTER_HTTP,
    GUIDER_DOMAIN_MAX
} domain_type_t;

int     iotx_guider_authenticate(iotx_conn_info_t *conn, void (*cb)(void *), void *client);
int     iotx_guider_set_custom_domain(int domain_type, const char *domain);
iotx_conn_info_pt iotx_conn_info_get(void);
int     iotx_facility_json_print(const char *str, int level, ...);

const char     *iotx_guider_get_domain(domain_type_t domain_type);

int iotx_device_info_get(iotx_device_info_t *device_info);

const char *iotx_ca_get(void);

iotx_conn_info_pt iotx_conn_info_get(void);
void iotx_conn_info_release(void);
iotx_conn_info_pt iotx_conn_info_reload(void (*cb)(void *), void* client);

void *iotx_event_callback(int evt);

#if defined(__cplusplus)
}
#endif
#endif
