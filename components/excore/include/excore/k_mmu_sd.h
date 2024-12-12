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
#ifndef K_MMU_SD_H
#define K_MMU_SD_H

#include "excore/k_mmu.h"

#ifdef __cplusplus
extern "C" {
#endif

//#define ARCH_MMU_ERROR(err)     __asm__ __volatile__("udf":::"memory");
#define ARCH_MMU_ERROR(err)

#define MAX_PTE_ENTRIES         512
#define PAGE_SHIFT              12
#define PAGE_SIZE               (1 << PAGE_SHIFT)
#define PAGE_MASK               (~(PAGE_SIZE - 1))

#define ATTR_SO                 (1ull << 4)
#define ATTR_CA                 (1ull << 3)
#define ATTR_BU                 (1ull << 2)
#define ATTR_SH                 (1ull << 1)
#define ATTR_SE                 (1ull << 0)

#define UPPER_ATTRS_SHIFT       (59)
#define UPPER_ATTRS(x)          (((x) & 0x1f) << UPPER_ATTRS_SHIFT)

#define DIRTY_FLAG              (1ull << 6)
#define ACCESS_FLAG             (1ull << 5)
#define GLOBAL_FLAG             (1ull << 4)
#define AP_UNPRIV               (1ull << 3)
#define AP_X                    (1ull << 2)
#define AP_W                    (1ull << 1)
#define AP_R                    (1ull << 0)

#define LOWER_ATTRS_SHIFT       1
#define LOWER_ATTRS(x)          (((x) & 0x1ff) << LOWER_ATTRS_SHIFT)

#define PAGE_PFN_SHIFT 10
#define PFN_PHYS(x)             ((unsigned long)(x) << PAGE_SHIFT)
#define PHYS_PFN(x)             (((unsigned long)(x) >> PAGE_SHIFT))
#define PFN_PTE(pfn, prot)      (((unsigned long)(pfn) << PAGE_PFN_SHIFT) | prot)
#define PTE_PFN(pte)            (((unsigned long)(pte) >> PAGE_PFN_SHIFT) & 0x1ffffffffffffULL)

#define MMU_PAGE_TABLE_NUM      (1+1+32) // 1pgd + 1pmd + 32pte => 32*2M=~64M

size_t k_continue_phymem_len(unsigned long vaddr, size_t len);

int k_pgt_add(int asid, unsigned long vaddr, unsigned long paddr, size_t len,
              kpgt_prot_t pgt_type);

int k_pgt_remove(int asid, unsigned long vaddr, size_t len);

int k_pgt_add_shared(int asid, unsigned long vaddr, unsigned long paddr, size_t len,
                     kpgt_prot_t pgt_type);

int k_pgt_remove_shared(int asid, unsigned long vaddr, size_t len);

int k_pgt_mmap(int asid, unsigned long vaddr, unsigned long paddr,
               size_t len, kpgt_prot_t pgt_type, int32_t privileged);

int k_pgt_munmap(int asid, unsigned long vaddr, size_t len);

unsigned long k_mmap_va2pa(int asid, unsigned long vaddr);
unsigned long k_mmu_va2pa(unsigned long vaddr);

#ifdef __cplusplus
}
#endif

#endif /* K_MMU_SD_H */
