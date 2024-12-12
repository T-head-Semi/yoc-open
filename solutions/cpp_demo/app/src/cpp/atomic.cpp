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
#include <vector>
#include <thread>
#include <atomic>
using namespace std;

static int cnt;
static std::atomic<int> acnt = {0};

static void f()
{
    for (int n = 0; n < 1000; ++n) {
        acnt.fetch_add(1, std::memory_order_relaxed);
        ++cnt; // 未定义行为，实际上会失去一些更新
    }
}

extern "C" int run_case_atomic();
int run_case_atomic()
{
    printf("======cpp case start: %s\r\n", __FUNCTION__);
    for (int i = 0; i < 20; i++) {
        acnt = 0;
        cnt  = 0;
        std::vector<std::thread> v;
        for (int n = 0; n < 10; ++n) {
            v.emplace_back(f);
        }
        for (auto& t : v) {
            t.join();
        }
        //printf("The atomic counter is %d\n", acnt);
        std::cout << "Final counter value is " << acnt << '\n';
        printf("The non-atomic counter is %u\n", cnt);
    }
    printf("======cpp case end : %s\r\n", __FUNCTION__);
    return 0;
}

