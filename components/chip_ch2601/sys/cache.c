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

/******************************************************************************
 * @file     cache.c
 * @brief    source file for setting cache.
 * @version  V1.0
 * @date     18. July 2018
 ******************************************************************************/

#include <stdint.h>
#include <drv/porting.h>
#include <csi_core.h>

#ifndef __ICACHE_PRESENT
#define __ICACHE_PRESENT          1U
#endif

#ifndef __DCACHE_PRESENT
#define __DCACHE_PRESENT          1U
#endif

#define DCACHE_CLEAN_ALL()                __ASM volatile("dcache.call")
#define DCACHE_CLEAN_INVALID_ALL()        __ASM volatile("dcache.ciall")
#define DCACHE_CLEAN_INVALID_CIPA(addr)    __ASM volatile("dcache.cipa %0" : : "r"(addr))

#define ICACHE_INVALID_ALL()              __ASM volatile("icache.iall")

void dcache_clean_invalid_range(uint32_t *addr, int32_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    volatile int32_t op_size = dsize + (uint32_t)addr % 32;
    uint32_t op_addr = (uint32_t) addr;
    int32_t linesize = 32;

    __DSB();

    while (op_size > 0) {
        DCACHE_CLEAN_INVALID_CIPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
    __ISB();
#endif
}



void soc_dcache_clean_invalid_range(unsigned long addr, uint32_t size)
{
    if (size < 512U) {
        dcache_clean_invalid_range((uint32_t *)addr, size);
    } else {
        DCACHE_CLEAN_INVALID_ALL();
    }
}

void soc_dcache_clean_invalid_all(void)
{
    DCACHE_CLEAN_INVALID_ALL();
}

void soc_dcache_invalid_range(unsigned long addr, uint32_t size)
{
    dcache_clean_invalid_range((uint32_t *)addr, size);
}

void soc_icache_invalid(void)
{
#if (__ICACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    ICACHE_INVALID_ALL();                        /* invalidate all icache */
    __DSB();
    __ISB();
#endif
}

void soc_dcache_clean(void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    DCACHE_CLEAN_ALL();                          /* clean all Cache */
    __DSB();
    __ISB();
#endif
}
