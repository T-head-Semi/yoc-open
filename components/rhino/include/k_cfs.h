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

#ifndef K_CFS_H
#define K_CFS_H

#include "k_rbtree.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup aos_rhino cfs
 *  Completely Fair Scheduler.
 *
 *  @{
 */

typedef struct cfs_node_s {
    struct k_rbtree_node_t rbt_node;  /* rbttree node */
    lr_timer_t      key;       /* key */
} cfs_node;

void cfs_node_insert(cfs_node *node, lr_timer_t key);
void cfs_node_del(cfs_node *node);
lr_timer_t cfs_node_min_get(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* K_CFS_H */

