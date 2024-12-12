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

#include <stdarg.h>
#include <sys/prctl.h>
#include <aos/errno.h>
#include <pthread.h>

int prctl(int option, ...)
{
    va_list ap;
    unsigned long arg;

    if (option == PR_SET_NAME) {
        va_start(ap, option);
        arg = va_arg(ap, unsigned long);
        va_end(ap);

        if (arg == 0) {
            errno = EINVAL;
            return -1;
        }

        pthread_setname_np(pthread_self(), (char *)arg);
        return 0;
    } else {
        errno = ENOTSUP;
        return -1;
    }
}
