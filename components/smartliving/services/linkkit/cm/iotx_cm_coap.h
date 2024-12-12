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


#ifndef _IOTX_CM_COAP_H_
#define _IOTX_CM_COAP_H_
#include "iotx_cm.h"
#include "iotx_cm_internal.h"
#include "iot_export_coap.h"
#include "lite-list.h"


typedef struct {
    uint32_t token_num;
    void * user_data;
    char * topic;
    iotx_cm_data_handle_cb responce_cb;
    void * context;
    dlist_t linked_list;
} coap_response_node_t;

iotx_cm_connection_t *iotx_cm_open_coap(iotx_cm_init_param_t *params);


#endif /* _LINKKIT_CM_H_ */
