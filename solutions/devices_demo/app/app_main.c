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

#include <aos/aos.h>
#include <stdio.h>
#include <sys_clk.h>

#include "app_main.h"
extern void app_init(void);
int main(int argc, char *argv[])
{
    board_yoc_init();
    
    printf("\r\napp start core clock %d........\r\n", soc_get_cur_cpu_freq());

    app_init();

    return 0;
}
