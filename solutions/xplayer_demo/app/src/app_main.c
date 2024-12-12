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
#include <aos/kernel.h>
#include <aos/yloop.h>
#include "app_main.h"

extern void cxx_system_init(void);
extern int cli_reg_cmd_xplayer(void);

int main(int argc, char *argv[])
{
    cxx_system_init();
    board_yoc_init();
    cli_reg_cmd_xplayer();
#ifdef CONFIG_WIFI_DRIVER_BL606P
    aos_loop_run();
#endif
    for (;;) {
        aos_msleep(2000);
    };
}

