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
#include <cli/cli_api.h>
#include <lwip/netdb.h>

static void lsfd_command(char *buffer, int32_t buf_len, int32_t argc, char **argv);

struct cli_command_st lsfd_cmd[] = {
    { "lsfd", "lsfd app",  lsfd_command},
};
static void lsfd_help_command(void)
{
    LWIP_DEBUGF( SOCKET_ALLOC_DEBUG, ("Usage: lsfd\n"));
    LWIP_DEBUGF( SOCKET_ALLOC_DEBUG, ("Eample:\n"));
    LWIP_DEBUGF( SOCKET_ALLOC_DEBUG, ("lsfd\n"));
}

static void lsfd_exec_command(void)
{
#ifdef CONFIG_GENIE_DEBUG
    extern void print_sock_alloc_info(void);
    print_sock_alloc_info();
#else
    LWIP_DEBUGF( SOCKET_ALLOC_DEBUG, ("Not available!\n"));
#endif
}

static void lsfd_command(char *buffer, int32_t buf_len, int32_t argc, char **argv)
{
    if (argc == 1) {
        lsfd_exec_command();
        return;
    } 
    
    lsfd_help_command(); 
}

int32_t lsfd_cli_register(void)
{
    if (cli_register_commands(lsfd_cmd, 1)) {
        return 0;
    }

    return -1;
}
