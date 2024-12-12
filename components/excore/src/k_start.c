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

#include "k_api.h"
#include "excore/k_space.h"
#include "excore/k_cache.h"
#include "excore/k_mmu_sd.h"
//#include "bestat.h"

#if 0
#define VECTORS_BASE 0xFFFF0000

extern uint32_t _vector_table[];

/**
 * dynamic physical memory region,
 * defined in link script
 */
extern char *_phy_addr_dyn_start;
extern char *_phy_addr_dyn_len;

/**
 * kernel dynamic virtual address space region,
 * defined in link script
 */
extern char *_kernel_virt_addr_dyn_start;
extern char *_kernel_virt_addr_dyn_len;

/**
 * shared dynamic virtual address space region,
 * defined in link script
 */
extern char *_shared_virt_addr_dyn_start;
extern char *_shared_virt_addr_dyn_len;

/**
 * shared dynamic virtual address space region,
 * defined in link script
 */
extern char *_io_virt_addr_dyn_start;
extern char *_io_virt_addr_dyn_len;
static void k_vectable_set();

void k_addr_space_init()
{
    unsigned long addr;
    size_t    len;

    /* 1. init virtual address pool */
    addr = (unsigned long)&_kernel_virt_addr_dyn_start;
    len  = (size_t)&_kernel_virt_addr_dyn_len;

    k_space_init(&g_space_info[VAS_KERNEL], addr, len);

    /* 2. init shared virtual adress pool */
    addr = (unsigned long)&_shared_virt_addr_dyn_start;
    len  = (size_t)&_shared_virt_addr_dyn_len;

    k_space_init(&g_space_info[VAS_SHARED], addr, len);

    /* 3. init io virtual adress pool */
    addr = (unsigned long)&_io_virt_addr_dyn_start;
    len  = (size_t)&_io_virt_addr_dyn_len;

    k_space_init(&g_space_info[VAS_IO], addr, len);

    return;
}

static void k_vectable_set()
{
#if 0
    uint32_t reg;

    reg  = os_get_SCTLR();
    /*
    SCTLR.V, bit[13]   Vectors bit.
    0  Low exception vectors,
    1  High exception vectors (Hivecs), base address 0xFFFF0000.
    */
    reg |= 0x2000;
    os_set_SCTLR(reg);
#endif
}
#endif

