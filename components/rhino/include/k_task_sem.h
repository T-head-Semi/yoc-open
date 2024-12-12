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

#ifndef K_TASK_SEM_H
#define K_TASK_SEM_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup aos_rhino task_sem
 *  Task-semaphore can be used for tasks synchronize.
 *
 *  @{
 */

/**
 * Create a semaphore and attach it to the task.
 *
 * @param[in]  task   pointer to the task
 * @param[in]  sem    pointer to the semaphore
 * @param[in]  name   name of the task-semaphore
 * @param[in]  count  count of the semaphore
 *
 * @return  the operation status, RHINO_SUCCESS is OK, others is error
 */
kstat_t krhino_task_sem_create(ktask_t *task, ksem_t *sem, const name_t *name, size_t count);

/**
 * Delete a task-semaphore.
 *
 * @param[in]  task  pointer to the task
 *
 * @return  the operation status, RHINO_SUCCESS is OK, others is error
 */
kstat_t krhino_task_sem_del(ktask_t *task);

/**
 * Give a task-semaphore.
 *
 * @param[in]  task  pointer to the task
 *
 * @return  the operation status, RHINO_SUCCESS is OK, others is error
 */
kstat_t krhino_task_sem_give(ktask_t *task);

/**
 * Take a task-semaphore, task may be blocked.
 *
 * @param[in]  ticks  ticks to wait before take
 *
 * @return  the operation status, RHINO_SUCCESS is OK, others is error
 */
kstat_t krhino_task_sem_take(tick_t ticks);

/**
 * Set the count of a task-semaphore.
 *
 * @param[in]  task   pointer to the task
 * @param[in]  count  count of the semaphre to set
 *
 * @return  the operation status, RHINO_SUCCESS is OK, others is error
 */
kstat_t krhino_task_sem_count_set(ktask_t *task, sem_count_t count);

/**
 * Get task-semaphore count.
 *
 * @param[in]   task   pointer to the semphore
 * @param[out]  count  count of the semaphore
 *
 * @return  the operation status, RHINO_SUCCESS is OK, others is error
 */
kstat_t krhino_task_sem_count_get(ktask_t *task, sem_count_t *count);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* K_TASK_SEM_H */

