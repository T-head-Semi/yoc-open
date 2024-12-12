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

#ifndef __ATEMPO_ALL_H__
#define __ATEMPO_ALL_H__

#include "av/avutil/common.h"
#include "av/avutil/av_config.h"

__BEGIN_DECLS__

#define REGISTER_ATEMPOER(X, x)                                          \
    {                                                                     \
        extern int atempo_register_##x();                                 \
        if (CONFIG_ATEMPOER_##X)                                         \
            atempo_register_##x();                                        \
    }

/**
 * @brief  regist audio atempoer for sonic
 * @return 0/-1
 */
int atempo_register_sonic();

/**
 * @brief  regist audio atempoer for ipc
 * @return 0/-1
 */
int atempo_register_ipc();

/**
 * @brief  regist audio atempoer for dummy
 * @return 0/-1
 */
int atempo_register_dummy();

/**
 * @brief  regist audio atempoer
 * @return 0/-1
 */
static inline int atempo_register()
{
#if defined(CONFIG_ATEMPOER_SONIC)
    REGISTER_ATEMPOER(SONIC, sonic);
#endif
#if defined(CONFIG_ATEMPOER_IPC)
    REGISTER_ATEMPOER(IPC, ipc);
#endif
#if defined(CONFIG_ATEMPOER_DUMMY)
    REGISTER_ATEMPOER(DUMMY, dummy);
#endif
    return 0;
}

__END_DECLS__

#endif /* __ATEMPO_ALL_H__ */

