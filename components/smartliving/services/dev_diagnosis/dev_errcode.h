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

#ifndef __DEV_ERRCODE_H__
#define __DEV_ERRCODE_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "iot_export.h"

#ifdef DEV_ERRCODE_ENABLE
extern void dev_errcode_module_init(void);
extern int dev_errcode_handle(const int state_code, const char *state_message);
extern uint16_t dev_errcode_sdk_filter(const int state_code);
#endif

#if defined(__cplusplus)
}       /* extern "C" */
#endif
#endif  /* __DEV_ERRCODE_H__ */