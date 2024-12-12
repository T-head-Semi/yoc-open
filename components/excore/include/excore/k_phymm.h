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

#ifndef K_PHYMM_H
#define K_PHYMM_H

#include "excore/k_vmm.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    size_t total;
    size_t used;
    size_t maxused;
} k_phymm_statis_t;

int32_t   k_phymm_init(uintptr_t addr, size_t len);
int32_t   k_phymm_reserve(uintptr_t addr, size_t len);
uintptr_t k_phymm_alloc(int pid, size_t len, size_t align, int reverse, kvmm_type_t type);
int32_t   k_phymm_free(int pid, uintptr_t addr, size_t len, kvmm_type_t type);
size_t    k_phymm_freesize(void);
void      k_phymm_statis_show(int (*print_func)(const char *fmt, ...));
void      k_phymm_statis_get(k_phymm_statis_t *info);

#ifdef __cplusplus
}
#endif

#endif /* K_PHYMM_H */

