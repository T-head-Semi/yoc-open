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
#include <thread>
#include <mutex>

using namespace std;

static std::once_flag onceflag;

extern "C" int run_case_call_once();
void CallOnce()
{
    std::call_once(onceflag, []() {
        cout << "call once" << endl;
    });
}

int run_case_call_once()
{
    printf("======cpp case start: %s\r\n", __FUNCTION__);
    std::thread threads[5];
    for (int i = 0; i < 5; ++i) {
        threads[i] = std::thread(CallOnce);
    }
    for (auto& th : threads) {
        th.join();
    }
    printf("======cpp case end : %s\r\n", __FUNCTION__);
    return 0;
}
