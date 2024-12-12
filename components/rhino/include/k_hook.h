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

#ifndef K_HOOK_H
#define K_HOOK_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup aos_rhino hook
 *  OS hook, called when specific OS operations
 *
 *  @{
 */

#if (RHINO_CONFIG_USER_HOOK > 0)

/**
 * Called in 'krhino_init' - initialization process
 *
 * @return none
 */
void krhino_init_hook(void);

/**
 * Called in 'krhino_start' - just before the first task runs
 *
 * @return none
 */
void krhino_start_hook(void);

/**
 * Called in 'krhino_task_create' and 'krhino_task_dyn_create'
 *
 * @param[in]  task  pointer to the created task
 *
 * @return none
 */
void krhino_task_create_hook(ktask_t *task);

void krhino_task_create_hook_lwip_thread_sem(ktask_t *task);
void krhino_task_del_hook_lwip_thread_sem(ktask_t *task, res_free_t *arg);

/**
 * Called in 'krhino_task_del_hook' and 'krhino_task_dyn_del'
 *
 * @param[in]  task  pointer to the deleted task
 * @param[in]  arg   useless now
 *
 * @return none
 */
void krhino_task_del_hook(ktask_t *task, res_free_t *arg);

/**
 * Called in 'krhino_task_wait_abort' and 'krhino_task_cancel'
 *
 * @param[in]  task  pointer to the canceled and abort task
 *
 * @return none
 */
void krhino_task_abort_hook(ktask_t *task);

/**
 * Called when task switching
 *
 * @param[in]  orgin  pointer to the switch out task
 * @param[in]  dest   pointer to the switch in task
 *
 * @return none
 */
void krhino_task_switch_hook(ktask_t *orgin, ktask_t *dest);

/**
 * Called in every system tick process
 *
 * @return none
 */
void krhino_tick_hook(void);

/**
 * Called in idle task loop
 *
 * @return none
 */
void krhino_idle_hook(void);

/**
 * Called before idle task loop
 *
 * @return none
 */
void krhino_idle_pre_hook(void);

/**
 * Called in 'krhino_mm_alloc'
 *
 * @param[in]  mem      alloced memory block
 * @param[in]  size     alloced size
 *
 * @return none
 */
void krhino_mm_alloc_hook(void *mem, size_t size);
#endif

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* K_HOOK_H */

