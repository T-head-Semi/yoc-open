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

/* eip76_internal_pp.h
 *
 * EIP-76 Internal Post Processor Interface
 */

#ifndef EIP76_INTERNAL_PP_H_
#define EIP76_INTERNAL_PP_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Definitions API
#include "basic_defs.h"         // uint32_t

// Driver Framework Device API
#include "device_types.h"       // Device_Handle_t

// EIP-76 Driver Library Types API
#include "eip76_types.h"        // EIP76_* types


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define EIP76_MIN_PS_AI_WORD_COUNT  1
#define EIP76_MAX_PS_AI_WORD_COUNT  12


/*----------------------------------------------------------------------------
 * EIP76_Internal_PostProcessor_PS_AI_Write
 *
 */
void
EIP76_Internal_PostProcessor_PS_AI_Write(
        const Device_Handle_t Device,
        const uint32_t * PS_AI_Data_p,
        const unsigned int PS_AI_WordCount);


#endif /* EIP76_INTERNAL_PP_H_ */

/* end of file eip76_internal_pp.h */
