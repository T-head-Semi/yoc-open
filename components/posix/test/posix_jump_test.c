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
#include <setjmp.h>

#include "ulog/ulog.h"

#define TAG "jump_test"

jmp_buf buf_jump_test;

void banana(void)
{
    LOGI(TAG, "running banana()");

    /* jump and set value 1 as the return value of setjmp */
    longjmp(buf_jump_test, 1);

    LOGI(TAG, "you will never see this, because i will longjmp !");
}

void posix_jump_test_case(void)
{
    int ret = -1;

    /* set jump point */
    ret = setjmp(buf_jump_test);

    /* setjmp will return 0 at the first time, when jump back the
       return value will be decided by para of longjmp */
    if (ret == 0) {
        LOGI(TAG, "first time through");
        banana();
    } else {
        /* the second para of longjmp is 1, so ret = 1, and this branch will run */
        LOGI(TAG, "jump back");
        LOGI(TAG, "posix jump test OK !");
    }
}
