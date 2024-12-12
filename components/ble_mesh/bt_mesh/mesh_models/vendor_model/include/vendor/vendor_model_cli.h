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

#ifndef _VENDOR_MODEL_CLI_H_
#define _VENDOR_MODEL_CLI_H_

#include "vendor/vendor_model.h"

#define VENDOR_CLI_MODEL_OPC_NUM 8
#define MESH_MODEL_VENDOR_CLI(_user_data)                                                                              \
    BT_MESH_MODEL_VND(BT_MESH_MODEL_VND_COMPANY_ID, BT_MESH_MODEL_VND_MODEL_CLI, g_vendor_cli_model_alibaba_op,        \
                      &g_vendor_cli_model_alibaba_pub, _user_data)

#define MESH_MODEL_VENDOR_CLI_NULL() MESH_MODEL_VENDOR_CLI(NULL)

extern struct bt_mesh_model_pub      g_vendor_cli_model_alibaba_pub;
extern const struct bt_mesh_model_op g_vendor_cli_model_alibaba_op[VENDOR_CLI_MODEL_OPC_NUM];

int ble_mesh_vendor_cli_model_msg_send(vnd_model_msg *model_msg);
int ble_mesh_vendor_cli_model_msg_send_with_ttl(vnd_model_msg *model_msg, uint8_t ttl);

#endif //_VENDOR_MODEL_SRV_H
