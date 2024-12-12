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

#ifndef __K_COMMON_H__
#define __K_COMMON_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "excore/k_mk_config.h"

#ifndef printk
extern int32_t aos_debug_printf(const char *fmt, ...);
#define printk aos_debug_printf
#endif

#ifndef OS_ALIGN_UP
#define OS_ALIGN_UP(x, align)       (((x) + (align) - 1) & ~((align) - 1))
#endif

#ifndef OS_ALIGN_DOWN
#define OS_ALIGN_DOWN(x, align)     ((x) & ~((align) - 1))
#endif

#ifndef min
#define min(a, b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b)  (((a) > (b)) ? (a) : (b))
#endif

#define K_ARCH_INVALID_ADDR     (unsigned long)(-1)

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))
#endif

#ifndef barrier
#define barrier() asm volatile("" ::: "memory")
#endif

#ifndef CHECK_PARAM
#define CHECK_PARAM(x, ret) \
	do { \
		if (!(x)) { \
			return ret; \
		}\
	} while (0)
#endif

#endif /* __K_COMMON_H__ */

