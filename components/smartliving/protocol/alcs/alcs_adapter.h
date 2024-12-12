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



#ifndef __ALCS_ADAPTER_H__
#define __ALCS_ADAPTER_H__
#if defined(__cplusplus)
extern "C" {
#endif

#include "iotx_utils.h"
#include "iot_export_mqtt.h"
#include "CoAPExport.h"
#include "alcs_mqtt.h"
#include "iotx_alcs.h"

typedef struct iotx_alcs_send_msg_st {
    uint8_t token_len;
    uint8_t *token;
    char *uri;
    struct list_head linked_list;
} iotx_alcs_send_msg_t, *iotx_alcs_send_msg_pt;

typedef enum {
    IOTX_ALCS_SUBDEV_DISCONNCET_CLOUD,
    IOTX_ALCS_SUBDEV_CONNECT_CLOUD
} iotx_alcs_subdev_stage_t;

#define IOTX_ALCS_SUBDEV_RETRY_INTERVAL_MS (10000)

typedef struct iotx_alcs_subdev_item_st {
    char product_key[PRODUCT_KEY_MAXLEN];
    char device_name[DEVICE_NAME_MAXLEN];
    char prefix[ALCS_MQTT_PREFIX_MAX_LEN];
    char secret[ALCS_MQTT_SECRET_MAX_LEN];
    uint8_t stage;
    uint64_t retry_ms;
    struct list_head linked_list;
} iotx_alcs_subdev_item_t, *iotx_alcs_subdev_item_pt;

typedef void (*iotx_alcs_auth_timer_fnuc_t)(CoAPContext *);

typedef struct iotx_alcs_adapter_st {
    void *mutex;
    int local_cloud_inited;
    CoAPContext *coap_ctx;
    uint8_t role;
    iotx_alcs_auth_timer_fnuc_t alcs_client_auth_timer_func;
    iotx_alcs_auth_timer_fnuc_t alcs_server_auth_timer_func;
    iotx_alcs_event_handle_t *alcs_event_handle;
    struct list_head alcs_send_list;
    struct list_head alcs_subdev_list;
    char local_ip[NETWORK_ADDR_LEN];
    uint16_t local_port;
} iotx_alcs_adapter_t, *iotx_alcs_adapter_pt;

iotx_alcs_adapter_t *iotx_alcs_get_ctx(void);
int iotx_alcs_subdev_insert(iotx_alcs_subdev_item_t *item);
int iotx_alcs_subdev_remove(const char *pk, const char *dn);
int iotx_alcs_subdev_search(const char *pk, const char *dn, iotx_alcs_subdev_item_t **item);
int iotx_alcs_subdev_update_stage(iotx_alcs_subdev_item_t *item);
void iotx_alcs_send_list_handle(void *list_node, va_list *params);
int iotx_alcs_adapter_list_init(iotx_alcs_adapter_t *adapter);

#if defined(__cplusplus)
}
#endif
#endif
