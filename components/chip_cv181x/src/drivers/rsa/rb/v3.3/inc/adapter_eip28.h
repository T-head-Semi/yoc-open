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
/* adapter_internal.h
 *
 * Data types and Interfaces
 *
 * Extensions for the Security-IP-28 hardware.
 * This file is included from adapter_internal.h
 */



// ensure inclusion from adapter_internal.h
#ifndef INCLUDE_GUARD_ADAPTER_EIP28_H
#define INCLUDE_GUARD_ADAPTER_EIP28_H 1

/*----------------------------------------------------------------------------
 *                           Adapter_EIP28
 *----------------------------------------------------------------------------
 */

#include "eip28.h"
#include "stdbool.h"

extern EIP28_IOArea_t Adapter_EIP28_IOArea;

extern bool Adapter_EIP28_IsUsable;

bool Adapter_EIP28_Init(void);

void
Adapter_EIP28_UnInit(void);

#endif /* Include Guard */

/* end of file adapter_internal_ext.h */
