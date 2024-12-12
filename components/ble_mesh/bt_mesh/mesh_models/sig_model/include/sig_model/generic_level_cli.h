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

#ifndef _GENERIC_LEVEL_CLI_H_
#define _GENERIC_LEVEL_CLI_H_

#define GEN_LEVEL_CLI_OPC_NUM 2
#define MESH_MODEL_GEN_LEVEL_CLI(_user_data)                                                                           \
    BT_MESH_MODEL(BT_MESH_MODEL_ID_GEN_LEVEL_CLI, g_generic_level_cli_op, &g_generic_level_cli_pub, _user_data)

#define MESH_MODEL_GEN_LEVEL_CLI_NULL() MESH_MODEL_GEN_LEVEL_CLI(NULL)

typedef struct _set_level_arg {
    uint16_t level;
    uint16_t def;
    uint16_t move;
    uint8_t  tid;
    uint8_t  trans;
    uint8_t  delay;
    uint8_t  send_trans : 1;
    s32_t    delta;
} set_level_arg;

int ble_mesh_generic_level_get(uint16_t netkey_idx, uint16_t appkey_idx, uint16_t unicast_addr,
                               struct bt_mesh_model *model);

int ble_mesh_generic_level_set(uint16_t netkey_idx, uint16_t appkey_idx, uint16_t unicast_addr,
                               struct bt_mesh_model *model, set_level_arg *send_arg, bool ack);

int ble_mesh_generic_level_move_set(uint16_t netkey_idx, uint16_t appkey_idx, uint16_t unicast_addr,
                                    struct bt_mesh_model *model, set_level_arg *send_arg, bool ack);

int ble_mesh_generic_level_delta_set(uint16_t netkey_idx, uint16_t appkey_idx, uint16_t unicast_addr,
                                     struct bt_mesh_model *model, set_level_arg *send_arg, bool ack);

extern const struct bt_mesh_model_op g_generic_level_cli_op[GEN_LEVEL_CLI_OPC_NUM];
extern struct bt_mesh_model_pub      g_generic_level_cli_pub;

#endif
