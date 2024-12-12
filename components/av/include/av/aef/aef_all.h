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

#ifndef __AEF_ALL_H__
#define __AEF_ALL_H__

#include "av/avutil/common.h"
#include "av/avutil/av_config.h"

__BEGIN_DECLS__

#define REGISTER_AEFXER(X, x)                                          \
    {                                                                  \
        extern int aefx_register_##x();                                \
        if (CONFIG_AEFXER_##X)                                         \
            aefx_register_##x();                                       \
    }

/**
 * @brief  regist audio effecter for sona
 * @return 0/-1
 */
int aefx_register_sona();

/**
 * @brief  regist audio effecter for ipc
 * @return 0/-1
 */
int aefx_register_ipc();

/**
 * @brief  regist audio effecter
 * @return 0/-1
 */
static inline int aefx_register()
{
#if defined(CONFIG_AEFXER_SONA)
    REGISTER_AEFXER(SONA, sona);
#endif
#if defined(CONFIG_AEFXER_IPC)
    REGISTER_AEFXER(IPC, ipc);
#endif
    return 0;
}

__END_DECLS__

#endif /* __AEF_ALL_H__ */

