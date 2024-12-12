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
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


#include <lwip/sockets.h>
#include <lwip/netdb.h>

extern uint32_t cmd_ping4_func(ip_addr_t *ping_target);
extern uint32_t cmd_ping6_func(ip_addr_t *ping_target);

int ping(int type, char *remote_ip)
{
    ip_addr_t target;
    struct hostent *host;

    if (remote_ip == NULL) {
        printf("Usage: ping dest or ping -6 dest\n");
        return -1;
    }

    host = gethostbyname(remote_ip);

    if (host) {
        if(host->h_addrtype == AF_INET) {
            ip_addr_copy(target, *(ip_addr_t *)host->h_addr);
            printf("\tping %s(%s)\n", remote_ip, ipaddr_ntoa(&target));
#if LWIP_IPV4
            // can be implemented together with ipv6, refer to lwip/apps/ping
            cmd_ping4_func(&target);
#endif
        }else if (host->h_addrtype == AF_INET6) {
#if LWIP_IPV6
            cmd_ping6_func(&target);
#endif
        }
    }else{
        return -1;
    }

    return 0;
}

