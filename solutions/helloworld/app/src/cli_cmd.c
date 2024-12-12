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
#include <aos/kernel.h>
#include <aos/cli.h>
#include "app_main.h"

static void version_cmd(char *buf, int32_t len, int32_t argc, char **argv)
{
    aos_cli_printf("kernel version : %s\r\n", aos_kernel_version_get());
}

static int cli_reg_cmd_kernel(void)
{
	static const struct cli_command cmd_info = {
        "sysver",
        "sysver",
        version_cmd,
	};
	aos_cli_register_command(&cmd_info);
	return 0;
}

void board_cli_init(void)
{
    aos_cli_init();
    cli_reg_cmd_kernel();
}
