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

#include <aos/cli.h>

extern void hal_rtc_set_fel_flag();
static void efex_cmd(char *buf, int len, int argc, char **argv)
{
    hal_rtc_set_fel_flag();
}

static const struct cli_command cmd_xfex_specific = {
    /*cli self*/
    "xfex", "Enter xfex mode to burn image", efex_cmd
};

void cli_reg_cmd_board_specific(void)
{
    aos_cli_register_command(&cmd_xfex_specific);
}
