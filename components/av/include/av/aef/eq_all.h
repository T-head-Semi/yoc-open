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

#ifndef __EQ_ALL_H__
#define __EQ_ALL_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

#define REGISTER_EQXER(X, x)                                          \
    {                                                                 \
        extern int eqx_register_##x();                                \
        if (CONFIG_EQXER_##X)                                         \
            eqx_register_##x();                                       \
    }

/**
 * @brief  regist equalizer for silan
 * @return 0/-1
 */
int eqx_register_silan();

/**
 * @brief  regist equalizer for ipc
 * @return 0/-1
 */
int eqx_register_ipc();

/**
 * @brief  regist audio equalizer
 * @return 0/-1
 */
static inline int eqx_register()
{
#if defined(CONFIG_EQXER_SILAN)
    REGISTER_EQXER(SILAN, silan);
#endif
#if defined(CONFIG_EQXER_IPC)
    REGISTER_EQXER(IPC, ipc);
#endif
    return 0;
}

__END_DECLS__

#endif /* __EQ_ALL_H__ */

