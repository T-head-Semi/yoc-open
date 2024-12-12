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

#if defined(CONFIG_SAL) || defined(CONFIG_TCPIP)
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#ifdef __linux__
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#else
#include <lwip/netdb.h>
#endif
#include <arpa/inet.h>

#include "av/avutil/socket_rw.h"

extern int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, struct timeval *timeout);
/**
 * @brief  read n bytes from a sockfd with timeout
 * @param  [in] fd
 * @param  [in] buf
 * @param  [in] count
 * @param  [in] timeout_ms
 * @return -1 on err
 */
int sock_readn(int fd, char *buf, size_t count, int timeout_ms)
{
    fd_set fds;
    int lfirst = 1;
    int rc, len = 0;
    struct timeval tv;
    unsigned long long delta;
    struct timeval t1 = {0}, t2 = {0};

    if (!((fd >= 0) && buf && count && (timeout_ms > 0))) {
        return -1;
    }

    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;

    gettimeofday(&t1, NULL);
    while (len < count) {
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        /* FIXME: patch for select. */
        if (lfirst) {
            lfirst = 0;
        } else {
            gettimeofday(&t2, NULL);
            delta = (t2.tv_sec  - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000;
            if (delta >= timeout_ms)
                break;
        }

        rc = select(fd + 1, &fds, NULL, NULL, &tv);
        if (rc < 0) {
            if ((errno == EINTR) || (errno == EAGAIN)) {
                aos_msleep(20);
                continue;
            }
            return -1;
        } else if (rc == 0) {
            /* time out */
            break;
        }

        if (!FD_ISSET(fd, &fds)) {
            aos_msleep(20);
            continue;
        }

        rc = recv(fd, buf + len, count - len, 0);
        if (rc < 0) {
            if ((errno == EINTR) || (errno == EAGAIN)) {
                aos_msleep(20);
                continue;
            }
            return -1;
        } else if (rc == 0) {
            /* the sockfd may be closed */
            break;
        }

        len += rc;
    }

    return len;
}


/**
 * @brief  write n bytes from a sockfd with timeout
 * @param  [in] fd
 * @param  [in] buf
 * @param  [in] count
 * @param  [in] timeout_ms
 * @return -1 on err
 */
int sock_writen(int fd, const char *buf, size_t count, int timeout_ms)
{
    fd_set fds;
    int lfirst = 1;
    int rc, len = 0;
    struct timeval tv;
    unsigned long long delta;
    struct timeval t1 = {0}, t2 = {0};

    if (!((fd >= 0) && buf && count && (timeout_ms > 0))) {
        return -1;
    }

    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;

    gettimeofday(&t1, NULL);
    while (len < count) {
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        /* FIXME: patch for select. */
        if (lfirst) {
            lfirst = 0;
        } else {
            gettimeofday(&t2, NULL);
            delta = (t2.tv_sec  - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000;
            if (delta >= timeout_ms)
                break;
        }

        rc = select(fd + 1, NULL, &fds, NULL, &tv);
        if (rc < 0) {
            if ((errno == EINTR) || (errno == EAGAIN)) {
                aos_msleep(20);
                continue;
            }
            return -1;
        } else if (rc == 0) {
            /* time out */
            break;
        }

        if (!FD_ISSET(fd, &fds)) {
            aos_msleep(20);
            continue;
        }

        rc = send(fd, buf + len, count - len, 0);
        if (rc < 0) {
            if ((errno == EINTR) || (errno == EAGAIN)) {
                aos_msleep(20);
                continue;
            }
            return -1;
        } else if (rc == 0) {
            /* the sockfd may be closed */
            break;
        }

        len += rc;
    }

    return len;
}
#endif


