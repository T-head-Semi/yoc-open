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

#ifndef __PERF_IPC_H__
#define __PERF_IPC_H__

#include <perf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Thread API
 *
 */
typedef void (*perf_thread_func)(void *arg);
typedef void (*perf_task_switch_hook)(perf_thread_id thread);

perf_err_t perf_thread_yield(void);
void perf_task_switch_sethook(perf_task_switch_hook hook);

#ifdef __cplusplus
}
#endif

#endif  // __PERF_IPC_H__
