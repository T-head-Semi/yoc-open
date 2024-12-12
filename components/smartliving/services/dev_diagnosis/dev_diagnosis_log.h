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

#ifndef __DEV_DIAGNOSIS_LOG_H__
#define __DEV_DIAGNOSIS_LOG_H__

#include "iotx_log.h"

#define diagnosis_flow(...)      log_flow("diagnosis", __VA_ARGS__)
#define diagnosis_debug(...)     log_debug("diagnosis", __VA_ARGS__)
#define diagnosis_info(...)      log_info("diagnosis", __VA_ARGS__)
#define diagnosis_warn(...)      log_warning("diagnosis", __VA_ARGS__)
#define diagnosis_err(...)       log_err("diagnosis", __VA_ARGS__)
#define diagnosis_crit(...)      log_crit("diagnosis", __VA_ARGS__)
#define diagnosis_emerg(...)     log_emerg("diagnosis", __VA_ARGS__)
#define diagnosis_trace(...)     log_crit("diagnosis", __VA_ARGS__)

#endif