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

#ifndef CLI_UAGENT_H
#define CLI_UAGENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "uagent.h"

#define MOD_VER "1.0.0"
#define CLI_RESPONE   (UAGENT_FUNC_USER_BASE)
#define CLI_CMD_INPUT (UAGENT_FUNC_USER_BASE + 1)

extern unsigned char g_cmd_from_cloud;

void cli_uagent_init(void);

#ifdef __cplusplus
}
#endif

#endif /* CLI_UAGENT_H */

