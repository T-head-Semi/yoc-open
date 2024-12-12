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

extern void cli_reg_cmd_kvtool(void);
extern void cli_reg_cmd_iperf(void);
extern void cli_reg_cmd_ping(void);
extern void cli_reg_cmd_ifconfig(void);

void board_cli_init()
{
    aos_cli_init();
    cli_reg_cmd_kvtool();
    cli_reg_cmd_ping();
    cli_reg_cmd_ifconfig();
    cli_reg_cmd_iperf();
}
