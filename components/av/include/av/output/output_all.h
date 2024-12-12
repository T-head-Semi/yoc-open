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

#ifndef __OUTPUT_ALL_H__
#define __OUTPUT_ALL_H__

#include "av/avutil/common.h"
#include "av/avutil/av_config.h"

__BEGIN_DECLS__

#define REGISTER_AV_AO(X, x)                                          \
    {                                                                    \
        extern int ao_register_##x();                                    \
        if (CONFIG_AV_AO_##X)                                         \
            ao_register_##x();                                           \
    }

/**
 * @brief  regist audio output for dummy
 * @return 0/-1
 */
int ao_register_dummy();

/**
 * @brief  regist audio output for alsa
 * @return 0/-1
 */
int ao_register_alsa();

/**
 * @brief  regist audio output for alsa_standard
 * @return 0/-1
 */
int ao_register_alsa_standard();

/**
 * @brief  regist all output
 * attention: can rewrite this function by caller
 * @return 0/-1
 */
int ao_register_all();

__END_DECLS__

#endif /* __OUTPUT_ALL_H__ */

