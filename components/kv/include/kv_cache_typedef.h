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
#ifndef __KV_CACHE_TYPEDEF_H__
#define __KV_CACHE_TYPEDEF_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <aos/hash.h>
#include <aos/list.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CACHE_INVALID_VAL (0xFFFF)

typedef struct cache_node {
#if CONFIG_KV_LARGE_NODE
    uint32_t           block_id;
    uint32_t           offset;
#else
    uint16_t           block_id;
    uint16_t           offset;
#endif
} cache_node_t;

//FIXME: kv-conflict may be one only, list no-needed
typedef struct cache_node_list {
    char               *key;
    struct cache_node  cache;
    slist_t            node;
} lcache_node_t;

#ifdef __cplusplus
}
#endif

#endif /* __KV_CACHE_TYPEDEF_H__ */
#endif

