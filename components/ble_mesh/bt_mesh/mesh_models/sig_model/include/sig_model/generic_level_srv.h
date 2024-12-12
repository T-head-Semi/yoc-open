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

#ifndef _GENERIC_LEVEL_SRV_H_
#define _GENERIC_LEVEL_SRV_H_

#define GEN_LV_OPC_NUM 8

#define MESH_MODEL_GEN_LEVEL_SRV(_user_data)                                                                           \
    BT_MESH_MODEL(BT_MESH_MODEL_ID_GEN_LEVEL_SRV, g_generic_level_op, &g_generic_level_pub, _user_data)

#define MESH_MODEL_GEN_LEVEL_SRV_NULL() MESH_MODEL_GEN_LEVEL_SRV(NULL)

extern struct bt_mesh_model_pub      g_generic_level_pub;
extern const struct bt_mesh_model_op g_generic_level_op[GEN_LV_OPC_NUM];

int ble_mesh_generic_level_publication(struct bt_mesh_model *model, int16_t level);

#endif //
