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
/* cs_ringhelper.h
 *
 * Ring Helper Configuration File
 */



#ifndef INCLUDE_GUARD_CS_RINGHELPER_H
#define INCLUDE_GUARD_CS_RINGHELPER_H

#include "cs_driver.h"

// when enabled, all function call parameters are sanity-checked
// comment-out to disable this code
#ifndef DRIVER_PERFORMANCE
#define RINGHELPER_STRICT_ARGS
#endif

// the following switch removes support for the Status Callback Function
//#define RINGHELPER_REMOVE_STATUSFUNC

// the following switch removes support for separate rings
// use when only overlapping rings are used
//#define RINGHELPER_REMOVE_SEPARATE_RING_SUPPORT


#endif /* Include Guard */


/* end of file cs_ringhelper.h */
