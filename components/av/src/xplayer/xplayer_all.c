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

#include "av/xplayer/xplayer_cls.h"
#include "av/xplayer/xplayer.h"
#include "av/xplayer/xplayer_all.h"

/**
 * @brief  regist xplayer for yoc
 * @return 0/-1
 */
int xplayer_register_yoc()
{
    extern const struct xplayer_cls xplayer_cls_yoc;
    return xplayer_cls_register(&xplayer_cls_yoc);
}

/**
 * @brief  regist xplayer for tplayer
 * @return 0/-1
 */
int xplayer_register_tplayer()
{
    extern const struct xplayer_cls xplayer_cls_tplayer;
    return xplayer_cls_register(&xplayer_cls_tplayer);
}


