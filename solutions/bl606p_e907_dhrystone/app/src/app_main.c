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
#include "app_config.h"
#include "app_main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <soc.h>
#include <drv/tick.h>

void pre_main(int argc, char *argv[0])
{
    board_yoc_init();
    printf("start dhrystone\r\n");
    benchmark_dhry_main();
}
