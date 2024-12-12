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

#ifndef __XPLAYER_ALL_H__
#define __XPLAYER_ALL_H__

#include "av/avutil/common.h"
#include "av/avutil/av_config.h"

__BEGIN_DECLS__

#define REGISTER_PLAYER(X, x)                                          \
    {                                                                    \
        extern int xplayer_register_##x();                                \
        if (CONFIG_PLAYER_##X)                                         \
            xplayer_register_##x();                                       \
    }

/**
 * @brief  regist xplayer for yoc
 * @return 0/-1
 */
int xplayer_register_yoc();

/**
 * @brief  regist xplayer for allwinner
 * @return 0/-1
 */
int xplayer_register_tplayer();

/**
 * @brief  regist xplayer
 * @return 0/-1
 */
static inline int xplayer_register()
{
#if defined(CONFIG_PLAYER_YOC)
    REGISTER_PLAYER(YOC, yoc);
#endif
#if defined(CONFIG_PLAYER_TPLAYER)
    REGISTER_PLAYER(TPLAYER, tplayer);
#endif

    return 0;
}

__END_DECLS__

#endif /* __XPLAYER_ALL_H__ */

