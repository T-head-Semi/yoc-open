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

#include <csi_config.h>
#include <stdio.h>
#include <string.h>
#include <csi_core.h>
#include <soc.h>
#include "ecc_stats.h"

extern ecc_stats_t g_ecc_stats;

void ecc_l1_irqhandler(void *arg)
{
    g_ecc_stats.err_cnt_l1++;
    printf("come to ecc_l1_irqhandler\r\n");
    if (!(__get_MCER() >> MCER_ECC_VLD_Pos) || (__get_MCER() & MCER_ECC_FATAL_Msk)) {
        /* may be ecc fatal error happens */
        g_ecc_stats.mcer_fault_ram = ((__get_MCER() & MCER_RAMID_Msk) >> MCER_RAMID_Pos);
    }
    /* clear MCER EE_VLD */
#if __riscv_xlen == 32
    __set_MCER(0);
    __set_MCERH(0);
#else
    __set_MCER(0);
#endif
}

void ecc_l2_irqhandler(void *arg) {
    g_ecc_stats.err_cnt_l2++;
    printf("come to ecc_l2_irqhandler\r\n");
#if __riscv_xlen == 32
    if ((__get_MCER2H() & CACHE_MCER2H_ECC_FATAL_Msk) >> CACHE_MCER2H_ECC_FATAL_Pos) {
        /* may be ecc fatal error happens */
        g_ecc_stats.mcer2_fault_ram = (__get_MCER2H() & CACHE_MCER2H_RAMID_Msk) >> CACHE_MCER2H_RAMID_Pos;
    }
    /* clear MCER EE_VLD */
    __set_MCER2(0);
    __set_MCER2H(0);
#else
    if ((__get_MCER2() & CACHE_MCER2_ECC_FATAL_Msk) >> CACHE_MCER2_ECC_FATAL_Pos) {
        /* may be ecc fatal error happens */
        g_ecc_stats.mcer2_fault_ram = (__get_MCER2() & CACHE_MCER2_RAMID_Msk) >> CACHE_MCER2_RAMID_Pos;
    }
    /* clear MCER EE_VLD */
    __set_MCER2(0);
#endif
}