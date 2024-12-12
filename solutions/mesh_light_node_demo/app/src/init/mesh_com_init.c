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

#include "mesh_model/mesh_model.h"

#define NODE 1

static struct bt_mesh_model elem0_root_models[] = {
    MESH_MODEL_CFG_SRV_NULL(),
    MESH_MODEL_HEALTH_SRV_NULL(),
    MESH_MODEL_GEN_ONOFF_SRV_NULL(),
    MESH_MODEL_GEN_LEVEL_SRV_NULL(),
    MESH_MODEL_LIGHTNESS_SRV_NULL(),
    MESH_MODEL_CTL_SRV_NULL(),
    MESH_MODEL_CTL_SETUP_SRV_NULL(),
    MESH_MODEL_CTL_TEMP_SRV_NULL(),
};

static struct bt_mesh_model elem0_vnd_models[] = {
    MESH_MODEL_VENDOR_SRV_NULL(),
};

static struct bt_mesh_elem elements[] = {
    BT_MESH_ELEM(0, elem0_root_models, elem0_vnd_models, 0),
};

/*comp*/
static const struct bt_mesh_comp mesh_comp = {
    .cid = 0x01A8,
    .elem = elements,
    .elem_count = ARRAY_SIZE(elements),
};

int app_mesh_composition_init()
{
    int ret;
    ret = ble_mesh_model_init(&mesh_comp);
    return ret;
}

