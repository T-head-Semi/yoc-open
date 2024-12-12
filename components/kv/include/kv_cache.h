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

#if (CONFIG_KV_ENABLE_CACHE || CONFIG_KV_START_OPT)
#ifndef __KV_CACHE_H__
#define __KV_CACHE_H__

#include "kv_cache_typedef.h"
#include "kvset.h"
#include "block.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  malloc & init cache node for kv
 * @param  [in] kv
 * @param  [in] num count of cache-nodes
 * @return
 */
void kv_cache_nodes_init(kv_t *kv, size_t num);

/**
 * @brief  reset the cache node
 * @param  [in] node
 * @return
 */
void kv_cache_node_reset(cache_node_t *node);

/**
 * @brief  request one cache node index unused
 * @param  [in] kv
 * @return -1 on error
 */
int kv_cache_node_get(kv_t *kv);

/**
 * @brief  put the key with other params to the inner-hash_map of the kv
 * @param  [in] kv
 * @param  [in] key
 * @param  [in] block_id
 * @param  [in] offset : head_offset of the key in one block
 * @return
 */
void kv_cache_node_in(kv_t *kv, const char *key, int block_id, uint32_t offset);

/**
 * @brief  remove the key from the inner-hash_map of the kv
 * @param  [in] kv
 * @param  [in] key
 * @return
 */
void kv_cache_node_out(kv_t *kv, const char *key);

#ifdef __cplusplus
}
#endif

#endif /* __KV_CACHE_H__ */
#endif

