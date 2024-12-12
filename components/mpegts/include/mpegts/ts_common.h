/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __TS_COMMON_H__
#define __TS_COMMON_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/time.h>

#ifdef __linux__
#include <errno.h>
#include <pthread.h>
#else
#include <aos/types.h>
#include <aos/aos.h>
#include <aos/debug.h>
#include <aos/kernel.h>
#include <aos/list.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UNUSED
#define UNUSED(x)
#endif

#ifndef container_of
#define container_of(ptr, type, member) \
        ((type *)((char *)(ptr) - offsetof(type,member)))
#endif

#ifndef MIN
#define MIN(x,y)                ((x) < (y) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x,y)                ((x) > (y) ? (x) : (y))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)           (sizeof(x) / sizeof((x)[0]))
#endif

#ifdef __cplusplus
}
#endif

#endif /* __TS_COMMON_H__ */
