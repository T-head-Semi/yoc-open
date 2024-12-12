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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

extern int run_case_thread();
extern int run_case_mutex();
extern int run_case_atomic();
extern int run_case_condition();
extern int run_case_lock_guard();
extern int run_case_unique_lock();
extern int run_case_call_once();
extern int run_case_async();
extern int run_case_packaged_task_future();
extern int run_case_promise_future();
extern int run_case_chrono();
int run_cpp_case()
{
    printf("======cpp case start: %s\r\n", __FUNCTION__);
    run_case_thread();
    run_case_mutex();
    run_case_atomic();
    run_case_condition();
    run_case_lock_guard();
    run_case_unique_lock();
    run_case_call_once();
    run_case_async();
    run_case_packaged_task_future();
    run_case_promise_future();
    run_case_chrono();
    printf("======cpp case end : %s\r\n", __FUNCTION__);
    return 0;
}

