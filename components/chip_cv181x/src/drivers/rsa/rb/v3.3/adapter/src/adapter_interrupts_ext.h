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
/* adapter_interrupts_ext.h
 *
 * Host hardware specific extensions for the Adapter Interrupts interface
 */



#ifndef ADAPTER_INTERRUPTS_EXT_H_
#define ADAPTER_INTERRUPTS_EXT_H_
#include "cs_adapter.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

// Adapter logical EIP-28 PKA interrupts
enum
{
    IRQ_EIP28_READY = ADAPTER_EIP28_READY_IRQ,
    IRQ_LAST_LINE
};


#endif /* ADAPTER_INTERRUPTS_EXT_H_ */

/* end of file adapter_interrupts_ext.h */
