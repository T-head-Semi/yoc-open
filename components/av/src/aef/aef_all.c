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

#include "av/aef/aef.h"
#include "av/aef/aef_all.h"

/**
 * @brief  regist audio effecter for sona
 * @return 0/-1
 */
int aefx_register_sona()
{
    extern struct aefx_ops aefx_ops_sona;
    return aefx_ops_register(&aefx_ops_sona);
}

/**
 * @brief  regist audio effecter for ipc
 * @return 0/-1
 */
int aefx_register_ipc()
{
    extern struct aefx_ops aefx_ops_ipc;
    return aefx_ops_register(&aefx_ops_ipc);
}



