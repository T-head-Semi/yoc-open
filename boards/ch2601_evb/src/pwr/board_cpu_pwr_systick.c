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

/*
DESCRIPTION
This file provides two fundtions systick_suspend()/systick_resume()
which is used by cpu tickless module to suspend/resume system tick
interrupt.

Differrent board may has different way to suspend/resume system tick
interrupt, please reference your board/soc user manual to find the
detail for how to implement these two functions.
*/

#include "k_api.h"
#include "cpu_pwr_config.h"
#include "port.h"
#include "csi_core.h"
#if (RHINO_CONFIG_PWRMGMT > 0)
extern uint32_t csi_coret_suspend();
extern uint32_t csi_coret_resume();

void systick_suspend(void)
{
    CORET->CTRL  = CORET_CTRL_CLKSOURCE_Msk | CORET_CTRL_TICKINT_Msk;
}

void systick_resume(void)
{
    CORET->CTRL  = CORET_CTRL_CLKSOURCE_Msk |
                   CORET_CTRL_TICKINT_Msk |
                   CORET_CTRL_ENABLE_Msk;                              /* Enable CORET IRQ and CORET Timer */
}

#else

void systick_suspend(void)
{
}

void systick_resume(void)
{
}

#endif /* RHINO_CONFIG_PWRMGMT */
