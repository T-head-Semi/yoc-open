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

#include <board.h>

#include <stdint.h>
#include <string.h>

#include <csi_core.h>

#if defined(CONFIG_COMP_LOG_IPC) && CONFIG_COMP_LOG_IPC
#include <log_ipc.h>

#define ALG_CPUID 0
int board_logipc_init()
{
    uint8_t cpu_id[] = { ALG_CPUID };

    return log_ipc_ap_init(cpu_id, (int)sizeof(cpu_id));
}

int board_get_alg_cpuid()
{
    return ALG_CPUID;
}
#endif

#if defined(CONFIG_BOARD_AMP_LOAD_FW) && CONFIG_BOARD_AMP_LOAD_FW
#define CACHE_ALIGN_MASK    (__riscv_xlen - 1)
#define CACHE_ALIGN_UP(a)   (((a) + CACHE_ALIGN_MASK) & ~CACHE_ALIGN_MASK)
#define CACHE_ALIGN_DOWN(a) ((a) & ~CACHE_ALIGN_MASK)
extern void boot_c906(int boot_addr);
int board_load_amp_fw(uint8_t cpuid, void * loaddr, const uint8_t * fw, uint32_t size)
{
    if (cpuid != 0) {
        return -1;
    }

    if (fw && size) {
        memcpy(loaddr, fw, size);
        csi_dcache_clean_invalid_range((unsigned long *)CACHE_ALIGN_DOWN((uint32_t)loaddr), CACHE_ALIGN_UP(size));
    }

    boot_c906((int)loaddr);
    return 0;
}
#endif
