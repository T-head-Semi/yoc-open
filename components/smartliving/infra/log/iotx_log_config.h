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

#ifndef __LITE_LOG_CONFIG_H__
#define __LITE_LOG_CONFIG_H__

#include "iot_import.h"

#define LITE_printf                     HAL_Printf
#define LITE_snprintf                   HAL_Snprintf
#define LITE_vsnprintf                  HAL_Vsnprintf
#define LITE_LOG_ENABLED

#define LOG_MSG_MAXLEN                  (255)
#define LOG_MOD_NAME_LEN                (7)
#define LOG_PREFIX_FMT                  "[%s](%u) %s(%d): "
#define LOG_PREFIX_FMT_ONLINE           "%ld %s %s "

#define HEXDUMP_SEP_LINE                "+" \
    "-----------------------" \
    "-----------------------" \
    "-----------------------"

#if defined(_PLATFORM_IS_LINUX_)
    #undef  LOG_MSG_MAXLEN
    #define LOG_MSG_MAXLEN              (512)
#endif

#endif  /* __LITE_LOG_CONFIG_H__ */
