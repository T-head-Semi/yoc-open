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

#include <sys/time.h>
#include <time.h>

extern int clock_gettime(clockid_t clockid, struct timespec *tp);

/*
SVr4, 4.3BSD.  POSIX.1-2001 describes gettimeofday() but not
settimeofday().  POSIX.1-2008 marks gettimeofday() as obsolete,
recommending the use of clock_gettime(2) instead.
*/
int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    struct timespec ts;
    int             ret;

    if (!tv) {
        return -1;
    }

    ret = clock_gettime(CLOCK_REALTIME, &ts);

    if (ret == 0) {
        tv->tv_sec = ts.tv_sec;
        tv->tv_usec = ts.tv_nsec / NSEC_PER_USEC;
    }

    return ret;
}
