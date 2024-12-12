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

#include "av/atempo/atempo.h"
#include "av/atempo/atempo_all.h"

/**
 * @brief  regist audio atempoer for sonic
 * @return 0/-1
 */
int atempo_register_sonic()
{
    extern struct atempo_ops atempo_ops_sonic;
    return atempo_ops_register(&atempo_ops_sonic);
}

/**
 * @brief  regist audio atempoer for ipc
 * @return 0/-1
 */
int atempo_register_ipc()
{
    extern struct atempo_ops atempo_ops_ipc;
    return atempo_ops_register(&atempo_ops_ipc);
}

/**
 * @brief  regist audio atempoer for dummy
 * @return 0/-1
 */
int atempo_register_dummy()
{
    extern struct atempo_ops atempo_ops_dummy;
    return atempo_ops_register(&atempo_ops_dummy);
}



