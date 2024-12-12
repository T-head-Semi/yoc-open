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
#include <stdlib.h>
#include <string.h>
#include <aos/cli.h>

extern void cmd_micgain(char *wbuf, int wbuf_len, int argc, char **argv);

void cli_reg_cmd_codec(void)
{
    static const struct cli_command cmd_list[] = {
        {"micgain", "show mic config", cmd_micgain},
    };

    aos_cli_register_commands(cmd_list, sizeof(cmd_list)/sizeof(struct cli_command));
}

