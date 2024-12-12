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
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
static std::mutex mutex_;

extern "C" int run_case_lock_guard();
int run_case_lock_guard()
{
    printf("======cpp case start: %s\r\n", __FUNCTION__);
    auto func1 = [](int k) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (int i = 0; i < k; ++i) {
            cout << i << " ";
        }
        cout << endl;
    };
    std::thread threads[10];
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(func1, 100);
    }
    for (auto& th : threads) {
        th.join();
    }
    printf("======cpp case end : %s\r\n", __FUNCTION__);
    return 0;
}

