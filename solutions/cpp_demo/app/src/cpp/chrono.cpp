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
#include <chrono>

using namespace std;

static void foo()
{
    printf("===prepare sleep 2secs: %s\r\n", __FUNCTION__);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    printf("===finish sleep 2secs: %s\r\n", __FUNCTION__);
}

static void bar()
{
    printf("===prepare sleep 4secs: %s\r\n", __FUNCTION__);
    std::this_thread::sleep_for(std::chrono::seconds(4));
    printf("===finish sleep 4secs: %s\r\n", __FUNCTION__);
}

extern "C" int run_case_chrono();
int run_case_chrono()
{
    printf("======cpp case start: %s\r\n", __FUNCTION__);
    std::thread helper1(foo);

    std::thread helper2(bar);

    helper1.join();
    helper2.join();
    printf("======cpp case end : %s\r\n", __FUNCTION__);
    return 0;
}

