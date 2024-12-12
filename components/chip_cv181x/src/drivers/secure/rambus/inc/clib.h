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

/* clib.h
 *
 * Driver Framework v4, C Library Abstraction
 *
 * This header function guarantees the availability of a select list of
 * Standard C APIs. This makes the user of this API compiler independent.
 * It also gives a single customization point for these functions.
 */



#ifndef INCLUDE_GUARD_CLIB_H
#define INCLUDE_GUARD_CLIB_H

/* guaranteed APIs:

    memcpy
    memmove
    memset
    memcmp
    offsetof
    strcmp

*/

/* Note: This is a template. Copy and customize according to your needs! */

#if defined(linux) && defined(MODULE)

#include <linux/string.h>     // memmove, memcpy, memset, strcmp
#include <linux/stddef.h>     // offsetof

#else

#include <string.h>           // memmove, memset, strcmp
#include <memory.h>           // memcpy, etc.
#include <stddef.h>           // offsetof

#endif


/* Zero-init macro
 *
 *   _x (input)
 *              Name of the variable that must be zeroed
 *
 */
#define ZEROINIT(_x)  memset(&_x, 0, sizeof(_x))


#endif /* Inclusion Guard */


/* end of file clib.h */
