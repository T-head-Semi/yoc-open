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

#ifndef __COMMON_H__
#define __COMMON_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//#include <stdarg.h>
//#include <stddef.h>
//#include <math.h>
#include <sys/time.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <sys/socket.h>
//#include <fcntl.h>

#ifdef __linux__
#include <errno.h>
#include <pthread.h>
#include "ulog/ulog.h"
#else
#include <aos/types.h>
#include <aos/aos.h>
#include <aos/debug.h>
#include <aos/kernel.h>
#include <aos/list.h>
#endif

#include "av/avutil/av_errno.h"
#include "av/avutil/av_port.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int handle_t;

#ifndef INT_MAX
#define INT_MAX     (2147483647)
#endif

#ifndef UNUSED
//#define UNUSED __attribute__((unused))
#define UNUSED(x)
#endif

#ifndef container_of
#define container_of(ptr, type, member) \
        ((type *)((char *)(ptr) - offsetof(type,member)))
#endif /* container_of */

#ifndef MIN
#define MIN(x,y)                ((x) < (y) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x,y)                ((x) > (y) ? (x) : (y))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)           (sizeof(x) / sizeof((x)[0]))
#endif

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif

#ifndef SEEK_END
#define SEEK_END 2
#endif

#ifndef AV_EPSINON
#define AV_EPSINON  (0.000001)
#endif

#ifndef AV_ALIGN_SIZE
#define AV_ALIGN_SIZE(size, align) (((size) + align - 1U) & (~(align - 1U)))
#endif

#ifndef AV_ALIGN_BUFZ
#define AV_ALIGN_BUFZ(size, align) (((size) + align - 1U))
#endif

#ifndef AV_ALIGN
#define AV_ALIGN(addr, align) ((void *)(((unsigned long)(addr) + align - 1U) & (~(unsigned long)(align - 1U))))
#endif

#ifdef __linux__
#define av_malloc          malloc
#define av_realloc         realloc
#define av_calloc          calloc
#define av_zalloc(size)    calloc(1, size)
#define av_free            free
#define av_freep           freep
#else
#define av_malloc      aos_malloc
#define av_realloc     aos_realloc
#define av_calloc      aos_calloc
#define av_zalloc      aos_zalloc
#define av_free        aos_free
#define av_freep       aos_freep
#endif

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_H__ */

