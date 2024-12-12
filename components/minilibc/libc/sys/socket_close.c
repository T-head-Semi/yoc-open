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
#include <unistd.h>
#if defined(CONFIG_TCPIP) || defined(CONFIG_SAL)
#include "lwip/sys.h"
#include "lwip/sockets.h"
#else
#undef MEMP_NUM_NETCONN
#define MEMP_NUM_NETCONN 0
#endif

int close(int fd)
{
    int ret = 0;

#if MEMP_NUM_NETCONN

    if ((fd >= LWIP_SOCKET_OFFSET)
        && (fd < (LWIP_SOCKET_OFFSET + MEMP_NUM_NETCONN))) {
        return lwip_close(fd);
    }

#endif

    return ret;
}

#if 1
int open(const char *path, int oflags, ...)
{
    return 0;
}

ssize_t read(int fd, void *buf, int nbytes)
{
    ssize_t nread = 0;

#if MEMP_NUM_NETCONN

    if ((fd >= LWIP_SOCKET_OFFSET)
        && (fd < (LWIP_SOCKET_OFFSET + MEMP_NUM_NETCONN))) {
        return recv(fd, buf, nbytes, 0);
    }

#endif
    return nread;
}

ssize_t write(int fd, const void *buf, int nbytes)
{
    ssize_t nwrite = 0;

#if MEMP_NUM_NETCONN

    if ((fd >= LWIP_SOCKET_OFFSET)
        && (fd < (LWIP_SOCKET_OFFSET + MEMP_NUM_NETCONN))) {
        return send(fd, buf, nbytes, 0);
    }

#endif

    return nwrite;
}

int fcntl(int fd, int cmd, ...)
{
    int ret = 0;
    va_list ap;
    va_start(ap, cmd);

#if MEMP_NUM_NETCONN

    if ((fd >= LWIP_SOCKET_OFFSET)
        && (fd < (LWIP_SOCKET_OFFSET + MEMP_NUM_NETCONN))) {
        #if defined(CONFIG_SAL)
        extern int sal_fcntl(int s, int cmd, ...);
        ret = sal_fcntl(fd, cmd, va_arg(ap, int));
        #else
        ret = lwip_fcntl(fd, cmd, va_arg(ap, int));
        #endif
    }

#endif
    va_end(ap);

    return ret;
}
#endif
