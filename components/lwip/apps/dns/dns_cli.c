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

static void dns_command(char *buffer, int32_t buf_len, int32_t argc, char **argv);

struct cli_command_st dns_cmd[] = {
    { "dns", "dns app", dns_command},
};

static void dns_help_command(void)
{
    LWIP_DEBUGF( DNSCLI_DEBUG, ("Usage: dns destination\n"));
    LWIP_DEBUGF( DNSCLI_DEBUG, ("Eample:\n"));
    LWIP_DEBUGF( DNSCLI_DEBUG, ("dns www.aliyun.com\n"));
}

static void dns_req_command(char *name)
{
    struct hostent *hostent;
    uint8_t index = 0;

    hostent = gethostbyname(name);

    if (hostent) {
        LWIP_DEBUGF( DNSCLI_DEBUG, ("hostent.h_name %s\n", hostent->h_name));
        if (hostent->h_addr_list != NULL) {
            for (index = 0; hostent->h_addr_list[index]; index++) {
                LWIP_DEBUGF( DNSCLI_DEBUG, ("hostent.h_addr_list[%i]->== %s\n",
                        index, ipaddr_ntoa((ip_addr_t *)hostent->h_addr_list[index])));
            }
        }
    } else {
        LWIP_DEBUGF( DNSCLI_DEBUG, ("gethostbyname failed, try again\n"));
    }
}

static void dns_command(char *buffer, int32_t buf_len, int32_t argc, char **argv)
{
    int32_t index = 0;

    if (argc < 2) {
        LWIP_DEBUGF( DNSCLI_DEBUG, ("%s, invalid command\n", __func__));
        dns_help_command();
        return;
    }

    if (strcmp(argv[1], "-h") == 0) {
        dns_help_command();
    } else {
        dns_req_command(argv[1]);
    }
}

int32_t dns_cli_register(void)
{
    if (cli_register_commands(dns_cmd, 1)) {
        return 0;
    }

    return -1;
}
