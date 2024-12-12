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
/* adapter_interrupts.h
 *
 * Adapter Interrupts interface
 */



#ifndef INCLUDE_GUARD_ADAPTER_INTERRUPTS_H
#define INCLUDE_GUARD_ADAPTER_INTERRUPTS_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Driver Framework Basic Defs API
#include "basic_defs.h"     // bool


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

typedef void (* Adapter_InterruptHandler_t)(const int nIRQ);


/*----------------------------------------------------------------------------
 *                           Adapter_Interrupts
 *----------------------------------------------------------------------------
 */

bool
Adapter_Interrupts_Init(
        const int nIRQ);

void
Adapter_Interrupts_UnInit(
        const int nIRQ);

void
Adapter_Interrupt_SetHandler(
        const int nIRQ,
        Adapter_InterruptHandler_t HandlerFunction);

void
Adapter_Interrupt_Enable(
        const int nIRQ,
        const unsigned int Flags);

/*
 * This function enables execution context (allows it to run) that services
 * the nIRQ interrupt.
 *
 * Note: this function is different from the Adapter_Interrupt_Enable()
 *       function which only enables the nIRQ interrupt event at an interrupt
 *       controller. The interrupt can be dispatched to some execution context
 *       (for example, a thread) that can be also enabled or disabled.
 */
void
Adapter_Interrupt_Context_Enable(
        const int nIRQ,
        const unsigned int Flags);

void
Adapter_Interrupt_Clear(
        const int nIRQ,
        const unsigned int Flags);

void
Adapter_Interrupt_ClearAndEnable(
        const int nIRQ,
        const unsigned int Flags);

void
Adapter_Interrupt_Disable(
        const int nIRQ,
        const unsigned int Flags);

/*
 * This function disables execution context (allows it to run) that services
 * the nIRQ interrupt.
 *
 * Note: this function is different from the Adapter_Interrupt_Disable()
 *       function which only disables the nIRQ interrupt event at an interrupt
 *       controller. The interrupt can be dispatched to some execution context
 *       (for example, a thread) that can be also enabled or disabled.
 */
void
Adapter_Interrupt_Context_Disable(
        const int nIRQ,
        const unsigned int Flags);

int
Adapter_Interrupts_Resume(void);


// Host hardware specific extensions
#include "adapter_interrupts_ext.h"


#endif /* Include Guard */


/* end of file adapter_interrupts.h */
