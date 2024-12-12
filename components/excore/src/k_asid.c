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
#include "excore/k_asid.h"

#define ASID_WORD ((CONFIG_EXCORE_PROCESS_MAX+31)/32)

static uint32_t g_asid[ASID_WORD] = {0};

int k_asid_reserve(int asid)
{
    int word;
    int bit;

    CPSR_ALLOC();

    if (asid >= CONFIG_EXCORE_PROCESS_MAX) {
        return -1;
    }

    RHINO_CPU_INTRPT_DISABLE();

    word = asid / 32;
    bit  = asid % 32;
    g_asid[word] |= 1 << bit;

    RHINO_CPU_INTRPT_ENABLE();

    return 0;
}

int k_asid_alloc(void)
{
    int word;
    int bit;
    int asid = OS_ASID_INV;

    CPSR_ALLOC();

    RHINO_CPU_INTRPT_DISABLE();
    for (word = 0; word < ASID_WORD; word++) {
        for (bit = 0; bit < 32; bit++) {
            if ((g_asid[word] & (1 << bit)) == 0) {
                asid = word * 32 + bit;
                if (asid >= CONFIG_EXCORE_PROCESS_MAX) {
                    asid = OS_ASID_INV;
                } else {
                    g_asid[word] |= (1 << bit);
                }
                goto out;
            }
        }
    }

out:
    RHINO_CPU_INTRPT_ENABLE();

    return asid;
}

int k_asid_dealloc(int asid)
{
    int word;
    int bit;

    CPSR_ALLOC();

    if (asid >= CONFIG_EXCORE_PROCESS_MAX) {
        return -1;
    }

    word = asid / 32;
    bit = asid % 32;

    RHINO_CPU_INTRPT_DISABLE();

    g_asid[word] &= ~(1 << bit);

    RHINO_CPU_INTRPT_ENABLE();

    return 0;
}

int k_asid_is_active(int asid)
{
    int word;
    int bit;
    int ret;

    CPSR_ALLOC();

    if (asid >= CONFIG_EXCORE_PROCESS_MAX) {
        return 0;
    }

    word = asid / 32;
    bit = asid % 32;

    RHINO_CPU_INTRPT_DISABLE();

    ret = g_asid[word] & (1 << bit)? 1: 0;

    RHINO_CPU_INTRPT_ENABLE();

    return ret;
}

void k_asid_set(int asid)
{
    //TODO:
}

int k_asid_get()
{
#if (CONFIG_EXCORE_PROCESS_MAX == 1)
    return OS_ASID_KERNEL;
#else
    //TODO:
    return 0;
#endif
}

