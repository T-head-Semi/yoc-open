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
#include <stdint.h>
#include <unistd.h>
#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include "board.h"

#define K_API_PARENT_PRIO    32

static TaskHandle_t example_main_task;
extern void example_main(void);

int main(void)
{
    BaseType_t ret;

    board_init();
    printf("FreeRTOS version:%s\n", tskKERNEL_VERSION_NUMBER);
    ret = xTaskCreate((TaskFunction_t)example_main, "example_main", CONFIG_APP_TASK_STACK_SIZE, NULL, K_API_PARENT_PRIO, &example_main_task);
    if (ret != pdPASS) {
        printf("create example_main fail\n");
    }
    return 0;
}

