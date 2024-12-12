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

#ifndef __INCLUDE_SYS_TYPES_H
#define __INCLUDE_SYS_TYPES_H

#ifndef _SYS_CDEFS_H
#define _SYS_CDEFS_H    1
# include <features.h>
#endif   /* sys/cdefs.h */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _USECONDS_T_DECLARED
typedef	uint32_t	useconds_t;	/* microseconds (unsigned) */
#define	_USECONDS_T_DECLARED
#endif

#define OK              0
typedef int             pid_t;
typedef uint32_t        clock_t;
typedef long            ssize_t;
typedef uint32_t        mode_t;

#ifdef __cplusplus
}
#endif

#endif

