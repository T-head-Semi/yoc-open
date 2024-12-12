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

#ifndef _MODEL_BOUND_OPERATION_H
#define _MODEL_BOUND_OPERATION_H

#include "mesh_model.h"

typedef enum _BIND_OPERATION_ID_
{
    /* !!!START!!! --- Don't add new ID before this ID */
    B_OPS_START_ID = -1,

    /* Generic OnOff */
    B_GEN_ONOFF_ID = 0,

    /* Generic Level */
    B_GEN_LEVEL_ID,
    B_GEN_DELTA_ID,
    B_GEN_MOVE_ID,

    /* Generic Default Transition Time */
    B_GEN_DFT_TRANS_TIME_ID,

    /* Generic Power OnOff */
    B_GEN_ON_PWR_UP_ID,

    /* Generic Power Level */
    B_GEN_PWR_ACTUAL_ID,
    B_GEN_PWR_LAST_ID,
    B_GEN_PWR_DFT_ID,
    B_GEN_PWR_RANGE_ID,

    /* Lightness sev model*/
    B_GEN_LIGHTNESS_LINEAR_ID,
    B_GEN_LIGHTNESS_ACTUAL_ID,

    /* !!!END!!! --- Don't add new ID after this ID */
    B_OPS_END_ID

} BIND_OPERATION_ID;

#endif //_MODEL_BOUND_OPERATION_H
