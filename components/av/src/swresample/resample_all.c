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

#include "av/swresample/resample.h"
#include "av/swresample/resample_all.h"

/**
 * @brief  regist swresample for ipc
 * @return 0/-1
 */
int resample_register_ipc()
{
    extern struct resx_ops resx_ops_ipc;
    return resx_ops_register(&resx_ops_ipc);
}

/**
 * @brief  regist swresample for speex
 * @return 0/-1
 */
int resample_register_speex()
{
    extern struct resx_ops resx_ops_speex;
    return resx_ops_register(&resx_ops_speex);
}

/**
 * @brief  regist swresample for dummy
 * @return 0/-1
 */
int resample_register_dummy()
{
    extern struct resx_ops resx_ops_dummy;
    return resx_ops_register(&resx_ops_dummy);
}
