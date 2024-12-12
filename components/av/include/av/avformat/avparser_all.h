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

#ifndef __AVPARSER_ALL_H__
#define __AVPARSER_ALL_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

#define REGISTER_AVPARSER(X, x)                                         \
    {                                                                   \
        extern int avparser_register_##x();                             \
        if (CONFIG_AVPARSER_##X)                                        \
            avparser_register_##x();                                    \
    }

/**
 * @brief  regist avparser for mp3
 * @return 0/-1
 */
int avparser_register_mp3();

/**
 * @brief  regist avparser for adts
 * @return 0/-1
 */
int avparser_register_adts();

/**
 * @brief  regist all avparser
 * @return 0/-1
 */
static inline int avparser_register_all()
{
#if defined(CONFIG_AVPARSER_MP3)
    REGISTER_AVPARSER(MP3, mp3);
#endif
#if defined(CONFIG_AVPARSER_ADTS)
    REGISTER_AVPARSER(ADTS, adts);
#endif

    return 0;
}

__END_DECLS__

#endif /* __AVPARSER_ALL_H__ */

