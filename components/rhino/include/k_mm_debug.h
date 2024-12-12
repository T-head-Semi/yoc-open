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

#ifndef K_MM_DEBUG_H
#define K_MM_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup aos_rhino mm
 *  Memory debug includes buffer over flow check, memory usage statistics, etc.
 *
 *  @{
 */

#if (RHINO_CONFIG_MM_DEBUG > 0)

#define AOS_UNSIGNED_INT_MSB    (1u << (sizeof(unsigned int) * 8 - 1))

extern uint8_t g_mmlk_cnt;

/**
 * Add owner info to the memory buffer.
 *
 * @param[in]  addr  pointer to the buffer
 * @param[in]  allocator   address of the allocator
 *
 * @return  NULL
 */
void krhino_owner_attach(void *addr, size_t allocator);

/**
 * Set owner to return address of function.
 *
 */
#define krhino_owner_return_addr(addr) \
    krhino_owner_attach(addr, (size_t)__builtin_return_address(0))

/**
 * Show heap information.
 *
 * @param[in]  mm status
 *
 * @return  RHINO_SUCCESS
 */
uint32_t dumpsys_mm_info_func(uint32_t mm_status);

#endif /* RHINO_CONFIG_MM_DEBUG */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* K_MM_DEBUG_H */

