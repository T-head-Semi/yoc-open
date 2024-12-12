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
/* cs_hwpal_umdevxs.h
 *
 * Configuration for Driver Framework Device API implementation for
 * Linux user-space.
 */



#ifndef INCLUDE_GUARD_CS_HWPAL_UMDEVXS_H
#define INCLUDE_GUARD_CS_HWPAL_UMDEVXS_H

// we accept a few settings from the top-level configuration file
#include "cs_hwpal.h"

#define HWPAL_DEVICE0_UMDEVXS  HWPAL_DEVICE_TO_FIND

// Check if an endian conversion must be performed
#ifdef DRIVER_SWAPENDIAN
#define HWPAL_DEVICE_ENABLE_SWAP
#endif // DRIVER_SWAPENDIAN

#define HWPAL_DMARESOURCE_UMDEVXS_DCACHE_CTRL

#endif // INCLUDE_GUARD_CS_HWPAL_UMDEVXS_H


/* end of file cs_hwpal_umdevxs.h */
