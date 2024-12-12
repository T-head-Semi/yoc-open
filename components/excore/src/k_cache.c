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

#include <csi_core.h>

void k_icache_enable()
{
    csi_icache_enable();
}

void k_icache_disable()
{
    csi_icache_disable();
}

void k_icache_invalidate(unsigned long text, size_t size)
{
    //TODO:
    csi_icache_invalid();
}

void k_icache_invalidate_all()
{
    csi_icache_invalid();
}

void k_dcache_enable()
{
    csi_dcache_enable();
}

void k_dcache_disable()
{
    csi_dcache_disable();
}

void k_dcache_clean(unsigned long buffer, size_t size)
{
    csi_dcache_clean_range((uint64_t*)buffer, size);
}

void k_dcache_invalidate(unsigned long buffer, size_t size)
{
    csi_dcache_invalid_range((uint64_t*)buffer, size);
}

void k_dcache_clean_invalidate(unsigned long buffer, size_t size)
{
    csi_dcache_clean_invalid_range((uint64_t*)buffer, size);
}

