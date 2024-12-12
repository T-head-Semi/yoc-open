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
#include <stdint.h>
#include <aos/kernel.h>
#include <errno.h>

/*
4.3BSD, POSIX.1-2001.  POSIX.1-2001 declares this function
obsolete; use nanosleep(2) instead.  POSIX.1-2008 removes the
specification of usleep().

On the original BSD implementation, and in glibc before version
2.2.2, the return type of this function is void.  The POSIX
version returns int, and this is also the prototype used since
glibc 2.2.2.

Only the EINVAL error return is documented by SUSv2 and
POSIX.1-2001.
*/
__attribute__((weak)) int usleep(useconds_t usec)
{
    if (usec && (usec <= 1000000)) {
        if (usec < 1000) {
            usec = 1000;
        }

        aos_msleep(usec / 1000);
        return 0;
    }

    return -EINVAL;
}

