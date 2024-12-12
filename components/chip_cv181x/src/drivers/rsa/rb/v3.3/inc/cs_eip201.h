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
/* cs_eip201.h
 *
 * Configuration options for the EIP201 Driver Library module.
 */



#ifndef INCLUDE_GUARD_CS_EIP201_H
#define INCLUDE_GUARD_CS_EIP201_H

// we accept a few settings from the top-level configuration file
#include "cs_driver.h"

/* EIP201_STRICT_ARGS
 *
 * Set this option to enable checking of all arguments to all EIP201 DL
 * functions. Disable it to reduce code size and reduce overhead.
 */
#ifndef DRIVER_PERFORMANCE
#define EIP201_STRICT_ARGS
#endif

/* EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS <NOI>
 *
 * This configures the maximum Number Of Interrupt (NOI) sources
 * actually available in the EIP201 AIC.
 * This can be used for strict argument checking.
 */
#define EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS    30


#endif /* Include Guard */


/* end of file cs_eip201.h */
