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
/******************************************************************************
 * @file     lib_string.h
 * @brief    CSI Source File for string
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#include <string.h>
#include <stdlib.h>

char *strtok_r(char *str, const char *delim, char **saveptr)
{
    if (!str && !(str = *saveptr))
        return NULL;

    str += strspn(str, delim);
    if (!*str)
        return *saveptr = 0;
    *saveptr = str + strcspn(str, delim);

    if (**saveptr)
        *(*saveptr)++ = 0;
    else
        *saveptr = 0;

    return str;
}