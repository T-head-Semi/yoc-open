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

#if (RHINO_CONFIG_SCHED_CFS > 0)
static struct k_rbtree_root_t  cfs_root = RBT_ROOT;

/*
 * Insert @key into rbtree, On success, return 0, else return -1
 */
static void node_insert(struct k_rbtree_root_t *root, cfs_node *node, lr_timer_t key)
{
    struct k_rbtree_node_t **tmp = &(root->rbt_node), *parent = NULL;

    /* Figure out where to put new node */
    while (*tmp) {
        cfs_node *my = k_rbtree_entry(*tmp, cfs_node, rbt_node);
        parent = *tmp;
        if (key <= my->key)
            tmp = &((*tmp)->rbt_left);
        else if (key > my->key)
            tmp = &((*tmp)->rbt_right);
    }

    node->key = key;

    /* Add new node and rebalance tree. */
    k_rbtree_link_node(&node->rbt_node, parent, tmp);
    k_rbtree_insert_color(&node->rbt_node, root);
}

void cfs_node_insert(cfs_node *node, lr_timer_t key)
{
    node_insert(&cfs_root, node, key);
}

void cfs_node_del(cfs_node *node)
{
    k_rbtree_erase(&node->rbt_node, &cfs_root);
}

lr_timer_t cfs_node_min_get(void)
{
    struct k_rbtree_node_t *tmp;
    cfs_node        *node_cfs;

    tmp  = k_rbtree_first(&cfs_root);
    if (tmp == NULL) {
        return 0;
    }

    node_cfs = k_rbtree_entry(tmp, cfs_node, rbt_node);
    return node_cfs->key;
}

ktask_t *cfs_preferred_task_get(void)
{
    struct k_rbtree_node_t *tmp;
    cfs_node        *node_cfs;
    ktask_t         *task;

    tmp  = k_rbtree_first(&cfs_root);
    if (tmp == NULL) {
        return 0;
    }

    node_cfs = k_rbtree_entry(tmp, cfs_node, rbt_node);
    task     = krhino_list_entry(node_cfs, ktask_t, node);

    return task;
}
#endif

