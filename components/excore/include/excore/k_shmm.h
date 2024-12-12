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

#ifndef K_SHMM_H
#define K_SHMM_H

#include "k_list.h"
#include "excore/k_vmm.h"

typedef struct {
    klist_t   map_list;
    uintptr_t vaddr;
    uintptr_t paddr;
    size_t    len;
    uint32_t  type;
    uint32_t  app_mapped;
} k_shmm_map_t;

#ifdef __cplusplus
extern "C" {
#endif

int k_shmm_map_init(int pid);

/*
 * Setup shared memory area between kernel and user space
 * process.
 *
 * If @start is given, it will map the region to both
 * kernel and user space process page table
 * Else, it allocate physical pages from physical pool
 * and then map it to both kernel and user space process
 * page table
 *
 * On success, return virtual address which can be accessed
 * by kernel and user space process.
 * Else return NULL.
 *
 */
void *k_shmm_map_area(void *vaddr, void *paddr,size_t len, kvmm_prot_t prot, kvmm_type_t type);

/*
 * Unmap the shared memory area
 */
int k_shmm_unmap_area(void *start, size_t len);
#ifdef __cplusplus
}
#endif

#endif /* K_SHMM_H */

