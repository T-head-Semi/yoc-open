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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static char g_strerr[16];
char *strerror(int errnum)
{
    if (errnum > ESTRPIPE || errnum < EPERM) {
        return NULL;
    }

    switch (errnum) {
        case EIO:
            return "EIO";
        case EINVAL:
            return "EINVAL";
        case ENOMEM:
            return "ENOMEM";
        case EBUSY:
            return "EBUSY";
        default:
            sprintf(g_strerr, "%d", errnum);
    }

    return g_strerr;
}
