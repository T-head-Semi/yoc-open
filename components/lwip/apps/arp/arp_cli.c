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
#include <lwip/etharp.h>

static void arp_command(char *buffer, int32_t buf_len, int32_t argc, char **argv);

struct cli_command_st arp_cmd[] = {
    { "arp", "arp app", arp_command},
};

static void arp_help_command(void)
{
    LWIP_DEBUGF( ARP_DEBUG, ("Usage: arp -a\n"));
    LWIP_DEBUGF( ARP_DEBUG, ("Eample:\n"));
    LWIP_DEBUGF( ARP_DEBUG, ("arp -a\n"));
}
 
static void arp_query_command(void)
{
    if (etharp_info_print() < 0) {
        LWIP_DEBUGF( ARP_DEBUG, ("arp list empty!\n"));
    }
}

static void arp_command(char *buffer, int32_t buf_len, int32_t argc, char **argv)
{
    int32_t index = 0;

    if (argc < 2) {
        LWIP_DEBUGF( ARP_DEBUG, ("%s, invalid command\n", __func__));
        arp_help_command();
        return;
    }

    if (strcmp(argv[1], "-a") == 0) {
        arp_query_command();
    } else {
        arp_help_command();
    }
}

int32_t arp_cli_register(void)
{
    if (cli_register_commands(arp_cmd, 1)) {
        return 0;
    }

    return -1;
}
