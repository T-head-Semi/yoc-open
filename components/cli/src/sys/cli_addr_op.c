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
#if defined (CONFIG_CLI) && defined (CONFIG_CLI_ADDR_OP)
#include <string.h>
#include <stdlib.h>
#include <aos/cli.h>

static void cmd_addr_func(char *wbuf, int wbuf_len, int argc, char **argv)
{
    char     *addr_s;
    int      addr_n;
    char     *str;
    uint32_t tmp = 0;
    int      write_number = 0;

    if (argc == 1) {
        printf("addr *addr -w 0xa0\r\n");
        return;
    }

    addr_s = (char *)argv[1];
    addr_n = (int)strtol(&addr_s[1], &str, 16);


    if (0 == strcmp(argv[2], "-r")) {
        tmp = *((volatile unsigned int *) addr_n);
        printf("%s addr 0x%08x = 0x%08x\n", "get", addr_n, tmp);
    }

    if (0 == strcmp(argv[2], "-w")) {
        write_number = (int)strtol(argv[3], &str, 16);
        tmp = *((volatile unsigned int *) addr_n);

        printf("%s addr 0x%08x = 0x%08x\n", "get", addr_n, tmp);
        *((volatile unsigned int *) addr_n) = write_number;
        printf("%s addr 0x%08x = 0x%08x\n", "set", addr_n, write_number);
        tmp = *((volatile unsigned int *) addr_n);
        printf("%s addr 0x%08x = 0x%08x\n", "get", addr_n, tmp);
    }
}

void cli_reg_cmd_addr(void)
{
    static const struct cli_command cmd_info = {
        "addr",
        "mem adress read write",
        cmd_addr_func
    };

    aos_cli_register_command(&cmd_info);
}
#endif /* CONIFG_CLI && CONFIG_CLI_ADDR_OP */
