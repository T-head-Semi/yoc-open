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

#include <string.h>
#include <aos/cli.h>
#include <aos/kernel.h>
#include <aos/aos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELP_INFO "show tasks"

void cmd_ps_func(char *wbuf, int wbuf_len, int argc, char **argv)
{
    if (argc == 1) {
        aos_task_show_info();
#if defined(CONFIG_DEBUG) && defined(CONFIG_DEBUG_UTASK)
    } else if (argc == 2 && strcmp(argv[1], "utask") == 0) {
        tasks_debug();
#endif
    } else {
        printf("%s\r\n", HELP_INFO);
    }
}

void cli_reg_cmd_ps(void)
{
    static const struct cli_command cmd_info = {
        "ps",
        HELP_INFO,
        cmd_ps_func
    };

    aos_cli_register_command(&cmd_info);
}
