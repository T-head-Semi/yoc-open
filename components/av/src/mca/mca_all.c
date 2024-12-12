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

#include "av/mca/mca.h"
#include "av/mca/mca_all.h"

/**
 * @brief  regist mca for local
 * @return 0/-1
 */
int mcax_register_local()
{
    extern struct mcax_ops mcax_ops_local;
    return mcax_ops_register(&mcax_ops_local);
}

/**
 * @brief  regist mca for ipc
 * @return 0/-1
 */
int mcax_register_ipc()
{
    extern struct mcax_ops mcax_ops_ipc;
    return mcax_ops_register(&mcax_ops_ipc);
}


